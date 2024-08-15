#include "LightningPickUp.h"


ALightningPickUp::ALightningPickUp()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALightningPickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALightningPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

