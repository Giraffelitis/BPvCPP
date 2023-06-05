// Copyright Epic Games, Inc. All Rights Reserved.

#include "BvC_BaseGameMode.h"
#include "BvC_DataTypes.h"
#include "Engine/DataTable.h"
#include "UObject/ConstructorHelpers.h"

ABvC_BaseGameMode::ABvC_BaseGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	Http = &FHttpModule::Get();
	
	//Gets the DT Blueprint and sets it 
	static ConstructorHelpers::FObjectFinder<UDataTable>
	TestTable_BP(TEXT("DataTable'/Game/TestingHub/Data/DT_PerformanceTestList'"));
	SetTestTable(TestTable_BP.Object);
	
	ResponseString = "None";
}

void ABvC_BaseGameMode::UpdateTestTable()
{
	//Call Http request 
	RetrieveTestTableData();

	// Set the Row Structure for the Data table
	FPerformanceTestList Row;

	//Create Row Array and parse Response String into it
	TArray<FString> RowArray ;
	ResponseString.ParseIntoArray(RowArray, TEXT("\r\n"), false);

	// Loop through each Element of RowArray and Parse into a TempArray
	for (int i = 1; i < RowArray.Num(); i++)
	{
		//Recreate Temp array for each iteration
		TArray<FString> TempArray;
		RowArray[i].ParseIntoArray(TempArray, TEXT(","));

		//Check element to make sure its the first element
		if (TempArray.Num() == 0){continue;}
		FString LineLabel = TempArray[0];
		if ((LineLabel.Len() == 0)  || LineLabel.StartsWith("\";") || LineLabel.StartsWith(";"))
		{
			continue;	// Skip comments or lines with no label
		}

		//Use elements from TempArray and fill into proper Struct fields
		Row.TestingMethod = FText::FromString(*TempArray[1]);
		Row.NumOfTestIterations = FCString::Atoi(*TempArray[2]);

		// Add the Row to the table
		TestTable->AddRow(FName(*TempArray[0]), Row);		
	}
	OnDataTableUpdated.Broadcast();
}

void ABvC_BaseGameMode::RetrieveTestTableData()
{
	// Create an http request
	// The request will execute asynchronously, and call us back on the Lambda below
	TSharedRef<IHttpRequest,ESPMode::ThreadSafe> Request = Http->CreateRequest();

	//Bind request response
	Request->OnProcessRequestComplete().BindUObject(this, &ThisClass::ProcessResponse);
	
	// Set Request URL
	Request->SetURL(GetURL());

	// This is where we set the HTTP method (GET, POST, etc)
	Request->SetVerb("GET");
	
	// We'll need to tell the server what type of content to expect in the POST data
	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("text/csv"));
	Request->SetHeader(TEXT("Accepts"), TEXT("text/csv"));

	// Submit the request for processing
	Request->ProcessRequest();
}

FString ABvC_BaseGameMode::GetURL()
{
	//Default GoogleSheet Url
	ApiBaseUrl = TEXT("https://docs.google.com/spreadsheets/d/");
	// This is where you need to change the DocID to get it to work with a different google sheet.
	// It needs to be shared as public for this to work 
	DocID = TEXT("1FMx0AtfPwXPzlOdKIgYyFYh62jZGZWYV1viUZpTwNLc"); 
	// This sets the Google Sheet to be exported into a csv
	Subroute = TEXT("/export?format=csv");
	//Return full URL
	return ApiBaseUrl + DocID + Subroute;
}

void ABvC_BaseGameMode::ProcessResponse(FHttpRequestPtr InRequest, FHttpResponsePtr InResponse, bool bWasSuccessful)
{
	//Checks is response was successful
	if (!ResponseIsValid(InResponse, bWasSuccessful))
	{
		UE_LOG(LogTemp, Warning, TEXT("HTTP Request Failed"))
		return;
	}

	//Store Response as string
	ResponseString = *InResponse->GetContentAsString();

	//Delegate verbiage if needed to be used somewhere else 
	//OnResponseDelegate.Broadcast(InResponse->GetContentAsString());
}

bool ABvC_BaseGameMode::ResponseIsValid(FHttpResponsePtr InResponse, bool bWasSuccessful)
{
	if (!bWasSuccessful || !InResponse.IsValid()) return false;
	if (EHttpResponseCodes::IsOk(InResponse->GetResponseCode())) return true;
	
	UE_LOG(LogTemp, Error, TEXT("Http Response returned error code: %d"), InResponse->GetResponseCode());
	return false;
}
