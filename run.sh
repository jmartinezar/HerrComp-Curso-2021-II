for i in $(seq 1 16); do
         ./a.out 400000000 ${i} 2> /dev/null;
done > Nthreads.txt
