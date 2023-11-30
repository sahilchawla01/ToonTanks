// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Projectile.h"
#include "Particles/ParticleSystem.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create root component as capsule component
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;
	// Create the base mesh and attach it to root component
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	// Create the turrent mesh and attach it to base mesh
	TurrentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turrent Mesh"));
	TurrentMesh->SetupAttachment(BaseMesh);

	// Create the projectile spawn point and attach to turrent mesh
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurrentMesh);
	
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Rotate turrent mesh to target
void ABasePawn::RotateTurrent(FVector LookAtTarget)
{
	// Get to target vector
	FVector ToTarget = LookAtTarget - TurrentMesh->GetComponentLocation();
	// Get rotation to rotate to
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);

	TurrentMesh->SetWorldRotation(
		FMath::RInterpTo(
		TurrentMesh->GetComponentRotation(),
		LookAtRotation,
		UGameplayStatics::GetWorldDeltaSeconds(this),
		25.f)
		);
}

void ABasePawn::Shoot()
{
	FVector ProjectileSpawnPointLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();

	// Spawn the actor
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPointLocation, Rotation);

	Projectile->SetOwner(this);
}

void ABasePawn::DestroySelf()
{
	// Visual/sound effects

	// Play death particle effect
	if(DeathEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathEffect, GetActorLocation(), GetActorRotation());
	}

	// Play death sound
	if(DeathSound)
	{
		// Plays a death sound for the pawn
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation(), 0.6);
	}

	// Play Camera shake for a pawn death
	if(DeathCameraShakeClass)
	{
		// Start camera shake
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}
}

