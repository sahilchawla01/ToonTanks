// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "GameFramework/Pawn.h"



void ATankPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
    if(bPlayerEnabled)
    {
        UE_LOG(LogTemp, Display, TEXT("Enable Player Input"));
        GetPawn()->EnableInput(this);
        // EnableInput(this);
        GetPawn()->SetActorTickEnabled(true);
    }
    else 
    {
        UE_LOG(LogTemp, Display, TEXT("Disable Player Input"));
        GetPawn()->DisableInput(this);
        // DisableInput(this);
        GetPawn()->SetActorTickEnabled(false);
    }
    bShowMouseCursor = bPlayerEnabled;
}
