#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:

	// Sets default values for this pawn's properties
	ABasePawn();

	/*
	Handle the destruction of the pawn
	@param none
	@return void
	*/
	void handlePawnDestruction();

protected:

	/*
	Rotate the tankTurretComponent  in the Yaw axis to point to the target
	@param FVector targetLocation the location to face 
	@return void
	*/
	void rotateTurretComponent(FVector targetLocation);

	/*
	Fire a projectile from the spawnProjectileComponent
	@param none
	@return void
	*/
	void fire();

private:

	// Hold the pointer to the collision capsule
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess= "true"))
	class  UCapsuleComponent* capsuleComponent;
	
	// Hold the pointer to the tank base mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess= "true"))
	UStaticMeshComponent* tankBaseComponent;
	
	// Hold the pointer to the tank turret mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess= "true"))
	UStaticMeshComponent* tankTurretComponent;

	// Hold the pointer to the project spawn
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess= "true"))
	USceneComponent* spawnProjectileComponent;

	// Hold the template for the projectile
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess= "true"))
	TSubclassOf<class ATurretProjectile> projectileClass;

	// Hold the particle system for the pawns
	UPROPERTY(EditAnywhere, Category = "Effects")
	class UParticleSystem* deathParticles;

	// Hold the sound for the pawn death
	UPROPERTY(EditAnywhere, Category = "Effects")
	class USoundBase* deathSound;

	// Hold the camera shake
	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<class UCameraShakeBase> deathCameraShakeClass;
};
