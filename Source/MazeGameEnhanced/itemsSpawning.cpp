// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeGameEnhanced.h"
#include "itemsSpawning.h"

// Sets default values
AitemsSpawning::AitemsSpawning()
{
   // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
   //PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AitemsSpawning::BeginPlay()
{
   Super::BeginPlay();
   
}

// Called every frame
void AitemsSpawning::Tick( float DeltaTime )
{

   Super::Tick( DeltaTime );
}

void AitemsSpawning::spawn(int rows, int columns, float widthApart, FVector thisLoc)
{
   /*    This worked in Maze.cpp
   Ainventory *heroInventory = GetWorld()->SpawnActor<Ainventory>(FVector(-500, -500, -1000), FRotator(0,0,0));
   AitemBasic *testItem = GetWorld()->SpawnActor<AitemBasic>(FVector(-500, -500, 100), FRotator(0,90,0));
   testItem->HeroBag = heroInventory;
   */

   // Assign this "bag" for all of the items. For the onHit, it'll dump into here.
   Ainventory *HeroBag = GetWorld()->SpawnActor<Ainventory>(FVector(-500, -500, -1000), FRotator(0,0,0));

   // For each item spawned, make sure it has its inventory set to the main one
   AitemBasic *newItem;
   for(int i=0; i<5; i++){
      newItem = GetWorld()->SpawnActor<AitemBasic>
         ( thisLoc + FVector(-i*500, -200.f, 0.f), FRotator(0,0,0) );
      newItem->HeroBag = HeroBag;
   }
}








