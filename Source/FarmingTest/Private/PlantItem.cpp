// Fill out your copyright notice in the Description page of Project Settings.


#include "PlantItem.h"
#include "Components/StaticMeshComponent.h"
#include "MainCharacter.h"
#include "AC_PlayerInteractSystem.h"
 
APlantItem::APlantItem()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("/Game/StarterContent/Props/SM_Bush"));	 
	myMesh->SetStaticMesh(MeshAsset.Object);

	mainCharRef = nullptr;

	// TODO: TESTING ONLY - These get changed to None in prod
	growthStatus = EGrowthStatus::Ripe;
	plotStatus = EPlotStatus::Planted;
}

void APlantItem::BeginPlay()
{
	Super::BeginPlay();	
}

void APlantItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);

	if (MainCharacter)
	{		
		mainCharRef = MainCharacter;
		
		iComp = MainCharacter->FindComponentByClass<UAC_PlayerInteractSystem>();
		iComp->SetPlantOverlapStatus(this, true);
	}	
}

void APlantItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{	 
	if (mainCharRef)
	{
		iComp->SetPlantOverlapStatus(this, false);
	}
}

void APlantItem::InteractWithPlant()
{
	switch (plotStatus)
	{
	case Unused:
	{
		// Plant if player has seed
		if (bHasSeed)
		{
			// Plant seed according to seed croptype
			plotStatus = EPlotStatus::Plowed;
		}
		else
		{
			// Notify user they have no seeds
		}
	}
	case Plowed:
	{
		// Show plowing and seed planting animation
		//if (PlowAnimation)
		//{
		//	//PlayPlowAnimation();
		//	plotStatus = EPlotStatus::Planted;
		//  growthStatus = EGrowthStatus::Seedling;
		//  FTimerHandle TempHandle;
		//  GetWorld()->GetTimerManager().SetTimer(TempHandle, this, &ACursedHarvestGameMode::PerformSeedlingStuff, SeedlingTimerLength, false);
		//}		 
	}
		break;	 
	case Planted:
	{
		switch (growthStatus)
		{
		case Seedling:
		{
			// Changes the mesh to reflect the current growth state TODO: Get meshes to use
			UStaticMesh* meshToUse = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/StarterContent/Props/SM_Bush")));
			myMesh->SetStaticMesh(meshToUse);
			// TODO: This is just to show a growth scale until actual meshes are available
			myMesh->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
			UE_LOG(LogTemp, Warning, TEXT("Seedling planted"));
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
			 // Change mesh back to unplowed and spawn combat plant
			 //CombatSystem->SpawnEnemy(itemCropType);
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

