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

	BvCGameMode->OnDataTableUpdated.AddUObject(this,&ThisClass::SetTestInfoText);
	IntArray = {64, 34, 72, 25, 18, 12, 22, 11, 90, 3, 47, 53, 13, 24, 99, 2, 16, 39, 9, 42, 57, 74, 63, 85, 6,};
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

void ABvC_Target::SetStartTime()
{
	NumOfBPCalcs = 0;
	NumOfCalculations = 0;
	
	StartTime = FGenericPlatformTime::ToMilliseconds64(FPlatformTime::Cycles64());
}

void ABvC_Target::CalculateElapsedTime()
{
	TimeElapsed = FGenericPlatformTime::ToMilliseconds64(FPlatformTime::Cycles64()) - StartTime;
}

void ABvC_Target::CollectResults()
{
	if (NumOfBPCalcs > NumOfCalculations)
	{
		NumOfCalculations = NumOfBPCalcs;
	}
	
	TotalCalculationsText = FText::AsNumber(NumOfCalculations);
	CalculationsTextRender->SetText(TotalCalculationsText);

	TimeElapsed = SetDecimalPlaces(TimeElapsed, 10, 2);
	FString TempString = FString::SanitizeFloat(TimeElapsed);
	
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

void ABvC_Target::StartTestIterations(int InLastIndex)
{
	for (int i = 1; i <= InLastIndex; i++)
	{
		 StartSecondLoop(i);
	}
}

void ABvC_Target::StartSecondLoop(int InLastIndex)
{
	for (int i = 1; i <= InLastIndex; i++)
	{
		NumOfCalculations += 1;
	}
}

void ABvC_Target::StartTestIterationsPlusPlus(int InLastIndex)
{
	for (int i = 1; i <= InLastIndex; i++)
	{
		StartSecondLoopPlusPlus(i);
	}
}

void ABvC_Target::StartSecondLoopPlusPlus(int InLastIndex)
{
	for (int i = 1; i <= InLastIndex; i++)
	{
		NumOfCalculations++;
	}
}

void ABvC_Target::StartBubbleSortOuter(int InLastIndex)
{
	for (int i = 0; i <= InLastIndex; i++)
	{
		StartBubbleSortInner();
	}
}

void ABvC_Target::StartBubbleSortInner()
{
	for (int i = 0; i < IntArray.Num() - 2; i++)
		{
		bSwapped = false;
		for (int j = 0; j <= IntArray.Num() - i - 2; j++)
			{
			NumOfCalculations++;
			if (IntArray[j] > IntArray[j + 1])
			{
					Swap(IntArray[j], IntArray[j + 1]);
					bSwapped = true;
			}
		}
		// If no two elements were swapped in the inner loop, the array is already sorted
		if (!bSwapped)
			break;
	}
}

void ABvC_Target::PrintBubbleSortArray()
{
	FString Temp = "Array order: ";
	for(int Int : IntArray )
	{
		Temp.Append(FString::FromInt(Int));
		Temp.Append(", ");
	}
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Temp);
	IntArray.Empty();
	IntArray = {64, 34, 72, 25, 18, 12, 22, 11, 90, 3, 47, 53, 13, 24, 99, 2, 16, 39, 9, 42, 57, 74, 63, 85, 6,};
}