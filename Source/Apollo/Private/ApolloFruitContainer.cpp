// Fill out your copyright notice in the Description page of Project Settings.


#include "ApolloFruitContainer.h"

UApolloFruitContainer::UApolloFruitContainer()
{
	PrimaryComponentTick.bCanEverTick = true;
	BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionComponent"));
	BoxCollisionComponent->SetCollisionProfileName("OverlapAll");
	BoxCollisionComponent->SetGenerateOverlapEvents(true);

}

int32 UApolloFruitContainer::GetFruitCount()
{

	return int32();
}

void UApolloFruitContainer::BeginPlay() {
	Super::BeginPlay();
	FBoxSphereBounds MeshBounds = GetStaticMesh()->GetBounds();
	BoxCollisionComponent->SetBoxExtent(MeshBounds.BoxExtent*0.7);
	BoxCollisionComponent->SetRelativeLocation(MeshBounds.Origin);
	BoxCollisionComponent->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	//BoxCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &UApolloFruitContainer::OnOverlapBegin);
	//BoxCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &UApolloFruitContainer::OnOverlapEnd);
}

void UApolloFruitContainer::DestroyFruit_Implementation(){}