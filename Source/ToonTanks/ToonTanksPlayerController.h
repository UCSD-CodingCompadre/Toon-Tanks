#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ToonTanksPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	/*
	Handle the players controller enabled state
	@param bool playerEnabled holds true if the player is going to be enabled
	@return void
	*/
	void setPlayerEnabled(bool playerEnabled);
};
