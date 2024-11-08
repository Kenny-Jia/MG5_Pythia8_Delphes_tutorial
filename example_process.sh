source /cvmfs/sft.cern.ch/lcg/views/LCG_105/x86_64-centos7-gcc11-opt/setup.sh
export mg5dir=$workdir/MG5_aMC_v3_5_6
export datadir=$workdir/Monte_Carlo/data
export PYTHIA8DATA=`$mg5dir/HEPTools/pythia8/bin/pythia8-config --xmldoc`
export scriptDir=$workdir/Monte_Carlo/MG_script
export PATH=$mg5dir/bin:$mg5dir/HEPTools/bin:$PATH
export LD_LIBRARY_PATH=$mg5dir/HEPTools/lib/:$mg5dir/HEPTools/lhapdf6_py3/lib/:$mg5dir/HEPTools/lhapdf6_py3/lib/python3.9/site-packages/:$mg5dir/HEPTools/hepmc/lib/:$mg5dir/HEPTools/pythia8//lib:$mg5dir/HEPTools/zlib/lib/:$LD_LIBRARY_PATH:/sdf/data/atlas/u/hjia625/LD_lib:$ROOTSYS/lib:$LD_LIBRARY_PATH

export LHAPDF_DATA_PATH=$mg5dir/HEPTools/lhapdf6_py3/share/LHAPDF
source $mg5dir/Delphes/DelphesEnv.sh
echo "Using ROOTSYS=$ROOTSYS"
echo "Using mg5dir=$mg5dir"
echo "Using PATH=$PATH"
echo "Using LD_LIBRARY_PATH=$LD_LIBRARY_PATH"
echo "Using PYTHIA8DATA=$PYTHIA8DATA"
echo "Using LHAPDF_DATA_PATH=$LHAPDF_DATA_PATH"
if [ "$MyRandomNumber" == ""  ]; then export MyRandomNumber=`date +"%-N"`; fi
temp_file=$(mktemp)

# Perform the first sed operation
sed 's/output /output '"$SLURM_ARRAY_TASK_ID"'/g' "$scriptDir/example-MG5-pythia8-delphes.txt" > "$temp_file"

# Perform the second sed operation, writing to the final output file
sed 's/set iseed 0/set iseed '"$MyRandomNumber"'/g' "$temp_file" > "$scriptDir/example-MG5-pythia8-delphes_$SLURM_ARRAY_TASK_ID.txt"

# Remove the temporary file
rm "$temp_file"

# Run the Python script
cd $datadir
python $mg5dir/bin/mg5_aMC $scriptDir/example-MG5-pythia8-delphes_$SLURM_ARRAY_TASK_ID.txt
