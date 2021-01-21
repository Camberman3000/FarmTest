// Fill out your copyright notice in the Description page of Project Settings.


#include "CropPickupItem.h"
#include "MainCharacter.h"
#include "AC_PlayerInteractSystem.h"

 

ACropPickupItem::ACropPickupItem()
{
	 CropType = ECropType::None;

	 // TODO: TESTING ONLY - These get changed to None in prod
	 growthStatus = EGrowthStatus::Ripe;
	 plotStatus = EPlotStatus::Planted;
}

void ACropPickupItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	//UE_LOG(LogTemp, Warning, TEXT(" ACropPickupItem::OnOverlapBegin")); 

	AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
	if (MainCharacter)
	{		 
		switch (plotStatus)
		{
		case Unused:
			break;
		case Plowed:
			break;
		case Planted:
		{
			switch (growthStatus)
			{
			case Seedling:
			{

			}
			break;
			case Sprout:
			{

			}
			break;
			case Ripening:
			{

			}
			break;
			case Ripe:
			{
				// Get CropType
				TEnumAsByte<ECropType> itemCropType;
				itemCropType = GetCropType();

				// Convert to string for logging
				FString itemstr;
				itemstr = UEnum::GetDisplayValueAsText(itemCropType).ToString();
				UE_LOG(LogTemp, Warning, TEXT("CropPickupItem: You picked a %s and now it's turned! Catch it to collect its bounty!"), *itemstr);

				MainCharacter->InteractionComp->DisplayCropTypeUponPickup(itemCropType);

				//CombatSystem->SpawnEnemy(itemCropType);

				// Call parent function OnBeginOverlap to destroy the pickup item (TODO: May just hide it and disable collision until planted again)
				Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
			}
			break;
			default:
				break;
			}
		}
			break;
		default:
			break;
		}		
	}	 
}

TEnumAsByte<ECropType> ACropPickupItem::GetCropType()
{
	return CropType;
}
 
