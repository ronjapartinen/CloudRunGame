#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightningPickUp.generated.h"

UCLASS()
class CLOUDRUN_API ALightningPickUp : public AActor
{
	GENERATED_BODY()
	
public:	

	ALightningPickUp();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

};
