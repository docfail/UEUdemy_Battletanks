// Doctor Fail 2018

#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed) {
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f);
	//UE_LOG(LogTemp, Warning, TEXT("TurretRotate called with spd %f"), RelativeSpeed);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewRotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0, NewRotation, 0));
}
