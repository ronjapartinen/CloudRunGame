#include "BaseLevel.h"
#include "Components/BoxComponent.h"
#include "CloudRunGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "RunnerChar.h"

ABaseLevel::ABaseLevel()
{
	PrimaryActorTick.bCanEverTick = true;
}


void ABaseLevel::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<ACloudRunGameMode>(UGameplayStatics::GetGameMode(this));
	
	if (Trigger != nullptr) {
		Trigger->bHiddenInGame = true;
	}

	if (Trigger) {
		Trigger->OnComponentBeginOverlap.AddDynamic(this, &ABaseLevel::OnOverlapBegin);
	}
}


void ABaseLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UBoxComponent* ABaseLevel::GetTrigger()
{
	return Trigger;
}

UBoxComponent* ABaseLevel::GetSpawnLocation()
{
	return SpawnLocation;
}

void ABaseLevel::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (OtherActor)
	{
		if (ACharacter* OverlappingCharacter = Cast<ACharacter>(OtherActor))
		{
			UE_LOG(LogTemp, Warning, TEXT("Player has entered the trigger!"));
			GameMode->LevelComplete();	
		}
	}
	
}

void ABaseLevel::GetLevelComplete()
{
	GameMode->LevelComplete();
}



