// Doctor Fail 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * Custom class for tank barrel.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 maxdown +1 maxup
	void Elevate(float RelativeSpeed);
private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesPerSecond = 10;
	UPROPERTY(EditAnywhere, Category = Setup) 
		float MaxElevationDegrees = 40;	
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevationDegrees = 0; // From the front, its fine at -10, but when it rotates around the back it will go through the tank.

};
