#include "ApolloPlayerController.h"
#include "../ApolloCharacter.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void AApolloPlayerController::OnPossess(APawn* PlayerPawn)
{
	Super::OnPossess(PlayerPawn);
	PlayerCharacter = Cast<AApolloCharacter>(PlayerPawn);
}

void AApolloPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(InputMappingContext, 0);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	check(EnhancedInputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AApolloPlayerController::Move);
}

void AApolloPlayerController::Move(const FInputActionValue& Value)
{
	if (PlayerCharacter && PlayerCharacter->CanMove())
	{
		FVector2D MovementVector = Value.Get<FVector2D>();
		PlayerCharacter->AddMovementInput(FVector::ForwardVector, MovementVector.X);
		PlayerCharacter->AddMovementInput(FVector::RightVector, -MovementVector.Y);
	}
}
