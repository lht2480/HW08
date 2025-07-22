#include "HWGameMode.h"
#include "HWCharacter.h"
#include "HWPlayerController.h"
#include "HWGameState.h"

AHWGameMode::AHWGameMode()
{
	DefaultPawnClass = AHWCharacter::StaticClass();
	PlayerControllerClass = AHWPlayerController::StaticClass();
	GameStateClass = AHWGameState::StaticClass();
}