// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
// Copyright 2015 Matthias Hölzl, All Rights Reserved.


#pragma once
#include "PickupCollector.h"
#include "GameFramework/Character.h"
#include "Pickups/PickupHandler.h"
#include "PGCharacter.generated.h"


/*
 * The base class for all playable characters.
 * Contains a camera, support for handling pickups as well as the functionality for
 * applying effects when picking up items.
 */
UCLASS(Abstract, config=Game)
class PG_API APGCharacter : public ACharacter, public IPickupCollector
{
	GENERATED_BODY()

protected:
	APGCharacter();

	void ConfigureControllerRotation();
	void ConfigureCharacterMovement();
	void ConfigureCameraBoom();
	void ConfigureFollowCamera();
	void ConfigureCollectionSphere();

	virtual void ConfigureMeshCollision();


	// Perform the work that has to be done after initializing the components, e.g., setting the PowerMaterial.
	virtual void PostInitializeComponents() override;

private:

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

public:
	virtual void HandlePickup(class APickup* Pickup);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	TArray<UPickupHandler*> PickupHandlers;

public:

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

public:

	/** Called when we press a key to collect all pickups inside the collection sphere */
	UFUNCTION(BlueprintCallable, Category = "Pickups")
	void CollectPickups();

protected:

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	FName PowerChangeParameter;

	/** The starting power level of our character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float InitialPower;

	/** Apply the visual effect */
	UFUNCTION(BlueprintCallable, Category = "Power", Meta = (BlueprintProtected = "true"))
	virtual void PowerChangeEffect();

protected:
	/** Current power level of our character */
	UPROPERTY(VisibleAnywhere, Category = "Power")
	float CurrentPower;

	void CreateAndApplyPowerMaterial();

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
