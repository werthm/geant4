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
// $Id: G4VectorCreator.hh,v 1.5 2002/11/21 16:49:46 gcosmo Exp $
// GEANT4 tag $Name: geant4-05-01 $
//
// ----------------------------------------------------------------------
// Class G4VectorCreator
//
// Class description:
//
//

// Authors: J.Sulkimo, P.Urban.
// Revisions by: L.Broglia, G.Cosmo.
//
// History:
//   18-Nov-1999: First step of re-engineering - G.Cosmo
// ----------------------------------------------------------------------
#ifndef G4VECTORCREATOR_HH
#define G4VECTORCREATOR_HH

#include "G4GeometryCreator.hh"

class G4VectorCreator: private G4GeometryCreator 
{
  public:

  // Constructor & destructor

    G4VectorCreator();
    ~G4VectorCreator();

  // Member functions

    void CreateG4Geometry(STEPentity&);
    void CreateSTEPGeometry(void* G4obj);
    const char* Name() const { return "Vector"; }
    static G4VectorCreator GetInstance();

  // Members

  private:

    static G4VectorCreator csc;
};

#endif