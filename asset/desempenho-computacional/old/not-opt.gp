set term postscript eps color 14
set encoding utf8
set output "not-opt.eps"
set title "Desempenho sem Otimização"
set xlabel "Quantidade de URLs"
set ylabel "Tempo de Execução (s)"
set key left top
plot "not-opt.gpdat" u 1:2 w linesp t "Geração de Rodadas",\
"not-opt.gpdat" u 1:3 w linesp t "Intercalação",\
"not-opt.gpdat" u 1:4 w linesp t "Total"
