#include "HealthWidget.h"
#include "HealthComponent.h"
#include "PointComponent.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"


void UHealthWidget::NativeConstruct()
{

}

UHealthWidget::UHealthWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{	
	TargetHealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("TargetHealthComponent"));

	TargetPointComponent = CreateDefaultSubobject<UPointComponent>(TEXT("TargetPointComponent"));
}


