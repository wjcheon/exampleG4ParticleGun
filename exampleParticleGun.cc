// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list Sof copyright holders.                             *
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

// Run manager and mandatory classes
#include "G4RunManager.hh"
#include "DetectorConstruction.hh"

//#include "PhysicsList.hh"
#include "G4PhysListFactory.hh"

#include "ActionInitialization.hh"

// UI and visualization classes
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

int main(int argc, char** argv)
{

    G4RunManager* runManager = new G4RunManager();

    runManager->SetUserInitialization(new DetectorConstruction());
    G4PhysListFactory factory;
    G4VModularPhysicsList* phys = factory.GetReferencePhysList("QGSP_BIC");
    runManager->SetUserInitialization(phys);
    runManager->SetUserInitialization(new ActionInitialization());
    runManager->Initialize();

    // Construct ui and visualization manager
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    G4VisManager* visManager = new G4VisExecutive();
    visManager->Initialize();

    if(argc==1)     // GUI (qt) based interactive mode
    {
        G4UIExecutive* UI = new G4UIExecutive(argc, argv, "qt");
        UImanager->ApplyCommand("/control/execute vis.mac");
        UI->SessionStart();
        delete UI;
    }
    else            // Batch mode
    {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command+fileName);
    }

    // Free the store
    delete runManager;

    return 0;
}
