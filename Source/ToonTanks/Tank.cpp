// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "TankPlayerController.h"

ATank::ATank()
{
    // Create a spring arm component
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    // Create a camera component
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Main Camera"));
    Camera->SetupAttachment(SpringArm);


}

void ATank::BeginPlay()
{
    Super::BeginPlay();

    TankPlayerController = Cast<APlayerController>(GetController());

    // Initially disable tick
    SetActorTickEnabled(false);
    
}

void ATank::Tick(float DeltaTime)
{

    if(!TankPlayerController) return;

    // Get hit result
    FHitResult CursorHitResult;
    bool bHasHitAnything = TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, CursorHitResult );

    if(!bHasHitAnything) return;

    FVector TargetLocation = CursorHitResult.ImpactPoint;

    RotateTurrent(TargetLocation);
}

void ATank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Get Player controller
    ATankPlayerController* PC = Cast<ATankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    if(!PC)
    {
        UE_LOG(LogTemp, Error, TEXT("Couldn't fetch TankPlayerController"));
        return;
    }

    // Get the local player subsystem
    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());

    if(!Subsystem)
    {
        UE_LOG(LogTemp, Error, TEXT("Couldn't fetch Local Player Subsystem"));
        return;
    }

    // Clear out existing mapping and our mapping
    Subsystem->ClearAllMappings();
    Subsystem->AddMappingContext(InputMapping, 0);

      // Get Enhanced Input Component
    UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

    // Bind the actions
    Input->BindAction(InputMove, ETriggerEvent::Triggered, this, &ATank::Move);
    // Input->BindAction(InputLook, ETriggerEvent::Triggered, this, &ATank::Look);
    Input->BindAction(InputShoot, ETriggerEvent::Triggered, this, &Super::Shoot);
    Input->BindAction(InputBoostSpeedUp, ETriggerEvent::Triggered, this, &ATank::BoostSpeedUp);
    Input->BindAction(InputBoostSpeedReset, ETriggerEvent::Triggered, this, &ATank::ResetBoostSpeed);
}



void ATank::Move(const FInputActionValue& Value) 
{

    if(Controller == nullptr) return;

    const FVector2D MoveValue = Value.Get<FVector2D>();
    const FRotator MovementRotation(0, Controller->GetControlRotation().Yaw, 0);

    // Forward/Backward Direction
    if(MoveValue.Y != 0.f) 
    {
        float CurrentSpeedMultipler = (bIsBoostActivated == false) ? 0.f : SpeedBoostMultiplier;

        FVector Direction = FVector::ZeroVector;
        Direction.X = MoveValue.Y * UGameplayStatics::GetWorldDeltaSeconds(this) * MoveSpeed * (1 + CurrentSpeedMultipler);

        AddActorLocalOffset(Direction, true);
    }

    // Left/Right Direction
    if(MoveValue.X != 0.f) 
    {
        FRotator DeltaRotation = FRotator::ZeroRotator;
        DeltaRotation.Yaw = MoveValue.X * UGameplayStatics::GetWorldDeltaSeconds(this) * TurnSpeed ;

        //UE_LOG(LogTemp, Display, TEXT("Currently Looking %f"), MoveValue.X);
        // Only concerned with yaw i.e look left and right
        AddActorLocalRotation(DeltaRotation, true);

        // FVector Direction = FVector::ZeroVector;
        // Direction.Y = MoveValue.X * UGameplayStatics::GetWorldDeltaSeconds(this) * MoveSpeed;
        // AddActorLocalOffset(Direction, true);
    }
}

void ATank::BoostSpeedUp(const FInputActionValue& Value)
{
    bIsBoostActivated = true;
}

void ATank::ResetBoostSpeed(const FInputActionValue& Value)
{
    bIsBoostActivated = false;
}

// void ATank::Look(const FInputActionValue& Value) 
// {
//     UE_LOG(LogTemp, Display, TEXT("Look started"));
//     if(Controller == nullptr) return;

//     const FVector2D LookValue = Value.Get<FVector2D>();

//     FRotator DeltaRotation = FRotator::ZeroRotator;
//     DeltaRotation.Yaw = LookValue.X * UGameplayStatics::GetWorldDeltaSeconds(this) * TurnSpeed ;

//     UE_LOG(LogTemp, Display, TEXT("Currently Looking %f"), LookValue.X);
//     // Only concerned with yaw i.e look left and right
//     if(LookValue.X != 0.f) 
//     {
//         AddActorLocalRotation(DeltaRotation, true);
//     }

// }


void ATank::DestroySelf()
{
    Super::DestroySelf();
    
    // Hide the actor and disable tick
    ShowHideActor(true);
    
}

void ATank::ShowHideActor(bool bHide)
{
    SetActorHiddenInGame(bHide);
    SetActorTickEnabled(!bHide);
    // Set alive = false
    bIsAlive = false;

}



