#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CloudRunGameMode.generated.h"

class ABaseLevel;
class UUserWidget;
class UMyWidget;
class AStorm;
class ARunnerChar;
class UHealthWidget;
class UTryAgainWidget;

UCLASS(minimalapi)
class ACloudRunGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACloudRunGameMode();

	virtual void BeginPlay() override;

	void SpawnActors();

	void LoadLevel();

	void LevelComplete();

	void Died();

	UFUNCTION()
	void SetUpMenuBack();

	UFUNCTION()
	void RemoveLevel();

	UPROPERTY(BlueprintReadWrite)
	int CurrentLevel;
	

protected:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(VisibleInstanceOnly)
	UMyWidget* MyWidget;

	UPROPERTY(VisibleInstanceOnly)
	UHealthWidget* HealthWidget;

	UPROPERTY()
	ARunnerChar* SpawnedPlayer;

	UPROPERTY()
	AStorm* SpawnedStorm;

	bool IsLoaded = false;

	ABaseLevel* MyLevel = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseLevel> Level_1;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseLevel> Level_2;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseLevel> Level_3;

	FVector LevelSpawnLocation = FVector();
	FRotator LevelSpawnRotation = FRotator();
	FActorSpawnParameters SpawnInfo = FActorSpawnParameters();

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<ACharacter> PlayerClass;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AStorm> StormClass;

	APlayerController* Controller;

	FVector PlayerLocation = FVector();
	FRotator PlayerRotation = FRotator();
	FActorSpawnParameters PlayerSpawnParameters{};

	FVector StormLocation = FVector();
	FRotator StormRotation = FRotator();
	FActorSpawnParameters StormSpawnParameters{};


	float FinalTime;
};



