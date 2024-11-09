# usage: ./run_pileup_gen.sh
# Edit pileup properties by changing generatePileUp.cmnd
# The .cmnd script is copied from MG5_aMC_v3_5_6/Delphes/examples/Pythia8/generatePileUp.cmnd
# The pythia program to run the cmnd script is edited from MG5_aMC_v3_5_6/HEPTools/pythia8/share/Pythia8/examples/main42.cc
# The makefile to compile the program is edited from MG5_aMC_v3_5_6/HEPTools/pythia8/share/Pythia8/examples/Makefile

export mg5dir=$workdir/MG5_aMC_v3_5_6
export datadir=$workdir/Monte_Carlo/data
export PYTHIA8DATA=`$mg5dir/HEPTools/pythia8/bin/pythia8-config --xmldoc`
export scriptDir=$workdir/Monte_Carlo/MG_script
export PATH=$mg5dir/bin:$mg5dir/HEPTools/bin:$PATH
export LD_LIBRARY_PATH=$mg5dir/HEPTools/lib/:$mg5dir/HEPTools/lhapdf6_py3/lib/:$mg5dir/HEPTools/lhapdf6_py3/lib/python3.9/site-packages/:$mg5dir/HEPTools/hepmc/lib/:$mg5dir/HEPTools/pythia8//lib:$mg5dir/HEPTools/zlib/lib/:$LD_LIBRARY_PATH:/sdf/data/atlas/u/hjia625/LD_lib:$ROOTSYS/lib:$LD_LIBRARY_PATH
export LHAPDF_DATA_PATH=$mg5dir/HEPTools/lhapdf6_py3/share/LHAPDF

if [ -z "$mg5dir" ]; then
  echo "Error: mg5dir environment variable is not set. Run setup.sh"
  exit 1
fi

export PILEUP_DIR=$workdir/Monte_Carlo/pileup_gen
if [ ! -d "$PILEUP_DIR/output"  ]; then
  mkdir $PILEUP_DIR/output
fi

export PYTHIA_BASE_DIR="$mg5dir/HEPTools/pythia8"
# export EXAMPLES_DIR="$mg5dir/HEPTools/pythia8/share/Pythia8/examples"
echo "Using PYTHIA_BASE_DIR=$PYTHIA_BASE_DIR";

make info-pythia

make generatePUHemc

"$PILEUP_DIR/generatePUHemc" "$PILEUP_DIR/generatePileUp.cmnd" "$PILEUP_DIR/output/MinBias.dat" > "$PILEUP_DIR/output/pythia_log"

"$mg5dir/Delphes/hepmc2pileup" "$PILEUP_DIR/output/MinBias.pileup" "$PILEUP_DIR/output/MinBias.dat"
