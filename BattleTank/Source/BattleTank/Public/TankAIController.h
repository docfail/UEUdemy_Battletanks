// Doctor Fail 2018

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Tank.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;

	virtual void Tick(float) override;

	ATank * GetControlledTank();

	ATank * GetPlayerTank();



};
