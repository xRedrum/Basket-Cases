// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "ApolloGameState.generated.h"

/**
 * 
 */

UCLASS()
class APOLLO_API AApolloGameState : public AGameState
{
	GENERATED_BODY()
public:
	AApolloGameState();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	int32 GetATeamScore();
	UFUNCTION(BlueprintCallable)
	int32 GetBTeamScore();

	void SetATeamScore(int32 NewScore);
	void SetBTeamScore(int32 NewScore);

	UFUNCTION(BlueprintCallable)
	int32 GetFruitScore(FString FruitTypeName);
	UFUNCTION(BlueprintCallable)
	void SetFruitScore(FString FruitTypeName, int32 NewScore);
	int32 GetOriginFruitScore(FString FruitTypeName);
	UFUNCTION(BlueprintCallable)
	FString GetTeamAName();
	UFUNCTION(BlueprintCallable)
	FString GetTeamBName();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CurrentRandomType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentScaler = 0;

	void GetAllFruitType(TArray<FString>& KeyArray);
	void AddFruitType(FString FruitTypeName);
	void AddFruitTypeWithValue(FString FruitTypeName, int32 NewScore);

	int32 GetTeamInfoNum(int32 TeamID);
	void AddTeamInfo(int32 TeamID, APlayerState* NewPlayerState);
	UFUNCTION(BlueprintCallable)
	bool FindPlayerInTeam(int32 TeamID, APlayerState* CurrentPlayerState);
	TArray<APlayerState*> GetAllPlayersInTeam(int32 TeamID);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ATeamName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString BTeamName;

protected:
	virtual void BeginPlay() override;

private:
	// Two team scores
	int32 ATeamScore;
	int32 BTeamScore;

	// Current fruits' corresponding scores info
	TMap<FString, int32> FruitScore;

	TMap<FString, int32> OriginFruitScore;

	class UWorld* World;

	TMap<int32, TArray<APlayerState*>> TeamInfo;
};
