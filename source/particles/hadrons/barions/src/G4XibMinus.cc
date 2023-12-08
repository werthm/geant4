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
// ----------------------------------------------------------------------
//      GEANT 4 class implementation file
//
//      History: first implementation, based on object model of
//      4th April 1996, G.Cosmo
//
//      Created                 Hisaya Kurashige, 11 Aug. 2011
// **********************************************************************
//

#include "G4XibMinus.hh"

#include "G4ParticleTable.hh"
#include "G4String.hh"
#include "G4SystemOfUnits.hh"

G4XibMinus* G4XibMinus::theInstance = nullptr;

G4XibMinus* G4XibMinus::Definition()
{
  if (theInstance != nullptr) return theInstance;
  const G4String name = "xi_b-";
  // search in particle table]
  G4ParticleTable* pTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* anInstance = pTable->FindParticle(name);
  if (anInstance == nullptr) {
    // create particle
    //
    //    Arguments for constructor are as follows
    //               name             mass          width         charge
    //             2*spin           parity  C-conjugation
    //          2*Isospin       2*Isospin3       G-parity
    //               type    lepton number  baryon number   PDG encoding
    //             stable         lifetime    decay table
    //             shortlived      subType    anti_encoding

    // clang-format off
   anInstance = new G4ParticleDefinition(
                 name,      5.7945*GeV,  0.419e-9*MeV,   -1.*eplus,
                    1,              +1,             0,
                    1,              -1,             0,
             "baryon",               0,            +1,        5132,
                false,     1.571e-3*ns,          nullptr,
                false,       "xi_b");
    // clang-format on
  }
  theInstance = static_cast<G4XibMinus*>(anInstance);
  return theInstance;
}

G4XibMinus* G4XibMinus::XibMinusDefinition()
{
  return Definition();
}

G4XibMinus* G4XibMinus::XibMinus()
{
  return Definition();
}
