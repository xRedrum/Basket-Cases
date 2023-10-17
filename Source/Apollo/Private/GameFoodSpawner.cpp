#include "GameFoodSpawner.h"
#include "../Food.h"

AGameFoodSpawner::AGameFoodSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	SpawnPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UStaticMeshComponent"));
	RootComponent = SpawnPlane;
}

void AGameFoodSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnPlane->GetLocalBounds(MinPoint, MaxPoint);
	MinPoint = ActorToWorld().TransformPosition(MinPoint);
	MaxPoint = ActorToWorld().TransformPosition(MaxPoint);
}

void AGameFoodSpawner::SpawnFood()
{
	int32 NumFood = FMath::RandRange(0, MaxFruitsAtOnce);
	for (int32 i = 0; i < NumFood; i++)
	{
		FQuat InRotation = FQuat(
			FMath::RandRange(-1.f, 1.f),
			FMath::RandRange(-1.f, 1.f),
			FMath::RandRange(-1.f, 1.f),
			FMath::RandRange(-1.f, 1.f)
		);

		FVector InTranslation = FVector(
			FMath::RandRange(MinPoint.X, MaxPoint.X),
			FMath::RandRange(MinPoint.Y, MaxPoint.Y),
			GetActorLocation().Z
		);

		FVector InScale3D = FVector(SizeScalar);

		FTransform SpawnTransForm = FTransform(InRotation, InTranslation, InScale3D);

		TSubclassOf<AFood> FoodToSpawn;
		FString FoodName;
		switch (FMath::RandRange(0, 2))
		{
		case 0:
			FoodToSpawn = AppleFood;
			FoodName = TEXT("Apple");
			break;
		case 1:
			FoodToSpawn = BananaFood;
			FoodName = TEXT("Banana");
			break;
		case 2:
			FoodToSpawn = OrangeFood;
			FoodName = TEXT("Orange");
			break;
		default:
			break;
		}

		AFood* Food = GetWorld()->SpawnActor<AFood>(FoodToSpawn, SpawnTransForm);
		Food->Tags.Add(FName(*FoodName));
		Food->Tags.Add(FName(FString::FromInt(TeamID)));
	}
}

void AGameFoodSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//float X = FMath::RandRange(MinPoint.X, MaxPoint.X);
	//float Y = FMath::RandRange(MinPoint.Y, MaxPoint.Y);
	//float Z = GetActorLocation().Z;
}

