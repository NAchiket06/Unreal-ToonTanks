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

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void HandleDestruction();

	APlayerController* GetTankPlayerController() const{	  return TankPlayerController;   }
	

private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Components",meta=(AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Components",meta=(AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;


	void Move(float value);
	void Turn(float value);

	APlayerController* TankPlayerController;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
