// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ApolloUICloudActor.generated.h"

UCLASS()
class APOLLO_API AApolloUICloudActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AApolloUICloudActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	static bool Clicked;
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void SetClicked(bool boo);

	UFUNCTION(BlueprintCallable)
	bool GetClicked();

};
bool AApolloUICloudActor::Clicked = false;