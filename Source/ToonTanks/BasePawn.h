// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class UCapsuleComponent;
// class USceneComponent;

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 EventGraphRead = 3;

	// Handle Shoot Input
	void Shoot();
	// Handle destruction of pawn
	void DestroySelf();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void RotateTurrent(FVector LookAtTarget);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Collider Related", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent *CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Mesh Related", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Mesh Related", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *TurrentMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Mesh Related", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Particles")
	class UParticleSystem* DeathEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundBase* DeathSound;

	UPROPERTY(EditDefaultsOnly, Category = "Camera Shake")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;

};
