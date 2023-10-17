// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ApolloPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class APOLLO_API AApolloPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
    AApolloPlayerState();

    //Current Player Score
    UFUNCTION(BlueprintCallable, Category = "Player State")
    int32 GetPlayerScore();

    UFUNCTION(BlueprintCallable, Category = "Player State")
    void SetPlayerScore(int32 NewPlayerScore);

    UFUNCTION(BlueprintCallable, Category = "Player State")
    int32 GetAppleCount();

    UFUNCTION(BlueprintCallable, Category = "Player State")
    void SetAppleCount(int32 NewAppleCount);

    UFUNCTION(BlueprintCallable, Category = "Player State")
    int32 GetBananaCount();

    UFUNCTION(BlueprintCallable, Category = "Player State")
    void SetBananaCount(int32 NewBananaCount);

    UFUNCTION(BlueprintCallable, Category = "Player State")
    int32 GetOrangeCount();

    UFUNCTION(BlueprintCallable, Category = "Player State")
    void SetOrangeCount(int32 NewOrangeCount);

    UFUNCTION(BlueprintCallable, Category = "Player State")
    int32 GetFruitCount();

    UFUNCTION(BlueprintCallable, Category = "Player State")
    int32 GetApolloPlayerID();

	UFUNCTION(BlueprintCallable, Category = "Player State")
	void SetApolloPlayerID(int32 CurrentID);

private:
    UPROPERTY(VisibleAnywhere, Category = "Player State")
    int32 PlayerScore;

    UPROPERTY(VisibleAnywhere, Category = "Player State")
    int AppleCount;

    UPROPERTY(VisibleAnywhere, Category = "Player State")
    int BananaCount;

    UPROPERTY(VisibleAnywhere, Category = "Player State")
    int OrangeCount;

    UPROPERTY(VisibleAnywhere, Category = "Player State")
    int ApolloPlayerID;

};
