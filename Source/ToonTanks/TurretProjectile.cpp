#include "TurretProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

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

	// Create the trail particles
	trailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle_Trail"));

	// Attach the trail particles to the root component
	trailParticles->SetupAttachment(RootComponent);

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

	// Check if we have sound for the launch
	if(launchSound)
	{

		// Play the launch sound
		UGameplayStatics::PlaySoundAtLocation(this, launchSound, GetActorLocation());
	}
}

// Called every frame
void ATurretProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void  ATurretProjectile::onHit(UPrimitiveComponent* hitComponent, AActor* actorHit, 
UPrimitiveComponent* otherComponent, FVector impluse, const FHitResult& hit)
{

	// Get the owner that spawned the projectile
	AActor* owner = GetOwner();

	// Return if there is no owner
	if(!owner) return;

	// Hold the controller of the actor
	AController* ownerInstigator = owner->GetInstigatorController();
	
	// Hold the default damage type 
	UClass* damageTypeClass = UDamageType::StaticClass();

	// Check if there is an actor hit, the projectile itself, and it is not the owner
	if(actorHit && actorHit != this && actorHit != owner)
	{

		// Call the apply damage event 
		UGameplayStatics::ApplyDamage(actorHit, damage, ownerInstigator, this, damageTypeClass);

		// Check if there is particles for the hit
		if(hitParticles)
		{
			
			// Spawn the hit particles
			UGameplayStatics::SpawnEmitterAtLocation(this, hitParticles, GetActorLocation(), GetActorRotation());
		}

		// Check if there is sound for the hit
		if(hitSound)
		{

			// Play the hit sound
			UGameplayStatics::PlaySoundAtLocation(this, hitSound, GetActorLocation());
		}

		// Check if we have a camera shake
		if(hitCameraShakeClass)
		{

			// Start the camera shake
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(hitCameraShakeClass);
		}
	}

	// Destroy the projectile
	Destroy();
}
