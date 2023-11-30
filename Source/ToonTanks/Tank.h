// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "InputActionValue.h"
#include "Tank.generated.h"

class UInputAction;
/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

	public:

	ATank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool bIsAlive = true;
	
	#pragma region InputActions
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category ="Enhanced Input")
	UInputAction* InputMove;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category ="Enhanced Input")
	UInputAction* InputLook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category ="Enhanced Input")
	UInputAction* InputShoot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* InputBoostSpeedUp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* InputBoostSpeedReset;
	#pragma endregion

	#pragma region Getters
	APlayerController* GetTankPlayerController() const {return TankPlayerController;}
	#pragma endregion
	
	// Handle Tank's destruction 
	void DestroySelf();

	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	#pragma region InputMappingContext
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category ="Enhanced Input")
	class UInputMappingContext* InputMapping;
	#pragma endregion

	#pragma region PlayerSettings
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Settings")
	float MoveSpeed = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Settings")
	float TurnSpeed = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Settings")
	float SpeedBoostMultiplier = 0.25f;
	#pragma endregion
	
	private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Camera Related", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components|Camera Related", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY()
	APlayerController* TankPlayerController;

	#pragma region InputFunctions
	// Handle Move Input
	void Move(const FInputActionValue& Value);

	// Handle Boost Speed Increase Input 
	void BoostSpeedUp(const FInputActionValue& Value);

	// Handle Boost Speed Reset Input
	void ResetBoostSpeed(const FInputActionValue& Value);

	// Handle Look Input
	// void Look(const FInputActionValue& Value);

	#pragma endregion


	#pragma region PlayerCurrentStateValues
		bool bIsBoostActivated = true;
	#pragma region

	// Shows and hides actor whenever requried along with disabling tick
	void ShowHideActor(bool bHide);

};
