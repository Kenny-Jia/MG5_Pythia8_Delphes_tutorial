# Usage

in `Monte_Carlo/` , run setup.sh
```
source setup.sh
```
Now run the pileup generation script in this directory
```
cd pileup_gen
mkdir output
./run_pileup_gen.sh
```
The shell script will do three things

1) compile `generatePUHemc.c`, which is the c program used to run the `generatePileUp.cmnd` Pythia script

2) Run `generatePUHemc` and store the .dat output and the Pythia output to `output/`

3) Run the Delphes script `hepmc2pileup` to convert the `hepmc2 (.dat)` file into `.pileup` .

The pileup generation parameters are specified in `generatePileUp.cmnd`. 