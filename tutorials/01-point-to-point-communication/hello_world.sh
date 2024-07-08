#!/bin/bash -l
#SBATCH -o hello_world.output
#SBATCH -J mpi-test
#SBATCH --time=5
#SBATCH --mem=256
#SBATCH --nodes=1
#SBATCH --ntasks=4

mpirun hello_world
