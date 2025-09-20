#!/usr/bin/env python
import os
import sys

# requer argumento
if len(sys.argv) < 2:
    raise ValueError("falta argumento <processos MPI>")

# captura quantos processos MPI
nTask = int(sys.argv[1])

# processos por no
coresPerNode=48

# nos
nNodes= (nTask-1)//coresPerNode + 1

# nomes job, executavel, arquivo de saida
job="Pi_"+str(nTask)
pwd=os.getcwd()
execName=pwd+"/Pi.exe"
if nTask < 10:
    outFile=pwd+"/Out_Pi_0"+str(nTask)+".txt"
else:
    outFile=pwd+"/Out_Pi_"+str(nTask)+".txt"

# fila
queue="sequana_cpu_dev"

# tempo de execucao
execTime="00:02:00"

# monta script
fOut=open("ssub.sh","w")
strOut="#!/bin/bash\n"
strOut+="#SBATCH --nodes="+str(nNodes)+"\n"
strOut+="#SBATCH --ntasks-per-node="+str(coresPerNode)+"\n"
strOut+="#SBATCH --ntasks="+str(nTask)+"\n"
strOut+="#SBATCH --cpus-per-task=1\n"
strOut+="#SBATCH -p "+queue+"\n"
strOut+="#SBATCH -J "+job+"\n"
strOut+="#SBATCH --time="+execTime+"\n"
strOut+="#SBATCH --output="+outFile+"\n"
strOut+="#SBATCH --exclusive\n"
strOut+="\n"
strOut+="cd $SLURM_SUBMIT_DIR\n"
strOut+="ulimit -s unlimited\n"
strOut+="mpirun -n $SLURM_NTASKS "+execName+"\n"
strOut+="exit\n"
fOut.write(strOut)
fOut.close()

# submete script
os.system("chmod +x "+pwd+"/ssub.sh")
os.system("sbatch ssub.sh")
