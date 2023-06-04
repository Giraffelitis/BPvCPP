// Fill out your copyright notice in the Description page of Project Settings.


#include "BvC_Target.h"

#include "BvC_BaseGameMode.h"
#include "BvC_DataTypes.h"
#include "Components/SphereComponent.h"
#include "Components/TextRenderComponent.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformTime.h"

// Sets default values
ABvC_Target::ABvC_Target()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetupAttachment(Mesh);

	MethodTextRender = CreateDefaultSubobject<UTextRenderComponent>("Method Text");
	MethodTextRender->SetupAttachment(Mesh);
	IterationsTextRender = CreateDefaultSubobject<UTextRenderComponent>("Iterations Text");
	IterationsTextRender->SetupAttachment(Mesh);
	TimeTextRender = CreateDefaultSubobject<UTextRenderComponent>("Time Text");
	TimeTextRender->SetupAttachment(Mesh);
	CalculationsTextRender = CreateDefaultSubobject<UTextRenderComponent>("Calculations Text");
	CalculationsTextRender->SetupAttachment(Mesh);

	TestID = "None";
}

void ABvC_Target::BeginPlay()
{
	Super::BeginPlay();

	BvCGameMode = Cast<ABvC_BaseGameMode>(GetWorld()->GetAuthGameMode());
	if(!IsValid(BvCGameMode)) return;

	SetTestInfoText();
}

void ABvC_Target::SetTestInfoText()
{
	TestTable = BvCGameMode->GetTestTable();
	FPerformanceTestList* TestData = TestTable->FindRow<FPerformanceTestList>(TestID,"");
	if(TestTable->GetRowMap().IsEmpty()) return;
	
	MethodTextRender->SetText(TestData->TestingMethod);
	NumOfIterations = TestData->NumOfTestIterations;
	IterationsTextRender->SetText(FText::AsNumber(NumOfIterations));
}

//Gets performance test start time
void ABvC_Target::SetStartTime()
{
	StartTime = FGenericPlatformTime::ToMilliseconds64(FPlatformTime::Cycles64());
}

//Calculates the duration of the performance test
void ABvC_Target::CalculateElapsedTime()
{
	TimeElapsed = FGenericPlatformTime::ToMilliseconds64(FPlatformTime::Cycles64()) - StartTime;
}

//Collect results and update TextRenderComponents
void ABvC_Target::CollectResults()
{
	TotalCalculationsText = FText::AsNumber(NumOfCalculations);
	CalculationsTextRender->SetText(TotalCalculationsText);

	TimeElapsed = SetDecimalPlaces(TimeElapsed, 10, 2);
	FString TempString = FString::SanitizeFloat(TimeElapsed);
	// Run significant figure conversion
	
	TempString.Append("ms");
	ElapsedTimeText = FText::FromString(TempString);
	TimeTextRender->SetText(ElapsedTimeText);
		
	UE_LOG(LogTemp, Warning, TEXT("@@@ BvC TestID: %s"), *TestID.ToString());
	UE_LOG(LogTemp, Warning, TEXT("@@@ BvC Number of Planned Iterations: %d"), NumOfIterations);
	UE_LOG(LogTemp, Warning, TEXT("@@@ BvC Total Number of Calculations: %d"), NumOfCalculations);
	UE_LOG(LogTemp, Warning, TEXT("@@@ BvC Elapsed Time: %f"), TimeElapsed);
}

double ABvC_Target::SetDecimalPlaces(double InTimeElapsed, int AccuracyLowerLimit, int DecimalPlaces)
{
	if (InTimeElapsed >= AccuracyLowerLimit)
	{
		InTimeElapsed = ceil(InTimeElapsed * 100)/100;
		return InTimeElapsed;
	}	
	return InTimeElapsed;	
}

//Starting loop for += using the BP version of addition
void ABvC_Target::StartTestIterations(int InLastIndex)
{
	for (int i = 1; i <= InLastIndex; i++)
	{
		 StartSecondLoop(i);
	}
}

//Second loop for += using the BP version of addition
void ABvC_Target::StartSecondLoop(int InLastIndex)
{
	for (int i = 1; i <= InLastIndex; i++)
	{
		NumOfCalculations += 1;
	}
}

//Starting loop for using the increment version of addition
void ABvC_Target::StartTestIterationsPlusPlus(int InLastIndex)
{
	for (int i = 1; i <= InLastIndex; i++)
	{
		StartSecondLoopPlusPlus(i);
	}
}

//Second loop for using the increment version of addition
void ABvC_Target::StartSecondLoopPlusPlus(int InLastIndex)
{
	for (int i = 1; i <= InLastIndex; i++)
	{
		NumOfCalculations++;
	}
}
