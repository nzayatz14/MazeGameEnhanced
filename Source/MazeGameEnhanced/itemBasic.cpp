// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeGameEnhanced.h"
#include "itemBasic.h"


// Sets default values
AitemBasic::AitemBasic()
{
   found = false;
   // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
   PrimaryActorTick.bCanEverTick = true;

   struct FConstructorStatics
   {
      ConstructorHelpers::FObjectFinderOptional<UStaticMesh> genericItemShape;
      ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> genericItemMaterial;
      FConstructorStatics()
         : genericItemShape(TEXT("/Game/items/itemBasic_Shape.itemBasic_Shape"))
         , genericItemMaterial(TEXT("/Game/items/itemBasic_Material.itemBasic_Material"))
      {
      }
   };
   static FConstructorStatics ConstructorStatics;

   // Create dummy root scene component
   DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
   RootComponent = DummyRoot;

   // Create static mesh component
   ItemBasicMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("item_shape"));
   ItemBasicMesh->SetStaticMesh(ConstructorStatics.genericItemShape.Get());
   ItemBasicMesh->SetRelativeScale3D(FVector(1.f,1.f,1.f));
   ItemBasicMesh->SetRelativeLocation(FVector(0.f,0.f,0.f));
   ItemBasicMesh->SetMaterial(0, ConstructorStatics.genericItemMaterial.Get());
   ItemBasicMesh->AttachTo(DummyRoot);
   //ItemBasicMesh->SetSimulatePhysics(true);

   this->OnActorHit.AddDynamic(this, &AitemBasic::onHit);
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

   GEngine -> AddOnScreenDebugMessage( 0, 5.f, FColor::Blue, "Test" );

   spinWithQuaternion();
}

void AitemBasic::onHit(AActor *Self, AActor *neighbor, FVector NormalImpulse, const FHitResult &Hit)
{
   // If the hero touched me, I need to go into *HeroBag and "despawn"
   if(neighbor && (neighbor->GetActorLabel()).Contains( TEXT("Avatar"), ESearchCase::CaseSensitive, ESearchDir::FromEnd ) && !found){
      //(AAvatar*)Aneighbor->MyInventory = HeroBag;
      found = true;
      Self->SetActorLocation( FVector(0, 0, -1000) );
      ((Ainventory*)HeroBag)->push(neighbor->GetActorLabel());
   }

   /*
   int i=0;
   auto it = ((Ainventory*)HeroBag)->GetInventory()->CreateIterator();
   for( ; it; ++it){
      i++;
      GEngine->AddOnScreenDebugMessage(i++, 15.f, FColor::Green, it->Key);
   }
   */
   
   /*
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

void AitemBasic::spinWithQuaternion()
{
   /*       CRASHES MY COMPUTER
   FVector actorLocation, rotatePoint, rotateAxis, diff;
   FQuat q, nuuq;
   float angleInDegrees = 1;

   // What's the anchor for this rotation?
   rotatePoint = FVector(0, 0, 0);
   // What's the axis for this rotation? (normalized)
   rotateAxis = FVector(0, 1, 0);
   // Who am I rotating?
   actorLocation = this->GetActorLocation();
   // What's the current quaternion?
   q = this->GetActorQuat();

   // IMPLEMENT
   //    Move the object
   diff = actorLocation - rotatePoint;
   //    Make the change quaternion
   //    Move the anchor, relate it back to original
   actorLocation = diff.RotateAngleAxis(angleInDegrees, rotateAxis);
   actorLocation = actorLocation + rotatePoint;
   //    Use the quaternion
   q = FQuat(rotateAxis, angleInDegrees * 180.0 / 3.14159);
   nuuq = this->GetActorQuat() * q;
   this->SetActorLocationAndRotation(actorLocation, nuuq);
   */
}