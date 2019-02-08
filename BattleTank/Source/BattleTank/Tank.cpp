// Doctor Fail 2018

#include "Tank.h"
//#define BT_CURRENT_GAME_TIME GetWorld()->GetTimeSeconds()

// Sets default values
ATank::ATank()
{
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}
