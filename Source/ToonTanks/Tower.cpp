#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(Tank)
	{
		// Find Distance to Tank

		float Distance = FVector::Dist(GetActorLocation(),Tank->GetActorLocation());

		// Check if tank in range
		if(Distance <= AttackRange)
		{
			// if in range, rotate turrent to tank
			RotateTurret(Tank->GetActorLocation());
		}
	}
}
void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
	
}