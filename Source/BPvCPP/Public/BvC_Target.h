// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"
#include "BvC_Target.generated.h"

class USphereComponent;

UCLASS()
class BPVCPP_API ABvC_Target : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABvC_Target();

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
	USphereComponent* SphereComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BCT")
	int NumOfIterations;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BCT")
	int TestID;
	UPROPERTY(BlueprintReadWrite, Category = "BCT")
	int Result;

	UFUNCTION(BlueprintCallable)
	void StartTestIterations(int InLastIndex);
	UFUNCTION(BlueprintCallable)
	void StartSecondLoop(int InLastIndex);	
	UFUNCTION(BlueprintCallable)
	void StartTestIterationsPlusPlus(int InLastIndex);
	UFUNCTION(BlueprintCallable)
	void StartSecondLoopPlusPlus(int InLastIndex);
	UFUNCTION(BlueprintCallable)
	void StartTestIterationsBranch(int InLastIndex);
};
