
#include "HWGameModeBase.h"
#include "HWPawn.h"
#include "HWPlayerController.h"

AHWGameModeBase::AHWGameModeBase()
{
	DefaultPawnClass = AHWPawn::StaticClass();
	PlayerControllerClass = AHWPlayerController::StaticClass();
}
