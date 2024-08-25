#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyWidget.generated.h"


class UButton;
class UTextBlock;
class ACloudRunGameMode;
class UPlayerBaseWidget;

UCLASS()
class CLOUDRUN_API UMyWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:

	UFUNCTION()
	void SetLevelText(int CurrentLevel);

	UFUNCTION()
	void SetLevelButtons(int CurrentLevel);

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* Level1Button;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* Level2Button;


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* Level3Button;

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* PlayButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* LevelText;

	UPROPERTY(BlueprintReadWrite)
	ACloudRunGameMode* GameMode;

	virtual void NativeConstruct() override;


	UFUNCTION()
	void PlayButtonOnClick();

};
