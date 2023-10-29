#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	// Hold the max health
	UPROPERTY(EditAnywhere)
	float maxHealth = 100.f;

	// Hold the current health
	float currentHealth = 0.f;

	/*
	Callback function that handles the damage taken
	@param AActor* actorDamaged the actor damaged
	float damage the damage caused by the hit
	UDamageType* the damage caused by 
	*/
	UFUNCTION()
	void damageTaken(AActor* actorDamaged, float damage, const UDamageType* damageType, AController* instigator, AActor* damageCauser);

		
};
