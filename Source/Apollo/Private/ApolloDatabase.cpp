// Fill out your copyright notice in the Description page of Project Settings.


#include "ApolloDatabase.h"

ApolloDatabase::ApolloDatabase(FString Path, ESQLiteDatabaseOpenMode OpenMode)
{
	Database = new FSQLiteDatabase();
	if (!Database->Open(*Path, OpenMode) || !Database->IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Fail to open apollo database: %s"), *Database->GetLastError());
	}
	// const TCHAR* SaveQuery = TEXT("insert into ApolloScores(score) values ($score)");
	const TCHAR* SaveQuery = TEXT("insert into ApolloTeamScores(name, score) values ($name, $score)");
	ScoreSaveStatement.Create(*Database, SaveQuery, ESQLitePreparedStatementFlags::Persistent);

	// const TCHAR* LoadQuery = TEXT("select score from ApolloScores order by score desc limit 10");
	const TCHAR* LoadQuery = TEXT("select * from ApolloTeamScores order by score desc limit 10");
	ScoreLoadStatement.Create(*Database, LoadQuery, ESQLitePreparedStatementFlags::Persistent);

	const TCHAR* TeamNameQuery = TEXT("select * from ApolloTeamScores where name = $name");
	QueryTeamStatement.Create(*Database, TeamNameQuery, ESQLitePreparedStatementFlags::Persistent);

	const TCHAR* TeamUpdateQuery = TEXT("update ApolloTeamScores set score = $score where name = $name");
	UpdateTeamStatement.Create(*Database, TeamUpdateQuery, ESQLitePreparedStatementFlags::Persistent);
}

ApolloDatabase::~ApolloDatabase()
{
	ScoreSaveStatement.Destroy();
	ScoreLoadStatement.Destroy();
	QueryTeamStatement.Destroy();
	UpdateTeamStatement.Destroy();
	if (!Database->Close())
	{
		UE_LOG(LogTemp, Warning, TEXT("Fail to close apollo database: %s"), *Database->GetLastError());
	}
	else
	{
		delete Database;
	}
}

bool ApolloDatabase::SaveTeamScore(FString TeamName, int32 TeamScore)
{
	if (Database->IsValid() && ScoreSaveStatement.IsValid())
	{
		ScoreSaveStatement.Reset();
		bool bSuccessBinding = true;
		bSuccessBinding = bSuccessBinding && ScoreSaveStatement.SetBindingValueByName(TEXT("$name"), TeamName);
		bSuccessBinding = bSuccessBinding && ScoreSaveStatement.SetBindingValueByName(TEXT("$score"), TeamScore);
		UE_LOG(LogTemp, Warning, TEXT("Saved team is: %s,  score is: %d"), *TeamName, TeamScore);
		if (!bSuccessBinding || !ScoreSaveStatement.Execute())
		{
			return false;
		}
	}
	return true;
}

bool ApolloDatabase::QueryTeamExist(FString TeamName)
{
	if (Database->IsValid() && QueryTeamStatement.IsValid())
	{
		QueryTeamStatement.Reset();
		bool bSuccessBinding = true;
		bSuccessBinding = bSuccessBinding && QueryTeamStatement.SetBindingValueByName(TEXT("$name"), TeamName);
		if(bSuccessBinding && QueryTeamStatement.Execute() && QueryTeamStatement.Step() == ESQLitePreparedStatementStepResult::Row)
		{
			return true;
		}
	}
	return false;
}

bool ApolloDatabase::UpdateTeamScore(FString TeamName, int32 NewScore)
{
	if (Database->IsValid() && UpdateTeamStatement.IsValid()) 
	{
		UpdateTeamStatement.Reset();
		bool bSuccessBinding = true;
		bSuccessBinding = bSuccessBinding && UpdateTeamStatement.SetBindingValueByName(TEXT("$score"), NewScore);
		bSuccessBinding = bSuccessBinding && UpdateTeamStatement.SetBindingValueByName(TEXT("$name"), TeamName);
		UE_LOG(LogTemp, Warning, TEXT("Updated team is: %s,  score is: %d"), *TeamName, NewScore);
		if (!bSuccessBinding || !UpdateTeamStatement.Execute())
		{
			return false;
		}
	}
	return true;
}

TMap<int32, TPair<FString, int32>> ApolloDatabase::LoadHistoryScores()
{
	//TMap<FString, int32> HistoryScoreBoard;
	TMap<int32, TPair<FString, int32>> HistoryScoreBoard;
	if (Database->IsValid() && ScoreLoadStatement.IsValid())
	{
		ScoreLoadStatement.Reset();
		if (ScoreLoadStatement.Execute())
		{
			while (ScoreLoadStatement.Step() == ESQLitePreparedStatementStepResult::Row) 
			{
				int32 CurrentId = 0;
				FString CurrentName;
				int32 CurrentScore = 0;
				ScoreLoadStatement.GetColumnValueByName(TEXT("id"), CurrentId);
				ScoreLoadStatement.GetColumnValueByName(TEXT("name"), CurrentName);
				ScoreLoadStatement.GetColumnValueByName(TEXT("score"), CurrentScore);
				HistoryScoreBoard.Add(CurrentId, {CurrentName, CurrentScore});
			}
		}
	}
	return HistoryScoreBoard;
}

