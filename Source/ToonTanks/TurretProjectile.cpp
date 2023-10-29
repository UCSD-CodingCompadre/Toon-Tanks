#include "TurretProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATurretProjectile::ATurretProjectile()
{

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Set the projectile component
	projectileComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile"));

	// Reassign root component to the projectile component
	RootComponent = projectileComponent;

	// Set the projectile movement component
	projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile_Movement"));

	// Set the max speed
	projectileMovementComponent->MaxSpeed = 1300.f;
	
	// Set the initial speed 
	projectileMovementComponent->InitialSpeed = 1300.f;
}

// Called when the game starts or when spawned
void ATurretProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	// Add the onHit function to the projectile component
	projectileComponent->OnComponentHit.AddDynamic(this, &ATurretProjectile::onHit);
}


void  ATurretProjectile::onHit(UPrimitiveComponent* hitComponent, AActor* actorHit, 
UPrimitiveComponent* otherComponent, FVector impluse, const FHitResult& hit)
{

	// Get the owner that spawned the projectile
	auto owner = GetOwner();

	// Return if there is no owner
	if(!owner) return;

	// Hold the controller of the actor
	auto ownerInstigator = owner->GetInstigatorController();
	
	// Hold the default damage type 
	auto damageTypeClass = UDamageType::StaticClass();

	// Check if there is an actor hit, the projectile itself, and it is not the owner
	if(actorHit && actorHit != this && actorHit != owner)
	{

		// Call the apply damage event 
		UGameplayStatics::ApplyDamage(actorHit, damage, ownerInstigator, this, damageTypeClass);
		
		// Destroy the projectile
		Destroy();
	}
}
