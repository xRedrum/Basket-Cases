// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCAnimInstance.h"
#include "NPCCharacter.h"

void UNPCAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UNPCAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	IsGetFruit = false;
	if (!NPC)
	{
		NPC = Cast<ANPCCharacter>(GetOwningActor());
		return;
	}
}
