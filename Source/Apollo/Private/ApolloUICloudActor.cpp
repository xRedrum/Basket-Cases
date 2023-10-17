// Fill out your copyright notice in the Description page of Project Settings.


#include "ApolloUICloudActor.h"

// Sets default values
AApolloUICloudActor::AApolloUICloudActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AApolloUICloudActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AApolloUICloudActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AApolloUICloudActor::SetClicked(bool boo) {
	AApolloUICloudActor::Clicked = boo;
}

bool AApolloUICloudActor::GetClicked() {
	return AApolloUICloudActor::Clicked;
}
