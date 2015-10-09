// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "inventory.h"

#include "GameFramework/Character.h"
#include "Avatar.generated.h"

UCLASS()
class MAZEGAMEENHANCED_API AAvatar : public ACharacter
{
   GENERATED_BODY()

public:
   // Sets default values for this character's properties
   AAvatar();

   //void *HeroBag;
   Ainventory *HeroBag;
   bool HUDOn;

   // Called when the game starts or when spawned
   virtual void BeginPlay() override;
   
   // Called every frame
   virtual void Tick( float DeltaSeconds ) override;

   // Called to bind functionality to input
   //virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

    void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
    
    void MoveForward(float amount);
    void MoveRight(float amount);
    void Yaw(float amount);
    void Pitch(float amount);
    
    void ToggleInventory();  

    UFUNCTION()
      void onHit(AActor *Self, AActor *neighbor, FVector NormalImpulse, const FHitResult &Hit);

};
