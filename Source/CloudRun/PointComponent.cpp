#include "PointComponent.h"


UPointComponent::UPointComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UPointComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UPointComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


