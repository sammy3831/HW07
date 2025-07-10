#include "HWPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "HWPlayerPawn.h"
#include "HWDronePawn.h"

AHWPlayerController::AHWPlayerController() :
	PlayerInputMappingContext(nullptr),
	PlayerMoveAction(nullptr),
	PlayerLookAction(nullptr),
	DroneInputMappingContext(nullptr),
	DroneMoveAction(nullptr),
	DroneLookAction(nullptr)
{
}

void AHWPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (Cast<AHWPlayerPawn>(GetPawn()))
			{
				if (PlayerInputMappingContext)
				{
					SubSystem->AddMappingContext(PlayerInputMappingContext, 0);
					UE_LOG(LogTemp, Warning, TEXT("Player"));
				}
			}
			else if (Cast<AHWDronePawn>(GetPawn()))
			{
				if (DroneInputMappingContext)
				{
					SubSystem->AddMappingContext(DroneInputMappingContext, 0);
					UE_LOG(LogTemp, Warning, TEXT("Drone"));
				}
			}
		}
	}
}
