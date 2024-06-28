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
/// \file medical/GammaTherapy/include/StepLimiter.hh
/// \brief Definition of the StepLimiter class
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef StepLimiter_h
#define StepLimiter_h 1

#include "G4ParticleDefinition.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4VDiscreteProcess.hh"
#include "globals.hh"

class StepLimiterMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class StepLimiter : public G4VDiscreteProcess
{
  public:
    StepLimiter(const G4String& processName = "UserMaxStep");
    virtual ~StepLimiter();

    G4bool IsApplicable(const G4ParticleDefinition&);

    // G4double GetMaxStep() {return MaxChargedStep;};

    G4double PostStepGetPhysicalInteractionLength(const G4Track& track, G4double previousStepSize,
                                                  G4ForceCondition* condition);

    G4VParticleChange* PostStepDoIt(const G4Track&, const G4Step&);

    G4double GetMeanFreePath(const G4Track&, G4double, G4ForceCondition*);

    inline void SetMaxStep(G4double);

  private:
    StepLimiter& operator=(const StepLimiter& right);
    StepLimiter(const StepLimiter&);

    G4double fMaxChargedStep;

    StepLimiterMessenger* fMessenger;
};

inline void StepLimiter::SetMaxStep(G4double value)
{
  fMaxChargedStep = value;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
