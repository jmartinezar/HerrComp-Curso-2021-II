#include <omp.h>
#include <iostream>
#include <cmath>
#include <chrono>

int main(int argc, char *argv[]) {
    const int N = 80000000;
    int i;
    double *a = new double[N];
    auto start = std::chrono::system_clock::now();

#pragma omp parallel for
    for(i = 0; i < N; i++) {
        a[i] = 2*i*std::sin(std::sqrt(i/56.7)) +
            std::cos(std::pow(i*i, 0.3));
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<float,std::milli> duration = end - start;

    std::cout << duration.count() << "s"  << std::endl;

    //std::cout << a[1] << "\n";

    delete [] a;
    return 0;
}
