// Doctor Fail 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force and to apply forces to the tank.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle); // Note: if you don't put the parameter name on UFunctions, they wont compile. The header tool reads this for the blueprint editor.
	// Max force per track in newtons
	UPROPERTY(EditDefaultsOnly)
	float TankMaxDrivingForce = 40000000; // 20Mg tank @ 1g acceleration
};
