set term postscript eps color 14
set encoding utf8
set output "2a-fase-aux-acesso-0.eps"
set title "Gráfico de acesso - ID 0"
set xlabel "Acesso"
set ylabel "Endereço"
plot "2a-fase-aux-acesso-0-0.gpdat" u 2:4 w points t "L", "2a-fase-aux-acesso-1-0.gpdat" u 2:4 w points t "E"
