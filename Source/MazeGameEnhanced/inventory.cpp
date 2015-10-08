// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeGameEnhanced.h"
#include "inventory.h"


// Sets default values
Ainventory::Ainventory()
{
   // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
   PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void Ainventory::BeginPlay()
{

   Super::BeginPlay();
}

// Called every frame
void Ainventory::Tick( float DeltaTime )
{
   
   Super::Tick( DeltaTime );
}

void Ainventory::push(FString itemName)
{
   bool exists=false;
   auto it = MyInventory.CreateIterator();
   for( ; it; ++it){
      if(it->Key == itemName){
         exists = true;
         it->Value = it->Value + 1;
      }      
   }  
   if(!exists)
      MyInventory.Add(itemName, 1);
   GEngine->AddOnScreenDebugMessage(5, 3.f, FColor::Red, FString::FromInt(GetItemCnt(itemName)));
}

int Ainventory::GetItemCnt(FString itemName)
{
   auto B = MyInventory.CreateIterator();
   for( ; B; ++B){
      if(B->Key == itemName){   
         return B->Value;
      }      
   }
   return 0;
}


