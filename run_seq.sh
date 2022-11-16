#!/bin/bash
#SBATCH --time=1:00
#SBATCH --partition=cpar
###SBATCH --constraint=k20

perf record ./bin/k_meansv2 10000000 4 
perf report --stdio > perfreportseq