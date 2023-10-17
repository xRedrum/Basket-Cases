#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingObstacle.generated.h"

UCLASS()
class APOLLO_API AMovingObstacle : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Speed;

	bool IsLaunched;

	UPROPERTY(EditAnywhere)
	FVector MoveDirection;
	
public:	
	AMovingObstacle();

	virtual void Tick(float DeltaTime) override;

	void ObstaclesMovement(float DeltaTime);

	void SetDirection(FVector Direction);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Livetime;
};
