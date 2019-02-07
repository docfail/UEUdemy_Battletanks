// Doctor Fail 2018

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UTankAimingComponent::AimAt(FVector AimPoint, float LaunchSpeed)
{
	if (!Barrel) {
		return;
	}
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
		auto AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	if (!BarrelToSet) { return; }
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret * TurretToSet)
{
	if (!TurretToSet) { return; }
	Turret = TurretToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}

