#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "TrafficLightControl.generated.h"

UCLASS()
class APOLLO_API ATrafficLightControl : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* SpawnBox;

	UPROPERTY(EditAnywhere)
    bool ShouldSpawn = true;

	FTimerHandle SpawnTimeHandler;

	UFUNCTION()
	void SpawnActorScheduled();

	void ScheduleActorSpawn();
	
public:	
	ATrafficLightControl();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ObstacleToBeSpawned;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RandomSpawnTimeOffset;

	UFUNCTION(BlueprintCallable)
	bool SpawnObstacles();

	UFUNCTION(BlueprintCallable)
	void EnableActorSpawning(bool Enable);

	void TrafficLightUpdate();

protected:
	virtual void BeginPlay() override;
};
