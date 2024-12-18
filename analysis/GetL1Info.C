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
#include "/fs/ddn/sdf/group/atlas/d/lizhx/Monte_Carlo/MG5_aMC_v3_5_6/Delphes/external/ExRootAnalysis/ExRootTreeReader.h"
#include "/fs/ddn/sdf/group/atlas/d/lizhx/Monte_Carlo/MG5_aMC_v3_5_6/Delphes/external/ExRootAnalysis/ExRootResult.h"
#endif

class ExRootResult;
class ExRootTreeReader;

void printCurrEntry(double curr_entry[19][4]) {
    for (int i = 0; i < 19; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << "curr_entry[" << i << "][" << j << "] = " << curr_entry[i][j] << " ";
        }
        cout << endl;
    }
}


void GetL1Info(const char *inputFile, const char *outputFile, bool append){
  /* Delphes tree init */
  gSystem->Load("libDelphes");
  TChain *chain = new TChain("Delphes");
  chain->Add(inputFile);

  ExRootTreeReader *treeReader = new ExRootTreeReader(chain);
  Long64_t numEntries = treeReader->GetEntries();
  cout << "** Chain contains " << numEntries << " events" << endl;

  /* HDF5 file init */
  // dimensions: 19x4 features, numEntries events
  hid_t fileId, datasetId, dataspaceId; 
  herr_t status;
  hsize_t dims[3] = {static_cast<hsize_t>(numEntries), 19, 4};
  hsize_t max_dims[3] = {H5S_UNLIMITED, 19, 4};
  hsize_t current_dims[3];
  int prevEntries = 0;
  hsize_t append_dims[3];
  hid_t cparms;
  hsize_t chunk_dims[3] ={100, 19, 4};

  int ret;

  if (append) {
    fileId = H5Fopen(outputFile, H5F_ACC_RDWR, H5P_DEFAULT);
  } else {
    // const char *outputFile = "analysis/h5_output/zz4l.h5";
    fileId = H5Fcreate(outputFile, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
  }
  if (fileId < 0) {
    fprintf(stderr, "Error creating file.\n");
    return;
  }

  if (append) {
    // extend dataset
    datasetId = H5Dopen(fileId,  "/Particles", H5P_DEFAULT);
    dataspaceId = H5Dget_space(datasetId);
    H5Sget_simple_extent_dims(dataspaceId, current_dims, NULL);
    cout << "** Dataset previously contains " << current_dims[0] << " events" << endl;
    prevEntries = (int)current_dims[0];
    append_dims[0] = current_dims[0] + numEntries;
    append_dims[1] = current_dims[1];
    append_dims[2] = current_dims[2];
    cout << "new dims "<<append_dims[0] <<endl;
    status = H5Dset_extent(datasetId, append_dims);
    if (status < 0) {
      fprintf(stderr, "Error appending to dataset.\n");
      return;
    }
  } else {
    // create new dataset with unlimited dimensions
    dataspaceId = H5Screate_simple(3, dims,  max_dims);
    // Modify dataset creation properties to enable chunking.
    cparms = H5Pcreate (H5P_DATASET_CREATE);
    status = H5Pset_chunk(cparms, 3, chunk_dims);
    if (status < 0) {
      fprintf(stderr, "Error chunking dataset.\n");
      return;
    }
    datasetId = H5Dcreate(fileId, "/Particles", H5T_NATIVE_DOUBLE, dataspaceId,
                          H5P_DEFAULT, cparms, H5P_DEFAULT);
  }
  if (datasetId < 0) {
    fprintf(stderr, "Error creating dataset.\n");
    return;
  }

  /* Populate the dataset */
  TClonesArray *branchJet = treeReader->UseBranch("Jet");
  TClonesArray *branchElectron = treeReader->UseBranch("Electron");
  TClonesArray *branchMuon = treeReader->UseBranch("Muon");
  TClonesArray *branchMissingET = treeReader->UseBranch("MissingET");

  int numJetsTotal = 10;
  int numEleTotal = 4;
  int numMuonTotal = 4;
  int metIndex = 0;
  int eleIndex = 1;
  int muonIndex = 5;
  int jetIndex = 9;

  Jet *jet[10];
  MissingET *met;
  Electron *electrons[4];
  Muon *muons[4];
  Long64_t entry;

  hsize_t len[1] = {76};

  // Loop over all events
  for(entry = 0; entry < numEntries; entry++){
    double curr_entry[19][4] = {0};

    hid_t filespace_id = H5Dget_space(datasetId);
    hid_t memspace_id = H5Screate_simple(1, len, NULL);

    hsize_t start[3] = {static_cast<hsize_t>(entry+prevEntries), 0, 0};
    hsize_t stride[3] = {1,1,1};
    hsize_t count[3] = {1,19,4};
    hsize_t block[3] = {1,1,1};
    ret = H5Sselect_hyperslab(filespace_id, H5S_SELECT_SET, start, NULL, count, NULL);
    if (ret < 0) {
      fprintf(stderr, "Error selecting dataset.\n");
      cout << "Error selecting to dataset" << entry << endl;
      return;
    }

    treeReader->ReadEntry(entry);

    // 10 leading jets
    int numJets = branchJet->GetEntriesFast();
    if (numJets > numJetsTotal) numJets = numJetsTotal;

    for (int i=0; i<numJets; i++){
      jet[i] = (Jet*) branchJet->At(i);
      // Jet* jeti = (Jet*) branchJet->At(i);
      curr_entry[i+jetIndex][0] = (double)jet[i]->PT;
      curr_entry[i+jetIndex][1] = (double)jet[i]->Eta;
      curr_entry[i+jetIndex][2] = (double)jet[i]->Phi;
      curr_entry[i+jetIndex][3] = 4.0;
    }
    
    // 4 muons - pt eta phi
    int numMuon = branchMuon->GetEntriesFast();
    if (numMuon > numMuonTotal) numMuon = numMuonTotal;
    for (int i=0; i<numMuon; i++){
      muons[i] = (Muon*) branchMuon->At(i);
      curr_entry[i+muonIndex][0] = muons[i]->PT;
      curr_entry[i+muonIndex][1] = muons[i]->Eta;
      curr_entry[i+muonIndex][2] = muons[i]->Phi;
      curr_entry[i+muonIndex][3] = 3;
    }

    // 4 electrons - pt eta phi
    int numEle = branchElectron->GetEntriesFast();
    if (numEle > numEleTotal) numEle = numEleTotal;
    for (int i=0; i<numEle; i++){
      electrons[i] = (Electron*) branchElectron->At(i);
      curr_entry[i+eleIndex][0] = electrons[i]->PT;
      curr_entry[i+eleIndex][1] = electrons[i]->Eta;
      curr_entry[i+eleIndex][2] = electrons[i]->Phi;
      curr_entry[i+eleIndex][3] = 2;
    }

    // missing ET - pt phi
    if(branchMissingET->GetEntriesFast() > 0){
      met = (MissingET*) branchMissingET->At(0);
      curr_entry[metIndex][0] = met->MET;
      curr_entry[metIndex][1] = 0;
      curr_entry[metIndex][2] = met->Phi;
      curr_entry[metIndex][3] = 1;
    }

    ret = H5Dwrite(datasetId, H5T_NATIVE_DOUBLE, memspace_id, filespace_id, H5P_DEFAULT, curr_entry);
    if (ret < 0) {
        cout << "Error writing to dataset"<< entry << endl;
      fprintf(stderr, "Error writing to dataset.\n");
      return;
    }
  H5Sclose(filespace_id);
  H5Sclose(memspace_id);

  }

  cout << "** Exiting..." << endl;

  delete treeReader;
  delete chain;

  // Close the dataset and file
  H5Dclose(datasetId);
  H5Sclose(dataspaceId);
  H5Fclose(fileId);
}
