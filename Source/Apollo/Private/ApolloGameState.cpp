// Fill out your copyright notice in the Description page of Project Settings.

#include "ApolloGameState.h"
#include "Engine/World.h"
#include "..\Public\ApolloGameState.h"

AApolloGameState::AApolloGameState()
{
	ATeamScore = 0;
	BTeamScore = 0;
	FruitScore.Add(TEXT("Apple"), 1);
	FruitScore.Add(TEXT("Banana"), 2);
	FruitScore.Add(TEXT("Orange"), 3);
	OriginFruitScore.Add(TEXT("Apple"), 1);
	OriginFruitScore.Add(TEXT("Banana"), 2);
	OriginFruitScore.Add(TEXT("Orange"), 3);
	// FruitScore.Add(TEXT("Pizza"), 4);
	TeamInfo.Add(1, {});
	TeamInfo.Add(2, {});
	ATeamName = TEXT("AAA");
	BTeamName = TEXT("BBB");
}

void AApolloGameState::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;
}

void AApolloGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

int32 AApolloGameState::GetATeamScore()
{
	return ATeamScore;
}

int32 AApolloGameState::GetBTeamScore()
{
	return BTeamScore;
}

void AApolloGameState::SetATeamScore(int32 NewScore)
{
	ATeamScore = NewScore;
}

void AApolloGameState::SetBTeamScore(int32 NewScore)
{
	BTeamScore = NewScore;
}

int32 AApolloGameState::GetFruitScore(FString FruitTypeName)
{
	return FruitScore[FruitTypeName];
}

void AApolloGameState::SetFruitScore(FString FruitTypeName, int32 NewScore)
{
	FruitScore[FruitTypeName] = NewScore;
}

int32 AApolloGameState::GetOriginFruitScore(FString FruitTypeName)
{
	return OriginFruitScore[FruitTypeName];
}

void AApolloGameState::GetAllFruitType(TArray<FString>& KeyArray)
{
	FruitScore.GetKeys(KeyArray);
}

void AApolloGameState::AddFruitType(FString FruitTypeName)
{
	FruitScore.Add(FruitTypeName, 1);
}

void AApolloGameState::AddFruitTypeWithValue(FString FruitTypeName, int32 NewScore)
{
	FruitScore.Add(FruitTypeName, NewScore);
}

int32 AApolloGameState::GetTeamInfoNum(int32 TeamID)
{
	return TeamInfo[TeamID].Num();
}

void AApolloGameState::AddTeamInfo(int32 TeamID, APlayerState* NewPlayerState)
{
	TeamInfo[TeamID].Add(NewPlayerState);
}

bool AApolloGameState::FindPlayerInTeam(int32 TeamID, APlayerState* CurrentPlayerState)
{
	if (TeamInfo.Contains(TeamID) && TeamInfo[TeamID].Find(CurrentPlayerState) != INDEX_NONE){
		return true;
	}
	return false;
}

TArray<APlayerState*> AApolloGameState::GetAllPlayersInTeam(int32 TeamID)
{
	return TeamInfo[TeamID];
}

FString AApolloGameState::GetTeamAName()
{
	return ATeamName;
}

FString AApolloGameState::GetTeamBName()
{
	return BTeamName;
}