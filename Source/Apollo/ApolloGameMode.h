// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ApolloGameState.h"
#include "ApolloGameMode.generated.h"


UCLASS(minimalapi)
class AApolloGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AApolloGameMode();
	
	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	UFUNCTION(BlueprintCallable, Category = "Scores")
	TArray<int32> GetAllPlayerScores();

	UFUNCTION(BlueprintCallable, Category = "Scores")
	TArray<int32> GetSortedPlayerScores();

	UFUNCTION(BlueprintCallable, Category = "Scores")
	TArray<int32> GetSortedPlayerID();

	UFUNCTION(BlueprintCallable, Category = "Bucket")
	TArray<int32> GetPlayerBucketDetail(int32 PlayerID);

	UFUNCTION(BlueprintCallable)
	void TrueStart();

	UFUNCTION(BlueprintCallable)
	bool FirstTeamWinGame();

	UFUNCTION(BlueprintCallable)
	bool SecondTeamWinGame();

	UFUNCTION(BlueprintCallable)
	bool DrawGame();

	UFUNCTION(BlueprintCallable)
	bool GetGameStatus();

	UFUNCTION(BlueprintCallable)
	void EndGame();

	UFUNCTION()
	void CountDown();

	UFUNCTION(BlueprintCallable)
	TArray<int32> GetScoreBoard();

	UFUNCTION(BlueprintCallable)
	TArray<FString> GetScoreBoardNameField();

	TArray<TArray<int32>> PlayerBucketDetail();

	UFUNCTION(BlueprintCallable, Category = "Scores")
	void UpdateScoreWithTeamInitial();

	UFUNCTION(BlueprintCallable)
	void ReadScoreFromDatabase();

	UFUNCTION(BlueprintCallable)
	bool GetIsGameEnd();

	UFUNCTION(BlueprintCallable)
	bool GetIsGameTrueStart();

	UFUNCTION(BlueprintCallable)
	void ScoreEvaluateWidget();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEndGameCharacterAnimationDelegate, int32, Value);

    UPROPERTY(BlueprintAssignable, Category = "Your Category")
	FEndGameCharacterAnimationDelegate OnEndGame;

	void TeamWinWidget();

	void PlayEndGameCharacterAnimation();

	void EnterInitialWidget();

	void ScoreBoardWidget();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<UUserWidget> DefaultTimeOutWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<UUserWidget> DefaultFirstTeamGameWinWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<UUserWidget> DefaultSecondTeamGameWinWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<UUserWidget> DefaultDrawGameWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<UUserWidget> DefaultEnterTeamInitialsWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<UUserWidget> DefaultEvaluateWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<UUserWidget> DefaultScoreBoardWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	UUserWidget* TimeOutWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	UUserWidget* FirstTeamGameWinWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	UUserWidget* SecondTeamGameWinWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	UUserWidget* DrawGameWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	UUserWidget* EnterTeamInitialsWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	UUserWidget* EvaluateWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	UUserWidget* TopTenScoreBoardWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game")
	int32 TimeRemaining;

	TMap<int32, TPair<FString, int32>> HistoryScoreBoard;

	FTimerHandle CountdownTimerHandle;

	FTimerHandle TeamWinWidgetDelayTimerHandle;

	FTimerHandle EvaluateWidgetDelayTimerHandle;

	FTimerHandle EndGameCharacterAnimationTimerHandle;

	FTimerHandle ScoreBoardWidgetDelayTimerHandle;

	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EEndPlayReason) override;

private:
	UPROPERTY()
	APlayerController* Controller;
	bool bIsTrueStart;
	bool bIsGameEnd;
	class ApolloDatabase* Database;
	int32 WinnerTeam;
};



