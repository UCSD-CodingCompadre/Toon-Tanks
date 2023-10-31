#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	/*
	Handles an actor's death in the game mode
	@param AActor* actorDied the actor that died in game
	@return void
	*/
	void actorDied(AActor* actorDead);

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*
	Trigger the start game event in the game mode event graph
	@param none
	@return void
	*/
	UFUNCTION(BlueprintImplementableEvent)
	void startGame();
	
	/*
	Trigger the game over event
	@param none
	@return void
	*/
	UFUNCTION(BlueprintImplementableEvent)
	void endGame(bool wonGame);

private:

	// Hold the player's tank 
	class ATank* playerTank;

	// Hold the player's controller
	class AToonTanksPlayerController* playerController;

	// Hold the timer for the game to start
	float timer = 3.f;

	// Hold the amount of turret pawns in the level
	float turretsInGame;

	/*
	Handles the start of the game
	@param none
	@return void
	*/
	void handleGameStart();

	/*
	Handles retrieving all the turrets in the level
	@param none
	@return int the amount of turrets in the level
	*/
	int getTurretCount();
};
