#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(Tank)
	{

		// Check if tank in range
		if(InFireRange() && Tank->bAlive)
		{
			// if in range,
			// 
			// rotate turrent to tank
			RotateTurret(Tank->GetActorLocation());
		}
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));

	GetWorldTimerManager().SetTimer(
				FireRateTimerHandle,
				this,
				&ATower::CheckFireCondition,
				FireRate,
				true
			);
}

void ATower::CheckFireCondition()
{
	if(Tank)
	{
		if(InFireRange())
		{
			Fire();
		}
	}
}

bool ATower::InFireRange() const
{
	return (FVector::Dist(GetActorLocation(),Tank->GetActorLocation()) <= AttackRange);
}

