#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
	
public:

	ATank();	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Hold if the tank is alive
	bool isTankAlive = true;
	
	/*
	Handle the destruction of the Tank pawn
	@param none
	@return void
	*/
	void handlePawnDestruction();

	/*
	Get the player controller
	@param none
	@return APlayerController* the pawns controller
	*/
	APlayerController* getPlayerController() const;
protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	// Hold the pointer to the spring arm component
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* springArmComponent;

	// Hold the pointer to the camera component
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* cameraComponent;

	// Hold the delta location
	UPROPERTY(VisibleAnywhere, Category = "Input")
	FVector deltaLocation = FVector(0.f);
	
	// Hold the delta rotation
	UPROPERTY(VisibleAnywhere, Category = "Input")
	FRotator deltaRotation = FRotator(0.f);

	// Hold the move speed of the tank
	UPROPERTY(VisibleAnywhere, Category = "Input")
	float moveSpeed = 700.0;
	
	// Hold the turn speed of the tank
	UPROPERTY(VisibleAnywhere, Category = "Input")
	float turnSpeed = 150.0;

	// Hold the pointer to the player controller
	APlayerController* playerController;

	/*
	Moves the tank in the direction determined by the value
	@param float value the direction in which to move
	@return void
	*/
	void move(float value);
	
	/*
	Rotates the turretTankComponent in the direction determined
	by the value
	@param float value the firection in which to rotate
	@return void
	*/
	void rotate(float value);
};
