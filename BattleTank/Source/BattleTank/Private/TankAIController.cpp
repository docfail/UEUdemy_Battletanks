// Doctor Fail 2018

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	GetWorld();
	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ControlledTank = Cast<ATank>(GetPawn());
	if (!PlayerTank || !ControlledTank) UE_LOG(LogTemp, Warning, TEXT("TankAIController::BeginPlay():\nSOMETHING HAS GONE WRONG(Neither should be None):\nPlayerTank is: %s \nControlledTank is: %s"), *((PlayerTank) ? PlayerTank->GetName() : "None"), *((ControlledTank) ? ControlledTank->GetName() : "None"));;
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!PlayerTank || !ControlledTank) {
		float Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: TankAIController::Tick():\nSOMETHING HAS GONE WRONG(Neither should be None):\nPlayerTank is: %s \nControlledTank is: %s"), Time ,*((PlayerTank) ? PlayerTank->GetName() : "None"), *((ControlledTank) ? ControlledTank->GetName() : "None"));;
		return;
	}
	if (PlayerTank) {
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		ControlledTank->Fire();
	}
}