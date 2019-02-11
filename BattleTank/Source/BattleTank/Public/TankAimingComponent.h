// Doctor Fail 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

#define BT_POINTER_GUARD(pointers) if(!ensure(pointers)) { return; }

// Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

// Holds barrel properties and methods
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void AimAt(FVector);
	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet);
	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();
	UFUNCTION(BlueprintCallable, Category = Firing)
	int32 GetRoundsLeft() const;
protected:
	UPROPERTY(BlueprintReadOnly,Category="State")
	EFiringState FiringState = EFiringState::Reloading;
private:

	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	bool IsBarrelMoving();
	void BeginPlay() override;
	// Sets default values for this component's properties
	UTankAimingComponent();

	void MoveBarrelTowards(FVector);

	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 8000;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 2.0f; // If it says EditAnywhere, you can edit it on every instance. If its on EditDefaultsOnly it can only be edited on the blueprint.
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	double LastFireTime = 0;

	FVector AimDirection = FVector(0);
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	int32 RoundsLeft = 20;
};

// Used in AimAt to determine if the engine draws a debug line for the projectile suggestion.
#define BT_DRAW_DEBUG false 