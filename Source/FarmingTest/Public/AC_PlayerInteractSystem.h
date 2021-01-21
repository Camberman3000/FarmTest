// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AC_BaseInteraction.h"
#include "CropPickupItem.h"
#include "AC_PlayerInteractSystem.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class FARMINGTEST_API UAC_PlayerInteractSystem : public UAC_BaseInteraction
{
	GENERATED_BODY()

public:
	UAC_PlayerInteractSystem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float playerHealth;
	 	 
	void DisplayCropTypeUponPickup(TEnumAsByte<ECropType> pickup);
};
