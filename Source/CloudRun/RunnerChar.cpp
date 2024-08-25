#include "RunnerChar.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HurricanePickUp.h"
#include "LightningPickUp.h"
#include "Storm.h"
#include "Engine.h"
#include "HealthComponent.h"
#include "PointComponent.h"
#include "HealthComponent.h"
#include "CoinPickUp.h"
#include "PlayerBaseWidget.h"
#include "BaseLevel.h"
#include "Misc/OutputDeviceNull.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "HealthWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "CloudRunGameMode.h"
#include "Math/UnrealMathUtility.h"





ARunnerChar::ARunnerChar()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("Health");
	PointComponent = CreateDefaultSubobject<UPointComponent>("Points");


	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	SideViewCam = CreateDefaultSubobject<UCameraComponent>("SideViewCam");
	SideViewCam->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.8f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.F;

	TempPos = GetActorLocation();
	ZPos = TempPos.Z + 300;
	Time = 0;
}

void ARunnerChar::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ARunnerChar::OnOverlapBegin);

	GameMode = Cast<ACloudRunGameMode>(UGameplayStatics::GetGameMode(this));

	HealthComponent->OnDeath.AddDynamic(this, &ARunnerChar::RespondToOnDeath);

	GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, this, &ARunnerChar::OnTimer, 1.0f, true);

	CanMove = true;

	HitByLightning = false;


	HealthWidget = Cast<UHealthWidget>(CreateWidget(GetWorld(), HealthWidgetClass));

	if (HealthWidget != nullptr) {
		HealthWidget->AddToViewport();
		HealthWidget->TargetHealthComponent = HealthComponent;
		HealthWidget->TargetPointComponent = PointComponent;
	}

	
}

void ARunnerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TempPos = GetActorLocation();

	TempPos.X -= 850.f;
	

	float ZDifference = FMath::Abs(TempPos.Z - ZPos);
	float ZThreshold = 200.0f;
	if (ZDifference > ZThreshold)
	{
		// Smoothly interpolate the camera's Z position towards the player's Z position
		ZPos = FMath::FInterpTo(ZPos, TempPos.Z, DeltaTime, 1.0f); // Adjust speed (5.0f) as needed
		TempPos.Z = ZPos;
		SideViewCam->SetWorldLocation(TempPos);
		
	}
	else {
		TempPos.Z = ZPos;
		SideViewCam->SetWorldLocation(TempPos);
	}
	

	Time = PointComponent->PassedTime;
	HealthWidget->Time->SetText(FText::AsNumber(Time));

	int Coins = PointComponent->CoinCount;
	HealthWidget->Coins->SetText(FText::AsNumber(Coins));

	if (HealthComponent->CurrentHealth == 2) {
		HealthWidget->ThirdLife->SetVisibility(ESlateVisibility::Hidden);
	}
	else if (HealthComponent->CurrentHealth == 1) {
		HealthWidget-> SecondLife->SetVisibility(ESlateVisibility::Hidden);
	}
	else if (HealthComponent->CurrentHealth == 0) {
		HealthWidget->FirstLife->SetVisibility(ESlateVisibility::Hidden);
	}
	for (TActorIterator<AStorm> It(GetWorld()); It; ++It)
	{
		Storm = *It;

		if (Storm) {
			float StormLocationY = Storm->GetActorLocation().Y;

			if (GetActorLocation().Y < StormLocationY) {
				OnDie();
			}
		}
	}

	if (GetActorLocation().Z < 0) {
		OnDie();
	}	

}

void ARunnerChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ARunnerChar::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ARunnerChar::StopJumping);

	PlayerInputComponent->BindAxis("MoveRight", this, &ARunnerChar::MoveRight);
}

void ARunnerChar::MoveRight(float value)
{
	if (CanMove) {
	
		if (!HitByLightning) {
			AddMovementInput(FVector(0, 1, 0), value);
		}
		else {
			AddMovementInput(FVector(0, 1, 0), value/2);
		}
	}
}

void ARunnerChar::OnDie()
{
	GameMode->Died();
}

void ARunnerChar::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (OtherActor != nullptr) {
		AStorm* StormActor = Cast<AStorm>(OtherActor);
		AHurricanePickUp* Hurricane = Cast<AHurricanePickUp>(OtherActor);
		ALightningPickUp* Lightning = Cast<ALightningPickUp>(OtherActor);
		ACoinPickUp* Coin = Cast<ACoinPickUp>(OtherActor);

		if (StormActor) {
			HealthComponent->TakeDamage(1);
		}
		if (Hurricane) {
				
			for (TActorIterator<AStorm> It(GetWorld()); It; ++It)
			{
				Storm = *It;

				if (Storm)
				{
					Storm->HurricaneOn = true;
					Hurricane->Destroy();
					FTimerHandle UnusedHandle;
					GetWorldTimerManager().SetTimer(UnusedHandle, this, &ARunnerChar::HurricaneTimeOut, 10, false);
				}
			}
		}
		if (Lightning) {
			HitByLightning = true;
			Lightning->Destroy();
			FTimerHandle UnusedHandle;
			GetWorldTimerManager().SetTimer(UnusedHandle, this, &ARunnerChar::LightningTimeOut, 5, false);
		}
		if (Coin) {
			PointComponent->PickACoin(1);
			Coin->Destroy();
			UE_LOG(LogTemp, Warning, TEXT("coin picked"));
		}
	}
	
}

void ARunnerChar::RespondToOnDeath()
{
	GetMesh()->Deactivate();
	GetMesh()->SetVisibility(false);
	CanMove = false;
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &ARunnerChar::OnDie, 2, false);
}

void ARunnerChar::OnTimer()
{
	PointComponent->PassedTime++;
}

void ARunnerChar::LightningTimeOut()
{
	HitByLightning = false;
}

void ARunnerChar::HurricaneTimeOut()
{
		if (Storm) {		
			Storm->HurricaneOn = false;
		}	
}

void ARunnerChar::RemoveWidgets()
{
	UE_LOG(LogTemp, Warning, TEXT("removing widgets-----"));


	int myhealth = HealthComponent->CurrentHealth;

	UE_LOG(LogTemp, Warning, TEXT("health %d"), myhealth);

	FName FunctionName = "Widgets";
	UFunction* Function = FindFunction(FunctionName);

	if (Function)
	{
		// Call the Blueprint function
		ProcessEvent(Function, nullptr);
	}
}


