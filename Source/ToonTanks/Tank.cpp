// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{

    // Set the spring arm component
    springArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring_Arm"));
    
    // Attach the spring arm component to the root component
    springArmComponent->SetupAttachment(RootComponent);

    // Set the camera component 
    cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    
    // Attach the camera component to the spring arm component
    cameraComponent->SetupAttachment(springArmComponent);
}

void ATank::BeginPlay()
{

    // Call the parent's BeginPlay
    Super::BeginPlay();

    // Set the player controller
    playerController = Cast<APlayerController>(GetController());
}

APlayerController* ATank::getPlayerController() const
{

    // Return the player controller
    return playerController;
}

void ATank::handlePawnDestruction()
{

    // Call the parent's handlePawnDestruction
    Super::handlePawnDestruction();

    // Hide the actor in game
    SetActorHiddenInGame(true);

    // Disable the actor's tick function
    SetActorTickEnabled(false);

    // Set the tank death state
    isTankAlive = false;
}


void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    
    // Bind the MoveForward action mapping
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::move);
    
    // Bind the Turn action mapping
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::rotate);

    // Bind the Fire action mapping
    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::fire);
}

void ATank::move(float value)
{

    // Hold the change in location for the tank
    deltaLocation.X = value * UGameplayStatics::GetWorldDeltaSeconds(this) * moveSpeed;

    // Add the change in location to the actor's local offset
    AddActorLocalOffset(deltaLocation, true);
}

void ATank::rotate(float value)
{

    // Hold the change in rotation for the tank
    deltaRotation.Yaw = value * UGameplayStatics::GetWorldDeltaSeconds(this) * turnSpeed;

    // Add the change in rotation to the actor's local rotation
    AddActorLocalRotation(deltaRotation, true);
}   

void ATank::Tick(float DeltaTime)
{

    // Check if there is a player controller for the pawn
    if(playerController)
    {

        // Hold the hit result 
        FHitResult hitResult;

        // Get the hit result from the cursor colliding with the enviroment
        playerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, hitResult);

        // Rotate the turret to face the collision with the enviroment
        rotateTurretComponent(hitResult.ImpactPoint);
    }
}
