#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TryAgainWidget.generated.h"


class UButton;
class ACloudRunGameMode;

UCLASS()
class CLOUDRUN_API UTryAgainWidget : public UUserWidget
{
	GENERATED_BODY()
	

protected:
	virtual void NativeConstruct() override;

public:
	UTryAgainWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ToMenu;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ToGame;

	UFUNCTION()
	void ToMenuOnClick();

	UFUNCTION()
	void ToGameOnClick();

	UPROPERTY(BlueprintReadWrite)
	ACloudRunGameMode* GameMode;
};
