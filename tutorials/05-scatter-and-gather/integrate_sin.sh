#!/bin/bash
#SBATCH -o integrate_sin.output
#SBATCH -J 
#SBATCH --time=5
#SBATCH --ntasks=3
#SBATCH --partition=himem

mpirun -n 3 integrate_sin
