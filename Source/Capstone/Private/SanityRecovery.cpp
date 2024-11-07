// Fill out your copyright notice in the Description page of Project Settings.


#include "SanityRecovery.h"
#include "Components/WidgetComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "CapstoneCharacter.h"

// Sets default values
ASanityRecovery::ASanityRecovery()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	RootComponent = Mesh;
	

	UStaticMesh* SM_Object = Cast< UStaticMesh >(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("StaticMesh'/Game/SICKA_mansion/StaticMeshes/SM_Candlestickfourside.SM_Candlestickfourside'")));
	if (SM_Object) {
		Mesh->SetStaticMesh(SM_Object);
	}
	
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NE(TEXT("NiagaraSystem'/Game/SICKA_mansion/ParticleSystems/Particle_Fire_Emitter_System.Particle_Fire_Emitter_System'"));
	if (NE.Succeeded())
	{
		SanityFXSystem = NE.Object;
	}

	// ��ȣ�ۿ� UI
	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("INTERACTIONWIDGET"));
	InteractionWidget->SetupAttachment(Mesh);
	InteractionWidget->SetRelativeLocation(FVector(0, 0, 0));
	InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_Interaction(TEXT("/Game/UI/UI_Interaction.UI_Interaction_C"));
	if (UI_Interaction.Succeeded())
	{
		InteractionWidget->SetWidgetClass(UI_Interaction.Class);
		InteractionWidget->SetDrawSize(FVector2D(50, 40));
	}
	InteractionWidget->SetVisibility(false);
}

// Called when the game starts or when spawned
void ASanityRecovery::BeginPlay()
{
	Super::BeginPlay();
	
	SanityFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SanityFXSystem, FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 60.0f));

	if (SanityFXComponent)
	{
		SanityFXComponent->Activate();
	}
}

// Called every frame
void ASanityRecovery::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASanityRecovery::SetInteractionUIVisible(bool NewBool)
{
	InteractionWidget->SetVisibility(NewBool);
}

void ASanityRecovery::Interaction()
{
	ACapstoneCharacter* Ch = Cast<ACapstoneCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	Ch->SetSanity(Ch->GetSanity() + 10.0);

	Destroy();
	SanityFXComponent->Deactivate();
}

