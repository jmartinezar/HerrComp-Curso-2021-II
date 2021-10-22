set xlabel 'N'
set ylabel 'Diff %'
set log x; set log y
set term pdf; set out 'fig.pdf'
plot 'datos.txt' w l t 'Error'