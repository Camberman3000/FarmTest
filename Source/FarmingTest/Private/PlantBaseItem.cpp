// Fill out your copyright notice in the Description page of Project Settings.


#include "PlantBaseItem.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APlantBaseItem::APlantBaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collisionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionVolume"));
	RootComponent = collisionVolume;

	myMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	myMesh->SetupAttachment(GetRootComponent());

	collisionVolume->SetSphereRadius(90.f);

}

// Called when the game starts or when spawned
void APlantBaseItem::BeginPlay()
{
	Super::BeginPlay();
	
	collisionVolume->OnComponentBeginOverlap.AddDynamic(this, &APlantBaseItem::OnOverlapBegin);	 
	collisionVolume->OnComponentEndOverlap.AddDynamic(this, &APlantBaseItem::OnOverlapEnd);
}

// Called every frame
void APlantBaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Call from inherited class by use of "Super::OnOverlapBegin(...)" (override)
void APlantBaseItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Destroy the pickup actor
	//Destroy();
}

void APlantBaseItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

