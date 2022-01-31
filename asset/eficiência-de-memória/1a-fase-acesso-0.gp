set term postscript eps color 14
set encoding utf8
set output "1a-fase-acesso-0.eps"
set title "Gráfico de acesso - ID 0"
set xlabel "Acesso"
set ylabel "Endereço"
plot "1a-fase-acesso-0-0.gpdat" u 2:4 w points t "L", "1a-fase-acesso-1-0.gpdat" u 2:4 w points t "E"
