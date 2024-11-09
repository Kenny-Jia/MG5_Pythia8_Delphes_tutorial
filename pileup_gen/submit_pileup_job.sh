#!/bin/bash

#
#SBATCH --job-name=PileUp
#SBATCH --output=Pileup_output-%j.out
#SBATCH --error=Pileup_output-%j.err
#
#SBATCH --account=atlas:usatlas
#SBATCH --partition=roma
#SBATCH --cpus-per-task=32
#SBATCH --mem-per-cpu=5g
#
#SBATCH --time=2-03:00:0
#
#SBATCH --gpus 0 

source /fs/ddn/sdf/group/atlas/d/hjia625/Monte_Carlo/setup.sh 
$workdir/Monte_Carlo/pileup_gen/run_pileup_gen.sh 

