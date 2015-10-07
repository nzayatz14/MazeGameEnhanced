// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeGameEnhanced.h"
#include "Avatar.h"


// Sets default values
AAvatar::AAvatar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
}

// Called when the game starts or when spawned
void AAvatar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAvatar::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AAvatar::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	//Super::SetupPlayerInputComponent(InputComponent);
    check(InputComponent);
    InputComponent->BindAxis("Forward", this, &AAvatar::MoveForward);
    InputComponent->BindAxis("Strafe", this, &AAvatar::MoveRight);
    InputComponent->BindAxis("Yaw", this, &AAvatar::Yaw);
    InputComponent->BindAction("Inventory",IE_Pressed, this, &AAvatar::ToggleInventory);
}
void AAvatar::MoveForward(float amount)
{
    if(Controller && amount)
    {
        FVector fwd = GetActorForwardVector();
        AddMovementInput (fwd, amount);
    }
}


void AAvatar::MoveRight(float amount)
{
    if(Controller && amount)
    {
        FVector fwd = GetActorRightVector();
        AddMovementInput (fwd, amount);
    }
}

void AAvatar::Yaw(float amount)
{
    
    AddControllerYawInput(200.f * amount * GetWorld()->GetDeltaSeconds());
    
}

void AAvatar::ToggleInventory()
{
    if(GEngine)
        GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Red, "Inventory ..");
}

