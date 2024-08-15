#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthWidget.generated.h"


class UHealthComponent;
class UPointComponent;
class UTextBlock;
class UImage;

UCLASS()
class CLOUDRUN_API UHealthWidget : public UUserWidget
{
	GENERATED_BODY()


protected:
	virtual void NativeConstruct() override;

public:
	UHealthWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UHealthComponent* TargetHealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UPointComponent* TargetPointComponent;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Time;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Coins;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* FirstLife;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* SecondLife;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* ThirdLife;


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* LevelCompleteText;
};
