// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeGameEnhanced.h"
#include "itemBasic.h"

#include "inventory.h"
#include "Avatar.h"
#include <random>

// Sets default values
AitemBasic::AitemBasic()
{
   std::random_device rd;
   found = false;
   // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
   PrimaryActorTick.bCanEverTick = true;

   struct FConstructorStatics
   {
      ConstructorHelpers::FObjectFinderOptional<UStaticMesh> genericItemShapeA;
      ConstructorHelpers::FObjectFinderOptional<UStaticMesh> genericItemShapeB;
      ConstructorHelpers::FObjectFinderOptional<UStaticMesh> genericItemShapeC;
      ConstructorHelpers::FObjectFinderOptional<UStaticMesh> genericItemShapeD;
      ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> genericItemMaterialA;
      ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> genericItemMaterialB;
      ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> genericItemMaterialC;
      ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> genericItemMaterialD;
      FConstructorStatics()
         : genericItemShapeA(TEXT("/Game/items/itemBasic_Shape.itemBasic_Shape"))
         , genericItemShapeB(TEXT("/Game/items/itemBasic_PyramidShape.itemBasic_PyramidShape"))
         , genericItemShapeC(TEXT("/Game/items/itemBasic_MacaroniShape.itemBasic_MacaroniShape"))
         , genericItemShapeD(TEXT("/Game/items/itemBasic_CheeseShape.itemBasic_CheeseShape"))
         , genericItemMaterialA(TEXT("/Game/items/itemBasic_Material.itemBasic_Material"))
         , genericItemMaterialB(TEXT("/Game/items/itemBasic_Material2.itemBasic_Material2"))
         , genericItemMaterialC(TEXT("/Game/items/itemBasic_Material3.itemBasic_Material3"))
         , genericItemMaterialD(TEXT("/Game/items/itemBasic_Material4.itemBasic_Material4"))
      {
      }
   };
   static FConstructorStatics ConstructorStatics;

   // Create dummy root scene component
   DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
   RootComponent = DummyRoot;

   ItemBasicMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("item_shape"));
   // Create random mesh component
   switch(rd()%4){
      case 0:
         ItemBasicMesh->SetStaticMesh(ConstructorStatics.genericItemShapeA.Get());
         ItemBasicMesh->SetMaterial(0, ConstructorStatics.genericItemMaterialA.Get());
         itemType = 'A';   //red pill
         break;
      case 1:  
         ItemBasicMesh->SetStaticMesh(ConstructorStatics.genericItemShapeB.Get());  
         ItemBasicMesh->SetMaterial(0, ConstructorStatics.genericItemMaterialB.Get());
         itemType = 'B';   //blue pyramid
         break;
      case 2:  
         ItemBasicMesh->SetStaticMesh(ConstructorStatics.genericItemShapeC.Get());  
         ItemBasicMesh->SetMaterial(0, ConstructorStatics.genericItemMaterialC.Get());
         itemType = 'C';   //yellow macaroni
         break;
      case 3:  
         ItemBasicMesh->SetStaticMesh(ConstructorStatics.genericItemShapeD.Get());  
         ItemBasicMesh->SetMaterial(0, ConstructorStatics.genericItemMaterialD.Get());
         itemType = 'D';   //green cheese (ew)
         break;
   }
   ItemBasicMesh->SetRelativeScale3D(FVector(1.f,1.f,1.f));
   ItemBasicMesh->SetRelativeLocation(FVector(0.f,0.f,50.f));
   ItemBasicMesh->SetRelativeRotation(FRotator(15.f, 15.f, 0.f));
   ItemBasicMesh->AttachTo(DummyRoot);
   //ItemBasicMesh->SetSimulatePhysics(true);
}
// Called when the game starts or when spawned
void AitemBasic::BeginPlay()
{

   Super::BeginPlay();
}

// Called every frame
void AitemBasic::Tick( float DeltaTime )
{
   Super::Tick( DeltaTime );

   // lol just kidding, this crashes UE4 on mac, but not windows. 
   //    Just do yaw.
   spinWithQuaternion();
}
void AitemBasic::spinWithQuaternion()
{
   FRotator ActorRotator = this->GetActorRotation();
   ActorRotator.Yaw +=2;
   this->SetActorRotation(ActorRotator);
   /*       CRASHES MY COMPUTER
   FVector actorLocation, rotatePoint, rotateAxis, diff;
   FQuat q, nuuq;
   float angleInDegrees = 1;

   // What's the anchor for this rotation?
   rotatePoint = FVector(0, 0, 500);
   // What's the axis for this rotation? (normalized)
   rotateAxis = FVector(0, 0, 1);
   // Who am I rotating?
   actorLocation = this->GetActorLocation();
   // What's the current quaternion?
   q = this->GetActorQuat();

   // IMPLEMENT
   //    Move the object
   diff = actorLocation - rotatePoint;
   //    Make the change quaternion
   //    Move the anchor, relate it back to original
   //actorLocation = diff.RotateAngleAxis(angleInDegrees, rotateAxis);
   //actorLocation = actorLocation + rotatePoint;
   //    Use the quaternion
   q = FQuat(rotateAxis, angleInDegrees * 180.0 / 3.14159);
   nuuq = this->GetActorQuat() * q;
   this->SetActorLocationAndRotation(actorLocation, nuuq);
   */


   /*    Class notes
      FRotator ActorRotator = neighbor->GetActorRotation();
      FVector xProduct;

      // if wall, spin the wall around its anchor. DISABLED.
      else if( 0&& neighbor && (neighbor->GetActorLabel()).Contains( TEXT("mWall"), ESearchCase::CaseSensitive, ESearchDir::FromEnd )){
         xProduct = FVector::CrossProduct(neighbor->GetActorRightVector(), (neighbor->GetActorLocation() - Self->GetActorLocation()));
         if( xProduct.Z > 0 )
            ActorRotator.Yaw +=2;
         else
            ActorRotator.Yaw -=2;
         neighbor->SetActorRotation(ActorRotator);
      };
   */
}