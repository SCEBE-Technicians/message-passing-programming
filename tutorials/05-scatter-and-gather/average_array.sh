#!/bin/bash
#SBATCH -o average_array.output
#SBATCH -J 
#SBATCH --time=5
#SBATCH --ntasks=8
#SBATCH --partition himem

time mpirun -n 2 average_array
time mpirun -n 4 average_array
time mpirun -n 8 average_array
