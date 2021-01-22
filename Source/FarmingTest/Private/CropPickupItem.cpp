// Fill out your copyright notice in the Description page of Project Settings.


#include "CropPickupItem.h"
#include "MainCharacter.h"
#include "AC_PlayerInteractSystem.h"

 

ACropPickupItem::ACropPickupItem()
{
	 CropType = ECropType::None;

	 //// TODO: TESTING ONLY - These get changed to None in prod
	 //growthStatus = EGrowthStatus::Ripe;
	 //plotStatus = EPlotStatus::Planted;
}

void ACropPickupItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	//UE_LOG(LogTemp, Warning, TEXT(" ACropPickupItem::OnOverlapBegin")); 

	AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
	if (MainCharacter)
	{		 
		 /** PICK UP PLANT, ADD TO INVENTORY AND DESTROY THE PICKUP ACTOR*/
			// Get CropType
			TEnumAsByte<ECropType> itemCropType;
			itemCropType = GetCropType();

			// Convert to string for log
			FString itemstr;
			itemstr = UEnum::GetDisplayValueAsText(itemCropType).ToString();
			UE_LOG(LogTemp, Warning, TEXT("CropPickupItem: You picked up a %s."), *itemstr);

			// Pass croptype to MainCharacter and add to inventory
			MainCharacter->InteractionComp->DisplayCropTypeUponPickup(itemCropType); // TODO: Remove me before prod. Was just for proof of concept
			//MainCharacter->InventoryComp->AddToInventory(itemCropType, Qty); 

			// Call parent function OnBeginOverlap to destroy the pickup item
			Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);		 
	}	 
}

TEnumAsByte<ECropType> ACropPickupItem::GetCropType()
{
	return CropType;
}
 
