#!/bin/bash
#SBATCH -o print_array.output
#SBATCH -J 
#SBATCH --time=5
#SBATCH --ntasks=8
#SBATCH --partition himem

mpirun -n 3 print_array
