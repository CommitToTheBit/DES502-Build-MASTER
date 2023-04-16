#include "DES_L_Blood_Vessel.h"

ADES_L_Blood_Vessel::ADES_L_Blood_Vessel()
{
	PrimaryActorTick.bCanEverTick = false;
}

ADES_L_Blood_Vessel::~ADES_L_Blood_Vessel()
{

}

void ADES_L_Blood_Vessel::BeginPlay()
{
	Super::BeginPlay();

}

void ADES_L_Blood_Vessel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADES_L_Blood_Vessel::Initialize(UProceduralMeshComponent* Mesh, float Width, int Iterations, float Seed)
{
	// STEP 1: Write production rules...
	FDES_ProductionRule CForward;
	CForward.Productions.Add([this](FDES_L_Module L_Module) {
		FDES_L_Module K_Module = L_Module;
		K_Module.Letter = "X";
		return K_Module;
		});
	CForward.Productions.Add([this](FDES_L_Module L_Module) {
		FDES_L_Module K_Module = L_Module;
		K_Module.Letter = "C";
		K_Module.StaticRotation = 0.0f;
		K_Module.StaticWidth *= 1.0f / pow(1.0f + pow(L_Module.Asymmetry, 3.0f), 1.0f / 3.0f);
		return K_Module;
		});
	CForward.Weight = 3.0f;
	AddProductionRule("C", CForward);

	FDES_ProductionRule CLeft;
	CLeft.Productions.Add([this](FDES_L_Module L_Module) {
		FDES_L_Module K_Module = L_Module;
		K_Module.Letter = "X";
		return K_Module;
		});
	CLeft.Productions.Add([this](FDES_L_Module L_Module) {
		FDES_L_Module K_Module = L_Module;
		K_Module.Letter = "[";
		return K_Module;
		});
	CLeft.Productions.Add([this](FDES_L_Module L_Module) {
		FDES_L_Module K_Module = L_Module;
		K_Module.Letter = "L";
		K_Module.StaticLength *= 0.95f / pow(1.0f + pow(L_Module.Asymmetry, 3.0f), 1.0f / 3.0f);
		K_Module.RandomStaticLength *= 0.95f / pow(1.0f + pow(L_Module.Asymmetry, 3.0f), 1.0f / 3.0f);
		K_Module.RandomPeriodicLength *= 0.95f / pow(1.0f + pow(L_Module.Asymmetry, 3.0f), 1.0f / 3.0f);
		K_Module.StaticRotation = acos((pow(1.0f + pow(L_Module.Asymmetry, 3.0f), 4.0f / 3.0f) + 1.0f - pow(L_Module.Asymmetry, 4.0f)) / (2.0f * pow(L_Module.Asymmetry, 0.0f) * pow(1.0f + pow(L_Module.Asymmetry, 3.0f), 2.0f / 3.0f)));
		K_Module.PeriodicRotation *= 1.0f + 1.0f / pow(1.0f + pow(L_Module.Asymmetry, 3.0f), 1.0f / 3.0f);
		K_Module.RandomPeriodicRotation *= 1.0f + 1.0f / pow(1.0f + pow(L_Module.Asymmetry, 3.0f), 1.0f / 3.0f);
		K_Module.StaticWidth *= 0.95f / pow(1.0f + pow(L_Module.Asymmetry, 3.0f), 1.0f / 3.0f);
		return K_Module;
		});
	CLeft.Productions.Add([this](FDES_L_Module L_Module) {
		FDES_L_Module K_Module = L_Module;
		K_Module.Letter = "]";
		return K_Module;
		});
	CLeft.Productions.Add([this](FDES_L_Module L_Module) {
		FDES_L_Module K_Module = L_Module;
		K_Module.Letter = "R";
		K_Module.StaticLength *= 0.5625f * L_Module.Asymmetry / pow(1.0f + pow(L_Module.Asymmetry, 3.0f), 1.0f / 3.0f);
		K_Module.RandomStaticLength *= 0.5625f * L_Module.Asymmetry / pow(1.0f + pow(L_Module.Asymmetry, 3.0f), 1.0f / 3.0f);
		K_Module.RandomPeriodicLength *= 0.5625f * L_Module.Asymmetry / pow(1.0f + pow(L_Module.Asymmetry, 3.0f), 1.0f / 3.0f);
		K_Module.StaticRotation = -acos((pow(1.0f + pow(L_Module.Asymmetry, 3.0f), 4.0f / 3.0f) + pow(L_Module.Asymmetry, 4.0f) - 1.0f) / (2.0f * pow(L_Module.Asymmetry, 2.0f) * pow(1.0f + pow(L_Module.Asymmetry, 3.0f), 2.0f / 3.0f)));
		K_Module.PeriodicRotation = 1.0f + 1.0f * L_Module.Asymmetry / pow(1.0f + pow(L_Module.Asymmetry, 3.0f), 1.0f / 3.0f);
		K_Module.RandomPeriodicRotation = 1.0f + 1.0f * L_Module.Asymmetry / pow(1.0f + pow(L_Module.Asymmetry, 3.0f), 1.0f / 3.0f);
		K_Module.StaticWidth = 0.5625f * L_Module.Asymmetry / pow(1.0f + pow(L_Module.Asymmetry, 3.0f), 1.0f / 3.0f);
		return K_Module;
		});
	CLeft.Weight = 1.0f;
	AddProductionRule("C", CLeft);

	// STEP 2: Write axiom...
	FDES_L_Module C_Module = FDES_L_Module();
	C_Module.Letter = "C";
	C_Module.Period = 2.5f;
	C_Module.Aperiodicity = 0.5f;
	C_Module.Synchronisation = 0.0f;
	C_Module.Asynchronicity = 1.0f;
	C_Module.StaticLength = 1.0f;
	C_Module.RandomStaticLength = 0.5f;
	C_Module.RandomPeriodicLength = 0.125f;
	C_Module.StaticRotation = 0.0f;
	C_Module.RandomStaticRotation = 4.0f * PI / 180.0f;
	C_Module.PeriodicRotation = 0.1f * PI / 180.0f;
	C_Module.RandomPeriodicRotation = 1.0f * PI / 180.0f;
	C_Module.StaticWidth = Width;
	C_Module.StaticAsymmetry = 0.8f;
	C_Module.RandomStaticAsymmetry = 0.1f;

	TArray<FDES_L_Module> Axiom = TArray<FDES_L_Module>{ C_Module };

	// STEP 3: Initialise...
	return Super::Initialize(Mesh, Axiom, Iterations, Seed, PI / 2.0f);
}