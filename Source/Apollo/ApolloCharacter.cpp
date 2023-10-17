#include "ApolloCharacter.h"
#include "ApolloGameState.h"
#include "ApolloPlayerState.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"

AApolloCharacter::AApolloCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Face movement direction
	bool bUseControllerRotation = false;
	bUseControllerRotationPitch = bUseControllerRotation;
	bUseControllerRotationYaw = bUseControllerRotation;
	bUseControllerRotationRoll = bUseControllerRotation;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	GetCharacterMovement()->MaxWalkSpeed = MaxSpeed;
	GetCharacterMovement()->MaxAcceleration = MaxAcceleration;
	GetCharacterMovement()->BrakingDecelerationWalking = MaxDeceleration;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ApolloCharacter (to avoid direct content references in C++)
}

void AApolloCharacter::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(FName("ApolloCharacter"));
}

void AApolloCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ApolloPlayerState)
	{
		// TODO: delegate
		NumFruits = ApolloPlayerState->GetFruitCount();
		FruitPercent = (float)NumFruits / MaxFruits;
		FruitPercent = FMath::Clamp(FruitPercent, 0.f, 1.f);

		// the more you have, the worse it gets
		GetCharacterMovement()->MaxWalkSpeed = MaxSpeed - FruitPercent * (MaxSpeed - MinSpeed);
		GetCharacterMovement()->MaxAcceleration = MaxAcceleration - FruitPercent * (MaxAcceleration - MinAcceleration);
		GetCharacterMovement()->BrakingDecelerationWalking = MaxDeceleration - FruitPercent * (MaxDeceleration - MinDeceleration);
	}
	else
	{
		ApolloPlayerState = Cast<AApolloPlayerState>(GetPlayerState());
		if (ApolloPlayerState)
		{
			int32 PlayerID = ApolloPlayerState->GetApolloPlayerID();
			FOnHasPlayerState.Broadcast(PlayerID);
		}
	}

	if (!bCanMove && GetCharacterMovement()->GetLastUpdateVelocity().Size() <= 0.f)
	//if (!bCanMove && GetCharacterMovement()->GetLastUpdateVelocity().Size() < GetCharacterMovement()->MaxWalkSpeed / 4.f)
	{
		bCanMove = true;

		//FRagdollChange.Broadcast(0.f);
	}
}

bool AApolloCharacter::CanMove()
{
	return bCanMove;
}

void AApolloCharacter::DisableMove()
{
	bCanMove = false;

	//FRagdollChange.Broadcast(FruitPercent);
}

int32 AApolloCharacter::GetFruitPercent()
{
	return FruitPercent;
}

void AApolloCharacter::Squeak()
{
	if (bCanSqueak)
	{
		USoundBase* Squeak = SqueakA;
		switch (FMath::RandRange(0, 2))
		{
		case 0:
			Squeak = SqueakA;
			break;
		case 1:
			Squeak = SqueakB;
			break;
		case 2:
			Squeak = SqueakC;
			break;
		default:
			break;
		}
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Squeak, GetActorLocation(), GetActorRotation());

		bCanSqueak = false;
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AApolloCharacter::EnableSqueak, 0.25f, false);
	}
}

void AApolloCharacter::EnableSqueak()
{
	bCanSqueak = true;
}