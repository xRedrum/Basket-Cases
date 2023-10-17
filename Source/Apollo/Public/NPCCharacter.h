// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPCCharacter.generated.h"

UCLASS()
class APOLLO_API ANPCCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ANPCCharacter();

	virtual void Tick(float DeltaTime) override;

	struct FTimerHandle UpdateTimerHandle;

	bool IsGetFruit = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* CollisionBoxComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* DialogueWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NpcID;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void UpdateFruitValue();

private:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	class AApolloGameState* GameState;

	class UWorld* World;

	FString PreviousRandomType;
	int32 PreviousScaler;

	bool bIsPreviouslyMultiplying = false;
	int32 SecondsRemaining = 15;
	FRandomStream RandomStream;

	int32 MinInterval = 5;
	int32 MaxInterval = 10;
};
