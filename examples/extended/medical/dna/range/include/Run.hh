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
/// \file medical/dna/range/include/Run.hh
/// \brief Definition of the Run class

#ifndef Run_h
#define Run_h 1

#include "DetectorConstruction.hh"

#include "G4Run.hh"

class G4ParticleDefinition;

class Run : public G4Run
{
  public:
    Run(const DetectorConstruction* detector);
    ~Run();

    void SetPrimary(G4ParticleDefinition* particle, G4double energy);

    void AddEdep(G4double e);
    void AddTrackLength(G4double t);
    void AddProjRange(G4double x);
    void AddPenetration(G4double x);
    void AddStepSize(G4int nb, G4double st);

    G4double GetEdep() const { return fEdeposit; };

    virtual void Merge(const G4Run*);
    void EndOfRun();

  private:
    const DetectorConstruction* fDetector;

    G4ParticleDefinition* fParticle;
    G4double fEkin;

    G4double fEdeposit, fEdeposit2;
    G4double fTrackLen, fTrackLen2;
    G4double fProjRange, fProjRange2;
    G4double fPenetration, fPenetration2;
    G4int fNbOfSteps, fNbOfSteps2;
    G4double fStepSize, fStepSize2;
};

#endif
