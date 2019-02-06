// Doctor Fail 2018

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	GetWorld();
	ATank* tank = GetPlayerTank();
	UE_LOG(LogTemp, Warning, TEXT("AIController found player: %s"), *((tank) ? tank->GetName() : "None"));
}

ATank* ATankAIController::GetControlledTank() {
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank()
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) {
		return nullptr;
	}
	return Cast<ATank>(PlayerPawn);
}
