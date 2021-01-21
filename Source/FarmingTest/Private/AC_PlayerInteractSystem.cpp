// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_PlayerInteractSystem.h"
//#include "CropPickupItem.h"

ECropType cropType;

UAC_PlayerInteractSystem::UAC_PlayerInteractSystem()
{
	 playerHealth = 100.f;
}
 
void UAC_PlayerInteractSystem::DisplayCropTypeUponPickup(TEnumAsByte<ECropType> pickup)
{
	/** This is just a test to show that the pickup can "talk" to the player and tell them what was picked up. 
	This can be used for scoring, etc. */
	FString itemstr;
	itemstr = UEnum::GetDisplayValueAsText(pickup).ToString();
	UE_LOG(LogTemp, Warning, TEXT("AC_PlayerInteractionSystemItem - Crop type picked up: %s"), *itemstr);
}
