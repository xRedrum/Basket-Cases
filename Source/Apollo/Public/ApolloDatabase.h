// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SQLiteDatabase.h"

/**
 * 
 */
class APOLLO_API ApolloDatabase
{
public:
	ApolloDatabase(FString Path, ESQLiteDatabaseOpenMode OpenMode);
	~ApolloDatabase();

	bool SaveTeamScore(FString TeamName, int32 TeamScore);
	bool QueryTeamExist(FString TeamName);
	bool UpdateTeamScore(FString TeamName, int32 NewScore);
	TMap<int32, TPair<FString, int32>> LoadHistoryScores();

private:
	FSQLiteDatabase* Database;
	FSQLitePreparedStatement ScoreSaveStatement;
	FSQLitePreparedStatement ScoreLoadStatement;
	FSQLitePreparedStatement QueryTeamStatement;
	FSQLitePreparedStatement UpdateTeamStatement;
};
