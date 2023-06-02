// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BvC_Target.generated.h"

class UDataTable;
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
	UPROPERTY(EditAnywhere)
	UTextRenderComponent* MethodTextRender;
	UPROPERTY(EditAnywhere)
	UTextRenderComponent* IterationsTextRender;
	UPROPERTY(EditAnywhere)
	UTextRenderComponent* TimeTextRender;
	UPROPERTY(EditAnywhere)
	UTextRenderComponent* CalculationsTextRender;

	UDataTable* GetTestTable() { return TestTable; }
	void SetTestTable(UDataTable* InVal) { TestTable = InVal; }
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BvC")
	FName TestID;
	UPROPERTY(BlueprintReadOnly, Category = "BvC")
	int NumOfIterations;
	UPROPERTY(BlueprintReadWrite, Category = "BvC")
	int NumOfCalculations;
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
	
	void SetTestInfoText();	
	
	// Initial test loops for simple addition calculation
	UFUNCTION(BlueprintCallable)
	void StartTestIterations(int InLastIndex);
	UFUNCTION(BlueprintCallable)
	void StartSecondLoop(int InLastIndex);	
	UFUNCTION(BlueprintCallable)
	void StartTestIterationsPlusPlus(int InLastIndex);
	UFUNCTION(BlueprintCallable)
	void StartSecondLoopPlusPlus(int InLastIndex);
	
	UFUNCTION(BlueprintCallable)
	void SetStartTime();
	UFUNCTION(BlueprintCallable)
	void CalculateElapsedTime();
	UFUNCTION(BlueprintCallable)
	void CollectResults();
	UFUNCTION(BlueprintCallable)
	double SetDecimalPlaces(double InTimeElapsed, int AccuracyLowerLimit, int DecimalPlaces);

private:
	UPROPERTY()
	UDataTable* TestTable;
};
