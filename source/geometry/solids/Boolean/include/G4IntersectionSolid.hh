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
// $Id: G4IntersectionSolid.hh,v 1.6 2002/10/28 11:36:28 gcosmo Exp $
// GEANT4 tag $Name: geant4-05-01 $
//
//
// class G4IntersectionSolid
//
// Class description:
//
// Class for description of intersection of two CSG solids.

// History: 
//
// 12.09.98 V.Grichine: initial design and implementation
// 28.10.98 V.Grichine: addition of two constructors with G4PlacedSolid
//
// ********************************************************************

#ifndef G4INTERSECTIONSOLID_HH
#define G4INTERSECTIONSOLID_HH

#include "G4BooleanSolid.hh"
#include "G4VSolid.hh"

#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"
#include "G4AffineTransform.hh"

class G4IntersectionSolid : public G4BooleanSolid
{
  public:  // with description

    G4IntersectionSolid( const G4String& pName,
                               G4VSolid* pSolidA ,
                               G4VSolid* pSolidB   ) ;

    G4IntersectionSolid( const G4String& pName,
                               G4VSolid* pSolidA ,
                               G4VSolid* pSolidB, 
                               G4RotationMatrix* rotMatrix,
                         const G4ThreeVector& transVector   ) ;

    G4IntersectionSolid( const G4String& pName,
                               G4VSolid* pSolidA ,
                               G4VSolid* pSolidB,
                         const G4Transform3D& transform    ) ;

    virtual ~G4IntersectionSolid() ;

    virtual G4GeometryType  GetEntityType() const;

  public:  // without description

    G4bool CalculateExtent( const EAxis pAxis,
			    const G4VoxelLimits& pVoxelLimit,
			    const G4AffineTransform& pTransform,
				  G4double& pMin, G4double& pMax) const ;
       
    EInside Inside( const G4ThreeVector& p ) const ;

    G4ThreeVector SurfaceNormal( const G4ThreeVector& p ) const ;

    G4double DistanceToIn( const G4ThreeVector& p,
                           const G4ThreeVector& v  ) const ;

    G4double DistanceToIn( const G4ThreeVector& p) const ;

    G4double DistanceToOut( const G4ThreeVector& p,
			    const G4ThreeVector& v,
			    const G4bool calcNorm=false,
			    G4bool *validNorm=0,
			    G4ThreeVector *n=0      ) const ;

    G4double DistanceToOut( const G4ThreeVector& p ) const ;


    void ComputeDimensions( G4VPVParameterisation* p,
	                    const G4int n,
                            const G4VPhysicalVolume* pRep ) ;
                                   
    void DescribeYourselfTo ( G4VGraphicsScene& scene ) const ;
    G4Polyhedron* CreatePolyhedron () const ;
    G4NURBS*      CreateNURBS      () const ;

} ;

#endif
