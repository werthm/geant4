//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// $Id: G4gsdeth.cc,v 1.7 2003/04/03 11:30:54 gcosmo Exp $
// GEANT4 tag $Name: geant4-05-01 $

#include "G3toG4.hh"
#include "G3DetTable.hh"

class G4VSensitiveDetector;

void PG4gsdeth(G4String tokens[])
{
    // fill the parameter containers
    G3fillParams(tokens,PTgsdeth);

    // interpret the parameters
    G4String chset = Spar[0];
    G4String chdet = Spar[1];
    G4int nh = Ipar[0];
    G4String chnamh[100];
    for (G4int i=0; i<=nh; i++ ) chnamh[i] = Spar[2+i].data();
    G4int *nbitsh = &Ipar[1];
    G4double *orig = Rpar;
    G4double *fact = &Rpar[nh];

    G4gsdeth(chset,chdet,nh,chnamh,nbitsh,orig,fact);
}

void G4gsdeth(G4String, G4String, G4int, G4String*,
              G4int*, G4double*, G4double*)
{
    // Get pointer to sensitive detector chset
    // G4VSensitiveDetector* sdet = G3Det.GetSD(chset, chdet);
    // Add hits to sensitive detector
    // for (G4int i=0; i<nh; i++) {
      // $$$        sdet->AddHit(chnamh[i],nbitsh[i],orig[i],fact[i]);
    // }
}