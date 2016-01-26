// Copyright (c) 2016, Matthias Hölzl

#include "PG.h"
#include "AutomationCommon.h"
#include "AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(SimpleTest1, "PatternGame.SimpleTest1", EAutomationTestFlags::ATF_SmokeTest)
bool SimpleTest1::RunTest(const FString& Parameters)
{
	TestEqual("1 equals 1", 1, 1);
	TestNotEqual("1 does not equal 2", 1, 2);
	TestTrue("true is true", true);
	TestTrue("1 is true", 1);
	TestFalse("false is false", false);
	TestFalse("0 is false", 0);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(SimpleTest2, "PatternGame.SimpleTest2", EAutomationTestFlags::ATF_SmokeTest)
bool SimpleTest2::RunTest(const FString& Parameters)
{
	UE_LOG(PG, Log, TEXT("Running another simple test"));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FailingTest1, "PatternGame.FailingTest1", EAutomationTestFlags::ATF_SmokeTest)
bool FailingTest1::RunTest(const FString& Parameters)
{
	TestEqual("1 equals 2", 1, 2);
	TestTrue("false is true", false);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FailingTest2, "PatternGame.FailingTest2", EAutomationTestFlags::ATF_None)
bool FailingTest2::RunTest(const FString& Parameters)
{
	return false;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FailingTest3, "PatternGame.FailingTest3", EAutomationTestFlags::ATF_None)
bool FailingTest3::RunTest(const FString& Parameters)
{
	UE_LOG(PG, Warning, TEXT("Running a test that logs a warning"));
	return true;
}

namespace TestUtilities
{
	// Overwrite this to avoid link errors:
	bool LoadMap(FString MapName)
	{
		if (GEngine->GetWorldContexts().Num() != 1)
		{
			return false;
		}
		if (GEngine->GetWorldContexts()[0].WorldType != EWorldType::Game)
		{
			return false;
		}
		UE_LOG(LogEngineAutomationTests, Log, TEXT("Loading Map Now. '%s'"), *MapName);
		GEngine->Exec(GEngine->GetWorldContexts()[0].World(), *FString::Printf(TEXT("Open %s"), *MapName));
		return true;
	}
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(ScreenshotTest, "PatternGame.ScreenshotTest", EAutomationTestFlags::ATF_Game)
bool ScreenshotTest::RunTest(const FString& Parameters)
{
	if (!TestUtilities::LoadMap(TEXT("SelectionLevel")))
	{
		UE_LOG(LogEngineAutomationTests, Warning, TEXT("Could not load level"));
		return false;
	}
	return true;
}