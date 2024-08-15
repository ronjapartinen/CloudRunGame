#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Storm.generated.h"


UCLASS()
class CLOUDRUN_API AStorm : public AActor
{
	GENERATED_BODY()


public:	

	AStorm();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Hurricane();

	UFUNCTION()
	float GetSpeed();

	UPROPERTY(EditAnywhere)
	float StormSpeed;

	UPROPERTY(EditAnywhere)
	float HurSpeed;

	bool HurricaneOn = false;

};
