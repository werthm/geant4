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
// $Id: G4ClassicalRK4.cc,v 1.7 2003/04/02 08:52:18 gcosmo Exp $
// GEANT4 tag $Name: geant4-05-01 $
//
#include "G4ClassicalRK4.hh"
#include "G4ThreeVector.hh"


//////////////////////////////////////////////////////////////////
//
// Constructor sets the number of variables (default = 6)

G4ClassicalRK4::G4ClassicalRK4(G4Mag_EqRhs *EqRhs, G4int numberOfVariables)
  : G4MagErrorStepper(EqRhs, numberOfVariables)
    // fNumberOfVariables(numberOfVariables)
{
   unsigned int noVariables= G4std::max(numberOfVariables,8); // For Time .. 7+1
 
   dydxm = new G4double[noVariables];
   dydxt = new G4double[noVariables]; 
   yt    = new G4double[noVariables]; 
}

////////////////////////////////////////////////////////////////
//
// Destructor

G4ClassicalRK4::~G4ClassicalRK4()
{
  delete[] dydxm;
  delete[] dydxt;
  delete[] yt;
}

//////////////////////////////////////////////////////////////////////
//
// Given values for the variables y[0,..,n-1] and their derivatives
// dydx[0,...,n-1] known at x, use the classical 4th Runge-Kutta
// method to advance the solution over an interval h and return the
// incremented variables as yout[0,...,n-1], which not be a distinct
// array from y. The user supplies the routine RightHandSide(x,y,dydx),
// which returns derivatives dydx at x. The source is routine rk4 from
// NRC p. 712-713 .

void
G4ClassicalRK4::DumbStepper( const G4double  yIn[],
                             const G4double  dydx[],
                                   G4double  h,
                                   G4double  yOut[])
{
  const G4int nvar = this->GetNumberOfVariables();   //  fNumberOfVariables(); 
  G4int i;
  G4double  hh = h*0.5 , h6 = h/6.0  ;

  // Initialise time to t0, needed when it is not updated by the integration.
  //        [ Note: Only for time dependent fields (usually electric) 
  //                  is it neccessary to integrate the time.] 
  yt[7]   = yIn[7]; 
  yOut[7] = yIn[7];

  for(i=0;i<nvar;i++)
  {
    yt[i] = yIn[i] + hh*dydx[i] ;             // 1st Step K1=h*dydx
  }
  RightHandSide(yt,dydxt) ;                   // 2nd Step K2=h*dydxt

  for(i=0;i<nvar;i++)
  { 
    yt[i] = yIn[i] + hh*dydxt[i] ;
  }
  RightHandSide(yt,dydxm) ;                   // 3rd Step K3=h*dydxm

  for(i=0;i<nvar;i++)
  {
    yt[i]   = yIn[i] + h*dydxm[i] ;
    dydxm[i] += dydxt[i] ;                    // now dydxm=(K2+K3)/h
  }
  RightHandSide(yt,dydxt) ;                   // 4th Step K4=h*dydxt
 
  for(i=0;i<nvar;i++)    // Final RK4 output
  {
    yOut[i] = yIn[i]+h6*(dydx[i]+dydxt[i]+2.0*dydxm[i]); //+K1/6+K4/6+(K2+K3)/3
  }
  // NormaliseTangentVector( yOut );
  
  return ;
}  // end of DumbStepper ....................................................

////////////////////////////////////////////////////////////////////
//
//   

void
G4ClassicalRK4::StepWithEst( const G4double*,
                             const G4double*,
                                   G4double,
                                   G4double*,
                                   G4double&,
                                   G4double&,
                             const G4double*,
                                   G4double*  ) 
{

 G4Exception("ERROR - G4ClassicalRK4::StepWithEst(): method no longer used.");

 return ;
}  // end of StepWithEst ......................................................