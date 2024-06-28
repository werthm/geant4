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
/// \file visualization/standalone/standalone.cc
/// \brief Main program of the visualization/standalone example
//
//
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DrawGeometryVisAction.hh"
#include "StandaloneVisAction.hh"

#include "G4SystemOfUnits.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4VisExtent.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc, char** argv)
{
  G4UIExecutive* ui = new G4UIExecutive(argc, argv);

  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  auto standaloneVisAction = new StandaloneVisAction;
  visManager->RegisterRunDurationUserVisAction(
    "A standalone example - 3 boxes, 2 with boolean subtracted cutout", standaloneVisAction,
    G4VisExtent(-10 * cm, 10 * cm, -10 * cm, 10 * cm, -10 * cm, 10 * cm));

  auto geometryVisAction = new DrawGeometryVisAction;
  visManager->RegisterRunDurationUserVisAction("A detector geometry", geometryVisAction,
                                               geometryVisAction->GetVisxtent());

  G4UImanager::GetUIpointer()->ApplyCommand("/control/execute standalone.mac");
  ui->SessionStart();

  delete geometryVisAction;
  delete standaloneVisAction;
  delete visManager;
  delete ui;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
