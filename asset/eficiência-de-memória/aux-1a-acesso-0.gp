set term postscript eps color 14
set encoding utf8
set output "aux-1a-acesso-0.eps"
set title "Gráfico de acesso - ID 0"
set xlabel "Acesso"
set ylabel "Endereço"
plot "aux-1a-acesso-0-0.gpdat" u 2:4 w points t "L", "aux-1a-acesso-1-0.gpdat" u 2:4 w points t "E"
