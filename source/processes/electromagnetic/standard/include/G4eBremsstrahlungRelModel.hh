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
//
// -------------------------------------------------------------------
//
// GEANT4 Class header file
//
//
// File name:     G4eBremsstrahlungRelModel
//                extention of standard G4eBremsstrahlungModel
//
// Author:        Andreas Schaelicke
//
// Creation date: 28.03.2008
//
// Modifications:
//
// 15.07.18  introduced data structures to store LPM functions and element depen
//           dent data for faster run-time computation (see more in .cc M.Novak)
//
// Class Description:
//
// Implementation of energy loss for gamma emission by electrons and
// positrons including an improved version of the LPM effect

// -------------------------------------------------------------------
//

#ifndef G4eBremsstrahlungRelModel_h
#define G4eBremsstrahlungRelModel_h 1

#include "G4VEmModel.hh"
#include <memory>

class G4ParticleChangeForLoss;

class G4eBremsstrahlungRelModel : public G4VEmModel {

public:

  explicit G4eBremsstrahlungRelModel(const G4ParticleDefinition* p=nullptr,
                                     const G4String& nam="eBremLPM");

  ~G4eBremsstrahlungRelModel() override;

  void Initialise(const G4ParticleDefinition*, const G4DataVector&) override;

  void InitialiseLocal(const G4ParticleDefinition*,
                       G4VEmModel* masterModel) override;

  G4double ComputeDEDXPerVolume(const G4Material*,
                                const G4ParticleDefinition*,
                                G4double ekin,
                                G4double cutEnergy) override;

  G4double ComputeCrossSectionPerAtom(const G4ParticleDefinition*,
                                      G4double ekin,
                                      G4double zet,
                                      G4double,
                                      G4double cutEnergy,
                                      G4double maxEnergy = DBL_MAX) override;

  void SampleSecondaries(std::vector<G4DynamicParticle*>*,
                         const G4MaterialCutsCouple*,
                         const G4DynamicParticle*,
                         G4double cutEnergy,
                         G4double maxEnergy) override;

  void SetupForMaterial(const G4ParticleDefinition*,
                        const G4Material*, G4double) override;

  G4double MinPrimaryEnergy(const G4Material*,
                            const G4ParticleDefinition*,
                            G4double cutEnergy) override;

protected:

  virtual G4double ComputeDXSectionPerAtom(G4double gammaEnergy);

  void SetParticle(const G4ParticleDefinition* p);

private:

  G4double ComputeBremLoss(G4double cutEnergy);

  G4double ComputeXSectionPerAtom(G4double cutEnergy);

  G4double ComputeRelDXSectionPerAtom(G4double gammaEnergy);

  // init special data per element i.e. per Z
  void InitialiseElementData();

  // methods for initialisation and run-time evaluation of LPM functions:
  void InitLPMFunctions();

  void ComputeLPMfunctions(G4double& funcXiS,
                           G4double& funcGS,
                           G4double& funcPhiS,
                           const G4double egamma);

  void GetLPMFunctions(G4double& lpmGs,
                       G4double& lpmPhis,
                       const G4double ss);

  void ComputeLPMGsPhis(G4double& funcGS,
                        G4double& funcPhiS,
                        const G4double varShat);

  // for evaluating screening related functions
  void ComputeScreeningFunctions(G4double& phi1,
                                 G4double& phi1m2,
                                 G4double& psi1,
                                 G4double& psi1m2,
                                 const G4double gam,
                                 const G4double eps);
  // hide assignment operator and cctr
  G4eBremsstrahlungRelModel& operator=
  (const G4eBremsstrahlungRelModel& right) = delete;
  G4eBremsstrahlungRelModel(const  G4eBremsstrahlungRelModel&) = delete;

private:

  G4bool                      fIsUseCompleteScreening = false;
  G4bool                      fIsInitializer = false;
  G4bool                      fUseLPM = true;

protected:

  G4bool                      fIsElectron = true;
  G4bool                      fIsScatOffElectron = false;
  G4bool                      fIsLPMActive = false;
  //
  G4int                       fCurrentIZ = 0;
  const G4ParticleDefinition* fPrimaryParticle = nullptr;
  G4ParticleDefinition*       fGammaParticle = nullptr;
  G4ParticleChangeForLoss*    fParticleChange = nullptr;
  // cash
  G4double                    fPrimaryParticleMass = 0.;
  G4double                    fPrimaryKinEnergy = 0.;
  G4double                    fPrimaryTotalEnergy = 0.;
  G4double                    fDensityFactor = 0.;
  G4double                    fDensityCorr = 0.;
  G4double                    fLowestKinEnergy;
  // scattering off electrons
  G4double                    fNucTerm = 0.;
  G4double                    fSumTerm = 0.;

private:

  // LPM related members
  G4double                    fLPMEnergyThreshold;
  G4double                    fLPMEnergy;

protected:

  static const G4double       gBremFactor;
  static const G4double       gMigdalConstant;

private:

  static const G4int          gMaxZet;
  //
  static const G4double       gLPMconstant;
  //
  static const G4double       gXGL[8];
  static const G4double       gWGL[8];
  static const G4double       gFelLowZet[8];
  static const G4double       gFinelLowZet[8];
  //
  struct ElementData {
    /** @brief \f$ \ln(Z) \f$  */
    G4double  fLogZ;
    /** @brief \f$ \ln(Z)/3 + f_c \f$  */
    G4double  fFz;
    /** @brief \f$ ((Fel-fc)+Finel*invZ)\f$  */
    G4double  fZFactor1;
    /** @brief \f$ (Fel-fc)\f$  */
    G4double  fZFactor11;
    /** @brief \f$ (1.0+invZ)/12  \f$  */
    G4double  fZFactor2;
    // LPM variables
    G4double  fVarS1;
    G4double  fILVarS1;
    G4double  fILVarS1Cond;
    // constant factors to the screening function evaluations
    G4double  fGammaFactor;
    G4double  fEpsilonFactor;
  };
  //
  struct LPMFuncs {
    LPMFuncs() : fIsInitialized(false), fISDelta(100.), fSLimit(2.) {}
    G4bool                 fIsInitialized;
    G4double               fISDelta;
    G4double               fSLimit;
    std::vector<G4double>  fLPMFuncG;
    std::vector<G4double>  fLPMFuncPhi;
  };
  //
  static std::shared_ptr<LPMFuncs> gLPMFuncs();
  static std::shared_ptr<std::vector<ElementData*>> gElementData();
  std::shared_ptr<LPMFuncs> fLPMFuncs;
  std::shared_ptr<std::vector<ElementData*>> fElementData;
};

#endif
