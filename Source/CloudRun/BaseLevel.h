#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseLevel.generated.h"

class UBoxComponent;
class ACloudRunGameMode;
class ARunnerChar;

UCLASS()
class CLOUDRUN_API ABaseLevel : public AActor
{
	GENERATED_BODY()
	
public:	

	ABaseLevel();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Triggers")
	UBoxComponent* Trigger;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spawn")
	UBoxComponent* SpawnLocation;

	UPROPERTY(BlueprintReadWrite)
	ACloudRunGameMode* GameMode;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ARunnerChar> RunnerWidgetClass;

	UPROPERTY(VisibleInstanceOnly)
	ARunnerChar* Runner;


	UBoxComponent* GetTrigger();
	UBoxComponent* GetSpawnLocation();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void GetLevelComplete();
};
