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
// $Id: G4NullModel.cc,v 1.6 2001/08/24 20:36:28 johna Exp $
// GEANT4 tag $Name: geant4-05-01 $
//
// 
// John Allison  4th April 1998.
// Null model - simply a holder for modeling parameter.
// DO NOT INVOKE DescribeYourself.

#include "G4NullModel.hh"

G4NullModel::G4NullModel (const G4ModelingParameters* pMP):
  G4VModel (G4Transform3D::Identity, pMP) {}

G4NullModel::~G4NullModel () {}

void G4NullModel::DescribeYourselfTo (G4VGraphicsScene& sceneHandler) {
  G4Exception ("G4NullModel::DescribeYourselfTo called.");
}