set xlabel 'Time (10⁶ step)'
set ylabel 'Entropy'
set log x
set term png
set out 'Entropy.png'
plot 'entropy.txt' u 1:2 w l t 'Entropy in funct time'
