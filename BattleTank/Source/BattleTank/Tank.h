// Doctor Fail 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Delegates/Delegate.h"
#include "Tank.generated.h"

class UParticleSystemComponent;
class UStaticMeshComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()
	// Sets default values for this pawn's properties
	ATank();
	// Called by the engine when actor damage is dealt.
	float TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser) override;
	void Die(AActor * Killer);
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	int32 StartingHealth = 100;
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth;
	void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* DeathExplosion = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* TankMesh = nullptr;
public:
	// Return current health as a percentage of max health. Between 0 and 1.
	UFUNCTION(BlueprintPure,Category="Health")
	float GetHealthPercent() const;

	FTankDelegate OnDeath;
};
