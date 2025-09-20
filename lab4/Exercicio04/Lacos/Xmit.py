#!/usr/bin/env python
import os
import sys

nNodes=1
nTasksPerNode=1
nTasks=1
queue="sequana_cpu_dev"
execTime="00:01:00"

pwd=os.getcwd()
execName=pwd+"/Lacos.exe"
job="Lacos"
outFile=pwd+"/Out_Lacos.txt"

fOut=open("ssub.sh","w")
strOut="#!/bin/bash\n"
strOut+="#SBATCH --nodes="+str(nNodes)+"\n"
strOut+="#SBATCH --ntasks-per-node="+str(nTasksPerNode)+"\n"
strOut+="#SBATCH --ntasks="+str(nTasks)+"\n"
strOut+="#SBATCH --cpus-per-task=1\n"
strOut+="#SBATCH -p "+queue+"\n"
strOut+="#SBATCH -J "+job+"\n"
strOut+="#SBATCH --time="+execTime+"\n"
strOut+="#SBATCH --output="+outFile+"\n"
strOut+="#SBATCH --exclusive\n"
strOut+="\n"
strOut+="cd $SLURM_SUBMIT_DIR\n"
strOut+="ulimit -s unlimited\n"
strOut+="srun -n $SLURM_NTASKS "+execName+"\n"
strOut+="exit\n"
fOut.write(strOut)
fOut.close()

os.system("chmod +x "+pwd+"/ssub.sh")
os.system("sbatch ssub.sh")
