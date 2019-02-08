// Doctor Fail 2018

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

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
	ATank* ControlledTank = nullptr;

	ATank* PlayerTank = nullptr;
public:
	UPROPERTY(EditDefaultsOnly)
		float AcceptanceRadius = 3000.0f; // How close can the AI tank get to the player tank.
};
