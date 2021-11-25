// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerContoller.h"
#include "GameFramework/Pawn.h"

void AToonTanksPlayerContoller::SetPlayerEnabledState(bool bPlayerEnabled)
{
	if(bPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}

	bShowMouseCursor = bPlayerEnabled;
}