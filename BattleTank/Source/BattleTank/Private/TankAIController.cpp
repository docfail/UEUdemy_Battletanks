// Doctor Fail 2018

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	ControlledTank = GetPawn();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	BT_POINTER_GUARD(PlayerTank && AimingComponent);

	MoveToActor(PlayerTank, AcceptanceRadius);

	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	if (AimingComponent->GetFiringState() == EFiringState::Locked) {
		AimingComponent->Fire();
	}
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		BT_POINTER_GUARD(PossessedTank);
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedDeath);
	}
}

void ATankAIController::OnPossessedDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Received!"));
	if (!GetPawn()) {
		return;
	}
	GetPawn()->DetachFromControllerPendingDestroy();
}
