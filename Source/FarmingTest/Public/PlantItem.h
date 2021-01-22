// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlantBaseItem.h"
#include "PlantItem.generated.h"


/**
 * 
 */
UCLASS()
class FARMINGTEST_API APlantItem : public APlantBaseItem
{
	GENERATED_BODY()

public:
	
		APlantItem();

		// Define enums
		EGrowthStatus growthStatus;
		EPlotStatus plotStatus;

		UPROPERTY()
		class AMainCharacter* mainCharRef;
		UPROPERTY()
		class UAC_PlayerInteractSystem* iComp;
		UPROPERTY()
		bool bHasSeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	 
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	void InteractWithPlant();
};
