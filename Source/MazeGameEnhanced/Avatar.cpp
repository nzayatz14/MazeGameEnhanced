// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeGameEnhanced.h"
#include "Avatar.h"

#include "inventory.h"
#include "itemBasic.h"
#include "itemsSpawning.h"
#include "Maze.h"
#include "AvatarGameMode.h"

//Ainventory *HeroBag;

// Sets default values
AAvatar::AAvatar()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    //PrimaryActorTick.bCanEverTick = true;
    
    HUDOn = true;
}

// Called when the game starts or when spawned
void AAvatar::BeginPlay()
{
    Super::BeginPlay();
    
    this->OnActorHit.AddDynamic(this, &AAvatar::onHit);
    //Create a bag somewhere for the Hero
    HeroBag = GetWorld()->SpawnActor<Ainventory>( FVector(-500, -500.f, -5000.f), FRotator(0,0,0) );
}

void AAvatar::ToggleInventory()
{
    
    HUDOn = (!HUDOn);
}

void AAvatar::onHit(AActor *Self, AActor *neighbor, FVector NormalImpulse, const FHitResult &Hit)
{
  
    int row, col;
    FVector *AllTheItems;
    FVector2D MazeDimensions;
    // If the hero touched an item, drop it into his inventory and set it to found
    if(neighbor && (neighbor->GetActorLabel()).Contains( TEXT("itemBasic"), ESearchCase::CaseSensitive, ESearchDir::FromEnd )) {
        if(! (((AitemBasic*)neighbor)->found) ){
            ((AitemBasic*)neighbor)->found = true;
            row = ((AitemBasic*)neighbor)->GetMazeLocation().X;
            col = ((AitemBasic*)neighbor)->GetMazeLocation().Y;
            TActorIterator<AMaze> ActorItr =TActorIterator<AMaze>(GetWorld());
            if(ActorItr){
                AllTheItems = ActorItr->GetAllTheItems();
                MazeDimensions = ActorItr->GetMazeDimensions();
                for(int i=0; i< ((MazeDimensions.X>MazeDimensions.Y)?MazeDimensions.X-2:MazeDimensions.Y-2) ; i++){
                    if((int)(AllTheItems[i].X) == row && (int)(AllTheItems[i].Y) == col )
                        AllTheItems[i].Z = 1;
                }
            }
            neighbor->SetActorLocation( FVector(0, 0, -1000) );
            //increment itemBasic in Hero's Bag
            switch(((AitemBasic*)neighbor)->itemType){
                case 'A':
                    HeroBag->push("Pill");
                    Pill = true;
                    break;
                case 'B':
                    HeroBag->push("Pyramid");
                    Pill = false;
                    break;
                case 'C':
                    HeroBag->push("Macaroni");
                    Pill = false;
                    break;
                case 'D':
                    HeroBag->push("Moldy Cheese");
                    Pill= false;
                    break;
                default:
                    HeroBag->push("Trash");
                    Pill=false;
                    break;
            }
        }
        //check to see if all items have been found
        TActorIterator<AitemsSpawning> ActorItrItems =TActorIterator<AitemsSpawning>(GetWorld());
        if(ActorItrItems){
            if(ActorItrItems->allItemsFound() && !hasAllItems){
                hasAllItems = true;
                
                TActorIterator<AMaze> ActorItrMaze =TActorIterator<AMaze>(GetWorld());
                if(ActorItrMaze){
                    ActorItrMaze->openExit();
                }
            }
        }
    }

}

// Called every frame
void AAvatar::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    
    //check for the win if the user has all of the items and hasn't won
    if(hasAllItems && !hasWon){
        
        //move player start to that location
        TActorIterator<AAvatarGameMode> ActorItr =TActorIterator<AAvatarGameMode>(GetWorld());
        
        if (ActorItr) {
            
            hasWon = ActorItr->checkForWin(hasWon, this->GetActorLocation());
        }
    }
    
}


// Called to bind functionality to input
void AAvatar::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
    //Super::SetupPlayerInputComponent(InputComponent);
    check(InputComponent);
    InputComponent->BindAxis("Forward", this, &AAvatar::MoveForward);
    InputComponent->BindAxis("Strafe", this, &AAvatar::MoveRight);
    InputComponent->BindAxis("Yaw", this, &AAvatar::Yaw);
    InputComponent->BindAxis("Pitch", this, &AAvatar::Pitch);
    InputComponent->BindAction("Inventory",IE_Pressed, this, &AAvatar::ToggleInventory);
    InputComponent->BindAction("Jump", IE_Pressed, this, &AAvatar::OnStartJump);
    InputComponent->BindAction("Jump", IE_Released, this, &AAvatar::OnStopJump);
    
}


void AAvatar::MoveForward(float amount)
{
    if(Controller && amount && !hasWon && !hasLost)
    {
        FVector fwd = GetActorForwardVector();
        AddMovementInput (fwd, amount);
    }
}


void AAvatar::MoveRight(float amount)
{
    if(Controller && amount && !hasWon && !hasLost)
    {
        FVector fwd = GetActorRightVector();
        AddMovementInput (fwd, amount);
    }
}


void AAvatar::Yaw(float amount)
{
    
    if (!hasWon && !hasLost){
        AddControllerYawInput(200.f * amount * GetWorld()->GetDeltaSeconds());
    }
}


void AAvatar::Pitch(float amount)
{
    if (!hasWon && !hasLost){
        AddControllerPitchInput(-200.f * amount * GetWorld()->GetDeltaSeconds());
    }
}


void AAvatar::OnStartJump()
{
    bPressedJump = true;
    
}


void AAvatar::OnStopJump()
{
    bPressedJump = false;
}




