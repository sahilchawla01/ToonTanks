// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileComp->InitialSpeed = InitialSpeed;
	ProjectileComp->MaxSpeed = MaxSpeed;

	// Create a particle system component
	TrailParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	TrailParticle->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	if(LaunchSound)
	{
		// Plays a launch sound for the projectile
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation(), 0.6);
	}

	if(ProjectileMesh) 
	{
		ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
	auto MyOwner = GetOwner();

	if(MyOwner == nullptr) 
	{
		Destroy();
		return;
	}

	auto MyOwnerInstigator = MyOwner->GetInstigatorController();

	if(OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, UDamageType::StaticClass());
		if(HitParticle)
		{
			// Spawn particle at hit position
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation(), GetActorRotation());
		}

		if(HitSound)
		{
			// Plays a launch sound for the projectile
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation(), 0.4);
		}

		if(HitCameraShakeClass)
		{
			// Start camera shake
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}
	}
	Destroy();
}
