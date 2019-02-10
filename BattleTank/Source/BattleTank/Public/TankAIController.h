// Doctor Fail 2018

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

#define BT_POINTER_GUARD(pointers) if(!ensure(pointers)) { return; }

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;

	virtual void Tick(float) override;

private:
	APawn* ControlledTank = nullptr;

	APawn* PlayerTank = nullptr;
protected:
	UPROPERTY(EditDefaultsOnly, Category="Setup")
	float AcceptanceRadius = 8000.0f; // How close can the AI tank get to the player tank.
};
