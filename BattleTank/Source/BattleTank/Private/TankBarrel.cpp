// Doctor Fail 2018

#include "TankBarrel.h"


void UTankBarrel::Elevate(float RelativeSpeed) {
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f);
	//UE_LOG(LogTemp, Warning, TEXT("BarrelElevate called with spd %f"), RelativeSpeed);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto ClampedNewElevation = FMath::Clamp(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(ClampedNewElevation, 0, 0));
}
