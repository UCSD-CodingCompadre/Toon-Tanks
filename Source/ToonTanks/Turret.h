#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "TimerManager.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATurret : public ABasePawn
{
	GENERATED_BODY()
	
public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*
	Handle the destruction of the Turret pawn
	@param none
	@return void
	*/
	void handlePawnDestruction();

protected:
		
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	// Hold the turret range of the turret
	UPROPERTY(EditAnywhere)
	float turretRange = 500.f;

	// Hold the pointer to the player tank
	class ATank* playerTank;

	// Hold the timer handle for the fire rate
	FTimerHandle fireRateTimeHandle;
	
	// Hold the fire rate of the turret
	float fireRate = 2.f;
	
	/*
	Check if the conditions are met to fire a projectile from the turret
	@param none
	@return void
	*/
	void checkFireCondition();

	/*
	Check if the player tank is in range of the turret
	@param none
	@return bool true if the player thank is in range
	*/
	bool isInFireRange();
};
