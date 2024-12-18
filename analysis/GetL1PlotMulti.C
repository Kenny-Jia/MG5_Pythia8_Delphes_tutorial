/*
example usage
root 'analysis/GetL1Info.C("data/1atlas-pu-zz4l/Events/run_01/tag_1_delphes_events.root", "analysis/h5_output/zz4l.h5")'
*/

#include "TH1.h"
#include "TSystem.h"
#include <hdf5.h>

#ifdef __CLING__
R__LOAD_LIBRARY(libDelphes)
#include "classes/DelphesClasses.h"
#include "/fs/ddn/sdf/group/atlas/d/lizhx/MG5_aMC_v3_5_6/Delphes/external/ExRootAnalysis/ExRootTreeReader.h"
#include "/fs/ddn/sdf/group/atlas/d/lizhx/MG5_aMC_v3_5_6/Delphes/external/ExRootAnalysis/ExRootResult.h"
#endif

class ExRootResult;
class ExRootTreeReader;

const int numJetsTotal = 10;
const int numEleTotal = 4;
const int numMuonTotal = 4;
const int metIndex = 0;
const int eleIndex = 1;
const int muonIndex = 5;
const int jetIndex = 9;

// const char* baseDir = "plots/cms-pu60-hh4b/";

void printCurrEntry(double curr_entry[19][4]) {
    for (int i = 0; i < 19; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << "curr_entry[" << i << "][" << j << "] = " << curr_entry[i][j] << " ";
        }
        cout << endl;
    }
}

struct MyPlots
{
  TH1 *fJetPT[numJetsTotal];
  TH1 *fJetEta[numJetsTotal];
  TH1 *fJetPhi[numJetsTotal];

  TH1 *fMissingET;
  TH1 *fMissingETPhi;

  TH1 *fElectronPT[numEleTotal];
  TH1 *fElectronEta[numEleTotal];
  TH1 *fElectronPhi[numEleTotal];

  TH1 *fMuonPT[numMuonTotal];
  TH1 *fMuonEta[numMuonTotal];
  TH1 *fMuonPhi[numMuonTotal];
};


void BookHistograms(ExRootResult *result, MyPlots *plots, const char* baseDir)
{
  THStack *stack;
  TLegend *legend;
  TPaveText *comment;
  char histName[100];
  char histTitle[100];

  for (int i=0; i<numJetsTotal; i++){
    sprintf(histName, "%sjet_pt_%d", baseDir, i+1);
    sprintf(histTitle, "%dth jet P_{T} ", i+1);

    plots->fJetPT[i] = result->AddHist1D(
    histName, histTitle,
    "jet P_{T}, GeV/c", "count",
    50, 0.0, 100.0);

    sprintf(histName, "%sjet_eta_%d", baseDir, i+1);
    sprintf(histTitle, "%dth jet Eta", i+1);
    plots->fJetEta[i] = result->AddHist1D(
    histName, histTitle,
    "jet Eta, GeV/c", "count",
    50, -5.0, 5.0);

    sprintf(histName, "%sjet_phi_%d",baseDir, i+1);
    sprintf(histTitle, "%dth jet Phi", i+1);
    plots->fJetPhi[i] = result->AddHist1D(
    histName, histTitle,
    "jet Phi, GeV/c", "count",
    50, -5.0, 5.0);

    plots->fJetPT[i]->SetStats();
    plots->fJetEta[i]->SetStats();
    plots->fJetPhi[i]->SetStats();

  }

  // plots->fJetPT[0]->SetLineColor(kRed);
  // plots->fJetPT[1]->SetLineColor(kBlue);

  // book 1 stack of 2 histograms
  // stack = result->AddHistStack("jet_pt_all", "1st and 2nd jets P_{T}");
  // stack->Add(plots->fJetPT[0]);
  // stack->Add(plots->fJetPT[1]);
  // book legend for stack of 2 histograms
  // legend = result->AddLegend(0.72, 0.86, 0.98, 0.98);
  // legend->AddEntry(plots->fJetPT[0], "leading jet", "l");
  // legend->AddEntry(plots->fJetPT[1], "second jet", "l");
  // attach legend to stack (legend will be printed over stack in .eps file)
  // result->Attach(stack, legend);


  for (int i=0; i<4; i++){
    sprintf(histName, "%selectron_pt_%d",baseDir, i+1);
    sprintf(histTitle, "%d th electron P_{T} ", i+1);

    plots->fElectronPT[i] = result->AddHist1D(
      histName, histTitle,
      "electron P_{T}, GeV/c", "count",
      50, 0.0, 100.0);

    sprintf(histName, "%selectron_eta_%d",baseDir, i+1);
    sprintf(histTitle, "%d th electron Eta", i+1);
    plots->fElectronEta[i] = result->AddHist1D(
        histName, histTitle,
        "electron Eta", "count",
        50, -5.0, 5.0);
    
    sprintf(histName, "%selectron_phi_%d",baseDir, i+1);
    sprintf(histTitle, "%d th electron Phi", i+1);
    plots->fElectronPhi[i] = result->AddHist1D(
        histName, histTitle,
        "electron Phi", "count",
        50, -5.0, 5.0);

    plots->fElectronPT[i]->SetStats();
    plots->fElectronEta[i]->SetStats();
    plots->fElectronPhi[i]->SetStats();
  }

  for (int i=0; i<4; i++){
    sprintf(histName, "%smuon_pt_%d",baseDir, i+1);
    sprintf(histTitle, "%dth muon P_{T} ", i+1);

    plots->fMuonPT[i] = result->AddHist1D(
      histName, histTitle,
      "muon P_{T}, GeV/c", "number of muons",
      50, 0.0, 100.0);


    sprintf(histName, "%smuon_eta_%d",baseDir, i+1);
    sprintf(histTitle, "%d th muon Eta", i+1);
    plots->fMuonEta[i] = result->AddHist1D(
        histName, histTitle,
        "muon Eta", "number of muons",
        50, -5.0, 5.0);
    
    sprintf(histName, "%smuon_phi_%d",baseDir, i+1);
    sprintf(histTitle, "%d th muon Phi", i+1);
    plots->fMuonPhi[i] = result->AddHist1D(
        histName, histTitle,
        "muon Phi", "number of muons",
        50, -5.0, 5.0);

    plots->fMuonPT[i]->SetStats();
    plots->fMuonEta[i]->SetStats();
    plots->fMuonPhi[i]->SetStats();
  }

  sprintf(histName, "%smissing_et",baseDir);
  plots->fMissingET = result->AddHist1D(
    histName, "Missing E_{T}",
    "Missing E_{T}, GeV", "count",
    60, 0.0, 500.0);

  sprintf(histName, "%smissing_et_phi",baseDir);
  plots->fMissingETPhi = result->AddHist1D(
    histName, "Missing E_{T} Phi",
    "Missing E_{T} Phi", "count",
    60, 0.0, 5.0);


  // // book general comment
  // comment = result->AddComment(0.64, 0.86, 0.98, 0.98);
  // comment->AddText("demonstration plot");
  // comment->AddText("produced by Example2.C");

  // // attach comment to single histograms
  // result->Attach(plots->fJetPT[0], comment);
  // result->Attach(plots->fJetPT[1], comment);
  // result->Attach(plots->fElectronPT, comment);

  // show histogram statisics for MissingET
  plots->fMissingET->SetStats();
}

void PrintHistograms(ExRootResult *result, MyPlots *plots)
{
  result->Print("png");
}

void ProcessFile(const char *inputFile, ExRootTreeReader *treeReader, MyPlots *plots) {
  TClonesArray *branchJet = treeReader->UseBranch("Jet");
  TClonesArray *branchElectron = treeReader->UseBranch("Electron");
  TClonesArray *branchMuon = treeReader->UseBranch("Muon");
  if (!branchMuon) {
      TClonesArray *branchMuon = treeReader->UseBranch("MuonLoose");
  }
  TClonesArray *branchMissingET = treeReader->UseBranch("MissingET");
  TClonesArray *branchGenParticle = treeReader->UseBranch("Particle");

  Jet *jet[numJetsTotal];
  MissingET *met;
  Electron *electrons[numEleTotal];
  Muon *muons[numMuonTotal];
  Long64_t entry;

  Long64_t numEntries = treeReader->GetEntries();
  for (entry = 0; entry < numEntries; entry++) {
    treeReader->ReadEntry(entry);

    int numJets = branchJet->GetEntriesFast();
    if (numJets > numJetsTotal) numJets = numJetsTotal;

    for (int i=0; i<numJets; i++){
      jet[i] = (Jet*) branchJet->At(i);
      plots->fJetPT[i]->Fill(jet[i]->PT);
      plots->fJetEta[i]->Fill(jet[i]->Eta);
      plots->fJetPhi[i]->Fill(jet[i]->Phi);
    }

    int numMuon = branchMuon->GetEntriesFast();
    if (numMuon > numMuonTotal) numMuon = numMuonTotal;
    for (int i=0; i<numMuon; i++){
      muons[i] = (Muon*) branchMuon->At(i);
      plots->fMuonPT[i]->Fill(muons[i]->PT);
      plots->fMuonEta[i]->Fill(muons[i]->Eta);
      plots->fMuonPhi[i]->Fill(muons[i]->Phi);
    }

    int numEle = branchElectron->GetEntriesFast();
    if (numEle > numEleTotal) numEle = numEleTotal;
    for (int i=0; i<numEle; i++){
      electrons[i] = (Electron*) branchElectron->At(i);
      plots->fElectronPT[i]->Fill(electrons[i]->PT);
      plots->fElectronEta[i]->Fill(electrons[i]->Eta);
      plots->fElectronPhi[i]->Fill(electrons[i]->Phi);
    }

    if(branchMissingET->GetEntriesFast() > 0) {
      met = (MissingET*) branchMissingET->At(0);
      plots->fMissingET->Fill(met->MET);
      plots->fMissingETPhi->Fill(met->Phi);
    }
  }
}

void GetL1Plot(const char* baseDir, const vector<const char *> &inputFiles) {
  gSystem->Load("libDelphes");
  ExRootResult *result = new ExRootResult();

  struct stat st = {0};
  if (stat(baseDir, &st) == -1) {
      if (mkdir(baseDir, 0700) == 0) {
          printf("Directory created: %s\n", baseDir);
      } else {
          perror("mkdir");
      }
  } else {
      printf("Directory already exists: %s\n", baseDir);
  }

  MyPlots *plots = new MyPlots;
  BookHistograms(result, plots, baseDir);

  for (const char* inputFile : inputFiles) {
    TChain *chain = new TChain("Delphes");
    chain->Add(inputFile);
    
    ExRootTreeReader *treeReader = new ExRootTreeReader(chain);
    ProcessFile(inputFile, treeReader, plots);
    
    delete treeReader;
    delete chain;
  }

  PrintHistograms(result, plots);
  
  delete plots;
  delete result;
}