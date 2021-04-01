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

#include "DetectorConstruction.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"

#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"

#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"

#include "G4VisAttributes.hh"

DetectorConstruction::DetectorConstruction():
    G4VUserDetectorConstruction()
{

}

DetectorConstruction::~DetectorConstruction()
{

}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
	// World
	G4VSolid* sol_World = new G4Box("World", 0.5*m, 0.5*m, 0.5*m);
	G4Material* AIR = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR");
	G4LogicalVolume* lv_World =	new G4LogicalVolume(sol_World, AIR, "World");
	G4VPhysicalVolume* pv_World =
            new G4PVPlacement(0, G4ThreeVector(0.0*cm, 0.0*cm, 0.0*cm), lv_World, "World", 0, false, 0);

	// User geometry
    G4VSolid* sol_MyGeom = new G4Tubs("Geom", 0.0*cm, 5.0*cm, 5.0*cm, 0.0*deg, 360.0*deg);
    G4Material* MyMat = G4NistManager::Instance()->FindOrBuildMaterial("G4_Al");
	G4LogicalVolume* lv_MyGeom = new G4LogicalVolume(sol_MyGeom, MyMat, "Geom");
	G4VPhysicalVolume* pv_MyGeom =
            new G4PVPlacement(0, G4ThreeVector(0.0*cm, 0.0*cm, 10.0*cm), lv_MyGeom, "Geom", lv_World, false, 100);

    G4VSolid* sol_MyRep = new G4Tubs("RepGeom", 0.0*cm, 5.0*cm, 0.5*cm, 0.0*deg, 360.0*deg);
    G4LogicalVolume* lv_MyRep = new G4LogicalVolume(sol_MyRep, MyMat, "RepGeom");
    G4VPhysicalVolume* pv_MyRep = new G4PVReplica("RepGeom", lv_MyRep, lv_MyGeom, kZAxis, 10, 1.0*cm);

	// Visualization
	G4VisAttributes* va_World = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0));
	va_World->SetForceWireframe(true);
	lv_World->SetVisAttributes(va_World);

    G4VisAttributes* va_MyGeom = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0));
    va_MyGeom->SetForceWireframe(true);
	lv_MyGeom->SetVisAttributes(va_MyGeom);

    G4VisAttributes* va_MyRep = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0, 0.3));
    va_MyRep->SetForceSolid(true);
    lv_MyRep->SetVisAttributes(va_MyRep);

    return pv_World;
}

void DetectorConstruction::ConstructSDandField()
{

}
