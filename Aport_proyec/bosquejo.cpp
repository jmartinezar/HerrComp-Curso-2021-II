//Queremos que dada una copa m*m la distribución inicial sea un cuadrado (m/10)*(m/10) centrado en la copa
//
#include <cmath>
#include <random>
#include <iostream>
#include <vector>

void prototype(int Nmol, int size,  double prop, std::vector<int> & vector);//esta función pone las partículas en su arreglo inicial
void print_vector(int size, const std::vector<int> & vector);//esta función imprime el vector en pantalla en forma de matriz
int particle_mov(int Nmol, int size, int Nstep, int seed, std::vector<int> & vector);//esta función elige al azar la partícula que se va a mover
void step_int(int Nmol, int size, int Nstep, int seed, std::vector<int> & vector);//esta función mueve al azar la partícula en cualquier dirección o la deja quieta
double entropia(int Nmol, int size, const std::vector<int> & vector);//esta funcion calcula la entropia de la copa

int main(void)
{
    const int Part = 20;//numero de particulas
    const int size = 20;//tamaño de la matriz
    const double prop = 0.1;//proporcion entre el cuadrado del centro y la matriz
    const int seed = 3; //semilla del generador de numeros aleatorios
    const int Nstep = 1000; //numero de pasos del sistema

    std::vector<int> particles{0}; //inicializa el vector
    particles.resize(size*size);//poner el tamaño del vector
    print_vector(size, particles);//se imprime el vector antes de llenarlo
    prototype(Part, size, prop, particles);
    std::cout << "Aquí se llena\n";//se pone para diferenciar en la consola las dos matrices
    print_vector(size, particles);//se imprime despues de ser llenado
    std::cout << 0 << "\t" <<  entropia(Part, size, particles) << "\n";
    step_int(Part, size, Nstep, seed, particles);

    return 0;
}

void prototype(int Nmol, int size, double prop, std::vector<int> & vector)
{
    int initial_value = size*(1-prop)/2;//es el indice de la primera fila y columna que se va a llenar
    int ratio = size*prop;//la longitud del cuadrado central
    int counter = Nmol;//contador que sirve para poner todas las moleculas en la copa
    while(counter!=0)//si despues de haber llenado todo el cuadro quedan particular, se vuelve a recorrer con las que sobran
    {
        for(int ii = initial_value; ii<initial_value+ratio; ++ii)//recorre las filas desde el primer índice (hallado inicialmente) hasta el último, despues del radio
        {
            for(int jj=initial_value; jj<initial_value+ratio; ++jj)//hace lo mismo que el otro pero para las columnas
            {
                if(counter==0)//revisa que no se pongan partículas de más
                {
                    break;
                }
                vector[ii*size+jj]+=1;//añade 1 al valor de este componente del vector
                counter-=1;//le resta 1 al contador
            }
        }
    }

}

void print_vector(int size, const std::vector<int> & vector)
{
    for(int ii=0; ii<size; ++ii)
    {
        for(int jj=0; jj<size; ++jj)
        {
            std::cout << vector[ii*size+jj] << "\t";
        }
        std::cout << "\n";
    }
}

int particle_mov(int Nmol, int size, int Nstep, int seed, std::vector<int> & vector)
{
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> dis{1, Nmol};
    int counter = 0;
    for(int ii = 1; ii <= Nstep; ++ii)
    {
        counter = dis(gen);
    }
    for(int ii = 0; ii<size; ++ii)//bucle para recorrer las filas de la matriz
    {
        for(int jj = 0; jj<size; ++jj)//bucle para recorres las columnas
        {
            counter -= vector[ii*size+jj];//por cada partícula que haya, el contador se reduce en 1
            if(counter <= 0)// cuando el contador es cero es porque la posición en la que se encuentra el barrido de la matriz es la de la molécula que toca mover
            {
                return ii*size + jj;// la función retorna la posición de la molécula que toca mover
            }
        }
    }
}

void step_int(int Nmol, int size, int Nstep,  int seed, std::vector<int> & vector)
{
    int part = 0;
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> dis{1, 5};
    int lado = 0;
    for(int ii = 1; ii <= Nstep; ++ii)
    {
        part = particle_mov(Nmol, size, ii, seed,  vector);
        lado = dis(gen);//se genera un número aleatorio que determina para qué lado se mueve la partícula 1 es arriba, 2 es abajo, 3 es derecha y 4 es izquierda
        if(lado == 1)//si es 1 indica que se va a mover hacia arriba
        {
            if((part - size + 1) <= 0)//si la partícula se encuentra en la primera fila
            {
                vector[part] -= 1;//la retira de la fila en la que está
                vector[size*(size-1) + part] += 1;//la pone en la misma columna pero en la última fila
            }
            else//si no está en la última fila
            {
                vector[part] -= 1;//la retira de la fila en la que está
                vector[part - size] += 1;//la pone en la misma columna pero en la fila de arriba
            }
        }
        else if(lado == 2)
        {
            if(part/size == (size - 1))//si la partícula se encuentra en la última fila
            {
                vector[part]-=1;//la retira de la fila en la que está
                vector[part - size*(size-1)] += 1;//la pone en la misma columna pero en la primera fila
            }
            else//si no está en la última fila
            {
                vector[part] -= 1;//la retir de donde está
                vector[part + size] += 1;//la pone en la misma columna pero en la fila de abajo
            }
        }
        else if(lado == 3)
        {
            if(part%size == 0)//si la partícula está en la primera columna
            {
                vector[part] -= 1;//la retira de donde está
                vector[part + size - 1] += 1;//la pone en la misma fila pero al otro lado de la copa
            }
            else//si no
            {
                vector[part] -= 1;//la retira de donde está
                vector[part - 1] += 1;//la pone a la derecha
            }
        }
        else if(lado == 4)
        {
            if((part - size +1)%size == 0)//si está en la última columna
            {
                vector[part] -= 1;//la retira de donde está
                vector[part -size + 1] += 1;//la pone en la misma fila pero al otro lado de la copa
            }
            else//si no
            {
                vector[part] -= 1;//la retira de donde está
                vector[part + 1] += 1;//la pone a la izquierda
            }
        }
        std::cout << ii << "\t" << entropia(Nmol, size, vector) << "\n";
    }
}

double entropia(int Nmol, int size, const std::vector<int> & vector)
{
    double sum = 0.0;
    double aux = 0.0;
    double auxN = Nmol;
    for(int ii = 0; ii < size; ++ii)
    {
        for(int jj = 0; jj < size; ++jj )
        {
            if(vector[ii*size + jj] != 0)
            {
                aux = vector[ii*size + jj];
                sum += (aux/auxN)*std::log(aux/auxN);
            }
        }
    }
    return -sum;
}
