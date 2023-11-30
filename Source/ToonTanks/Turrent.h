// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Turrent.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATurrent : public ABasePawn
{
	GENERATED_BODY()

	public:

	virtual void Tick(float DeltaTime) override; 

	void DestroySelf();

	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Turrent Settings", meta = (AllowPrivateAccess = "true"))
	float TurrentShootRange = 100.f;

	UPROPERTY()
	class ATank* Tank;

	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.f;
	FVector OriginalOrientation;

	void CheckFireCondition();
	bool InFireRange();
};
