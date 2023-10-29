#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{

	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// Set the current health to the max health
	currentHealth = maxHealth;
	
	// Attach the damageTaken function to the owner when they take damage
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::damageTaken);
}

void UHealthComponent::damageTaken(AActor* actorDamaged, float damage, const UDamageType* damageType, AController* instigator, AActor* damageCauser)
{

	// Check if the damage is valid
	if(damage <= 0.f) return;

	// Apply the damage to the current health
	currentHealth -= damage;
}

