#include "TrafficLightControl.h"
#include "MovingObstacle.h"
#include "TimerManager.h"

ATrafficLightControl::ATrafficLightControl()
{
	PrimaryActorTick.bCanEverTick = false;

	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	RootComponent = SpawnBox;
}

void ATrafficLightControl::BeginPlay()
{
	Super::BeginPlay();

	if (ShouldSpawn)
	{
		ScheduleActorSpawn();
	}

	TrafficLightUpdate();
	
}

void ATrafficLightControl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ATrafficLightControl::SpawnObstacles()
{
	if (ObstacleToBeSpawned)
	{
		FBoxSphereBounds BoxBounds = SpawnBox->CalcBounds(GetActorTransform());
		FVector Location = BoxBounds.Origin;
		FRotator Rotation = GetActorRotation();

		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ObstacleToBeSpawned, Location, Rotation);

		if (AMovingObstacle* Car = Cast<AMovingObstacle>(SpawnedActor))
		{
			FVector Direction = GetActorForwardVector();
			Car->SetDirection(Direction);
			Car->SetActorRotation(FQuat(FVector(0, 0, 1), Direction.Y * PI / 2));
		}

		if (SpawnedActor)
		{
			TrafficLightUpdate();
			return true;
		}
	}
	return false;
}

void ATrafficLightControl::EnableActorSpawning(bool Enable)
{
	ShouldSpawn = Enable;
	if (Enable)
	{
		ScheduleActorSpawn();
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimeHandler);
	}
}

void ATrafficLightControl::TrafficLightUpdate()
{
}

void ATrafficLightControl::SpawnActorScheduled()
{
	if (SpawnObstacles())
	{
		if (ShouldSpawn)
		{
			ScheduleActorSpawn();
		}
	}
	else
	{
		//TO DO

	}
}

void ATrafficLightControl::ScheduleActorSpawn()
{
	float DeltaToNextSpawn = SpawnInterval + (-RandomSpawnTimeOffset + 2 * RandomSpawnTimeOffset * FMath::FRand());
	GetWorld()->GetTimerManager().SetTimer(SpawnTimeHandler, this, &ATrafficLightControl::SpawnActorScheduled, DeltaToNextSpawn, false);
}

