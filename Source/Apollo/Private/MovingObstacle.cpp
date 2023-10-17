#include "MovingObstacle.h"

AMovingObstacle::AMovingObstacle()
{
	PrimaryActorTick.bCanEverTick = true;

	Speed = 100.0f;
	Livetime = 10.0f;
	IsLaunched = true;
	MoveDirection = FVector(0, 1, 0);
}

void AMovingObstacle::BeginPlay()
{
	Super::BeginPlay();
}

void AMovingObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ObstaclesMovement(DeltaTime);
}

void AMovingObstacle::ObstaclesMovement(float DeltaTime)
{
	FVector NewLocation = GetActorLocation() + Speed * DeltaTime * MoveDirection;
	SetActorLocation(NewLocation, true);

	if (IsLaunched)
	{
		Livetime -= DeltaTime;
		if (Livetime <= 0.f)
		{
			Destroy();
		}
	}
}

void AMovingObstacle::SetDirection(FVector Direction)
{
	MoveDirection = Direction;
}
