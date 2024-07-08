#!/bin/bash
#SBATCH -o ping_pong.output
#SBATCH -J 
#SBATCH --time=5
#SBATCH --mem=128
#SBATCH --ntasks=2

mpirun -n 2 ping_pong
