set terminal pngcairo size 1200,800 enhanced font 'Verdana,12'
set output 'plots/grafico_bc32.png'

set title "Comparación Empírica: Estándar vs Strassen"
set xlabel "Tamaño de la matriz (n)"
set ylabel "Tiempo (ms)"
set grid
set key left top
set datafile separator ","

set logscale y

# Estilos de línea
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 1.5
set style line 2 lc rgb '#dd181f' lt 1 lw 2 pt 5 ps 1.5

plot 'data/resultados_bc32.csv' using 1:2 with linespoints ls 1 title 'Estándar', \
     'data/resultados_bc32.csv' using 1:3 with linespoints ls 2 title 'Strassen'
