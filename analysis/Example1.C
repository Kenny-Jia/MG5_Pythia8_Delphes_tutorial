/*
Simple macro showing how to access branches from the delphes output root file,
loop over events, and plot simple quantities such as the jet pt and the di-electron invariant
mass.

root -l examples/Example1.C'("delphes_output.root")'
*/

#include <hdf5.h>
#include <hdf5_hl.h>


#ifdef __CLING__
R__LOAD_LIBRARY(libDelphes)
#include "classes/DelphesClasses.h"
#include "/fs/ddn/sdf/group/atlas/d/lizhx/Monte_Carlo/MG5_aMC_v3_5_6/Delphes/external/ExRootAnalysis/ExRootTreeReader.h"
#endif

//------------------------------------------------------------------------------

void Example1(const char *inputFile)
{
  gSystem->Load("libDelphes");

  // Create chain of root trees
  TChain chain("Delphes");
  chain.Add(inputFile);

  // Create object of class ExRootTreeReader
  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  Long64_t numberOfEntries = treeReader->GetEntries();

  // Get pointers to branches used in this analysis
  TClonesArray *branchJet = treeReader->UseBranch("Jet");
  // TClonesArray *branchGenJet = treeReader->UseBranch("GenJet");
  // TClonesArray *branchElectron = treeReader->UseBranch("Electron");
  TClonesArray *branchEvent = treeReader->UseBranch("Event");

  // Book histograms
  TH1 *histJetPT = new TH1F("jet_pt", "jet P_{T}", 100, 0.0, 1000.0);
  TH1 *histJetB = new TH1F("jet_btag", "jet BTag", 100, 0.0, 3.0);

  // TH1 *histMass = new TH1F("mass", "M_{inv}(e_{1}, e_{2})", 100, 40.0, 140.0);

  // Loop over all events
  for(Int_t entry = 0; entry < numberOfEntries; ++entry)
  {
    // Load selected branches with data from specified event
    treeReader->ReadEntry(entry);

    
    //HepMCEvent *event = (HepMCEvent*) branchEvent -> At(0);
    //LHEFEvent *event = (LHEFEvent*) branchEvent -> At(0);
    //Float_t weight = event->Weight;

    // If event contains at least 1 jet
    // if(branchJet->GetEntries() > 0)
    // {
    //   // Take first jet
    //   Jet *jet = (Jet*) branchJet->At(0);

    //   // Plot jet transverse momentum
    //   histJetPT->Fill(jet->PT);
    //   // histJetB->Fill(jet->BTag);
    // }
    for(int i=0; i<branchJet->GetEntries(); i++)
    {
      // Take first jet
      Jet *jet = (Jet*) branchJet->At(i);

      // Plot jet transverse momentum
      histJetB->Fill(jet->BTag);
      histJetPT->Fill(jet->PT);
    }

  }

  // Show resulting histograms
  histJetPT->Draw();
  // histJetB->Draw();
}

