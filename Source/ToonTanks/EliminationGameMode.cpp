// Fill out your copyright notice in the Description page of Project Settings.


#include "EliminationGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Turrent.h"
#include "TankPlayerController.h"

void AEliminationGameMode::BeginPlay()
{
    Super::BeginPlay();

    // Call game start after a delay
    HandleStartGame();

}

void AEliminationGameMode::ActorDied(AActor *DeadActor)
{
    // If the actor died is the tank,
    if(DeadActor == Tank)
    {
        Tank->DestroySelf();

        if(TankPC)
        {
            TankPC->SetPlayerEnabledState(false);
        }

        // When game is lost
        GameOver(false);
    }
    else if(ATurrent* DestroyedTurrent = Cast<ATurrent>(DeadActor))
    {
        DestroyedTurrent->DestroySelf();

        // An enemy is destroyed
        NumberOfEnemies--;

        // Game is won
        if(NumberOfEnemies <= 0) GameOver(true);
    }
}

void AEliminationGameMode::HandleStartGame()
{
    // Assign following pointers
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    TankPC = Cast<ATankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();

     // Initialise total number of enemies in the world
    NumberOfEnemies = GetNumberOfEnemies();

    if(TankPC)
    {
        // Disable input
        TankPC->SetPlayerEnabledState(false);

        FTimerHandle PlayerEnableTimerHandle;

        // Create timer delegate
        FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(this, &AEliminationGameMode::SetPlayerEnabledStateAtStart, true);
        
        // Set timer handler, it enables the input after StartDelay (seconds)
        GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableDelegate, StartDelay, false);
    }

}

void AEliminationGameMode::SetPlayerEnabledStateAtStart(bool bIsEnabled)
{   

    UE_LOG(LogTemp, Display, TEXT("Set player enable at start is called"));

    if(!TankPC)
    {
        UE_LOG(LogTemp, Error, TEXT("Tank Controller pointer doesn't exist at SetPlayerEnableAtStart"));
        return;
    }

    // Set controller state
    TankPC->SetPlayerEnabledState(bIsEnabled);
}

int32 AEliminationGameMode::GetNumberOfEnemies()
{
    TArray<AActor*> EnemyActors;

    UGameplayStatics::GetAllActorsOfClass(this, ATurrent::StaticClass(), EnemyActors);

    
    return EnemyActors.Num();
}

