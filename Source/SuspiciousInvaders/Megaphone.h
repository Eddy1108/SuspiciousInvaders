// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Megaphone.generated.h"

UCLASS()
class SUSPICIOUSINVADERS_API AMegaphone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMegaphone();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		float FlySpeed{ 100.f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
		float FlyTime{ 5.f };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* StaticMesh{ nullptr };
	UPROPERTY(EditAnywhere)
		class UBoxComponent* BoxCollider{ nullptr };

	float TimeAlive{ 0.f };

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
