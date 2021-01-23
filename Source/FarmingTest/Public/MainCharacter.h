// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class FARMINGTEST_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

		/** Camera boom positioning the camera behind the pawn*/
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow Camera*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

protected:
	/** Reference to the Player Controller*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")
		class AMainPlayerController* MainPlayerController;

public:
	// Sets default values for this character's properties
	AMainCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interact")
	class UAC_PlayerInteractSystem* InteractionComp;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interact")
	float traceDistance;

	// Line trace forward from player for interaction	 
	void TraceForward();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	bool bDrawPlantingDebugLine;
	 

	// Get z location of ground at x,y
	UFUNCTION(BlueprintPure, meta = (AdvancedDisplay = "bDrawDebugLines"))
		float GetSurface(FVector2D Point, bool bDrawDebugLines = false);
	float GroundLoc;
	 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	 

public:
	 
	UFUNCTION()
		void EKeyPressed();

	 

public:

	
};
