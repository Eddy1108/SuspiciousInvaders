// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyImposter.generated.h"

class AEnemyController;
class AKnife;

UCLASS()
class SUSPICIOUSINVADERS_API AMyImposter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyImposter();

	void OnHit();
	void Move(float DeltaTime, FVector DirVector);
	void ImpShoot();
	AEnemyController* EnemyControllerRef{nullptr};

private:

	FVector RightVector;
	FVector LeftVector;
	FVector DownVector;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ImpStaticMesh{ nullptr };
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ImpVisorStaticMesh{ nullptr };
	UPROPERTY(EditAnywhere)
		class UCapsuleComponent* CapCollider{ nullptr };
	UPROPERTY(EditAnywhere)
		class UBoxComponent* BoxCollider{ nullptr };
	UPROPERTY(EditAnywhere)
		USceneComponent* ProjectileSpawnPoint;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AKnife> KnifeProjectile;

	UPROPERTY(EditAnywhere)
	int32 ImpHP{ 10 };
	UPROPERTY(EditAnywhere)
	float MoveSpeed{ 10.f };

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
