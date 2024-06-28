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
/// \file hadronic/Hadr01/include/EventAction.hh
/// \brief Definition of the EventAction class
//
//
/////////////////////////////////////////////////////////////////////////
//
// EventAction
//
// Created: 21.06.2008 V.Ivanchenko
//
// Modified:
//
////////////////////////////////////////////////////////////////////////
//

#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

#include <vector>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class G4Event;
class EventActionMessenger;
class G4UImanager;

class EventAction : public G4UserEventAction
{
  public:  // Without description
    EventAction();
    ~EventAction() override;

    void BeginOfEventAction(const G4Event*) override;
    void EndOfEventAction(const G4Event*) override;

    void SetPrintModulo(G4int val) { fPrintModulo = val; };
    void AddEventToDebug(G4int val) { fSelectedEvents.push_back(val); };

    EventAction& operator=(const EventAction& right) = delete;
    EventAction(const EventAction&) = delete;

  private:
    EventActionMessenger* fEventMessenger;
    G4UImanager* fUI;
    std::vector<G4int> fSelectedEvents;

    G4int fPrintModulo{100};
    G4bool fDebugStarted{false};
};

#endif
