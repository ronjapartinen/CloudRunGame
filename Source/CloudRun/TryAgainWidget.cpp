#include "TryAgainWidget.h"
#include "Components/Button.h"
#include "CloudRunGameMode.h"
#include "Kismet/GameplayStatics.h"



void UTryAgainWidget::NativeConstruct()
{
	GameMode = Cast<ACloudRunGameMode>(UGameplayStatics::GetGameMode(this));

	if (ToMenu) {
		ToMenu->OnClicked.AddDynamic(this, &UTryAgainWidget::ToMenuOnClick);
	}

	if (ToGame) {
		ToGame->OnClicked.AddDynamic(this, &UTryAgainWidget::ToGameOnClick);
	}

}

UTryAgainWidget::UTryAgainWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UTryAgainWidget::ToMenuOnClick()
{
	GameMode->SetUpMenuBack();
	UE_LOG(LogTemp, Warning, TEXT("ToMenu Pressed"));
}

void UTryAgainWidget::ToGameOnClick()
{
	UE_LOG(LogTemp, Warning, TEXT("ToGame Pressed"));
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()));
	GameMode->SpawnActors();
	GameMode->LoadLevel();
}
