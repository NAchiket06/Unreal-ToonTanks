// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerContoller.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if(DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if(ToonTanksPlayerController)
		{
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}

		GameOver(false);
	}

	else if(ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
		TargetTowers--;
		if(TargetTowers == 0)
		{
			GameOver(true);
		}
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
	TargetTowers = GetNoOfTowers();
	
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerContoller>(UGameplayStatics::GetPlayerController(this,0));

	StartGame();
	
	if(ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController,&AToonTanksPlayerContoller::SetPlayerEnabledState,true);
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle,PlayerEnableTimerDelegate,StartDelay,false);
	}

}

int32 AToonTanksGameMode::GetNoOfTowers()
{
	TArray<AActor*> outActors;
	UGameplayStatics::GetAllActorsOfClass(this,ATower::StaticClass(),outActors);

	return outActors.Num();
}




