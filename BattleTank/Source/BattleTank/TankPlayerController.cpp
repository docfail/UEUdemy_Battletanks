// Doctor Fail 2018

#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* tank = GetControlledTank();
	UE_LOG(LogTemp, Warning, TEXT("TankPlayerController::BeginPlay() : Controlled Tank: %s"),*((tank)?tank->GetName():"None"));
}
