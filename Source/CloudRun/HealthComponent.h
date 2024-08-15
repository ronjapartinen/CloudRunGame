#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthDeathSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CLOUDRUN_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UHealthComponent();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxHealth = 3;

	UPROPERTY(BlueprintReadOnly)
	float CurrentHealth;

	void TakeDamage(float Damage) {
		UE_LOG(LogTemp, Warning, TEXT("damagee"), CurrentHealth);
		CurrentHealth -= Damage;

		if (CurrentHealth <= 0) {
			OnDeath.Broadcast();
		}
	};

	UPROPERTY()
	FHealthDeathSignature OnDeath;
		
};
