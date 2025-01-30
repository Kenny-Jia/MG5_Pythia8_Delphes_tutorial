#!/bin/bash

#SBATCH --account=atlas:default
#SBATCH --partition=roma
#SBATCH --qos=preemptable
#
#SBATCH --job-name=MG_PY_Delphes_MC
#SBATCH --output=logs/MC_output-%j.out
#SBATCH --error=logs/MC_output-%j.err
#
#SBATCH --account=atlas:usatlas
#SBATCH --partition=roma
#SBATCH --array=1-2
#SBATCH --cpus-per-task=16
#SBATCH --mem-per-cpu=5g
#
#SBATCH --time=2-03:00:0
#
#SBATCH --gpus 0 

source $workdir/Monte_Carlo/example_process.sh 
echo "This is task number $SLURM_ARRAY_TASK_ID"