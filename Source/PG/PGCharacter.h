// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
// Copyright 2015 Matthias Hölzl, All Rights Reserved.


#pragma once
#include "GameFramework/Character.h"
#include "PGCharacter.generated.h"

UCLASS(config=Game)
class APGCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** Collection sphere */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pickup, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* CollectionSphere;

public:
	APGCharacter();

	// Perform the work that has to be done after initializing the components, e.g., setting the PowerMaterial.
	virtual void PostInitializeComponents() override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Accessor function for initial power */
	UFUNCTION(BlueprintPure, Category = "Power")
	float GetInitialPower() const { return InitialPower; };

	/** Accessor function for current power */
	UFUNCTION(BlueprintPure, Category = "Power")
	float GetCurrentPower() const { return CurrentPower; };

	/** 
	* Function to update the character's power
	* @param PowerChange This is the amount to change the power by, and it can be positive or negative.
	*/
	UFUNCTION(BlueprintCallable, Category = "Power")
	void UpdatePower(float PowerChange);

protected:

	/** Provide defaults for the mesh and animations */
	virtual void ConfigureMeshAndAnimation();

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

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	/** Called when we press a key to collect all pickups inside the collection sphere */
	UFUNCTION(BlueprintCallable, Category = "Pickups")
	void CollectPickups();

    /** Multiplier for character speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float SpeedFactor;

	/** Speed when baseline power = 0 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
    float BaseSpeed;

	/** Maximum speed the character can achieve */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float MaxSpeed;

	/** The colors for 0 and full power, respectively */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	FLinearColor ZeroPowerColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	FLinearColor FullPowerColor;

	/** The starting power level of our character */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
    float InitialPower;
    
	/** Apply the visual effect */
	UFUNCTION(BlueprintNativeEvent, Category = "Power", Meta = (BlueprintProtected = "true"))
	void PowerChangeEffect();
	virtual void PowerChangeEffect_Implementation();

private:
	/** Current power level of our character */
	UPROPERTY(VisibleAnywhere, Category = "Power")
	float CurrentPower;

	UMaterialInstanceDynamic* CreateAndApplyPowerMaterial();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Power", Meta = (AllowPrivateAccess = "true"))
	UMaterialInstanceDynamic* PowerMaterial;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	/** Returns CollectionSphere subobject */
	FORCEINLINE class USphereComponent* GetCollectionSphere() const { return CollectionSphere; }
};

