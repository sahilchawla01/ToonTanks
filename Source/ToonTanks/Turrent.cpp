// Fill out your copyright notice in the Description page of Project Settings.


#include "Turrent.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATurrent::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(InFireRange()) 
    {
        RotateTurrent(Tank->GetActorLocation());
    }
    else
    {
        RotateTurrent(OriginalOrientation);
    }
}

void ATurrent::BeginPlay()
{
    Super::BeginPlay();

    // Assign Player Pawn
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    
    // Set original orientation
    FVector OrigLocation = GetActorLocation();
    FVector LookDirection = GetActorRotation().Vector();
    OriginalOrientation = FVector(OrigLocation.X + (LookDirection.X * 100.f), OrigLocation.Y, OrigLocation.Z);

    // Sets Timer Handle for checking if firing is ok
    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATurrent::CheckFireCondition, FireRate, true);
}

void ATurrent::CheckFireCondition()
{

    if(Tank == nullptr) return;

    if(InFireRange() && Tank->bIsAlive) Shoot();
}

/**
 * @details Checks if the tank is in fire range, returns true if it is, else false
*/
bool ATurrent::InFireRange() 
{
    // Check if tank is in range of turrent
    if(!Tank) return false;

    float DistanceToTank = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

    // If within range, rotate to tank
    if(DistanceToTank <= TurrentShootRange)
    {
        return true;
    } 

    return false;
}

void ATurrent::DestroySelf()
{
    Super::DestroySelf();

    Destroy();
}