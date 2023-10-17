// Copyright Epic Games, Inc. All Rights Reserved.

#include "ApolloGameMode.h"
#include "ApolloCharacter.h"
#include "ApolloGameState.h"
#include "ApolloPlayerState.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "ApolloDatabase.h"
#include "GenericPlatform/GenericPlatformProcess.h"
#include "Misc/Paths.h"

AApolloGameMode::AApolloGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ApolloCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	TimeRemaining = 180;
	WinnerTeam = -1;
}

void AApolloGameMode::BeginPlay()
{
	Super::BeginPlay();

	Controller = GetWorld()->GetFirstPlayerController();

	FInputModeGameOnly InputMode;
	Controller->SetInputMode(InputMode);
	Controller->bShowMouseCursor = false;

	FString ApolloSlnPathString = (FPaths::ProjectContentDir()) + "Database/sqlite-tools-win32-x86-3430100/acs-1-year-2015.sqlite";
	Database = new ApolloDatabase(ApolloSlnPathString, ESQLiteDatabaseOpenMode::ReadWrite);
	UE_LOG(LogTemp, Warning, TEXT("Current Database file path is: %s"), *ApolloSlnPathString);
}

void AApolloGameMode::EndPlay(const EEndPlayReason::Type EEndPlayReason)
{
	Super::EndPlay(EEndPlayReason);
	delete Database;
}

APlayerController* AApolloGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	APlayerController* NewPlayerController = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);

	if (!NewPlayerController)
	{
		return nullptr;
	}
	else
	{
		AApolloGameState* ApolloGameState = GetGameState<AApolloGameState>();

		AApolloPlayerState* CurrentPlayerState = Cast<AApolloPlayerState>(NewPlayerController->PlayerState);
		if (!ApolloGameState || !CurrentPlayerState)
		{
			UE_LOG(LogGameMode, Error, TEXT("PlayerState error"));
			return nullptr;
		}

		else
		{
			int32 MemberNumberForTeam1 = ApolloGameState->GetTeamInfoNum(1);
			int32 MemberNumberForTeam2 = ApolloGameState->GetTeamInfoNum(2);
			
			if (MemberNumberForTeam1 < 2)
			{
				ApolloGameState->AddTeamInfo(1, NewPlayerController->PlayerState);
				CurrentPlayerState->SetApolloPlayerID(ApolloGameState->GetTeamInfoNum(1));
				
			}
			else if(MemberNumberForTeam1 == 2 && MemberNumberForTeam2 < 2)
			{
				ApolloGameState->AddTeamInfo(2, NewPlayerController->PlayerState);
				CurrentPlayerState->SetApolloPlayerID(ApolloGameState->GetTeamInfoNum(2) + ApolloGameState->GetTeamInfoNum(1));
			}
			else
			{
				UE_LOG(LogGameMode, Error, TEXT("exceed player"));
			}
		}
	}

	return NewPlayerController;
}

TArray<int32> AApolloGameMode::GetAllPlayerScores()
{
	TArray<int32> AllPlayerScores;

	AApolloGameState* ApolloGameState = Cast<AApolloGameState>(GameState);
	if (ApolloGameState)
	{
		for (int32 TeamID : {1, 2})
		{
			TArray<APlayerState*> PlayersInTeam = ApolloGameState->GetAllPlayersInTeam(TeamID);

			for (APlayerState* Player : PlayersInTeam)
			{
				AApolloPlayerState* ApolloPlayerState = Cast<AApolloPlayerState>(Player);
				if (ApolloPlayerState)
				{
					AllPlayerScores.Add(ApolloPlayerState->GetPlayerScore());
				}
			}
		}
	}

	return AllPlayerScores;
}

TArray<int32> AApolloGameMode::GetSortedPlayerScores()
{
	TArray<int32> SortedPlayerScores = GetAllPlayerScores();

	SortedPlayerScores.Sort([](const int32& A, const int32& B)
		{
			return A > B;
		});

	return SortedPlayerScores;
}

TArray<int32> AApolloGameMode::GetSortedPlayerID() 
{
	TMultiMap<int32, int32> PlayerScores; 

	AApolloGameState* ApolloGameState = Cast<AApolloGameState>(GameState);
	if (ApolloGameState)
	{
		for (int32 TeamID : {1, 2})
		{
			TArray<APlayerState*> PlayersInTeam = ApolloGameState->GetAllPlayersInTeam(TeamID);

			for (APlayerState* Player : PlayersInTeam)
			{
				AApolloPlayerState* ApolloPlayerState = Cast<AApolloPlayerState>(Player);
				if (ApolloPlayerState)
				{
					int32 Score = ApolloPlayerState->GetPlayerScore();
					int32 PlayerID = ApolloPlayerState->GetApolloPlayerID();
					PlayerScores.Add(Score, PlayerID);
				}
			}
		}
	}

	TArray<int32> SortedPlayerIDs;
	PlayerScores.ValueSort([](const int32& A, const int32& B)
	{
			return B < A; 
	});

	for (const auto& Elem : PlayerScores)
	{
		SortedPlayerIDs.Add(Elem.Value);
	}

	return SortedPlayerIDs;
}

TArray<TArray<int32>> AApolloGameMode::PlayerBucketDetail()
{
	TArray<TArray<int32>> PlayerBucketDetailArray;
	AApolloGameState* ApolloGameState = Cast<AApolloGameState>(GameState);
	if (ApolloGameState)
	{
		for (int32 TeamID : {1, 2})
		{
			TArray<APlayerState*> PlayersInTeam = ApolloGameState->GetAllPlayersInTeam(TeamID);

			for (APlayerState* Player : PlayersInTeam)
			{
				AApolloPlayerState* ApolloPlayerState = Cast<AApolloPlayerState>(Player);
				if (ApolloPlayerState)
				{
					TArray<int32> EachPlayerBucket;
					EachPlayerBucket.Add(ApolloPlayerState->GetAppleCount());
					UE_LOG(LogTemp, Warning, TEXT("AppleCount: %d"), ApolloPlayerState->GetAppleCount());
					EachPlayerBucket.Add(ApolloPlayerState->GetBananaCount());
					EachPlayerBucket.Add(ApolloPlayerState->GetOrangeCount());

					PlayerBucketDetailArray.Add(EachPlayerBucket);
				}
			}
		}
	}

	return PlayerBucketDetailArray;
}

TArray<int32> AApolloGameMode::GetPlayerBucketDetail(int32 PlayerID)
{
	return PlayerBucketDetail()[PlayerID];
}

void AApolloGameMode::TrueStart()
{
	bIsTrueStart = true;
	//MainWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultMainWidget);
	//MainWidget->AddToViewport();
	GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle, this, &AApolloGameMode::CountDown, 1.0f, true);
}

bool AApolloGameMode::FirstTeamWinGame()
{
	bIsGameEnd = true;

	if (AApolloGameState* ApolloGameState = GetGameState<AApolloGameState>())
	{

		if (ApolloGameState->GetATeamScore() > ApolloGameState->GetBTeamScore())
		{
			return true;
			EndGame();
		}
		else if (ApolloGameState->GetATeamScore() == ApolloGameState->GetBTeamScore())
		{
			return DrawGame();
			EndGame();
		}
		else
		{
			return false;
			EndGame();
		}



	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Game State Does Not Exist"));
		return false;
	}
}

bool AApolloGameMode::SecondTeamWinGame()
{
	bIsGameEnd = true;

	if (AApolloGameState* ApolloGameState = GetGameState<AApolloGameState>())
	{
		if (ApolloGameState->GetATeamScore() > ApolloGameState->GetBTeamScore())
		{
			return false;
			EndGame();
		}
		else if (ApolloGameState->GetATeamScore() == ApolloGameState->GetBTeamScore())
		{
			return DrawGame();
			EndGame();
		}
		else
		{
			return true;
			EndGame();
		}


	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Game State Does Not Exist"));
		return false;
	}
}

bool AApolloGameMode::DrawGame()
{
	bIsGameEnd = true;
	return true;
}

bool AApolloGameMode::GetGameStatus()
{
	return bIsGameEnd;
}

void AApolloGameMode::EndGame()
{
	if (GetGameStatus())
	{
		if (DefaultTimeOutWidget && DefaultFirstTeamGameWinWidget && DefaultSecondTeamGameWinWidget && DefaultDrawGameWidget)
		{
			TimeOutWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultTimeOutWidget);
			TimeOutWidget->AddToViewport();

			Controller->bShowMouseCursor = true;
			FInputModeUIOnly InputMode;
			Controller->SetInputMode(InputMode);

			GetWorld()->GetTimerManager().SetTimer(TeamWinWidgetDelayTimerHandle, this, &AApolloGameMode::TeamWinWidget, 3.0f, false);

		}
	}
	else
	{
		//TO DO
	}
}

void AApolloGameMode::TeamWinWidget()
{
	TimeOutWidget->RemoveFromParent();

	if (FirstTeamWinGame() && !SecondTeamWinGame())
	{
		FirstTeamGameWinWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultFirstTeamGameWinWidget);
		FirstTeamGameWinWidget->AddToViewport();
		WinnerTeam = 1;
	}
	else if (FirstTeamWinGame() && SecondTeamWinGame())
	{
		DrawGameWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultDrawGameWidget);
		DrawGameWidget->AddToViewport();
		WinnerTeam = 0;
	}
	else
	{
		SecondTeamGameWinWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultSecondTeamGameWinWidget);
		SecondTeamGameWinWidget->AddToViewport();
		WinnerTeam = 2;
	}
	//GetWorld()->GetTimerManager().SetTimer(EvaluateWidgetDelayTimerHandle, this, &AApolloGameMode::ScoreEvaluateWidget, 3.0f, false);
	GetWorld()->GetTimerManager().SetTimer(EvaluateWidgetDelayTimerHandle, this, &AApolloGameMode::PlayEndGameCharacterAnimation, 1.0f, false);

}

void AApolloGameMode::PlayEndGameCharacterAnimation()
{
	if (FirstTeamGameWinWidget)
	{
		FirstTeamGameWinWidget->RemoveFromParent();
	}
	if (DrawGameWidget)
	{
		DrawGameWidget->RemoveFromParent();
	}
	if (SecondTeamGameWinWidget)
	{
		SecondTeamGameWinWidget->RemoveFromParent();
	}

	OnEndGame.Broadcast(WinnerTeam);

	//GetWorld()->GetTimerManager().SetTimer(EndGameCharacterAnimationTimerHandle, this, &AApolloGameMode::EnterInitialWidget, 2.0f, false);

	//GetWorld()->GetTimerManager().SetTimer(EvaluateWidgetDelayTimerHandle, this, &AApolloGameMode::ScoreEvaluateWidget, 3.0f, false);

	AApolloGameState* ApolloGameState = GetGameState<AApolloGameState>();
	if (ApolloGameState)
	{
		int32 ATeamScore = ApolloGameState->GetATeamScore();
		int32 BTeamScore = ApolloGameState->GetBTeamScore();

		ReadScoreFromDatabase();

		TArray<int32> ScoreBoard = GetScoreBoard();
		//MainWidget->RemoveFromParent();
		if (ScoreBoard.Num() <= 0) {

			GetWorld()->GetTimerManager().SetTimer(EvaluateWidgetDelayTimerHandle, this, &AApolloGameMode::EnterInitialWidget, 1.0f, false);
		}
		else if (ATeamScore <= ScoreBoard.Last() && BTeamScore <= ScoreBoard.Last())
		{
			GetWorld()->GetTimerManager().SetTimer(EvaluateWidgetDelayTimerHandle, this, &AApolloGameMode::ScoreEvaluateWidget, 3.0f, false);
		}
		else
		{
			GetWorld()->GetTimerManager().SetTimer(EvaluateWidgetDelayTimerHandle, this, &AApolloGameMode::EnterInitialWidget, 1.0f, false);
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Game State not found"));
	}

	//GetWorld()->GetTimerManager().SetTimer(EvaluateWidgetDelayTimerHandle, this, &AApolloGameMode::EnterInitialWidget, 1.0f, false);
}

void AApolloGameMode::EnterInitialWidget()
{
	
	EnterTeamInitialsWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultEnterTeamInitialsWidget);
	EnterTeamInitialsWidget->AddToViewport();
}

void AApolloGameMode::ScoreEvaluateWidget()
{
	if (EnterTeamInitialsWidget)
	{
		EnterTeamInitialsWidget->RemoveFromParent();
	}
	EvaluateWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultEvaluateWidget);
	EvaluateWidget->AddToViewport();

	GetWorld()->GetTimerManager().SetTimer(ScoreBoardWidgetDelayTimerHandle, this, &AApolloGameMode::ScoreBoardWidget, 3.0f, false);
}

void AApolloGameMode::ScoreBoardWidget()
{
	if (EvaluateWidget)
	{
		EvaluateWidget->RemoveFromParent();
	}
	TopTenScoreBoardWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultScoreBoardWidget);
	TopTenScoreBoardWidget->AddToViewport();
}

void AApolloGameMode::UpdateScoreWithTeamInitial()
{
	AApolloGameState* ApolloGameState = GetGameState<AApolloGameState>();
	if (ApolloGameState)
	{
		// Write current two team scores to database
		int32 ATeamScore = ApolloGameState->GetATeamScore();
		int32 BTeamScore = ApolloGameState->GetBTeamScore();
		FString ATeamName = ApolloGameState->GetTeamAName();
		FString BTeamName = ApolloGameState->GetTeamBName();
		UE_LOG(LogTemp, Warning, TEXT("TeamA Name is %s"), *ATeamName);

		Database->SaveTeamScore(ATeamName, ATeamScore);
		Database->SaveTeamScore(BTeamName, BTeamScore);

		// Read top 10 history team scores from database
		
		ReadScoreFromDatabase();

		//if (!HistoryScoreBoard.IsEmpty())
		//{
		//	HistoryScoreBoard.Empty();
		//}
		//TMap<FString, int32> TempMap = Database->LoadHistoryScores();
		//for (const TPair<FString, int32>& pair : TempMap)
		//{
		//	FString CurrentName = pair.Key;
		//	int32 CurrentScore = pair.Value;
		//	UE_LOG(LogTemp, Warning, TEXT("History score team name is: %s"), *CurrentName);
		//	UE_LOG(LogTemp, Warning, TEXT("History score is: %d"), CurrentScore);
		//	HistoryScoreBoard.Add(CurrentName, CurrentScore);
		//}
	}
}

void AApolloGameMode::ReadScoreFromDatabase()
{
	if (!HistoryScoreBoard.IsEmpty())
	{
		HistoryScoreBoard.Empty();
	}
	TMap<int32, TPair<FString, int32>> TempMap = Database->LoadHistoryScores();
	UE_LOG(LogTemp, Warning, TEXT("History score team score size is: %d"), TempMap.Num());
	for (const TPair<int32, TPair<FString, int32>>& pair : TempMap)
	{
		int32 CurrentId = pair.Key;
		FString CurrentName = pair.Value.Key;
		int32 CurrentScore = pair.Value.Value;
		UE_LOG(LogTemp, Warning, TEXT("History score team name is: %s"), *CurrentName);
		UE_LOG(LogTemp, Warning, TEXT("History score is: %d"), CurrentScore);
		HistoryScoreBoard.Add(CurrentId, {CurrentName, CurrentScore});
	}
}

bool AApolloGameMode::GetIsGameEnd()
{
	return bIsGameEnd;
}

bool AApolloGameMode::GetIsGameTrueStart()
{
	return bIsTrueStart;
}

void AApolloGameMode::CountDown()
{
	if (TimeRemaining > 0)
	{
		TimeRemaining--;
	}
	else
	{
		//AApolloGameState* ApolloGameState = GetGameState<AApolloGameState>();
		//if (ApolloGameState)
		//{
		//	// Write current two team scores to database
		//	int32 ATeamScore = ApolloGameState->GetATeamScore();
		//	int32 BTeamScore = ApolloGameState->GetBTeamScore();
		//	FString ATeamName = ApolloGameState->GetTeamAName();
		//	FString BTeamName = ApolloGameState->GetTeamBName();
		//	Database->SaveTeamScore(ATeamName, ATeamScore);
		//	Database->SaveTeamScore(BTeamName, BTeamScore);

		//	// Read top 10 history team scores from database
		//	if (!HistoryScoreBoard.IsEmpty())
		//	{
		//		HistoryScoreBoard.Empty();
		//	}
		//	TMap<FString, int32> TempMap = Database->LoadHistoryScores();
		//	for (const TPair<FString, int32>& pair : TempMap)
		//	{
		//		FString CurrentName = pair.Key;
		//		int32 CurrentScore = pair.Value;
		//		UE_LOG(LogTemp, Warning, TEXT("History score team name is: %s"), *CurrentName);
		//		UE_LOG(LogTemp, Warning, TEXT("History score is: %d"), CurrentScore);
		//		HistoryScoreBoard.Add(CurrentName, CurrentScore);
		//	}
		//}
		GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
		bIsGameEnd = true;
		bIsTrueStart = false;
		EndGame();
	}
}



TArray<int32> AApolloGameMode::GetScoreBoard()
{
	TArray<int32> TeamScoreArray;
	for (const TPair<int32, TPair<FString, int32>>& pair : HistoryScoreBoard)
	{
		int32 TeamScore = pair.Value.Value;
		TeamScoreArray.Add(TeamScore);
	}
	return TeamScoreArray;
}

TArray<FString> AApolloGameMode::GetScoreBoardNameField()
{
	TArray<FString> TeamNameArray;
	for (const TPair<int32, TPair<FString, int32>>& pair : HistoryScoreBoard)
	{
		FString TeamName = pair.Value.Key;
		TeamNameArray.Add(TeamName);
	}
	return TeamNameArray;
}
