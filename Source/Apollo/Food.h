#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Food.generated.h"

UCLASS()
class APOLLO_API AFood : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Mesh;

public:	
	AFood();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void DestroySelf();

	void DestroyDelay();

protected:
	virtual void BeginPlay() override;
};
