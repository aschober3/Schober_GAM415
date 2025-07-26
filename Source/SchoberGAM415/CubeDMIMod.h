// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CubeDMIMod.generated.h"

class UNiagaraSystem;

UCLASS()
class SCHOBERGAM415_API ACubeDMIMod : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACubeDMIMod();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Collision box component used to detect overlaps
	UPROPERTY(EditAnywhere)
		UBoxComponent* boxComp;

	// Mesh component representing the cube's visual appearance
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* cubeMesh;

	// Base material applied to the cube before dynamic changes
	UPROPERTY(EditAnywhere)
		UMaterial* baseMat;

	// Dynamic material instance for runtime color/parameter changes
	UPROPERTY()
		UMaterialInstanceDynamic* dmiMat;

	// Niagara system to spawn visual effects on color change or interaction
	UPROPERTY(EditAnywhere)
		UNiagaraSystem* colorP;

	// Function called when another actor begins overlapping with the box component
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
};
