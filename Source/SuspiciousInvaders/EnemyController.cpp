// Fill out your copyright notice in the Description page of Project Settings.

//This ended up becoming more of a GameController

#include "EnemyController.h"
#include "MyImposter.h"
#include "ImposterPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AEnemyController::AEnemyController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	PlayerRef = Cast<AImposterPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	
	RightTrigger->OnActorBeginOverlap.AddDynamic(this, &AEnemyController::UpdateState);
	LeftTrigger->OnActorBeginOverlap.AddDynamic(this, &AEnemyController::UpdateState);
	EndTrigger->OnActorBeginOverlap.AddDynamic(this, &AEnemyController::EndGame);
	
	SpawnEnemies();
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyImposter::StaticClass(), EnemiesInWorld);
	GetWorld()->GetTimerManager().SetTimer(ShootTimer, this, &AEnemyController::MakeEnemyShoot, ShootInterval, true);
	
	ImposterAmount = EnemiesInWorld.Num();
	UpdateHUD(ImposterAmount);

}

void AEnemyController::UpdateState(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->IsA(AMyImposter::StaticClass()))
	{
		++MoveState;
		if (MoveState == 1 || MoveState == 3)
			GetWorld()->GetTimerManager().SetTimer(MoveDownTimer,this, &AEnemyController::QuickUpdateState, TimeToGoDown, false);
		else if (MoveState >= 4)
			MoveState = 0;
	}
}

void AEnemyController::QuickUpdateState()
{
	++MoveState;
	if (MoveState >= 4)
		MoveState = 0;
}


// Called every frame
void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyController::MakeEnemyShoot()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyImposter::StaticClass(), EnemiesInWorld);	//Dirty fix

	if (EnemiesInWorld.Num() <= 0)
	{
		return;
	}

	Cast<AMyImposter>(EnemiesInWorld[FMath::RandRange(0, EnemiesInWorld.Num()-1)])->ImpShoot();
}

void AEnemyController::SpawnEnemies()
{
	FVector SpawnLocation = GetActorLocation();
	
	for (int i = 0; i < Columns; ++i)
	{
		for (int j = 0; j < Row+0; j++)
		{
			GetWorld()->SpawnActor<AMyImposter>(Imposters, SpawnLocation + SpawnOffsetY* i + SpawnOffsetX * j, GetActorRotation());
		}
	}
	
}

void AEnemyController::UpdateEnemyCount()
{
	--ImposterAmount;
	UpdateHUD(ImposterAmount);
	if (ImposterAmount <= 0)
	{
		GameOver(false);
	}
}

void AEnemyController::EndGame(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->IsA(AMyImposter::StaticClass()))
	{
		PlayerRef->OnHit();
		GameOver(true);
		bHasGameEnded = false;
	}
	
}