// Fill out your copyright notice in the Description page of Project Settings.

#include "NPCCharacter.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "ApolloGameState.h"
#include "..\ApolloGameMode.h"
#include "..\ApolloPlayerState.h"
#include "ApolloFruitContainer.h"
#include "Components/WidgetComponent.h"

ANPCCharacter::ANPCCharacter()
{
	CollisionBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBoxComp->SetupAttachment(GetRootComponent());
	DialogueWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Dialogue Widget"));
	DialogueWidget->SetupAttachment(GetRootComponent());
	PreviousScaler = 0;
	RandomStream=FRandomStream(42);
}

void ANPCCharacter::BeginPlay()
{
	Super::BeginPlay();
	CollisionBoxComp->OnComponentBeginOverlap.AddDynamic(this, &ANPCCharacter::OnBoxBeginOverlap);
	World = GetWorld();
	if (World)
	{
		World->GetTimerManager().SetTimer(UpdateTimerHandle, this, &ANPCCharacter::UpdateFruitValue, 1, true);
	}
}

void ANPCCharacter::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* OtherPawn = Cast<APawn>(OtherActor);

	AApolloGameMode* GameMode = Cast<AApolloGameMode>(World->GetAuthGameMode());

	if (OtherPawn && OtherActor->ActorHasTag(FName("ApolloCharacter")))
	{
		APlayerState* PawnPlayerState = OtherPawn->GetPlayerState();
		AApolloPlayerState* CurrentPlayerState = Cast<AApolloPlayerState>(PawnPlayerState);
		if (CurrentPlayerState)
		{
			int32 CurrentPlayerScore = CurrentPlayerState->GetScore();
			AGameStateBase* baseState = World->GetAuthGameMode()->GameState;
			if (baseState)
			{
				GameState = Cast<AApolloGameState>(baseState);

				if (GameState->FindPlayerInTeam(1, CurrentPlayerState))
				{
					UE_LOG(LogTemp, Warning, TEXT("This player's team id: 1"));
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("This player's team id: 2"));
				}

				if (GameState && ((GameState->FindPlayerInTeam(1, CurrentPlayerState) == true && NpcID == 2) ||
					(GameState->FindPlayerInTeam(2, CurrentPlayerState) == true && NpcID == 1)))
				{
					int32 AppleNum = CurrentPlayerState->GetAppleCount();
					int32 BananaNum = CurrentPlayerState->GetBananaCount();
					int32 OrangeNum = CurrentPlayerState->GetOrangeCount();
					UE_LOG(LogTemp, Warning, TEXT("Apple count is: %d, Banana count is: %d, Orange count is: %d"), AppleNum, BananaNum, OrangeNum);

					int32 AppleValue = GameState->GetFruitScore(TEXT("Apple"));
					int32 BananaValue = GameState->GetFruitScore(TEXT("Banana"));
					int32 OrangeValue = GameState->GetFruitScore(TEXT("Orange"));
					UE_LOG(LogTemp, Warning, TEXT("Apple value is: %d, Banana value is: %d, Orange value is: %d"), AppleValue, BananaValue, OrangeValue);

					int32 NewPlayerScore = AppleNum * AppleValue + BananaNum * BananaValue + OrangeNum * OrangeValue;
					UE_LOG(LogTemp, Warning, TEXT("New Player score is: %d"), NewPlayerScore);
					if (GameMode->GetIsGameTrueStart() && !GameMode->GetIsGameEnd())
					{
						CurrentPlayerState->SetPlayerScore(CurrentPlayerState->GetPlayerScore() + NewPlayerScore);

						if (GameState->FindPlayerInTeam(1, CurrentPlayerState))
						{
							GameState->SetATeamScore(GameState->GetATeamScore() + NewPlayerScore);
							UE_LOG(LogTemp, Warning, TEXT("Team A Score update: %d"), GameState->GetATeamScore());
						}
						else if (GameState->FindPlayerInTeam(2, CurrentPlayerState))
						{
							GameState->SetBTeamScore(GameState->GetBTeamScore() + NewPlayerScore);
							UE_LOG(LogTemp, Warning, TEXT("Team B Score update: %d"), GameState->GetBTeamScore());
						}
					}
					
					OtherPawn->FindComponentByClass<UApolloFruitContainer>()->DestroyFruit();
				}
			}
		}
	}
	
}

void ANPCCharacter::UpdateFruitValue()
{
	if (World) 
	{
		AGameStateBase* baseState = World->GetAuthGameMode()->GameState;
		if (baseState)
		{
			GameState = Cast<AApolloGameState>(baseState);
			if (GameState)
			{
				if (--SecondsRemaining == 0)
				{
					SecondsRemaining = RandomStream.RandRange(MinInterval, MaxInterval);
					
					// Get random modifier
					int MaxValue = 5;
					int MinValue = 2;
					int RandomValue = (std::rand() % (MaxValue - MinValue + 1)) + MinValue;
	
					// Get random type
					TArray<FString> FruitType;
					GameState->GetAllFruitType(FruitType);
					int RandomIndex = (std::rand() % FruitType.Num());
					FString RandomFruitType = !bIsPreviouslyMultiplying ? FruitType[RandomIndex] : FString();
	
					//  Reset previous modified fruit's value
					if (PreviousRandomType.Len() > 0)
					{
						int32 OriginValue = GameState->GetOriginFruitScore(PreviousRandomType);
						GameState->SetFruitScore(PreviousRandomType, OriginValue);
						//UE_LOG(LogTemp, Warning, TEXT("Reset fruit value: %d"), OriginValue);
					}
	
					if (!bIsPreviouslyMultiplying)
					{
						PreviousRandomType = RandomFruitType;
						PreviousScaler = RandomValue;
					}
	
					GameState->CurrentRandomType = RandomFruitType;
					GameState->CurrentScaler = RandomValue;
					// PreviousValue = GameState->GetFruitScore(RandomFruitType);
					

					if (!bIsPreviouslyMultiplying)
					{
						GameState->SetFruitScore(RandomFruitType, GameState->GetFruitScore(RandomFruitType) * RandomValue);
					}
					//UE_LOG(LogTemp, Warning, TEXT("New fruit value: %d * %d"), GameState->GetFruitScore(RandomFruitType), RandomValue);

					bIsPreviouslyMultiplying = !bIsPreviouslyMultiplying;
				}
			}
		}
	}
}

void ANPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANPCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
