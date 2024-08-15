#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HurricanePickUp.generated.h"

class UShapeComponent;

UCLASS()
class CLOUDRUN_API AHurricanePickUp : public AActor
{
	GENERATED_BODY()
	
public:	

	AHurricanePickUp();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

};
