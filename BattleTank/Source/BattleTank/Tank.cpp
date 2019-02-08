// Doctor Fail 2018

#include "Tank.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "Engine/StaticMesh.h"
//#define BT_CURRENT_GAME_TIME GetWorld()->GetTimeSeconds()

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));


void ATank::Fire()
{
	bool isReloaded = ((GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds);
	if (Barrel && isReloaded) {
		
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));

		Projectile->LaunchProjectile(LaunchSpeed);
		
		LastFireTime = GetWorld()->GetTimeSeconds();
		// LastFireTime = FPlatformTime::Seconds(); <- This method returns real-world time. In other words, unlike the GetWorld method, it isnt affected by in game time dilation/pausing.
	}
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}
