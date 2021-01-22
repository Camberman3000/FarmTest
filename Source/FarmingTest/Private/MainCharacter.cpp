// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Components/InputComponent.h" 
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MainPlayerController.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AC_PlayerInteractSystem.h"
#include "PlantItem.h"
#include "DrawDebugHelpers.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Don't rotate when the Controller rotates. Let it just affect the camera. Decouples the mouse movement from the character.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...(W,S,A,D, etc) but camera remains where we place it with mouse
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	traceDistance = 2000.f;
	 
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("EKey", IE_Pressed, this, &AMainCharacter::EKeyPressed);
}

 // Player world interaction keypress
void AMainCharacter::EKeyPressed()
{
	
	 
	UE_LOG(LogTemp, Warning, TEXT("Pressed E Key"));
	// This is where the player plows the plot and plants the seed
	
	InteractionComp = FindComponentByClass<UAC_PlayerInteractSystem>();

	// Called from BP
	TraceForward();

	// Doing away with this in favor of an open-world planting system
	//if (InteractionComp->bPlantIsOverlapped == true)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Plant is overlapped. Open menu..."));

	//	// TODO: REMOVE LINES BELOW FOR PROD: Temp items for proof of concept. These will be set from the player menu (UI) when attempting to plant
	//	 InteractionComp->OverlappedPlantActor->bHasSeed = true;
	//	 InteractionComp->OverlappedPlantActor->plotStatus = EPlotStatus::Planted;
	//	 InteractionComp->OverlappedPlantActor->growthStatus = EGrowthStatus::Seedling;
	//	 InteractionComp->OverlappedPlantActor->InteractWithPlant();
	//	 // END REMOVE FOR PROD
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Plant is NOT overlapped. Do nothing or other world activity"));
	//}	 
}

void AMainCharacter::TraceForward()
{
	  
	FVector Loc;
	FRotator Rot;
	FHitResult Hit;

	this->GetController()->GetPlayerViewPoint(Loc, Rot);	
	FVector Start = Loc;
	FVector End = Start + (Rot.Vector() * traceDistance);	

	FCollisionQueryParams TraceParams;
	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 3.0f);		

	if (bHit)
	{
		DrawDebugBox(GetWorld(), Hit.ImpactPoint, FVector(5, 5, 5), FColor::Emerald, false, 3.f);
		 
		// Get ground Z location
		FVector2D GroundXY; // Define the X, Y var
		GroundXY = FVector2D(Start.X, Start.Y); // Get the X, Y of the line trace
		GroundLoc = GetSurface(GroundXY, false); // Get the ground (Z) location under the line trace impact point
		 
		 
		if (GroundLoc + 10.f > Hit.ImpactPoint.Z && GroundLoc - 10.f < Hit.ImpactPoint.Z)
		{
			UE_LOG(LogTemp, Warning, TEXT("Within tolerance, can plant here."));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("OUT OF TOLERANCE, CAN'T PLANT HERE"));
		}
		 
		UE_LOG(LogTemp, Warning, TEXT("Ground location Z(height): %f"), GroundLoc);
	}
}
  
// Gets the ground location at X,Y - Used for Determining the location to plant a seed
float AMainCharacter::GetSurface(FVector2D Point, bool bDrawDebugLines /*= false*/)
{
	UWorld* World{ this->GetWorld() };

	if (World)
	{
		FVector StartLocation{ Point.X, Point.Y, 1000 };    // Raytrace starting point.
		FVector EndLocation{ Point.X, Point.Y, 0 };            // Raytrace end point.

		// Raytrace for overlapping actors.
		FHitResult HitResult;
		World->LineTraceSingleByObjectType(
			OUT HitResult,
			StartLocation,
			EndLocation,
			FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),
			FCollisionQueryParams()
		);

		// Draw debug line.
		if (bDrawDebugLines)
		{
			FColor LineColor;

			if (HitResult.GetActor()) LineColor = FColor::Red;
			else LineColor = FColor::Green;

			DrawDebugLine(
				World,
				StartLocation,
				EndLocation,
				LineColor,
				true,
				5.f,
				0.f,
				10.f
			);
		}

		// Return Z location.
		if (HitResult.GetActor()) return HitResult.ImpactPoint.Z;
	}

	return 0;
}

void AMainCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// Find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMainCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// Find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get right vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// Add movement in that direction
		AddMovementInput(Direction, Value);
	}
}