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
// This example is provided by the Geant4-DNA collaboration
// Any report or published results obtained using the Geant4-DNA software
// shall cite the following Geant4-DNA collaboration publications:
// Med. Phys. 45 (2018) e722-e739
// Phys. Med. 31 (2015) 861-874
// Med. Phys. 37 (2010) 4692-4708
// Int. J. Model. Simul. Sci. Comput. 1 (2010) 157–178
//
// The Geant4-DNA web site is available at http://geant4-dna.org
//
/// \file medical/dna/wvalue/src/DetectorMessenger.cc
/// \brief Implementation of the DetectorMessenger class

#include "DetectorMessenger.hh"

#include "DetectorConstruction.hh"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::DetectorMessenger(DetectorConstruction* Det)
  : G4UImessenger(),
    fDetector(Det),
    fTestemDir(0),
    fDetDir(0),
    fMaterCmd(0),
    fRadiusCmd(0),
    fTrackingCutCmd(0)
{
  fTestemDir = new G4UIdirectory("/w/");
  fTestemDir->SetGuidance("Detector control");

  fDetDir = new G4UIdirectory("/w/det/");
  fDetDir->SetGuidance("Detector construction commands");

  fMaterCmd = new G4UIcmdWithAString("/w/det/setMat", this);
  fMaterCmd->SetGuidance("Select material of the sphere");
  fMaterCmd->SetParameterName("Choice", false);
  fMaterCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
  fMaterCmd->SetToBeBroadcasted(false);

  fRadiusCmd = new G4UIcmdWithADoubleAndUnit("/w/det/setRadius", this);
  fRadiusCmd->SetGuidance("Set radius of the absorber");
  fRadiusCmd->SetParameterName("Radius", false);
  fRadiusCmd->SetRange("Radius>0.");
  fRadiusCmd->SetUnitCategory("Length");
  fRadiusCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
  fRadiusCmd->SetToBeBroadcasted(false);

  fTrackingCutCmd = new G4UIcmdWithADoubleAndUnit("/w/det/setTrackingCut", this);
  fTrackingCutCmd->SetGuidance("Set tracking cut in the absorber");
  fTrackingCutCmd->SetParameterName("Cut", false);
  fTrackingCutCmd->SetRange("Cut>0.");
  fTrackingCutCmd->SetUnitCategory("Energy");
  fTrackingCutCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
  fTrackingCutCmd->SetToBeBroadcasted(false);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::~DetectorMessenger()
{
  delete fMaterCmd;
  delete fRadiusCmd;
  delete fTrackingCutCmd;
  delete fDetDir;
  delete fTestemDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  if (command == fMaterCmd) {
    fDetector->SetMaterial(newValue);
  }

  if (command == fRadiusCmd) {
    fDetector->SetRadius(fRadiusCmd->GetNewDoubleValue(newValue));
  }

  if (command == fTrackingCutCmd) {
    fDetector->SetTrackingCut(fTrackingCutCmd->GetNewDoubleValue(newValue));
  }
}
