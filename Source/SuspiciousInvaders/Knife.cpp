// Fill out your copyright notice in the Description page of Project Settings.


#include "Knife.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyController.h"
#include "ImposterPawn.h"

// Sets default values
AKnife::AKnife()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	RootComponent = CapCollider;

	Blade = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Blade"));
	Blade->SetupAttachment(RootComponent);

	RHandle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightHandle"));
	RHandle->SetupAttachment(Blade);

	LHandle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftHandle"));
	LHandle->SetupAttachment(Blade);
}

// Called when the game starts or when spawned
void AKnife::BeginPlay()
{
	Super::BeginPlay();

	Cast<UCapsuleComponent>(RootComponent)->OnComponentBeginOverlap.AddDynamic(this, &AKnife::OnOverlap);

	EnemyControllerRef = Cast<AEnemyController>(UGameplayStatics::GetActorOfClass(GetWorld(), AEnemyController::StaticClass()));
	
	if(!EnemyControllerRef)
	{
		UE_LOG(LogTemp, Error, TEXT("AKnife Missing referance to EnemyController! Place one in the scene!"));
		Destroy();
	}
}

// Called every frame
void AKnife::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation() + (FVector(-1.f, 0, 0) * FlySpeed * DeltaTime);
	SetActorLocation(NewLocation);

	TimeAlive += DeltaTime;
	if (TimeAlive >= FlyTime)
		Destroy();
}

void AKnife::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult) 
{	
	if (OtherActor->IsA(AImposterPawn::StaticClass()))
	{
		Cast<AImposterPawn>(OtherActor)->OnHit();
		EnemyControllerRef->GameOver(true);
		Destroy();
	}
}
