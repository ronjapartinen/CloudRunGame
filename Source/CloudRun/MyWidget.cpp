#include "MyWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "CloudRunGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "RunnerChar.h"

void UMyWidget::NativeConstruct()
{
	GameMode = Cast<ACloudRunGameMode>(UGameplayStatics::GetGameMode(this));

	if (PlayButton) {
		PlayButton->OnClicked.AddDynamic(this, &UMyWidget::PlayButtonOnClick);
	}
}

void UMyWidget::SetLevelText(int CurrentLevel)
{
	if (LevelText) {
		FString Text = FString::FromInt(CurrentLevel);

		LevelText->SetText(FText::FromString(Text));
	}
}

void UMyWidget::SetLevelButtons()
{
}

void UMyWidget::PlayButtonOnClick()
{

	this->SetVisibility(ESlateVisibility::Hidden);
	UE_LOG(LogTemp, Warning, TEXT("clicked"));
	GameMode->Playing = true;
	GameMode->SpawnActors();
	GameMode->LoadLevel();
}
