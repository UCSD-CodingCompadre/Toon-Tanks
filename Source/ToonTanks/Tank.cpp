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
	Super::BeginPlay();
	
    playerController = Cast<APlayerController>(GetController());
}


void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::rotate);

    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::fire);
}

void ATank::move(float value)
{
    deltaLocation.X = value * UGameplayStatics::GetWorldDeltaSeconds(this) * moveSpeed;

    AddActorLocalOffset(deltaLocation, true);
}

void ATank::rotate(float value)
{
    deltaRotation.Yaw = value * UGameplayStatics::GetWorldDeltaSeconds(this) * turnSpeed;

    AddActorLocalRotation(deltaRotation, true);
}   

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(playerController)
    {

        FHitResult hitResult;

        playerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, hitResult);

        DrawDebugSphere(GetWorld(), hitResult.ImpactPoint, 25, 24, FColor::Red, false, -1);

        rotateTurretComponent(hitResult.ImpactPoint);
    }
}
