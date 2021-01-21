// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupBaseItem.h"
#include "CropPickupItem.generated.h"


UENUM(BlueprintType)
enum ECropType
{
	None UMETA(DisplayName = "None"),
	Cabbage UMETA(DisplayName = "Cabbage"),
	Strawberry UMETA(DisplayName = "Strawberry"),
	Watermelon UMETA(DisplayName = "Watermelon"),
	Corn UMETA(DisplayName = "Corn")
};

enum EGrowthStatus
{
	Seedling UMETA(DisplayName = "Seedling"),
	Sprout UMETA(DisplayName = "Sprout"),
	Ripening UMETA(DisplayName = "Ripening"),
	Ripe UMETA(DisplayName = "Ripe")	
};

enum EPlotStatus
{
	Unused UMETA(DisplayName = "Unused"),
	Plowed UMETA(DisplayName = "Plowed"),
	Planted UMETA(DisplayName = "Planted")	 
};

/**
 * 
 */
UCLASS()
class FARMINGTEST_API ACropPickupItem : public APickupBaseItem
{
	GENERATED_BODY()
	
public:
	ACropPickupItem();

	/** TODO: REMOVE ME - TESTING ONLY - The crop type to spawn*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CropType")
		TEnumAsByte<ECropType> CropType;

		//Define enums - TODO: Will add croptype here. Using it as a blueprint property for testing
		EGrowthStatus growthStatus;
		EPlotStatus plotStatus;
 
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	TEnumAsByte<ECropType> GetCropType();
 
};
