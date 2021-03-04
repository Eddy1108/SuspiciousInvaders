// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Knife.generated.h"

class AEnemyController;

UCLASS()
class SUSPICIOUSINVADERS_API AKnife : public AActor
{
	GENERATED_BODY()


public:	
	// Sets default values for this actor's properties
	AKnife();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		float FlySpeed{ 100.f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		float FlyTime{ 5.f };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Blade{nullptr};
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* RHandle{nullptr};
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* LHandle{nullptr};
	UPROPERTY(EditAnywhere)
		class UCapsuleComponent* CapCollider{ nullptr };

	float TimeAlive{ 0.f };

	AEnemyController* EnemyControllerRef{nullptr};

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
