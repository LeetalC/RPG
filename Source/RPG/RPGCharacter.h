// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RPGCharacter.generated.h"

UCLASS(config=Game)
class ARPGCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	ARPGCharacter();
	virtual void BeginPlay();


	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
		float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Movement: Walking")
		float DefaultMaxWalkSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Movement: Walking")
		float MaxSprintSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		int level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float Happiness = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float Fullness = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float Stamina = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float HappinessDecrement = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float FullnessDecrement = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float StaminaDecrement = 1.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float MaxHappiness = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float MaxFullness = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float MaxStamina = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float StaminaDrainRate = 15.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float StaminaFillRate = 5.0f;


	UFUNCTION(BlueprintCallable)
		void SetStamina(float value);

	UFUNCTION(BlueprintCallable)
		void SetHappiness(float value);

	UFUNCTION(BlueprintCallable)
		void SetFullness(float value);

	UFUNCTION(BlueprintCallable)
		void AddFullness(float value);

	UFUNCTION(BlueprintCallable)
		void AddStamina(float value);

	UFUNCTION(BlueprintCallable)
		void AddHappiness(float value);

	UFUNCTION(BlueprintCallable)
		void AddLevel();



	//EVENTS-------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = StatEvent)
		void FullnessChanged();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = StatEvent)
		void StaminaChanged();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = StatEvent)
		void HappinessChanged();


	//SPRINTING-----------------------------
	void Sprint();

	UFUNCTION(BlueprintCallable)
		void StopSprinting();


	void CheckHappiness(float DeltaSeconds);
	void CheckFullness(float DeltaSeconds);
	void CheckStamina(float DeltaSeconds);

	
	bool IsSprinting;

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);


	virtual void Tick(float DeltaSeconds);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

