#include "TestBucket.h"
#include "Food.h"

ATestBucket::ATestBucket()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATestBucket::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATestBucket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATestBucket::SpawnFood(int32 TeamID)
{
	FTransform SpawnTransForm = this->GetActorTransform();
	SpawnTransForm.SetScale3D(FVector(SizeScalar));

	TSubclassOf<AFood> FoodToSpawn;
	FString FoodName;
	switch (FMath::RandRange(0, 2))
	{
	case 0:
		FoodToSpawn = AppleToSpawn;
		FoodName = TEXT("Apple");
		break;
	case 1:
		FoodToSpawn = BananaToSpawn;
		FoodName = TEXT("Banana");
		break;
	case 2:
		FoodToSpawn = OrangeToSpawn;
		FoodName = TEXT("Orange");
		break;
	default:
		break;
	}

	AFood* Food = GetWorld()->SpawnActor<AFood>(FoodToSpawn, SpawnTransForm);
	Food->Tags.Add(FName(*FoodName));
	Food->Tags.Add(FName(FString::FromInt(TeamID)));
}

