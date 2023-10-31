#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Turret.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::BeginPlay()
{

    // Call the parent's BeginPlay
    Super::BeginPlay();

    // Call the function to handle the game start
    handleGameStart();
}

void AToonTanksGameMode::actorDied(AActor* actorDead)
{

        // Check if the actor that died is the player's pawn
        if(actorDead == playerTank)
        {

            // Call the tank's destruction function
            playerTank->handlePawnDestruction();

            // Check if there is a controller
            if(playerController)
            {

                // Disable the user's controller 
                playerController->setPlayerEnabled(false);
            }

            // End the game with the player losing
            endGame(false);
        }

        // Check if the actor that died is a turret pawn by casting
        else if(ATurret* turret = Cast<ATurret>(actorDead))
        {

            // Call the turret's destruction function
            turret->handlePawnDestruction();

            // Decrement the turrets in game
            turretsInGame--;

            // Check if there is no more turrets in game
            if(turretsInGame == 0)
            {

                // End the game with the player winning
                endGame(true);
            }
        }
}

int AToonTanksGameMode::getTurretCount()
{

    // Hold the array of turret pawns
    TArray<AActor*> turrets;

    // Get all the turrets
    UGameplayStatics::GetAllActorsOfClass(this, ATurret::StaticClass(), turrets);

    // Set the turrets in game
    return turrets.Num();
}

void AToonTanksGameMode::handleGameStart()
{
    
    // Set the player's tank
    playerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    // Set the player's controller
    playerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    // Set the turret count
    turretsInGame = getTurretCount();

    // Call the start game event
    startGame();

    // Check if we have a toon tanks player controller
    if(playerController)
    {

        // Disable the player input 
        playerController->setPlayerEnabled(false);

        // Hold a timer to know when to enable the player's controller
        FTimerHandle playerControllerTimer; 

        // Hold a timer delegate for the the controller
        FTimerDelegate playerControllerDelegate = FTimerDelegate::CreateUObject(playerController, &AToonTanksPlayerController::setPlayerEnabled, true);

        // Set the timer for the delegate 
        GetWorldTimerManager().SetTimer(playerControllerTimer, playerControllerDelegate, timer, false);
    }
}
