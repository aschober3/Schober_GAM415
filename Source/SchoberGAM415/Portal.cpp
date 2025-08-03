// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "SchoberGAM415Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create and attach components
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	boxComp = CreateDefaultSubobject<UBoxComponent>("Box Comp");
	sceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>("Capture");
	rootArrow = CreateDefaultSubobject<UArrowComponent>("Root Arrow");

	RootComponent = boxComp;
	mesh->SetupAttachment(boxComp);
	sceneCapture->SetupAttachment(mesh);
	rootArrow->SetupAttachment(RootComponent);

	// Prevent portal mesh from interfering with collision
	mesh->SetCollisionResponseToAllChannels(ECR_Ignore);

}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();

	// Bind overlap event to handler
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnOverlapBegin);

	// Prevent mesh from being captured by its own SceneCapture
	mesh->SetHiddenInSceneCapture(true);

	// Set the portal material if one is assigned
	if (mat)
	{
		mesh->SetMaterial(0, mat);
	}
	
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update scene capture to simulate portal view
	UpdatePortals();

}

// Called when another actor overlaps the portal's collision box
void APortal::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Cast overlapped actor to player character
	ASchoberGAM415Character* playerChar = Cast<ASchoberGAM415Character>(OtherActor);

	if (playerChar)
	{
		if (OtherPortal)
		{
			// Only teleport if player is not currently teleporting
			if (!playerChar->isTeleporting)
			{
				playerChar->isTeleporting = true;

				// Move player to other portal's location
				FVector loc = OtherPortal->rootArrow->GetComponentLocation();
				playerChar->SetActorLocation(loc);

				// Set timer to reset teleport flag after delay
				FTimerHandle TimerHandle;
				FTimerDelegate TimerDelegate;
				TimerDelegate.BindUFunction(this, "SetBool", playerChar);
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 1, false);

			}
		}
	}
}

// Resets the player's teleport flag after delay
void APortal::SetBool(ASchoberGAM415Character* playerChar)
{
	if (playerChar)
	{
		playerChar->isTeleporting = false;
	}
}

// Updates scene capture to reflect view from the other portal
void APortal::UpdatePortals()
{
	// Calculate offset between portals
	FVector Location = this->GetActorLocation() - OtherPortal->GetActorLocation();

	// Get current camera location and rotation
	FVector camLocation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentLocation();
	FRotator camRotation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentRotation();

	// Offset camera position by portal difference
	FVector CombinedLocation = camLocation + Location;

	// Update scene capture to simulate the camera at the other portal's perspective
	sceneCapture->SetWorldLocationAndRotation(CombinedLocation, camRotation);
}
