// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EliminationGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AEliminationGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	public:

	void ActorDied(AActor* DeadActor);

	// Implemented in a blueprint and can be called in c++
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bGameWon);
	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	private:

	UPROPERTY()
	class ATank* Tank;

	UPROPERTY()
	class ATankPlayerController* TankPC;

	// Initially it is 0, set it to number of enemies
	int32 NumberOfEnemies = 0;
	float StartDelay = 3.f;

	void HandleStartGame();
	void SetPlayerEnabledStateAtStart(bool bIsEnabled);
	int32 GetNumberOfEnemies();


};
