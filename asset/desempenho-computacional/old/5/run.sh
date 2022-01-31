#!/bin/bash

# for i in {1..10}
# do
#     ../not-opt *_linhas.txt out 1000
#     mv log* ${i}
# done

# cat $(seq 1 10) > avg-not
# rm $(seq 1 10)
# ./calc-media < avg-not

for i in {1..10}
do
    ../opt *_linhas.txt out 1500
    mv log* ${i}
done

rm ro*
rm out

cat $(seq 1 10) > avg
rm $(seq 1 10)
./calc-media < avg
