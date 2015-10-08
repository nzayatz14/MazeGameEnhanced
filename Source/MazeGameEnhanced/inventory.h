// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "inventory.generated.h"

UCLASS()
class MAZEGAMEENHANCED_API Ainventory : public AActor
{
   GENERATED_BODY()

   /** Dummy root component */
   UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
   class USceneComponent* DummyRoot;

   /** StaticMesh component for the clickable block */
   UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
   class UStaticMeshComponent* InventoryMesh;

   
public:  
   // Sets default values for this actor's properties
   Ainventory();

   // Holds the Name:Cnt of any item
   TMap<FString, int> MyInventory;
   
   // Get the count of this item
   int GetItemCnt(FString);

   // Called when the game starts or when spawned
   virtual void BeginPlay() override;
   
   // Called every frame
   virtual void Tick( float DeltaSeconds ) override;

   // Given an item's name, push +1 into the inventory
   void push(FString);
   
public:
   /** Returns DummyRoot subobject **/
   FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
   /** Returns BlockMesh subobject **/
   FORCEINLINE class UStaticMeshComponent* GetInventoryMesh() const { return InventoryMesh; }
   /** Returns the entire inventory as a TMap **/
   TMap<FString,int> GetInventory(){ return MyInventory; }
};
