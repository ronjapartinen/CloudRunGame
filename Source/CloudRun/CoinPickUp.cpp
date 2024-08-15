#include "CoinPickUp.h"


ACoinPickUp::ACoinPickUp()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACoinPickUp::BeginPlay()
{
	Super::BeginPlay();
}

void ACoinPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

