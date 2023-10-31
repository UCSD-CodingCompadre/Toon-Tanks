#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TurretProjectile.generated.h"

class USoundBase;

UCLASS()
class TOONTANKS_API ATurretProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurretProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	// Hold the pointer to the projectile mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess= "true"))
	UStaticMeshComponent* projectileComponent;
	
	// Hold the pointer to the projectile movement component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess= "true"))
	UProjectileMovementComponent* projectileMovementComponent;

	// Hold the damage of the projectile
	UPROPERTY(EditAnywhere)
	float damage = 50.f;

	// Hold the particle system for the projectile
	UPROPERTY(EditAnywhere, Category = "Effects")
	class UParticleSystem* hitParticles;

	// Hold the particle system component for the projectile trail
	UPROPERTY(VisibleAnywhere, Category = "Effects")
	class UParticleSystemComponent* trailParticles;

	// Hold the sound for the projectile
	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* launchSound;

	// Hold the sound for the hit
	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* hitSound;

	// Hold the camera shake
	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<class UCameraShakeBase> hitCameraShakeClass;

	/*
	Callback function that handles the projectile hitting an actor
	@param UPrimitiveComponent* hitComponent the component that caused the hit
	AActor* actorHit the actor hit by the hitComponent
	UPrimitiveComponent* otherComponent the component of the actor hit
	FVector impulse the impulse of the hit event
	FHitResult hit the hit event of caused by the projectile
	@return void
	*/
	UFUNCTION()
	void onHit(UPrimitiveComponent* hitComponent, AActor* actorHit, 
	UPrimitiveComponent* otherComponent, FVector impluse, const FHitResult& hit);

public:
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
