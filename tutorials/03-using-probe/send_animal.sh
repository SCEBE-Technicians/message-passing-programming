#!/bin/bash
#SBATCH -o send_animal.output
#SBATCH -J 
#SBATCH --time=5
#SBATCH --mem=128
#SBATCH --ntasks=2

mpirun -n 2 send_animal
