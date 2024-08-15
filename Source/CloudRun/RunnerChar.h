#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RunnerChar.generated.h"

class UHealthComponent;
class UPointComponent;
class UUserWidget;
class UHealthWidget;
class ACloudRunGameMode;
class AStorm;

UCLASS()
class CLOUDRUN_API ARunnerChar : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* SideViewCam;

	

public:

	ARunnerChar();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	void MoveRight(float value);

public:

	class UCameraComponent* GetSideViewCamComponent() const {
		return SideViewCam;
	}

	void OnDie();

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UHealthComponent* HealthComponent;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UPointComponent* PointComponent;

		UFUNCTION()
		void RespondToOnDeath();

		void OnTimer();

		void LightningTimeOut();
		void HurricaneTimeOut();


		UFUNCTION(BlueprintCallable)
		void RemoveWidgets();

		/**
		UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> HealthWidgetClass;

		UPROPERTY(BlueprintReadWrite)
		UUserWidget* HealthWidget;
		**/

		UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> HealthWidgetClass;

		UPROPERTY(BlueprintReadWrite)
		UHealthWidget* HealthWidget;


		UPROPERTY(BlueprintReadWrite)
		ACloudRunGameMode* GameMode;

		AStorm* Storm;

		int Time;

		FTimerHandle MyTimerHandle;
	
private:

	float ZPos;
	FVector TempPos = FVector();
	bool CanMove;
	bool HitByLightning;
};
