set term postscript eps color 14
set encoding utf8
set output "2a-fase-aux-hist-0-0.eps"
set style fill solid 1.0
set title "Distância de Pilha Total 1996 - Fase  0 - ID 0"
set xlabel "Distância"
set ylabel "Endereço"
plot [-1:3] "2a-fase-aux-hist-0-0.gpdat" u 3:4 w boxes t ""
