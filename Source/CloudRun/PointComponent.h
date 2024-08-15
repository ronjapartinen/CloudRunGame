#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PointComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CLOUDRUN_API UPointComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UPointComponent();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadOnly)
	float CoinCount;

	UPROPERTY(BlueprintReadOnly)
	float PassedTime;

	void PickACoin(int Coin) {
		CoinCount += Coin;
	};
	
	
};
