#!/bin/bash
# 
# script para executar Tempo.exe sequencialmente no SantosDumont
#
# uso: Xmit.sh 
#
# nomes executavel, tarefa, arquivo de saida, arquivo de erro
#
Exec=`pwd`/Tempo.exe
Job=Tempo
ArqSaida=`pwd`/OutTempo
ArqErro=`pwd`/ErrTempo
#
# gera arquivo ssub.sh
#
cat << EOF0 > ssub.sh
#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1
#SBATCH -p sequana_cpu_dev
#SBATCH -J $Job
#SBATCH --time=00:01:00
#SBATCH --output=$ArqSaida
#SBATCH --error=$ArqErro
#SBATCH --exclusive

cd \$SLURM_SUBMIT_DIR
srun -n \$SLURM_NTASKS $Exec
EOF0
#
# envia ssub.sh para execucao
#
sbatch ssub.sh
exit


