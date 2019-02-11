// Doctor Fail 2018

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "Engine/World.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (!GetPawn()) return;
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	BT_POINTER_GUARD(AimingComponent);
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPawn())
		AimTowardsCrosshair();
	//UE_LOG(LogTemp, Warning, TEXT("PlayerController Ticking!!!"));
}

void ATankPlayerController::AimTowardsCrosshair()
{
	auto Tank = GetPawn();
	BT_POINTER_GUARD(Tank);
	auto AimingComponent = Tank->FindComponentByClass<UTankAimingComponent>();
	BT_POINTER_GUARD(AimingComponent);
	FVector HitLocation;
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	//UE_LOG(LogTemp, Warning, TEXT("bGotHitLocation: %i"), bGotHitLocation);
	if (bGotHitLocation) {
		AimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX*CrosshairXLocation, ViewportSizeY*CrossHairYLocation);


	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & OutLookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, OutLookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector & OutHitLocation) const
{
	FHitResult Hit;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + LookDirection * LineTraceRange;
	if (GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECollisionChannel::ECC_Camera)) {
		OutHitLocation = Hit.Location;
		return true;
	}
	return false;
}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		BT_POINTER_GUARD(PossessedTank);
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedDeath);
	}
}

void ATankPlayerController::OnPossessedDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Player Died!"));
	StartSpectatingOnly();
}
/*
void ATankPlayerController::StartSpectatingOnly()
{

}
*/

