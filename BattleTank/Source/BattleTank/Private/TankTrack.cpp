// Doctor Fail 2018

#include "TankTrack.h"
// Set the speed for this tank track
void UTankTrack::SetThrottle(float Throttle) {
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *Name, Throttle);
}