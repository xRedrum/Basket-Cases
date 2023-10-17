#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BumpPlayerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class APOLLO_API UBumpPlayerComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float MaxBumpStrength = 2000.f;

	UPROPERTY(EditAnywhere)
	float MinBumpStrength = 1000.f;

	UPROPERTY(EditAnywhere)
	float MinPlayerBumpStrength = 100.f;

	UFUNCTION(BlueprintCallable)
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	UBumpPlayerComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;
};
