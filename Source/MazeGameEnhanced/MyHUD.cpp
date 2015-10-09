// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeGameEnhanced.h"
#include "MyHUD.h"

#include "AvatarGameMode.h"
#include "Avatar.h"
#include "inventory.h"
#include "Maze.h"
#include "Wall.h"

AMyHUD::AMyHUD(const class FObjectInitializer &PCIP):Super(PCIP)
{
   /* Setup the font. Engine has these fonts
         Roboto
         RobotoDistanceField
         RobotoTiny
         SmallFont
         TinyFont
   */
   static ConstructorHelpers::FObjectFinder<UFont>HUDFontOb(TEXT("/Engine/EngineFonts/Roboto"));
   HUDFont = HUDFontOb.Object;
}

void AMyHUD::DrawHUD()
{
   // Get the screen size
   FVector2D ScreenSize = FVector2D(Canvas->SizeX, Canvas->SizeY);
   FVector2D InventoryTextSize, mazeDimensions;
   FString InventoryLine;
   bool *MyWalls;
   FVector *AllTheItems;
   int i;
   GetTextSize(TEXT("|"), InventoryTextSize.X, InventoryTextSize.Y, HUDFont);
   // Get the character and his inventory
   AAvatar *MyToon = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(this,0));
   TMap<FString, int> ToonInventory = MyToon->HeroBag->GetInventory();
   auto B = ToonInventory.CreateIterator();

   // call the original DrawHUD()
   Super::DrawHUD();

   i=0;
   // If the character wants to see his inventory, print it all
   if(MyToon->HUDOn){
      for( ; B; ++B){
         InventoryLine = B->Key + " : " + FString::FromInt(B->Value);
         DrawText(InventoryLine, FColor::Green, 50, (i++)*InventoryTextSize.Y+50, HUDFont);
      }
   }

   // Draw the mini-map
   TActorIterator<AMaze> ActorItr =TActorIterator<AMaze>(GetWorld());
   if(ActorItr){
      MyWalls = ActorItr->GetAllAWall();
      AllTheItems = ActorItr->GetAllTheItems();
      mazeDimensions  = ActorItr->GetMazeDimensions();
      DrawMinimap(MyWalls, AllTheItems, mazeDimensions, ScreenSize);
   }
}

// Credit: https://wiki.unrealengine.com/HUD,_Canvas,_Code_Sample_of_800%2B_Lines,_Create_Buttons_%26_Draw_Materials#Drawing_Images.2FTextures.2FMaterials
void AMyHUD::DrawLine(FVector Start, FVector End, FLinearColor TheColor, float Thick)
{
   FCanvasLineItem NewLine(Start,End);
   NewLine.SetColor(TheColor);
   NewLine.LineThickness = Thick;
   Canvas->DrawItem(NewLine);
}

// Credit: https://wiki.unrealengine.com/HUD,_Canvas,_Code_Sample_of_800%2B_Lines,_Create_Buttons_%26_Draw_Materials#Drawing_Images.2FTextures.2FMaterials
void AMyHUD::DrawRectangle( float X, float Y, float Width, float Height, const FLinearColor& Color)
{
   FCanvasTileItem RectItem( FVector2D(X, Y), FVector2D( Width, Height ), Color);
   RectItem.BlendMode = SE_BLEND_Translucent;
   Canvas->DrawItem(RectItem);
}

void AMyHUD::DrawMinimap(bool *MyWalls, FVector *AllItems, FVector2D mazeDimensions, FVector2D ScreenSize)
{
   FColor wallColor = FColor::White;
   FColor itemColor = FColor::Green;
   FColor bgColor   = FColor(0,0,0,200);
   float LineWidth = 3;
   int j;
   float LineLength = (ScreenSize.X < ScreenSize.Y) ? ScreenSize.X : ScreenSize.Y;
   int rows, cols;
   rows = (int)mazeDimensions.X;
   cols = (int)mazeDimensions.Y;
   int itemCount = (rows > cols) ? rows-2 : cols-2;
   int numBorders = rows*(cols+1) + cols*(rows+1);
   // the minimap takes 1/4 of the smaller dimension of the screen
   LineLength = LineLength/4.0;
   FVector topLeftOfMaze = FVector( ScreenSize.X - LineLength - 150, ScreenSize.Y - LineLength - 150 , 0);
   // each line is 1/largerXorY 1/4 of the screen
   LineLength = LineLength / ((mazeDimensions.X > mazeDimensions.Y) ? mazeDimensions.X : mazeDimensions.Y);

   DrawRectangle(topLeftOfMaze.X, topLeftOfMaze.Y, cols*LineLength, rows*LineLength, bgColor);

   //draw the walls
   for(int i=0; i<numBorders; i++)
      if( MyWalls[i] ){
         if( i < rows*(cols+1) ){
            DrawLine(
               FVector( LineLength*(i/rows), LineLength*((i%rows)+1),   0 )   + topLeftOfMaze, 
               FVector( LineLength*(i/rows),     LineLength*(i%rows),   0 )   + topLeftOfMaze, 
               wallColor, LineWidth
            );
         }
         else{
            j = i-(rows*(cols+1));
            DrawLine(
               FVector( LineLength*(j%cols),       LineLength*(j/cols), 0 )   + topLeftOfMaze, 
               FVector( LineLength*((j%cols)+1),   LineLength*(j/cols), 0 )   + topLeftOfMaze, 
               wallColor, LineWidth
            );
         }
      }

   //draw the items with locations in FVector2D AllItems[0..itemCount]
   for(int i=0; i<itemCount; i++){
      if(AllItems[i].Z == 0)
         DrawLine(
            FVector( LineLength*(AllItems[i].Y+.5)-5,   LineLength*(AllItems[i].X+.5)-5, 0 )   + topLeftOfMaze, 
            FVector( LineLength*(AllItems[i].Y+.5)+5,   LineLength*(AllItems[i].X+.5)+5, 0 )   + topLeftOfMaze, 
            itemColor, LineWidth
         );
   }
   DrawActor(ScreenSize, cols, rows, LineLength, topLeftOfMaze);
}

void AMyHUD::DrawActor(FVector2D ScreenSize, int cols, int rows, float LineLength, FVector topLeftOfMaze )
{
   float largerDimension = (rows>cols)?rows:cols;
   float LineWidth = 3;
   float minX, minY, maxX, maxY;
   FVector topPoint, leftPoint, rightPoint;
   minX = topLeftOfMaze.X;
   minY = topLeftOfMaze.Y;
   maxX = minX + cols*LineLength;
   maxY = minY + rows*LineLength;
   FVector2D mazeWallLocationMax;
   TActorIterator<AMaze> ActorItr = TActorIterator<AMaze>(GetWorld());
   if(ActorItr)
      mazeWallLocationMax = ActorItr->GetMazeMeshMaxs();
   FVector A = FVector(minX, minY, 0);
   FVector B = FVector(maxX, maxY, 0);
   FVector actorLoc = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(this,0))->GetActorLocation();
   FVector actorForward = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(this,0))->GetActorForwardVector();
   // peak of the actor location, create a tringle from it going away from the actorForward
   FVector actorMapLocation = FVector(
      minX + (maxX-minX)*(actorLoc.X/(mazeWallLocationMax.X*(largerDimension/rows))),
      minY + (maxY-minY)*(actorLoc.Y/(mazeWallLocationMax.Y*(largerDimension/cols))),
      0
   );
   
   topPoint = actorMapLocation;
   leftPoint =  (-1.0 * actorForward) + (FVector(actorForward.Y, -actorForward.X, 0) * -.4);
   leftPoint.Normalize();
   leftPoint = 15*leftPoint + actorMapLocation;
   rightPoint =  (-1.0 * actorForward) + (FVector(-actorForward.Y, actorForward.X, 0) * -.4);
   rightPoint.Normalize();
   rightPoint = 15*rightPoint + actorMapLocation;
   topPoint    += actorForward*7;
   leftPoint   += actorForward*7;
   rightPoint  += actorForward*7;
   topPoint.Z = leftPoint.Z = rightPoint.Z = 0;
   DrawLine(topPoint, leftPoint, FColor::Red, LineWidth);
   DrawLine(topPoint, rightPoint, FColor::Red, LineWidth);
   DrawLine(leftPoint, rightPoint, FColor::Red, LineWidth);
   //GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Black, rightPoint.ToString());
}