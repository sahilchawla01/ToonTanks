// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USoundBase;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	UPROPERTY(VisibleAnywhere, Category = "Movement Components")
	class UProjectileMovementComponent* ProjectileComp;

	UPROPERTY(VisibleAnywhere, Category = "Movement Variables")
	float InitialSpeed = 200.f;

	UPROPERTY(VisibleAnywhere, Category = "Movement Variables")
	float MaxSpeed = 200.f;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:

	UPROPERTY(EditAnywhere)
	float Damage = 50.f;

	UPROPERTY(EditDefaultsOnly, Category = "Static Meshes", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult &Hit);

	UPROPERTY(EditDefaultsOnly, Category = "Particles")
	class UParticleSystem* HitParticle;

	UPROPERTY(VisibleAnywhere, Category = "Particles")
	class UParticleSystemComponent* TrailParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* LaunchSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* HitSound;

	UPROPERTY(EditDefaultsOnly, Category = "Camera Shake")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;
};
