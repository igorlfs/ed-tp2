#!/bin/sh

for (( i=10000; i<=100000; i+=10000))
do
    # j=$((${i}/10))
    # ./geracarga -o ${i}_linhas.txt -u ${i} -p 20 -q 1 -r ${i} -s ${j}
    k=$((${i}/10000))
    # mv ${i}_linhas.txt desempenho-computacional/${k}
    cp calc-media ./desempenho-computacional/${k}/
    cp run.sh ./desempenho-computacional/${k}/
done
