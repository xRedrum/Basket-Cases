#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFoodSpawner.generated.h"

class AFood;

UCLASS()
class APOLLO_API AGameFoodSpawner : public AActor
{
	GENERATED_BODY()

	class UStaticMeshComponent* SpawnPlane; // geometry, not airplane

	FVector MinPoint = FVector::ZeroVector;
	FVector MaxPoint = FVector::ZeroVector;

public:	
	AGameFoodSpawner();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	int32 TeamID = 1;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AFood> AppleFood;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AFood> BananaFood;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AFood> OrangeFood;

	UPROPERTY(EditAnywhere)
	float SizeScalar = 1.0;

	UPROPERTY(EditAnywhere)
	int32 MaxFruitsAtOnce = 10;

	UFUNCTION(BlueprintCallable)
	void SpawnFood();
};
