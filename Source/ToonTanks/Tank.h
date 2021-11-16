// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Camera/CameraComponent.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public: 
	ATank();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Components",meta=(AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Components",meta=(AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;


	void Move(float value);
	void Turn(float value);

	APlayerController* PlayerControllerRef;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
    
};
