set term postscript eps color 14
set encoding utf8
set output "aux-1a-hist-0-0.eps"
set style fill solid 1.0
set title "Distancia de Pilha Total 77 - Fase  0 - ID 0"
set xlabel "Distância"
set ylabel "Endereço"
plot [-1:2] "aux-1a-hist-0-0.gpdat" u 3:4 w boxes t ""
