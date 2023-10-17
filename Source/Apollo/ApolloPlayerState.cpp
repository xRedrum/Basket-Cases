// Fill out your copyright notice in the Description page of Project Settings.


#include "ApolloPlayerState.h"

AApolloPlayerState::AApolloPlayerState()
{
    PlayerScore = 0;
    AppleCount = 0;
    BananaCount = 0;
    OrangeCount = 0;
}

int32 AApolloPlayerState::GetPlayerScore()
{
    return PlayerScore;
}

void AApolloPlayerState::SetPlayerScore(int32 NewPlayerScore)
{
    PlayerScore = NewPlayerScore;
}

int32 AApolloPlayerState::GetAppleCount()
{
    return AppleCount;
}

void AApolloPlayerState::SetAppleCount(int NewAppleCount)
{
    AppleCount = FMath::Clamp(NewAppleCount, 0, 100000);
}

int32 AApolloPlayerState::GetBananaCount()
{
    return BananaCount;
}

void AApolloPlayerState::SetBananaCount(int32 NewBananaCount)
{
    BananaCount = FMath::Clamp(NewBananaCount, 0, 100000);
}

int32 AApolloPlayerState::GetOrangeCount()
{
    return OrangeCount;
}

void AApolloPlayerState::SetOrangeCount(int32 NewOrangeCount)
{
    OrangeCount = FMath::Clamp(NewOrangeCount, 0, 100000);
}

int32 AApolloPlayerState::GetFruitCount()
{
    return GetAppleCount() + GetBananaCount() + GetOrangeCount();
}

int32 AApolloPlayerState::GetApolloPlayerID()
{
    return ApolloPlayerID;
}

void AApolloPlayerState::SetApolloPlayerID(int32 CurrentID)
{
    ApolloPlayerID = CurrentID;
    UE_LOG(LogTemp, Warning, TEXT("Yulan Current Player ID is: %d"), ApolloPlayerID);
}

