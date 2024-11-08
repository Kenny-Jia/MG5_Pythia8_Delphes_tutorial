# usage: ./run_pileup_gen.sh
# Edit pileup properties by changing generatePileUp.cmnd
# The .cmnd script is copied from MG5_aMC_v3_5_6/Delphes/examples/Pythia8/generatePileUp.cmnd
# The pythia program to run the cmnd script is edited from MG5_aMC_v3_5_6/HEPTools/pythia8/share/Pythia8/examples/main42.cc
# The makefile to compile the program is edited from MG5_aMC_v3_5_6/HEPTools/pythia8/share/Pythia8/examples/Makefile


if [ -z "$mg5dir" ]; then
  echo "Error: mg5dir environment variable is not set. Run setup.sh"
  exit 1
fi

export PILEUP_DIR=$workdir/pileup_gen
export PYTHIA_BASE_DIR="$mg5dir/HEPTools/pythia8"
# export EXAMPLES_DIR="$mg5dir/HEPTools/pythia8/share/Pythia8/examples"
echo "Using PYTHIA_BASE_DIR=$PYTHIA_BASE_DIR";

make info-pythia

make generatePUHemc

"$PILEUP_DIR/generatePUHemc" "$PILEUP_DIR/generatePileUp.cmnd" "$PILEUP_DIR/output/MinBias.dat" > "$PILEUP_DIR/output/pythia_log"

"$mg5dir/Delphes/hepmc2pileup" "$PILEUP_DIR/output/MinBias.pileup" "$PILEUP_DIR/output/MinBias.dat"