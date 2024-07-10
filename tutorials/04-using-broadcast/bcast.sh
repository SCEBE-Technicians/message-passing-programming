#!/bin/bash
#SBATCH -o bcast.output
#SBATCH --time=5
#SBATCH --mem=128
#SBATCH --ntasks=7

mpirun -n 7 bcast
