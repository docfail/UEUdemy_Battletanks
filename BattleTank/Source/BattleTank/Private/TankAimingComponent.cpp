// Doctor Fail 2018

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

#define CurrentTime GetWorld()->GetTimeSeconds()

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if (RoundsLeft <= 0) {
		FiringState = EFiringState::OutOfAmmo;
	} else if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTimeInSeconds) {
		FiringState = EFiringState::Reloading;
	} else if(IsBarrelMoving()){
		FiringState = EFiringState::Aiming;
	} else {
		FiringState = EFiringState::Locked;
	}
}

bool UTankAimingComponent::IsBarrelMoving() {
	if (!ensure(Barrel)) { return false; }
	return !AimDirection.Equals(Barrel->GetForwardVector(),0.01F);
}

void UTankAimingComponent::BeginPlay()
{
	LastFireTime = GetWorld()->GetTimeSeconds();
}
// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::AimAt(FVector AimPoint)
{
	BT_POINTER_GUARD(Barrel);

	FVector LaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,	// The object which is the point of reference?
		LaunchVelocity,	// An out parameter which gives us back the launch velocity vector
		StartLocation,	// The point we start from
		AimPoint,		// The point we want to trace to
		LaunchSpeed,	// Speed at which the projectile would be launched
		false,	// Should the engine return the higher of the two valid arcs, if there are two valid arcs
		0.0f,	// Collision radius, the default is 0.0f
		0.0f,	// Gravity override, if we use the default of 0.0f, it wont override
		ESuggestProjVelocityTraceOption::DoNotTrace,	// Ignore collision, trace as though nothing is in the path
		FCollisionResponseParams::DefaultResponseParam,
		TArray<AActor*>(),	// Actors to ignore, none by default
		BT_DRAW_DEBUG	// Should we draw a debug line showing the path traced?
	);
	
	if (bHaveAimSolution) {
		AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet) {
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	BT_POINTER_GUARD(Barrel);

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	
	Barrel->Elevate(DeltaRotator.Pitch);
	if (FMath::Abs(DeltaRotator.Yaw) <= 180.0f) {
		Turret->Rotate(DeltaRotator.Yaw);
	} else {
		Turret->Rotate(-(DeltaRotator.Yaw-180.0f));
	}
}


void UTankAimingComponent::Fire()
{
	if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming) {
		BT_POINTER_GUARD(Barrel);
		BT_POINTER_GUARD(ProjectileBlueprint);
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));

		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = GetWorld()->GetTimeSeconds();

		RoundsLeft--;
		UE_LOG(LogTemp, Warning, TEXT("%s Firing!"), *(GetOwner()->GetName()));
		// LastFireTime = FPlatformTime::Seconds(); <- This method returns real-world time. In other words, unlike the GetWorld method, it isnt affected by in game time dilation/pausing.
	}
}

int UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}
