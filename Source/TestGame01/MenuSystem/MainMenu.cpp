// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/TextBlock.h"
#include "Internationalization/Text.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableText.h"

void UMainMenu::NativeConstruct()
{

	Super::NativeConstruct();

	if(MainMenuTxt != nullptr)
	{
		MainMenuTxt->SetText(FText::FromString("Mein Menu"));
		
	}
}

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if(!Success) {return false;} //double check the pointers       

	if(!ensure(HostBtn!=nullptr)) return false;  //double check the pointers
	HostBtn->OnPressed.AddDynamic(this, &UMainMenu::HostServer);
	
	if(!ensure(JoinMenuBtn!=nullptr)) return false;  //double check the pointers
	JoinMenuBtn->OnPressed.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if(!ensure(JoinBtn!=nullptr)) return false;  //double check the pointers
	JoinBtn->OnPressed.AddDynamic(this, &UMainMenu::JoinServer);

	if(!ensure(CancelJoinMenuBtn!=nullptr)) return false;  //double check the pointers
	CancelJoinMenuBtn->OnPressed.AddDynamic(this, &UMainMenu::OpenMainMenu);
	
	return true;
}

void UMainMenu::SetMenuInterface(IMenuInterface* InMenuInterface)
{
	//this-> to remove ambiguity
	this->MenuInterface = InMenuInterface;    
}

void UMainMenu::HostServer()
{
	UE_LOG(LogTemp, Warning, TEXT("HostServer pressed"));
	
	if(MenuInterface != nullptr)
	{
		MenuInterface->Host();
	}
}

void UMainMenu::JoinServer()
{
	FString IpAddr = IpAddrArea->GetText().ToString();	 
	
	if(MenuInterface != nullptr && IpAddr != "")
	{
		
		MenuInterface->Join(IpAddr);
	}
}

void UMainMenu::OpenJoinMenu()
{
	MenuSwitch->SetActiveWidget(JoinMenu);	
}

void UMainMenu::OpenMainMenu()
{
	MenuSwitch->SetActiveWidget(MainMenuArea);
}

void UMainMenu::Setup()
{
	UWorld* World = GetWorld();
	if(!ensure(World!=nullptr)){return;}
	
	//setting preparations to set input mode and mouse coursor
    	FInputModeUIOnly InputModeData;
    	InputModeData.SetWidgetToFocus(this->TakeWidget());
    	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    
    	APlayerController* PlayerController = World->GetFirstPlayerController();
    	if(!ensure(PlayerController!=nullptr)){return;}
    
    	PlayerController->SetInputMode(InputModeData);
    	PlayerController->bShowMouseCursor = true;

}

void UMainMenu::TierDown()
{
	UWorld* World = GetWorld();
	if(!ensure(World!=nullptr)){return;}
	
	///setting preparations to set input mode and mouse coursor
	FInputModeGameOnly InputModeData;	
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if(!ensure(PlayerController!=nullptr)){return;}
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = false;
}
	