#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "ApolloPlayerController.generated.h"

UCLASS()
class APOLLO_API AApolloPlayerController : public APlayerController
{
	GENERATED_BODY()

	class AApolloCharacter* PlayerCharacter;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	virtual void OnPossess(APawn* PlayerPawn) override;

	virtual void SetupInputComponent() override;

	void Move(const FInputActionValue& Value);
};
