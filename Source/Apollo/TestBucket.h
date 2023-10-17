// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Food.h"
#include "TestBucket.generated.h"

UCLASS()
class APOLLO_API ATestBucket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestBucket();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void SpawnFood(int32 TeamID);

	UPROPERTY(EditAnywhere)
	TSubclassOf<AFood> AppleToSpawn;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AFood> BananaToSpawn;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AFood> OrangeToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SizeScalar = 1.0;
};
