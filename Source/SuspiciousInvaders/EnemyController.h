// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "Containers/Array.h"
#include "EnemyController.generated.h"

class AImposterPawn;

UCLASS()
class SUSPICIOUSINVADERS_API AEnemyController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyController();

	AImposterPawn* PlayerRef;

	UPROPERTY(VisibleAnywhere);
	int MoveState{ 0 };
	UPROPERTY(EditAnywhere, Category="EnemyControll");
	float TimeToGoDown{ 1.0f };
	UPROPERTY(EditAnywhere, Category="EnemyControll");
	float ShootInterval{ 1.0f };
	UPROPERTY(EditAnywhere, Category="EnemyControll");
	int32 Columns{5};
	UPROPERTY(EditAnywhere, Category="EnemyControll");
	int32 Row{5};
	UPROPERTY(EditAnywhere, Category="EnemyControll");
	FVector SpawnOffsetY = FVector(0.f, 200.f, 0.f);
	UPROPERTY(EditAnywhere, Category="EnemyControll");
	FVector SpawnOffsetX = FVector(200.f, 0.f, 0.f);
	
	UPROPERTY(VisibleAnywhere);
    bool bHasGameEnded{true};
	
	int32 ImposterAmount{0};
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AMyImposter> Imposters;

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool Condition);
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHUD(int32 Enemies);
	void UpdateEnemyCount();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly);
	ATriggerVolume* RightTrigger{ nullptr };
	UPROPERTY(EditInstanceOnly);
	ATriggerVolume* LeftTrigger{ nullptr };
	UPROPERTY(EditInstanceOnly);
	ATriggerVolume* EndTrigger{ nullptr };

private:
	UFUNCTION()
	void UpdateState(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void EndGame(AActor* OverlappedActor, AActor* OtherActor);

	void QuickUpdateState();
	void MakeEnemyShoot();
	void SpawnEnemies();
	
	FTimerHandle MoveDownTimer;
	FTimerHandle ShootTimer;
	TArray<AActor*> EnemiesInWorld;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
