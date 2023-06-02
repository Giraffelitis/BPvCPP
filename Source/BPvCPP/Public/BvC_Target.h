// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BvC_Target.generated.h"

class UTextRenderComponent;
class USphereComponent;

UCLASS()
class BPVCPP_API ABvC_Target : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABvC_Target();

protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
	USphereComponent* SphereComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextRenderComponent* MethodTextRender;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextRenderComponent* IterationsTextRender;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextRenderComponent* TimeTextRender;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextRenderComponent* CalculationsTextRender;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BvC")
	int NumOfIterations;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BvC")
	int TestID;
	UPROPERTY(BlueprintReadWrite, Category = "BvC")
	int NumOfCalculations;
	UPROPERTY(BlueprintReadWrite, Category = "BvC")
	double StartTime;
	UPROPERTY(BlueprintReadWrite, Category = "BvC")
	double TimeElapsed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BvC")
	FText MethodText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BvC")
	FText IterationsText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BvC")
	FText ElapsedTimeText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BvC")
	FText TotalCalculationsText;
	
	// Initial test loops for simple addition calculation
	UFUNCTION(BlueprintCallable)
	void SetStartTime();
	UFUNCTION(BlueprintCallable)
	void CalculateElapsedTime();
	UFUNCTION(BlueprintCallable)
	double SetDecimalPlaces(double InTimeElapsed, int AccuracyLowerLimit, int DecimalPlaces);
	UFUNCTION(BlueprintCallable)
	void CollectResults();
	UFUNCTION(BlueprintCallable)
	void StartTestIterations(int InLastIndex);
	UFUNCTION(BlueprintCallable)
	void StartSecondLoop(int InLastIndex);	
	UFUNCTION(BlueprintCallable)
	void StartTestIterationsPlusPlus(int InLastIndex);
	UFUNCTION(BlueprintCallable)
	void StartSecondLoopPlusPlus(int InLastIndex);
	
};
