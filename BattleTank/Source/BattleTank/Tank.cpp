// Doctor Fail 2018

#include "Tank.h"
#include "Particles/ParticleSystemComponent.h"
//#define BT_CURRENT_GAME_TIME GetWorld()->GetTimeSeconds()

// Sets default values
ATank::ATank()
{
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Tank"));
	SetRootComponent(TankMesh);

	DeathExplosion = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	DeathExplosion->SetupAttachment(RootComponent, FName("Turret"));
	DeathExplosion->bAutoActivate = false;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) {
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	auto DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);
	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0) {
		Die(DamageCauser);
	}
	return (float)DamageToApply;
}

void ATank::Die(AActor * Killer) {
	DeathExplosion->Activate();
	OnDeath.Broadcast();
	auto KillerName = (Killer) ? Killer->GetName() : FString("Unknown");
	UE_LOG(LogTemp, Warning, TEXT("%s has died! Killed by %s"), *GetName(), *KillerName);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth/(float)StartingHealth;
}
