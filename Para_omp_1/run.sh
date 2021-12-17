g++ -fopenmp -O3  openmp_parallel_for.cpp -o aut.x
for nthreads in $(seq 1 16); do
    echo -n "${nthreads}  ";
    OMP_NUM_THREADS=${nthreads} ./aut.x
done > aut.txt

g++ -fopenmp -O3  openmp_parallel_for_manual.cpp -o man.x
for nthreads in $(seq 1 16); do
    echo -n "${nthreads}  ";
    OMP_NUM_THREADS=${nthreads} ./man.x
done > man.txt
