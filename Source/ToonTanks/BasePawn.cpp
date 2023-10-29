// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TurretProjectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set the capsule component
	capsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule_Collider"));

	// Reassign root component to the capsule component
	RootComponent = capsuleComponent;

	// Set the tank base component
	tankBaseComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank_Base"));

	// Attach the tank base component to the capsule component
	tankBaseComponent->SetupAttachment(capsuleComponent);

	// Set the tank turret component
	tankTurretComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank_Turret"));

	// Attach the tank turret to the tank base component
	tankTurretComponent->SetupAttachment(tankBaseComponent);

	// Set the spawn projectile component
	spawnProjectileComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn_Projectile"));

	// Attach the spawn projectile component to the tank turret
	spawnProjectileComponent->SetupAttachment(tankTurretComponent);
}

void ABasePawn::rotateTurretComponent(FVector targetLocation)
{

	// Hold the target vector 
	FVector toTarget = targetLocation - tankTurretComponent->GetComponentLocation();
	
	// Hold the rotator of the target location
	FRotator rotationToTarget = FRotator(0.f, toTarget.Rotation().Yaw, 0.f);
	
	// Set the world rotation of the tankTurretComponent
	tankTurretComponent->SetWorldRotation(FMath::RInterpTo(
		tankTurretComponent->GetComponentRotation(), rotationToTarget, 
		UGameplayStatics::GetWorldDeltaSeconds(this), 15.f
	));
}

void ABasePawn::fire()
{
	
	// Spawn the projectile into the world and hold it
	auto projectile = GetWorld()->SpawnActor<ATurretProjectile>(projectileClass,
	spawnProjectileComponent->GetComponentLocation(),
	spawnProjectileComponent->GetComponentRotation());

	// Set the owner of the projectile spawned
	projectile->SetOwner(this);
}