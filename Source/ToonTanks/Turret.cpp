#include "Turret.h"
#include  "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATurret::BeginPlay()
{

    // Call the parent BeginPlay()
    Super::BeginPlay();

    // Set the playerTank pointer by grabbing the player pawn
    playerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    // Set a timer that checks if the turret can fire
    GetWorldTimerManager().SetTimer(fireRateTimeHandle, this, &ATurret::checkFireCondition, fireRate, true, 2.f);
}

void ATurret::handlePawnDestruction()
{

    // Call the parent's handlePawnDestruction
    Super::handlePawnDestruction();

    // Destroy the turret
    Destroy();
}

bool ATurret::isInFireRange()
{

    // Check if there is a player tank
    if(playerTank)
    {

        // Return true if the player tank is in range
        return FVector::Dist(GetActorLocation(), playerTank->GetActorLocation()) <= turretRange;
    }

    // Default return false
    return false;
}

void ATurret::checkFireCondition()
{

    // Check if the player tank is in fire range
    if(isInFireRange() && playerTank->isTankAlive)
    {

        // Fire the projectile at the player tank
        fire();
    }
} 

void ATurret::Tick(float DeltaTime)
{

    // Check if the player tank is in fire range
    if(isInFireRange())
    {

        // Rotate the turret's tankTurretComponent to face the player tank
        rotateTurretComponent(playerTank->GetActorLocation());
    }
}

