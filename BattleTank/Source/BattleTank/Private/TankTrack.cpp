// Doctor Fail 2018

#include "TankTrack.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;
}

// Set the speed for this tank track
void UTankTrack::SetThrottle(float Throttle) {
	DriveTrack(FMath::Clamp(Throttle, -1.0f, 1.0f));
}
void UTankTrack::DriveTrack(float CurrentThrottle) {
	auto ForceApplied = CurrentThrottle * TankMaxDrivingForce;
	auto Wheels = GetWheels();
	auto ForcePerWheel = ForceApplied / Wheels.Num();
	for (ASprungWheel* Wheel : Wheels) {
		Wheel->AddDrivingForce(ForcePerWheel);
	}
	/*auto ForceApplied = GetForwardVector() * CurrentThrottle * TankMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);*/
}

TArray<class ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<class ASprungWheel*> ResultArray;
	TArray<class USceneComponent*> Children;
	GetChildrenComponents(true, Children);
	for (USceneComponent* Child : Children) {
		auto SpawnPointChild = Cast<USpawnPoint>(Child);
		if (!SpawnPointChild) continue;
		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SprungWheel) continue;
		ResultArray.Add(SprungWheel);
	}
	return ResultArray;
}

/*
void UTankTrack::BeginPlay()
{
Super::BeginPlay();
OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
//UE_LOG(LogTemp, Warning, TEXT("%s: OnHit Event Fired!!!"), *GetName());
}

void UTankTrack::ApplySidewaysForce()
{
float DeltaTime = GetWorld()->GetDeltaSeconds();
auto SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
auto CorrectionAcceleration = (-SlippageSpeed / DeltaTime)*GetRightVector();
auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
TankRoot->AddForce(TankRoot->GetMass()*CorrectionAcceleration / 2);
}
*/
