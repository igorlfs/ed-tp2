set term postscript eps color 14
set encoding utf8
set output "qs.eps"
set title "Otimização vs sem Otimização"
set xlabel "Quantidade de URLs"
set ylabel "Tempo de Execução (s)"
set key left top
plot "opt.gpdat" u 1:2 w linesp t "Otimizado",\
"not-opt.gpdat" u 1:2 w linesp t "Sem Otimização"
