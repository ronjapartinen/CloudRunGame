#include "Storm.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Engine/Engine.h"


AStorm::AStorm()
{
	PrimaryActorTick.bCanEverTick = true;

	StormSpeed = 330;
	HurSpeed = 600;

}

void AStorm::BeginPlay()
{
	Super::BeginPlay();	
	
}

void AStorm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Location = GetActorLocation();
	Location += GetActorForwardVector() * GetSpeed() * DeltaTime;

	SetActorLocation(Location);
}

void AStorm::Hurricane()
{
	UE_LOG(LogTemp, Warning, TEXT("hurrikani2"));
}
float AStorm::GetSpeed()
{

	if (!HurricaneOn) {
		return StormSpeed;
	}
	else {
		return HurSpeed;
	}
	
}
;

