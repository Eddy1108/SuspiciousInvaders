// Fill out your copyright notice in the Description page of Project Settings.


#include "Megaphone.h"
#include "Components/BoxComponent.h"
#include "MyImposter.h"

// Sets default values
AMegaphone::AMegaphone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(RootComponent);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(BoxCollider);
}

// Called when the game starts or when spawned
void AMegaphone::BeginPlay()
{
	Super::BeginPlay();
	
	Cast<UBoxComponent>(RootComponent)->OnComponentBeginOverlap.AddDynamic(this, &AMegaphone::OnOverlap);
}

// Called every frame
void AMegaphone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation() + (FVector(1.f, 0, 0) * FlySpeed * DeltaTime);
	SetActorLocation(NewLocation);

	TimeAlive += DeltaTime;
	if (TimeAlive >= FlyTime)
		Destroy();

}

void AMegaphone::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("Bullet Overlap %s"), *OtherActor->GetName());

	if (OtherActor->IsA(AMyImposter::StaticClass()))
	{
		Cast<AMyImposter>(OtherActor)->OnHit();
		Destroy();
	}
}