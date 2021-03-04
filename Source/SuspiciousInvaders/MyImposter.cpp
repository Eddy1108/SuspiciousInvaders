// Fill out your copyright notice in the Description page of Project Settings.


#include "MyImposter.h"
#include "Components/BoxComponent.h"
#include "EnemyController.h"
#include "Knife.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyImposter::AMyImposter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(RootComponent);

	ImpStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	ImpStaticMesh->SetupAttachment(BoxCollider);

	ImpVisorStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visor"));
	ImpVisorStaticMesh->SetupAttachment(ImpStaticMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(ImpStaticMesh);
}

// Called when the game starts or when spawned
void AMyImposter::BeginPlay()
{
	Super::BeginPlay();

	RightVector = FVector(1.f, 0.f, 0.f);
	LeftVector = FVector(-1.f, 0.f, 0.f);
	DownVector = FVector(0.f, 1.f, 0.f);

	EnemyControllerRef = Cast<AEnemyController>(UGameplayStatics::GetActorOfClass(this, AEnemyController::StaticClass()));
}

void AMyImposter::OnHit()
{
	ImpHP -= 5;
	if (ImpHP <= 0)
	{
		EnemyControllerRef->UpdateEnemyCount();
		Destroy();
	}
}

// Called every frame
void AMyImposter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (EnemyControllerRef->MoveState) {
	case 0:
		Move(DeltaTime, RightVector);
		break;
	case 1:
	case 3:
		Move(DeltaTime, DownVector);
		break;
	case 2:
		Move(DeltaTime, LeftVector);
		break;
	default:
		break;
	}
}

void AMyImposter::Move(float DeltaTime, FVector DirVector)
{
	AddActorLocalOffset(DirVector * MoveSpeed * DeltaTime, false);
}

void AMyImposter::ImpShoot()
{
	GetWorld()->SpawnActor<AKnife>(KnifeProjectile, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation() + FRotator(0.f, -90.f, 90.f));
}