// Fill out your copyright notice in the Description page of Project Settings.


#include "CapstoneEndingUI.h"
#include "Components/Image.h"

void UCapstoneEndingUI::NativeConstruct()
{
	Super::NativeConstruct();

	Image = Cast<UImage>(GetWidgetFromName(TEXT("BadIMG")));

}


void UCapstoneEndingUI::SetHappyEnding()
{
	Image->SetVisibility(ESlateVisibility::Collapsed);
}