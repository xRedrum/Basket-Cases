#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ApolloCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHasPlayerStateDelegate, int32, PlayerID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRagdollChangeDelegate, float, RagdollWeight);


UCLASS(config=Game)
class AApolloCharacter : public ACharacter
{
	GENERATED_BODY()

	class AApolloPlayerState* ApolloPlayerState = nullptr;

	bool bCanMove = true;
	bool bCanSqueak = true;

	UPROPERTY(EditAnywhere)
	int32 MaxFruits = 10;	// number of fruits to apply max negative effect
	int32 NumFruits = 0;
	float FruitPercent = 0.f;

	UPROPERTY(EditAnywhere)
	float MinSpeed = 1000.f;

	UPROPERTY(EditAnywhere)
	float MaxSpeed = 2000.f;

	UPROPERTY(EditAnywhere)
	float MinAcceleration = 1000.f;

	UPROPERTY(EditAnywhere)
	float MaxAcceleration = 1500.f;

	UPROPERTY(EditAnywhere)
	float MinDeceleration = 1500.f;

	UPROPERTY(EditAnywhere)
	float MaxDeceleration = 2000.f;

	UPROPERTY(EditAnywhere)
	class USoundBase* SqueakA;

	UPROPERTY(EditAnywhere)
	class USoundBase* SqueakB;

	UPROPERTY(EditAnywhere)
	class USoundBase* SqueakC;

	void EnableSqueak();

public:
	AApolloCharacter();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable)
	FOnHasPlayerStateDelegate FOnHasPlayerState;

	UPROPERTY(BlueprintAssignable)
	FRagdollChangeDelegate FRagdollChange;

	bool CanMove();

	void DisableMove();

	UFUNCTION(BlueprintCallable)
	int32 GetFruitPercent();

	void Squeak();

protected:
	virtual void BeginPlay();
};
