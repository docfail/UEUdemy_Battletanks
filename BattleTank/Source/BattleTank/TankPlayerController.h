// Doctor Fail 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

#define BT_POINTER_GUARD(pointers) if(!ensure(pointers)) { return; }

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

public:

	virtual void BeginPlay() override;

	virtual void Tick(float) override;

private:

	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector &) const;
	bool GetLookDirection(FVector2D, FVector &) const;
	bool GetLookVectorHitLocation(FVector,FVector &) const;

	void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnPossessedDeath();
	
	//void StartSpectatingOnly();
	
	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation = 0.5f;
	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.33333333f;
	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.0f; // 10E3 * 100 <- 10km in cm
};
