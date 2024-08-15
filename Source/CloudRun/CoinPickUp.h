#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoinPickUp.generated.h"

UCLASS()
class CLOUDRUN_API ACoinPickUp : public AActor
{
	GENERATED_BODY()
	
public:	

	ACoinPickUp();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

};
