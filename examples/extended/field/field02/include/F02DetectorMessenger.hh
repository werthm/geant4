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
/// \file field/field02/include/F02DetectorMessenger.hh
/// \brief Definition of the F02DetectorMessenger class
//
//
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef F02DetectorMessenger_h
#define F02DetectorMessenger_h 1

#include "G4UImessenger.hh"

class F02DetectorConstruction;

class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithoutParameter;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class F02DetectorMessenger : public G4UImessenger
{
  public:
    F02DetectorMessenger(F02DetectorConstruction*);
    ~F02DetectorMessenger() override;

    void SetNewValue(G4UIcommand*, G4String) override;

  private:
    F02DetectorConstruction* fDetector = nullptr;

    G4UIdirectory* fDetDir = nullptr;
    G4UIdirectory* fFieldDir = nullptr;

    G4UIcmdWithAString* fAbsMaterCmd = nullptr;
    G4UIcmdWithADoubleAndUnit* fAbsThickCmd = nullptr;
    G4UIcmdWithADoubleAndUnit* fAbsRadCmd = nullptr;

    G4UIcmdWithADoubleAndUnit* fAbsZposCmd = nullptr;

    G4UIcmdWithAString* fWorldMaterCmd = nullptr;
    G4UIcmdWithADoubleAndUnit* fWorldZCmd = nullptr;
    G4UIcmdWithADoubleAndUnit* fWorldRCmd = nullptr;

    // moved from FieldSetup (depends on the user field)
    G4UIcmdWith3VectorAndUnit* fElFieldCmd = nullptr;
};

#endif
