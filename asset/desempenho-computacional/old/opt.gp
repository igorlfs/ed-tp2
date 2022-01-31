set term postscript eps color 14
set encoding utf8
set output "opt.eps"
set title "Desempenho com Otimização"
set xlabel "Quantidade de URLs"
set ylabel "Tempo de Execução (s)"
set key left top
plot "opt.gpdat" u 1:2 w linesp t "Geração de Rodadas",\
"opt.gpdat" u 1:3 w linesp t "Intercalação",\
"opt.gpdat" u 1:4 w linesp t "Total"
