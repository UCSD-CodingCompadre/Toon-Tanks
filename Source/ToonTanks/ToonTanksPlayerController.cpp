#include "ToonTanksPlayerController.h"
#include "GameFramework/Pawn.h"

void AToonTanksPlayerController::setPlayerEnabled(bool playerEnabled)
{

    // Check if the player controller should be enabled
    if(playerEnabled)
    {

        // Get the pawn of the controller and enable inputs
        GetPawn()->EnableInput(this);
    }

    // The player controller should be disabled
    else
    {

        // Get the pawn of the controller and disable inputs
        GetPawn()->DisableInput(this);
    }

    // Show the cursor if the controller is enabled
    bShowMouseCursor = playerEnabled;
}
