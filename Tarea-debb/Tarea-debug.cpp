#include <iostream>
#include <cstdlib>
#include <cmath>

typedef double REAL;

int foo(REAL a, REAL b);
int bar(REAL a, REAL b);
double baz(REAL x);

int main (int argc, char **argv)
{
  REAL ii, jj;
  ii =  0.0;
  jj = -1.0;
  std::cout << foo(ii, jj) << "\n";
  std::cout << foo(jj, ii) << "\n";

  std::cout << baz(25.9) << "\n";

  return EXIT_SUCCESS;
}

int foo(REAL a, REAL b)
{
    if(a!=0 && b!=0 && bar(a, b)!=0){
        return a/b + b/bar(a, b) + b/a;
    }
    else return 0;
}

int bar(REAL a, REAL b)
{
  REAL c = std::fabs(a);
  return c + a - b;
}

REAL baz(REAL x)
{
  if (x == 0){
    return 0;
  }
  else{
    REAL v = 1+(x-1);

    return std::sqrt(v);
  }
}
