#include "Food.h"
#include "Components/StaticMeshComponent.h"

AFood::AFood()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UStaticMeshComponent"));
	Mesh->SetGenerateOverlapEvents(true);
	Mesh->CanCharacterStepUpOn = ECB_No;
	Mesh->SetCollisionProfileName(FName("PhysicsActor"));
	Mesh->SetSimulatePhysics(true);
	RootComponent = Mesh;
}

void AFood::BeginPlay()
{
	Super::BeginPlay();
	Mesh->SetMassScale(NAME_None, 10.f);
	Mesh->SetLinearDamping(2.5f);
	Mesh->SetAngularDamping(0.5f);
}

void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFood::DestroySelf()
{
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AFood::DestroyDelay, 1.0f, false);
}

void AFood::DestroyDelay()
{
	this->Destroy(true);
}
