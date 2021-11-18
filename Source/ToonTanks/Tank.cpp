// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "DrawDebugHelpers.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet//GameplayStaticsTypes.h"
#include "Kismet/GameplayStatics.h"

//	Constructor
ATank::ATank()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

//	Called First
void ATank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());
}


//	Called Every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(PlayerControllerRef)
	{
		FHitResult HitResult;
		PlayerControllerRef->GetHitResultUnderCursor
		(ECollisionChannel::ECC_Visibility,false,HitResult);

		DrawDebugSphere(
			GetWorld(),
			HitResult.ImpactPoint,
			10.f,
			16,
			FColor::Red
			);

		RotateTurret(HitResult.ImpactPoint);
	}
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this,&ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"),this,&ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"),IE_Pressed,this,&ATank::Fire);
}

void ATank::Move(float value)
{
	// UE_LOG(LogTemp,Warning,TEXT("Value: %f."),value);
	
	FVector DeltaLocation(0.f);
	DeltaLocation.X = value*Speed*UGameplayStatics::GetWorldDeltaSeconds(this);
	
	AddActorLocalOffset(DeltaLocation,true);
}

void ATank::Turn(float value)
{
	FRotator DeltaRotation(0.f);
	DeltaRotation.Yaw = value * TurnSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotation),true;
}


