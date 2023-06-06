// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BvC_BaseGameMode.h"
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

	void UpdateTestInfoText();
	void SetTestInfoText();	

protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
	USphereComponent* SphereComp;
	UPROPERTY(EditAnywhere)
	UTextRenderComponent* MethodTextRender;
	UPROPERTY(EditAnywhere)
	UTextRenderComponent* IterationsTextRender;
	UPROPERTY(EditAnywhere)
	UTextRenderComponent* TimeTextRender;
	UPROPERTY(EditAnywhere)
	UTextRenderComponent* CalculationsTextRender;

	UPROPERTY()
	ABvC_BaseGameMode* BvCGameMode;

	FTimerHandle RequestDataDelayTimerHandle;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BvC")
	FName TestID;
	UPROPERTY(BlueprintReadOnly, Category = "BvC")
	int NumOfIterations;
	UPROPERTY(BlueprintReadWrite, Category = "BvC")
	int NumOfBPCalcs;
	UPROPERTY()
	uint64 NumOfCalculations;
	UPROPERTY()
	double StartTime;
	UPROPERTY()
	double TimeElapsed;
	UPROPERTY(BlueprintReadOnly, Category = "BvC")
	FText MethodText;
	UPROPERTY(BlueprintReadOnly, Category = "BvC")
	FText IterationsText;
	UPROPERTY(BlueprintReadOnly, Category = "BvC")
	FText ElapsedTimeText;
	UPROPERTY(BlueprintReadOnly, Category = "BvC")
	FText TotalCalculationsText;
	UPROPERTY(BlueprintReadWrite, Category = "BvC")
	bool bSwapped;
	UPROPERTY(BlueprintReadWrite, Category = "BvC")
	TArray<int> IntArray;
	
	// Initial test loops for simple addition calculation
	//Starting loop for += using the BP version of addition
	UFUNCTION(BlueprintCallable)
	void StartTestIterations(int InLastIndex);
	//Second loop for += using the BP version of addition
	UFUNCTION(BlueprintCallable)
	void StartSecondLoop(int InLastIndex);
	//Starting loop for using the increment version of addition
	UFUNCTION(BlueprintCallable)
	void StartTestIterationsPlusPlus(int InLastIndex);
	//Second loop for using the increment version of addition
	UFUNCTION(BlueprintCallable)
	void StartSecondLoopPlusPlus(int InLastIndex);
	//Starts Outer loop for bubble sort function
	UFUNCTION(BlueprintCallable)
	void StartBubbleSortOuter(int InLastIndex);
	//Starts inner loop for bubble sort function
	UFUNCTION(BlueprintCallable)
	void StartBubbleSortInner();
	//Prints sorted array to log and mixes it up for next test
	UFUNCTION(BlueprintCallable)
	void PrintBubbleSortArray();
	//Sets performance test start time
	UFUNCTION(BlueprintCallable)
	void SetStartTime();
	//Calculates the duration of the performance test
	UFUNCTION(BlueprintCallable)
	void CalculateElapsedTime();
	//Collect results and update TextRenderComponents
	UFUNCTION(BlueprintCallable)
	void CollectResults();
	UFUNCTION(BlueprintCallable)
	double SetDecimalPlaces(double InTimeElapsed, int AccuracyLowerLimit, int DecimalPlaces);

private:
	UPROPERTY()
	UDataTable* TestTable;
	
	
};
