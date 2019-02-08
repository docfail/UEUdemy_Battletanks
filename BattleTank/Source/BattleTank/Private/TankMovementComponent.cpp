// Doctor Fail 2018

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet ) {

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
	if (!LeftTrack || !RightTrack) return;
	//UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"), Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw) {
	if (!LeftTrack || !RightTrack) return;
	//UE_LOG(LogTemp, Warning, TEXT("Intend turn right throw: %f"), Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	IntendMoveForward(FVector::DotProduct(TankForward, AIForwardIntention));
	/*
	TankForward = FVector::VectorPlaneProject(TankForward, FVector(0, 0, 1));
	AIForwardIntention = FVector::VectorPlaneProject(AIForwardIntention, FVector(0, 0, 1));
	*/
	auto TurnThrow = FVector::CrossProduct(TankForward, AIForwardIntention);
	IntendTurnRight(TurnThrow.Z);
	//UE_LOG(LogTemp, Warning, TEXT("%s wants to move with velocity %s"), *Name, *(MoveVelocity.GetSafeNormal().ToString()));
}