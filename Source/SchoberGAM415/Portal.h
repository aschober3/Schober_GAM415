// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Portal.generated.h"

class SchoberGAM415Character;

UCLASS()
class SCHOBERGAM415_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Visual mesh for the portal
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* mesh;

	// Scene capture component that renders the view from the other portal
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneCaptureComponent2D* sceneCapture;

	// Arrow to indicate forward direction of the portal
	UPROPERTY(EditAnywhere)
		UArrowComponent* rootArrow;

	// Render target that the scene capture will write to
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextureRenderTarget2D* renderTarget;

	// Collision box used to detect overlaps with players
	UPROPERTY(EditAnywhere)
		UBoxComponent* boxComp;

	// Reference to the paired portal
	UPROPERTY(EditAnywhere)
		APortal* OtherPortal;

	// Material to apply to the portal mesh (likely uses the render target)
	UPROPERTY(EditAnywhere)
		UMaterialInterface* mat;

	// Overlap event callback when a player enters the portal
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Called to update the portal-travel flag for the character
	UFUNCTION()
		void SetBool(ASchoberGAM415Character* playerChar);

	// Updates the portal's render view and transformation
	UFUNCTION()
		void UpdatePortals();

};
