source /cvmfs/sft.cern.ch/lcg/views/LCG_105/x86_64-centos7-gcc11-opt/setup.sh
export workdir=/fs/ddn/sdf/group/atlas/d/$USER
export datadir=$workdir/Monte_Carlo/data
export mg5dir=$workdir/MG5_aMC_v3_5_6
export PYTHIA8DATA=`$mg5dir/HEPTools/pythia8/bin/pythia8-config --xmldoc` 
if [ -d "$ROOTSYS"  ]; then
    echo "Using ROOT from $ROOTSYS";
else
    echo "ROOT not found!";
fi
if [ -d "$mg5dir"  ]; then 
    echo "Using Madgraph5 from $mg5dir";
else
    echo "Madgraph not found!";
fi
echo "Using workdir=$workdir";
echo "Using datadir=$datadir";
cd $workdir/Monte_Carlo
echo "Ready for Monte Carlo generation at $PWD";
