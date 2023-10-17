// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NPCAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class APOLLO_API UNPCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class ANPCCharacter* NPC;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsGetFruit = false;

	struct FTimerHandle YawnTimeHandle;
};
