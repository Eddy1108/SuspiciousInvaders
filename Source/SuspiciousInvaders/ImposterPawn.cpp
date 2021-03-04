// Fill out your copyright notice in the Description page of Project Settings.


#include "ImposterPawn.h"
#include "Camera/CameraActor.h"
#include "Megaphone.h"

// Sets default values
AImposterPawn::AImposterPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	PlayerImpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	PlayerImpMesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(PlayerImpMesh);

}

// Called when the game starts or when spawned
void AImposterPawn::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->SetViewTarget(TopDownCamera);
}

void AImposterPawn::Move(float Value)
{
	CurrentDir.Y = FMath::Clamp(Value, -1.0f, 1.0f) * MoveSpeed;
}

void AImposterPawn::Fire()
{
	//UE_LOG(LogTemp, Warning, TEXT("Shoot!"));
	if (bPlayerAlive)
	{
		GetWorld()->SpawnActor<AMegaphone>(ProjectileMegaphone, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation() + FRotator(0.f, -90.f, 0.f));
	}
}


// Called every frame
void AImposterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!CurrentDir.IsZero() && bPlayerAlive)
	{
		FVector MoveLocation = GetActorLocation() + (CurrentDir * DeltaTime);
		SetActorLocation(MoveLocation);
	}
}

// Called to bind functionality to input
void AImposterPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Right", this, &AImposterPawn::Move);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AImposterPawn::Fire);
}

void AImposterPawn::OnHit()
{
	PlayerImpMesh->SetHiddenInGame(true);	//"pretending" the player is dead, cant shoot and is invisible, good enough right?
	bPlayerAlive = false;
	UE_LOG(LogTemp, Warning, TEXT("The player is dead!"));
}
