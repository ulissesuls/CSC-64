#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1
#SBATCH -p sequana_cpu_dev
#SBATCH -J Tempo
#SBATCH --time=00:01:00
#SBATCH --output=/scratch/csc642023/ulisses.silva2/lab1/OutTempo
#SBATCH --error=/scratch/csc642023/ulisses.silva2/lab1/ErrTempo
#SBATCH --exclusive

cd $SLURM_SUBMIT_DIR
srun -n $SLURM_NTASKS /scratch/csc642023/ulisses.silva2/lab1/Tempo.exe
