#!/bin/bash

#Lagrange -- function

./run.sh la 1 -4 3

#Troca de Sinal -- x_init passo function
echo "------------------------------------------------"
./run.sh tr 0 0.1 1 -4 3 

#Bisseção -- baixo alto precisão fucntion
echo "------------------------------------------------"
./run.sh bi 0 5 0.001 1 -4 3

#Corda -- baixo alto precisão fucntion
echo "------------------------------------------------"
./run.sh co 0 5 0.001 1 -4 3

#Newton -- baixo alto precisão fucntion
echo "------------------------------------------------"
./run.sh ne 0 5 0.001 1 -4 3

#Newton-Brisseção -- baixo alto precisão fucntion
echo "------------------------------------------------"
./run.sh bn 0 5 0.001 1 -4 3

#Ponto Fixo -- 
echo "------------------------------------------------"
#função g(x) =0.25x²+0.75
#intervalo: 0 ~ 1,9
./run.sh po 

#Broyden -- 
echo "------------------------------------------------"
./run.sh br


