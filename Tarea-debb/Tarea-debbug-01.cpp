#include <iostream>
#include <cstdlib>
#include <cmath>

int foo(int a, int b);
int bar(int a, int b);
double baz(double x);
void print_array(const double data[], const int & size);
void inicialized_array(double data[], const int & size);

int main (int argc, char **argv)
{
  int ii, jj;
  ii =  0;
  jj = -1;
  foo(ii, jj);
  foo(jj, ii);

  baz(25.9);

  const int NX = 2, NY = 3, NZ = 4;
  double *x=nullptr, y[NY] ={0}, z[NZ]={0};
  x = new double [NX];
  inicialized_array(x, NX);

  print_array(x, NX);
  print_array(y, NY);
  print_array(z, NZ);
  std::cout << std::endl;

  for (ii = 0; ii < NX; ++ii) {
    x[ii] = ii;
  }
  print_array(x, NX);
  print_array(y, NY);
  print_array(z, NZ);
  std::cout << std::endl;
  for (jj = 0; jj < NY; ++jj) {
      if(jj<NX){
          x[jj] = ii;
      }
      y[jj] = jj;
  }
  print_array(x, NX);
  print_array(y, NY);
  print_array(z, NZ);
  std::cout << std::endl;

  delete[] x;

  return EXIT_SUCCESS;
}

int foo(int a, int b)
{
    if(a!=0 && b!=0 && bar(a, b)!=0){
        return a/b + b/bar(a, b) + b/a;
    }
    else{
        return 0;
    }
}

int bar(int a, int b)
{
  unsigned int c = a;
  return c + a - b;
}

double baz(double x)
{
    if (x == 0) return 0;
    else{
        double v = 1-(x+1);
        return std::sqrt(v);
    }
}

void print_array(const double data[], const int & size)
{
  std::cout << std::endl;
  for (int ii = 0; ii < size; ++ii) {
    std::cout << data[ii] << "  " ;
  }
}

void inicialized_array(double data[], const int & size)
{
    for (int ii=0; ii < size; ++ii)
    {
        data[ii]=0;
    }
}
