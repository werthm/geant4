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
///////////////////////////////////////////////////////
// File name:     G4IonInverseIonisation
//
// Author:        Laurent Desorgher
//
// Creation date: 25.08.2009
//
///////////////////////////////////////////////////////

#include "G4IonInverseIonisation.hh"

#include "G4AdjointIonIonisationModel.hh"

////////////////////////////////////////////////////////////////////////////////
G4IonInverseIonisation::G4IonInverseIonisation(
  G4bool whichScatCase, const G4String& process_name,
  G4AdjointIonIonisationModel* aEmAdjointModel)
  : G4VAdjointReverseReaction(process_name, whichScatCase)
{
  fAdjointModel = aEmAdjointModel;
  fAdjointModel->SetSecondPartOfSameType(false);
}

////////////////////////////////////////////////////////////////////////////////
void G4IonInverseIonisation::ProcessDescription(std::ostream& out) const
{
  out << "Inversion ionisation process for ions.\n";
}
