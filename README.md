# MG5_Pythia8_Delphes_tutorial
This tutorial contains a specific guide to
1) Generate hard events using MadGraph5
2) Hadronize using Pythia8
3) Run fast simulation for FCC-hh (will be compatible for other collider) detector's response using Delphes
4) Submit jobs with Slurm in SLAC S3DF computing environment to produce large number of events
##Installation (first time only)
I highly recommend to done this tutorial and all Monte\_Carlo generation at S3DF iana /fs/ddn/sdf/group/atlas/d/$USER
First, clone this repo to hold everything
```
cd /fs/ddn/sdf/group/atlas/d/$USER
git clone https://github.com/Kenny-Jia/MG5_Pythia8_Delphes_tutorial Monte_Carlo
export workdir=$PWD/Monte_Carlo
cd $workdir
```
If you are on either S3DF or lxplus, you should have access to cvmfs. We will use ROOT from there.
```
source /cvmfs/sft.cern.ch/lcg/views/LCG_105/x86_64-centos7-gcc11-opt/setup.sh

```
Download the Madgragh5 package from the official website
```
wget https://launchpad.net/mg5amcnlo/3.0/3.5.x/+download/MG5_aMC_v3.5.5.tar.gz
tar zxf MG5_aMC_v3.5.5.tar.gz 
export mg5dir=$PWD/MG5_aMC_v3_5_5/
```
Open mg5\_aMC
```
python $mg5dir/bin/mg5_aMC
```
Now let's install all kinds of package we need within MG5\_aMC prompt. Be patient, they may take like 25 mins to finish.
```
install lhapdf6
install pythia8
install Delphes
exit
```
So far, this is only design for generating FCC-hh sample with pileup. But you can easily switch from the default to any detector card like what we need to do for FCC-hh here:
```
cp $mg5dir/Delphes/cards/FCC/FCChh_PileUp.tcl $mg5dir/Template/Common/Cards/delphes_card_default.dat
```
## Running with local machine
Assume you have successfully install everything, here the example is generating FCChh diHiggs production as an example. 
```
source setup.sh
python $mg5dir/bin/mg5_aMC $workdir/MG_script/example-MG5-pythia8-delphes.txt 

```
## Running with cluster using slurm
Similarly, we use the example MG5 script card:
```
sbatch $workdir/submit_job.sh
```
You can check the progress with 
```
squeue -u $USER
```
## Optional, Debugging, and other issues
```
pip install readline
```
readline is optional but strongly recommended for interactive MadGraph usage. For any issues regarding this repo, please feel free to contact Kenny through email: hjia625@stanford.edu. I would be happy to help!

