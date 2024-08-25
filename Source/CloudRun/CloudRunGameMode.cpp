#include "CloudRunGameMode.h"
#include "CloudRunCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "BaseLevel.h"
#include "Blueprint/UserWidget.h"
#include "MyWidget.h"
#include "RunnerChar.h"
#include "Storm.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "Engine.h"
#include "HealthWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "TryAgainWidget.h"

ACloudRunGameMode::ACloudRunGameMode()
{
	FinalTime = 0;
	CurrentLevel = 1;
	LevelSpawnRotation = FRotator(0, 90, 0);
}

void ACloudRunGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (IsLoaded) {
		return;
	}

	IsLoaded = true;
	Controller = GetWorld()->GetFirstPlayerController();
	FInputModeGameAndUI InputMode;
	Controller->SetInputMode(InputMode);
    Controller->bShowMouseCursor = true;

	SpawnedPlayer = nullptr;
	SpawnedStorm = nullptr;


		MyWidget = Cast<UMyWidget>(CreateWidget(GetWorld(), WidgetClass));

		if (MyWidget != nullptr) {
			MyWidget->AddToViewport();
		}
}

void ACloudRunGameMode::SpawnActors()
{
	PlayerLocation = FVector(0, 0, 100);
	PlayerRotation = FRotator(0, 90, 0);

	StormLocation = FVector(0, -700, 0);
	StormRotation = FRotator(0, 90, 0);

	SpawnedPlayer = GetWorld()->SpawnActor<ARunnerChar>(PlayerClass, PlayerLocation, PlayerRotation, PlayerSpawnParameters);
	Controller->Possess(SpawnedPlayer);

	SpawnedStorm = GetWorld()->SpawnActor<AStorm>(StormClass, StormLocation, StormRotation, StormSpawnParameters);

	HealthWidget = SpawnedPlayer->HealthWidget;
}

void ACloudRunGameMode::LoadLevel()
{

	if (CurrentLevel == 1) {
		MyLevel = GetWorld()->SpawnActor<ABaseLevel>(Level_1, LevelSpawnLocation, LevelSpawnRotation, SpawnInfo);
		UE_LOG(LogTemp, Warning, TEXT(" LOADING LEVEL 1 "));
	}
	else if (CurrentLevel == 2) {
		MyLevel = GetWorld()->SpawnActor<ABaseLevel>(Level_2, LevelSpawnLocation, LevelSpawnRotation, SpawnInfo);
		UE_LOG(LogTemp, Warning, TEXT(" LOADING LEVEL 2 "));
	}
	else if (CurrentLevel == 3) {
		MyLevel = GetWorld()->SpawnActor<ABaseLevel>(Level_3, LevelSpawnLocation, LevelSpawnRotation, SpawnInfo);
	}
}

void ACloudRunGameMode::LevelComplete()
{
	SpawnedStorm->SetActorTickEnabled(false);
	FinalTime = SpawnedPlayer->Time;
	CurrentLevel++;
	FTimerHandle PlayerTimer = SpawnedPlayer->MyTimerHandle;
	GetWorldTimerManager().ClearTimer(PlayerTimer);
	FString TimeText = FString::SanitizeFloat(FinalTime);
	FString CompleteText = ("Level complete with time of " + TimeText);
	HealthWidget->LevelCompleteText->SetText(FText::FromString(CompleteText));
	HealthWidget->LevelCompleteText->SetVisibility(ESlateVisibility::Visible);
	MyWidget->SetLevelButtons(CurrentLevel);
	FTimerHandle EndingTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(EndingTimerHandle, this, &ACloudRunGameMode::SetUpMenuBack, 5, false);

}

void ACloudRunGameMode::Died()
{
	if (SpawnedPlayer)
	{
		SpawnedPlayer->RemoveWidgets();
	}


	if (SpawnedPlayer) {
		SpawnedPlayer->Destroy();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("no player found"));
	}
	if (SpawnedStorm) {
		SpawnedStorm->Destroy();
	}

	LoadLevel();
	SpawnActors();
}

void ACloudRunGameMode::SetUpMenuBack()
{

	RemoveLevel();
	

	MyWidget->SetLevelText(CurrentLevel);
	MyWidget->SetVisibility(ESlateVisibility::Visible);
	

	UE_LOG(LogTemp, Warning, TEXT("My level %d"), CurrentLevel)
		UE_LOG(LogTemp, Warning, TEXT("player %s"), SpawnedPlayer)

		if (SpawnedPlayer)
		{
			SpawnedPlayer->RemoveWidgets();
		}


	if (SpawnedPlayer) {
		SpawnedPlayer->Destroy();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("no player found"));
	}
	if (SpawnedStorm) {
		SpawnedStorm->Destroy();
	}

}

void ACloudRunGameMode::RemoveLevel()
{
	if (MyLevel) {
		MyLevel->Destroy();
	}
}


