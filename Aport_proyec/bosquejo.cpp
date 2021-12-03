//Queremos que dada una copa m*m la distribución inicial sea un cuadrado (m/10)*(m/10) centrado en la copa
//
#include <random>
#include <iostream>
#include <vector>

void initial_distribution_array (int Nmol, int size, int ratio, int * vector, int seed);// int * vector?
void step (int Nmol, int size, int * vector, int seed);
void prototype(int Nmol, int size,  double prop, std::vector<int> & vector);
void print_vector(int size, const std::vector<int> & vector);

int main(int argc, char *argv[])
{
    //const int N = 10;
    const int Part = 20;//numero de particulas
    const int size = 20;//tamaño de la matriz
    const double prop = 0.1;//proporcion entre el cuadrado del centro y la matriz

    std::vector<int> particles{0}; //inicializa el vector
    particles.resize(size*size);//poner el tamaño del vector
    print_vector(size, particles);//se imprime el vector antes de llenarlo
    prototype(Part, size, prop, particles);
    std::cout << "Aquí se llena\n";//se pone para diferenciar en la consola las dos matrices
    print_vector(size, particles);//se imprime despues de ser llenado
/*
    int seed = 0;
    double mu=0, sigma=0.5;

    std::vector<int> particles{0}; //inicializa el vector

    std::mt19937 gen(seed);
    std::uniform_real_distribution<> dis{0,1};
    for (int i=0; i<N; i++){
	    std::cout<<dis(gen)<<std::endl;
    }*/

    return 0;
}

void initial_distribution_array (int Nmol, int size, int ratio, int * vector, int seed)
{
    int init_size = size/ratio;

    std::mt19937 gen(seed); //OJO: de pronto se generan los numeros aleatorios 2 veces
    std::uniform_int_distribution<> dis{0, init_size};

    for (int n=0; n<Nmol; n++){
	int i=0,j=0;
	i = size/2 -init_size/2 + dis(gen);
	j = size/2 -init_size/2 + dis(gen);
        vector[n] = i*size + j;
    }
}

void step (int Nmol, int size, int * vector, int seed)
{
    std::mt19937 gen(seed); //OJO: de pronto se generan los numeros aleatorios 3 veces
    std::uniform_int_distribution<> dis{0, Nmol -1};
    int mol = dis(gen);
    std::uniform_int_distribution<> dis{0, 4};
    int paso = dis(gen);
    int aqui = vector[mol]; //aqui es la posicion de la particula. reemplazar aqui por vector[mol] donde se usa en los if
    if (paso==1) {
	if (vector[mol]/size != 0) vector[mol] += -size;//arriba
	else vector[mol] += (size-1)*size; //se teletransporta hacia la pared de abajo
    }
    if (paso==2) {
	if (vector[mol]/size != size-1) vector[mol] += size;//abajo
	else vector[mol] = vector[mol] % size;//se teletransporta hacia la pared de arriba
    }
    if (paso==3) {
	if (vector[mol] % size != 0) vector[mol] += -1;//izquierda camarada
	else vector[mol] += size -1;//se teletransporta hacia la pared derecha
    }
    if (paso==4) {
	if (aqui % size != size-1)  vector[mol] += 1;//le voy a dar en la cara marica
	else vector[mol] = aqui/size; //se teletransporta hacia la pared izquierda
    }
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
