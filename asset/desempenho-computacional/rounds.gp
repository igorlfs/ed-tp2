set term postscript eps color 14
set encoding utf8
set output "rounds.eps"
set title "Tempo por Número de Páginas por Rodada"
set xlabel "Número de Páginas"
set ylabel "Tempo de Execução (s)"
set key left top
plot "rounds.gpdat" u 1:2 w linesp t "Geração de Rodadas",\
"rounds.gpdat" u 1:3 w linesp t "Intercalação",\
"rounds.gpdat" u 1:4 w linesp t "Total"
