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
// 	Author: wjcheon
//


#include "PrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "Randomize.hh"
#include "G4RandomDirection.hh"


PrimaryGeneratorAction::PrimaryGeneratorAction():
    G4VUserPrimaryGeneratorAction()
{

//    // Particle Gun
//    fPrimary = new G4ParticleGun();
//	fPrimary->SetParticleDefinition(G4ParticleTable::GetParticleTable()->FindParticle("proton"));
//	fPrimary->SetParticleEnergy(6.0*MeV);
//	fPrimary->SetParticlePosition((G4ThreeVector(0.0*cm, 0.0*cm, 0.0*cm)));
//	fPrimary->SetParticleMomentumDirection(G4ThreeVector(0.0,0.0,1.0));

	// General particle source
	fPrimary = new G4GeneralParticleSource();

}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
	delete fPrimary;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
//	// Line
//	G4double yPos = -5.0*cm+ (G4UniformRand()*10.0*cm);
//	fPrimary->SetParticlePosition(G4ThreeVector(0.0*cm, yPos, 0.0*cm));
//
//	//Iso
//	fPrimary->SetParticleMomentumDirection(G4RandomDirection());


    fPrimary->GeneratePrimaryVertex(anEvent);
}
