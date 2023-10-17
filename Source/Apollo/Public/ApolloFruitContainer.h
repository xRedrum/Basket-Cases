// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "ApolloFruitContainer.generated.h"

/**
 * 
 */
UCLASS()
class APOLLO_API UApolloFruitContainer : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UApolloFruitContainer();

	UFUNCTION(BlueprintPure, Category = "Apollo")
	int32 GetFruitCount();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
    UBoxComponent* BoxCollisionComponent;

	void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, Category = "Apollo")
	void DestroyFruit();
	
};
