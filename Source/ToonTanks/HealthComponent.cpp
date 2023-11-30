// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EliminationGameMode.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// Set initial health to max
	CurrentHealth = MaxHealth;

	// Assign delegate takeanydamage of actor
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);	

	// Assign game mode
	EliminationGameMode = Cast<AEliminationGameMode>(UGameplayStatics::GetGameMode(this));
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::DamageTaken(AActor *DamagedActor, float Damage, const UDamageType *DamageType, AController *Instigator, AActor *DamageCauser)
{
	if(Damage <= 0.f) return;

	CurrentHealth -= Damage;
	if(CurrentHealth <= 0.f && EliminationGameMode) 
	{
		EliminationGameMode->ActorDied(DamagedActor);
	}

	UE_LOG(LogTemp, Display, TEXT("Current Health is %f"), CurrentHealth);
}
