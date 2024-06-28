//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
#include "G4ParticleHPMessenger.hh"

#include "G4HadronicParameters.hh"
#include "G4ParticleHPManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"
#include "G4UIparameter.hh"
#include "G4UnitsTable.hh"

G4ParticleHPMessenger::G4ParticleHPMessenger(G4ParticleHPManager* man) : manager(man)
{
  ParticleHPDir = new G4UIdirectory("/process/had/particle_hp/");
  ParticleHPDir->SetGuidance("UI commands of ParticleHP");

  PhotoEvaCmd = new G4UIcmdWithAString("/process/had/particle_hp/use_photo_evaporation", this);
  PhotoEvaCmd->SetGuidance(
    " Force the use of the Photon Evaporation model, instead of the neutron capture final state "
    "data.");
  PhotoEvaCmd->SetParameterName("choice", false);
  PhotoEvaCmd->SetCandidates("true false");
  PhotoEvaCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  SkipMissingCmd = new G4UIcmdWithAString("/process/had/particle_hp/skip_missing_isotopes", this);
  SkipMissingCmd->SetGuidance(
    "Use only exact isotope data files, instead of allowing nearby isotope files to be used.");
  SkipMissingCmd->SetGuidance(
    "In this case if the exact file is not available, the cross section will be set to zero.");
  SkipMissingCmd->SetParameterName("choice", false);
  SkipMissingCmd->SetCandidates("true false");
  SkipMissingCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  NeglectDopplerCmd =
    new G4UIcmdWithAString("/process/had/particle_hp/neglect_Doppler_broadening", this);
  NeglectDopplerCmd->SetGuidance(
    "Switch off the Doppler broadening due to the thermal motion of the target nucleus.");
  NeglectDopplerCmd->SetGuidance("This option provides a significant CPU performance advantage.");
  NeglectDopplerCmd->SetParameterName("choice", false);
  NeglectDopplerCmd->SetCandidates("true false");
  NeglectDopplerCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  DoNotAdjustFSCmd =
    new G4UIcmdWithAString("/process/had/particle_hp/do_not_adjust_final_state", this);
  DoNotAdjustFSCmd->SetGuidance("Disable to adjust final state for getting better conservation.");
  DoNotAdjustFSCmd->SetParameterName("choice", false);
  DoNotAdjustFSCmd->SetCandidates("true false");
  DoNotAdjustFSCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  ProduceFissionFragementCmd =
    new G4UIcmdWithAString("/process/had/particle_hp/produce_fission_fragment", this);
  ProduceFissionFragementCmd->SetGuidance("Enable to generate fission fragments.");
  ProduceFissionFragementCmd->SetParameterName("choice", false);
  ProduceFissionFragementCmd->SetCandidates("true false");
  ProduceFissionFragementCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  WendtFissionModelCmd =
    new G4UIcmdWithAString("/process/had/particle_hp/use_Wendt_fission_model", this);
  WendtFissionModelCmd->SetGuidance("Enable use of Wendt fission model.");
  WendtFissionModelCmd->SetParameterName("choice", false);
  WendtFissionModelCmd->SetCandidates("true false");
  WendtFissionModelCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  NRESP71Cmd = new G4UIcmdWithAString("/process/had/particle_hp/use_NRESP71_model", this);
  NRESP71Cmd->SetGuidance("Enable to use NRESP71 model for n on C reaction");
  NRESP71Cmd->SetParameterName("choice", false);
  NRESP71Cmd->SetCandidates("true false");
  NRESP71Cmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  VerboseCmd = new G4UIcmdWithAnInteger("/process/had/particle_hp/verbose", this);
  VerboseCmd->SetGuidance("Set Verbose level of ParticleHP package");
  VerboseCmd->SetParameterName("verbose_level", true);
  VerboseCmd->SetDefaultValue(1);
  VerboseCmd->SetRange("verbose_level >=0");
  VerboseCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  UseDBRCCmd = new G4UIcmdWithABool("/process/had/particle_hp/use_DBRC", this);
  UseDBRCCmd->SetGuidance("Enable use of Doppler Broadening Rejection Correction algorithm.");
  UseDBRCCmd->SetDefaultValue(false);
  UseDBRCCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  MaxEnergySVTCmd = new G4UIcmdWithADoubleAndUnit("/process/had/particle_hp/SVT_E_max", this);
  MaxEnergySVTCmd->SetGuidance("Energy threshold under which the SVT method is applied.");
  MaxEnergySVTCmd->SetGuidance("The default is 400. kT.");
  MaxEnergySVTCmd->SetParameterName("MaxEnergySVT", false);
  MaxEnergySVTCmd->SetRange("MaxEnergySVT>=0.");
  MaxEnergySVTCmd->SetUnitCategory("Energy");
  MaxEnergySVTCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  MinADBRCCmd = new G4UIcmdWithADouble("/process/had/particle_hp/DBRC_A_min", this);
  MinADBRCCmd->SetGuidance("Atomic mass in neutron mass above which the DBRC is applied.");
  MinADBRCCmd->SetGuidance("The default is A=200.");
  MinADBRCCmd->SetParameterName("MinASVT", false);
  MinADBRCCmd->SetRange("MinASVT>=0.");
  MinADBRCCmd->SetDefaultValue(200);
  MinADBRCCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  MinEnergyDBRCCmd = new G4UIcmdWithADoubleAndUnit("/process/had/particle_hp/DBRC_E_min", this);
  MinEnergyDBRCCmd->SetGuidance(
    "Energy threshold under which the DBRC method is not applied and only the SVT is used.");
  MinEnergyDBRCCmd->SetGuidance("The default value is 0.1 eV.");
  MinEnergyDBRCCmd->SetParameterName("MinEnergyDBRC", false);
  MinEnergyDBRCCmd->SetRange("MinEnergyDBRC>0.");
  MinEnergyDBRCCmd->SetUnitCategory("Energy");
  MinEnergyDBRCCmd->SetDefaultValue(0.1 * CLHEP::eV);
  MinEnergyDBRCCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  MaxEnergyDBRCCmd = new G4UIcmdWithADoubleAndUnit("/process/had/particle_hp/DBRC_E_max", this);
  MaxEnergyDBRCCmd->SetGuidance("Energy threshold under which the DBRC method is applied.");
  MaxEnergyDBRCCmd->SetGuidance("The default value is 210. eV.");
  MaxEnergyDBRCCmd->SetParameterName("MaxEnergyDBRC", false);
  MaxEnergyDBRCCmd->SetRange("MaxEnergyDBRC>0.");
  MaxEnergyDBRCCmd->SetUnitCategory("Energy");
  MaxEnergyDBRCCmd->SetDefaultValue(210. * CLHEP::eV);
  MaxEnergyDBRCCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  PTformatCmd = new G4UIcmdWithAString("/process/had/particle_hp/use_probability_table_from", this);
  PTformatCmd->SetGuidance("Choose format of the probability tables.");
  PTformatCmd->SetParameterName("choice", false);
  PTformatCmd->SetCandidates("njoy calendf");
  PTformatCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

G4ParticleHPMessenger::~G4ParticleHPMessenger()
{
  delete ParticleHPDir;
  delete PhotoEvaCmd;
  delete SkipMissingCmd;
  delete NeglectDopplerCmd;
  delete DoNotAdjustFSCmd;
  delete ProduceFissionFragementCmd;
  delete WendtFissionModelCmd;
  delete NRESP71Cmd;
  delete VerboseCmd;
  delete UseDBRCCmd;
  delete MaxEnergySVTCmd;
  delete MinADBRCCmd;
  delete MinEnergyDBRCCmd;
  delete MaxEnergyDBRCCmd;
  delete PTformatCmd;
}

void G4ParticleHPMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  G4bool bValue = false;
  if (newValue == "true") bValue = true;

  if (command == PhotoEvaCmd) {
    if (manager->GetUseOnlyPhotoEvaporation() != bValue) {
      manager->SetUseOnlyPhotoEvaporation(bValue);
#ifdef G4VERBOSE
      if (G4HadronicParameters::Instance()->GetVerboseLevel() > 0) {
        G4cout << G4endl
               << "=== G4ParticleHPMessenger CHANGED PARAMETER UseOnlyPhotoEvaporation TO "
               << bValue << " ===" << G4endl;
      }
      if (bValue) {
        G4cout << "    -> Forced the use of the Photon Evaporation model (instead of the neutron "
                  "capture final state data)"
               << G4endl;
      }
      else {
        G4cout << "    -> Go back to use the default neutron capture final state data !" << G4endl;
      }
#endif
    }
  }

  if (command == SkipMissingCmd) {
    if (manager->GetSkipMissingIsotopes() != bValue) {
      manager->SetSkipMissingIsotopes(bValue);
#ifdef G4VERBOSE
      if (G4HadronicParameters::Instance()->GetVerboseLevel() > 0) {
        G4cout << G4endl << "=== G4ParticleHPMessenger CHANGED PARAMETER SkipMissingIsotopes TO "
               << bValue << " ===" << G4endl;
      }
      if (bValue) {
        G4cout
          << "    -> Use only exact isotope data files, instead of allowing nearby isotope files "
             "to be used: \n"
          << "       if the exact file is not available, the cross section will be set to zero !"
          << G4endl;
      }
      else {
        G4cout << "    -> Go back to the default, i.e. use nearby isotope files when the exact "
                  "isotope data files are not found !"
               << G4endl;
      }
#endif
    }
  }

  if (command == NeglectDopplerCmd) {
    if (manager->GetNeglectDoppler() != bValue) {
      manager->SetNeglectDoppler(bValue);
#ifdef G4VERBOSE
      if (G4HadronicParameters::Instance()->GetVerboseLevel() > 0) {
        G4cout << G4endl << "=== G4ParticleHPMessenger CHANGED PARAMETER NeglectDoppler TO "
               << bValue << " ===" << G4endl;
      }
      if (bValue) {
        G4cout << "    -> Switched off the Doppler broadening due to the thermal motion of the "
                  "target nucleus: \n"
               << "       on-the-fly Doppler broadening will be neglected in the cross section "
                  "calculations of \n"
               << "       capture, elastic, fission and inelastic reactions/scatterings of "
                  "neutrons below 20 MeV.\n"
               << "       This option provides a significant CPU performance advantage !" << G4endl;
      }
      else {
        G4cout
          << "    -> Go back to the default, i.e. switch on the Doppler broadening on-the-fly !"
          << G4endl;
      }
#endif
    }
  }

  if (command == DoNotAdjustFSCmd) {
    if (manager->GetDoNotAdjustFinalState() != bValue) {
      manager->SetDoNotAdjustFinalState(bValue);
#ifdef G4VERBOSE
      if (G4HadronicParameters::Instance()->GetVerboseLevel() > 0) {
        G4cout << G4endl << "=== G4ParticleHPMessenger CHANGED PARAMETER DoNotAdjustFinalState TO "
               << bValue << " ===" << G4endl;
      }
      if (bValue) {
        G4cout
          << "    -> Disabled the adjustment of the final state for getting better conservation !"
          << G4endl;
      }
      else {
        G4cout << "    -> Go back to the default, i.e. adjust the final state to get better "
                  "conservation !"
               << G4endl;
      }
#endif
    }
  }

  if (command == ProduceFissionFragementCmd) {
    if (manager->GetProduceFissionFragments() != bValue) {
      manager->SetProduceFissionFragments(bValue);
#ifdef G4VERBOSE
      if (G4HadronicParameters::Instance()->GetVerboseLevel() > 0) {
        G4cout << G4endl
               << "=== G4ParticleHPMessenger CHANGED PARAMETER ProduceFissionFragments TO "
               << bValue << " ===" << G4endl;
      }
      if (bValue) {
        G4cout << "    -> Enabled the generation of fission fragments !" << G4endl;
      }
      else {
        G4cout << "    -> Go back to the default, i.e. do not generate fission fragments !"
               << G4endl;
      }
#endif
    }
  }

  if (command == WendtFissionModelCmd) {
    if (manager->GetUseWendtFissionModel() != bValue) {
      manager->SetUseWendtFissionModel(bValue);
      // Make sure both fission fragment models are not active at same time
      if (bValue) manager->SetProduceFissionFragments(false);
#ifdef G4VERBOSE
      if (G4HadronicParameters::Instance()->GetVerboseLevel() > 0) {
        G4cout << G4endl << "=== G4ParticleHPMessenger CHANGED PARAMETER UseWendtFissionModel TO "
               << bValue << " ===" << G4endl;
      }
      if (bValue) {
        G4cout << "    -> Enabled the use of Wendt fission model !" << G4endl;
      }
      else {
        G4cout << "    -> Go back to the default, i.e. do not use the Wendt fission model !"
               << G4endl;
      }
#endif
    }
  }

  if (command == NRESP71Cmd) {
    if (manager->GetUseNRESP71Model() != bValue) {
      manager->SetUseNRESP71Model(bValue);
#ifdef G4VERBOSE
      if (G4HadronicParameters::Instance()->GetVerboseLevel() > 0) {
        G4cout << G4endl << "=== G4ParticleHPMessenger CHANGED PARAMETER UseNRESP71Model TO "
               << bValue << " ===" << G4endl;
      }
      if (bValue) {
        G4cout << "    -> Enabled the use of NRESP71 model for n on C reaction !" << G4endl;
      }
      else {
        G4cout << "    -> Go back to the default, i.e. do not use the NRESP71 model !" << G4endl;
      }
#endif
    }
  }

  if (command == VerboseCmd) {
    G4int verboseLevel = VerboseCmd->ConvertToInt(newValue);
    if (manager->GetVerboseLevel() != verboseLevel) {
      manager->SetVerboseLevel(verboseLevel);
#ifdef G4VERBOSE
      if (G4HadronicParameters::Instance()->GetVerboseLevel() > 0) {
        G4cout << G4endl << "=== G4ParticleHPMessenger CHANGED PARAMETER VerboseLevel TO "
               << verboseLevel << " ===" << G4endl;
      }
#endif
    }
  }

  if (command == UseDBRCCmd) {
    bValue = UseDBRCCmd->GetNewBoolValue(newValue);
    if (manager->GetUseDBRC() != bValue) {
      manager->SetUseDBRC(bValue);
#ifdef G4VERBOSE
      if (G4HadronicParameters::Instance()->GetVerboseLevel() > 0) {
        G4cout << G4endl << "=== G4ParticleHPMessenger CHANGED PARAMETER UseDBRC TO " << bValue
               << " ===" << G4endl;
      }
      if (bValue) {
        G4cout << "    -> Using the DBRC algorithm!" << G4endl;
      }
      else {
        G4cout << "    -> Do not use the DBRC algorithm!" << G4endl;
      }
#endif
    }
  }

  if (command == MaxEnergySVTCmd) {
    G4double energymax = MaxEnergySVTCmd->GetNewDoubleValue(newValue);
    if (G4HadronicParameters::Instance()->GetNeutronKineticEnergyThresholdForSVT() != energymax) {
      G4HadronicParameters::Instance()->SetNeutronKineticEnergyThresholdForSVT(energymax);
#ifdef G4VERBOSE
      if (G4HadronicParameters::Instance()->GetVerboseLevel() > 0) {
        G4cout << G4endl
               << "=== G4ParticleHPMessenger CHANGED PARAMETER for SVT algorithm ===" << G4endl;
        G4cout << "max energy: " << G4BestUnit(energymax, "Energy") << G4endl;
      }
#endif
    }
  }

  if (command == MinADBRCCmd) {
    G4double Amin = MinADBRCCmd->GetNewDoubleValue(newValue);
    if (manager->GetMinADBRC() != Amin) {
      manager->SetMinADBRC(Amin);
#ifdef G4VERBOSE
      if (G4HadronicParameters::Instance()->GetVerboseLevel() > 0) {
        G4cout << G4endl
               << "=== G4ParticleHPMessenger CHANGED PARAMETER for DBRC algorithm ===" << G4endl;
        G4cout << "min A: " << Amin << G4endl;
      }
#endif
    }
  }

  if (command == MinEnergyDBRCCmd) {
    G4double energymin = MinEnergyDBRCCmd->GetNewDoubleValue(newValue);
    if (manager->GetMinEnergyDBRC() != energymin) {
      manager->SetMinEnergyDBRC(energymin);
#ifdef G4VERBOSE
      if (G4HadronicParameters::Instance()->GetVerboseLevel() > 0) {
        G4cout << G4endl
               << "=== G4ParticleHPMessenger CHANGED PARAMETER for DBRC algorithm ===" << G4endl;
        G4cout << "min energy: " << G4BestUnit(energymin, "Energy") << G4endl;
      }
#endif
    }
  }

  if (command == MaxEnergyDBRCCmd) {
    G4double energymax = MaxEnergyDBRCCmd->GetNewDoubleValue(newValue);
    if (manager->GetMaxEnergyDBRC() != energymax) {
      manager->SetMaxEnergyDBRC(energymax);
#ifdef G4VERBOSE
      if (G4HadronicParameters::Instance()->GetVerboseLevel() > 0) {
        G4cout << G4endl
               << "=== G4ParticleHPMessenger CHANGED PARAMETER for SVT algorithm ===" << G4endl;
        G4cout << "max energy: " << G4BestUnit(energymax, "Energy") << G4endl;
      }
#endif
    }
  }

  if (command == PTformatCmd) {
    if (manager->GetUsedPTformat() != newValue) {
      manager->SetUsedPTformat(newValue);
    }
#ifdef G4VERBOSE
    if (G4HadronicParameters::Instance()->GetVerboseLevel() > 0) {
      G4cout << G4endl
             << "=== G4ParticleHPMessenger CHANGED PARAMETER UsedPTformat TO "
             << newValue << " ===" << G4endl;
    }
    if (newValue == "njoy") {
      G4cout << "    -> Probablity tables for the unresolved resonace region will be used from NJOY21." << G4endl;
    } else if (newValue == "calendf") {
      G4cout << "    -> Probablity tables for the unresolved resonace region will be used from CALENDF." << G4endl;
    }
#endif
  }
}
