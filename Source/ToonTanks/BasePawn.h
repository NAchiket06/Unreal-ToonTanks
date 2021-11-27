#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

#define UP UPROPERTY
UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Movement")
	float Speed = 50.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Movement")
	float TurnSpeed = 50.f;

protected:

	void RotateTurret(FVector LookAtTarget);
	void Fire();

	UPROPERTY(EditAnywhere,Category="Combat")
	class UParticleSystem* DeathParticles;
	
private: 
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Components",meta=(AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComponent;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Components",meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Components",meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Components",meta=(AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly,Category="Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere,Category="Combat")
	class USoundBase* DeathSound;
	
public:
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
