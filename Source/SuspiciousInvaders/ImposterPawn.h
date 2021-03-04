// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ImposterPawn.generated.h"


UCLASS()
class SUSPICIOUSINVADERS_API AImposterPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AImposterPawn();

	UPROPERTY(EditAnywhere, Category = "Edits")
		UStaticMeshComponent* PlayerImpMesh{ nullptr };
	UPROPERTY(EditAnywhere, Category = "Edits")
		USceneComponent* ProjectileSpawnPoint;
	UPROPERTY(EditAnywhere, Category = "Edits")
		ACameraActor* TopDownCamera{nullptr};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Edits")
		float MoveSpeed{ 100.f };
	UPROPERTY(EditAnywhere, Category = "Edits")
		TSubclassOf<class AMegaphone> ProjectileMegaphone;

	void OnHit();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Edits");
	bool bPlayerAlive{true};
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(float Value);
	void Fire();

	FVector CurrentDir{ 0.f };

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
