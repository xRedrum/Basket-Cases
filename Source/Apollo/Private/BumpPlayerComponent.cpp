#include "BumpPlayerComponent.h"
#include "../ApolloCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UBumpPlayerComponent::UBumpPlayerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBumpPlayerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBumpPlayerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UBumpPlayerComponent::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag("ApolloCharacter"))
	{
		//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.f, FColor::Green, TEXT("HIT PLAYER"));

		AApolloCharacter* OtherPlayerCharacter = Cast<AApolloCharacter>(OtherActor);
		float FruitPercent = OtherPlayerCharacter->GetFruitPercent();

		float Magnitude;
		if (AApolloCharacter* PlayerCharacter = Cast<AApolloCharacter>(GetOwner()))
		{
			// player bump
			Magnitude = PlayerCharacter->GetCharacterMovement()->GetLastUpdateVelocity().Size();
			Magnitude *= 1.f - FruitPercent;
			Magnitude = FMath::Max(Magnitude, MinPlayerBumpStrength);
		}
		else
		{
			// obstacle bump
			Magnitude = MaxBumpStrength - FruitPercent * (MaxBumpStrength - MinBumpStrength);
		}

		FVector Direction = OtherActor->GetActorLocation() - GetOwner()->GetActorLocation();
		Direction = FVector::VectorPlaneProject(Direction, FVector::UpVector);
		Direction.Normalize();
		
		OtherPlayerCharacter->Squeak();
		OtherPlayerCharacter->DisableMove();
		OtherPlayerCharacter->LaunchCharacter(Magnitude * Direction, true, false);
	}
}