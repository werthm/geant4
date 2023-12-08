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
//
/// \file optical/wls/include/WLSPhotonDetSD.hh
/// \brief Definition of the WLSPhotonDetSD class
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef WLSPhotonDetSD_h
#define WLSPhotonDetSD_h 1

#include "WLSPhotonDetHit.hh"

#include "G4VSensitiveDetector.hh"

class G4Step;
class G4HCofThisEvent;

class WLSPhotonDetSD : public G4VSensitiveDetector
{
 public:
  WLSPhotonDetSD(G4String);
  ~WLSPhotonDetSD() override = default;

  void Initialize(G4HCofThisEvent*) override;

  G4bool ProcessHits(G4Step*, G4TouchableHistory*) override;

  void EndOfEvent(G4HCofThisEvent*) override;

 private:
  WLSPhotonDetHitsCollection* fPhotonDetHitCollection = nullptr;
  G4int fHCID = -1;
};

#endif
