// Copyright Epic Games, Inc. All Rights Reserved.

#include "VariablesDebuggerStyle.h"
#include "VariablesDebuggerModule.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FVariablesDebuggerStyle::StyleInstance = nullptr;

void FVariablesDebuggerStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FVariablesDebuggerStyle::Shutdown()
{
	if (StyleInstance.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
		ensure(StyleInstance.IsUnique());
		StyleInstance.Reset();
	}

}

FName FVariablesDebuggerStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("VariablesDebuggerStyle"));
	return StyleSetName;
}


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FVariablesDebuggerStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("VariablesDebuggerStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("VariablesDebugger")->GetBaseDir() / TEXT("Resources"));

	Style->Set("VariablesDebugger.PluginAction", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));
	return Style;
}

void FVariablesDebuggerStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FVariablesDebuggerStyle::Get()
{
	return *StyleInstance;
}
