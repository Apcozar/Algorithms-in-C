
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

#define TAM 128000
typedef struct {
	int vector[TAM];
	int ultimo;
} monticulo;

//FUNCIONES PARA COMPARAR COTAS
double pow2_2(int n){
	return pow(n,2.2);
}

double pow2(int n){
	return pow(n,2);
}


double pow2_1(int n){
	return pow(n,2.1);
}

double pow1_8(int n){
	return pow(n,1.8);
}
	
double pow1_2(int n){
	return pow(n,1.1);
}

double pow1_5(int n){
	return pow(n,1.5);
}

double pow1(int n){
	return n;
}

double pow0_8(int n){
	return pow(n,0.8);
}

double pow0_5(int n){
	return pow(n,0.5);
}

double pow1_9(int n){
	return pow(n,1.95);
} 
double nlogn(int n){
	return n*log(n);
}
//FUNCIONES PARA INICIALIZAR VECTORES
void ascendente(int v[], int n){
	int i;
	
	for(i = 0; i < n; i++)
		v[i] = i;
	
}
void aleatorio(int v[], int n){ 

	int i, m = 2*n+1;
	for (i = 0; i < n; i++)
		v[i] = (rand() % m) - n;
	
}


void inicializar_semilla(){
	srand(time(NULL));
}



//Funciones testear algoritmo

//FUNCIONES K-ESIMO

void Hundir( monticulo * mont , int i){
	int HijoIzq,HijoDer,j,aux;
	
	do{
		HijoIzq = 2*(i)+1;
		HijoDer = 2*(i)+2;
		j=i;
		
		if ((HijoDer <= mont->ultimo) && 
			(mont->vector[HijoDer] > mont->vector[i])){
			i=HijoDer;
			}
			
		if ((HijoIzq <= mont->ultimo) && 
			(mont->vector[HijoIzq] > mont->vector[i])){
				i=HijoIzq;
				}
		aux=mont->vector[j];
		mont->vector[j] = mont->vector[i];
		mont->vector[i] = aux;
		
	}while  (j!=i);

}
void crear_monticulo(int a[], int x , monticulo * mont){
	int i ;
	
	for (i=0;i<x;i++){
		mont->vector[i]=a[i];
		
	}	
	mont->ultimo=x;
	
	for (i=(mont->ultimo / 2) ; i>=0  ; i--){
		
		Hundir(mont,i);
	}
}
int eliminar_mayor (monticulo * mont){
	int x;
	
	if ( mont->ultimo == 0){ printf("monticulo vacio");
		exit(EXIT_FAILURE);}
	
	else{
			x = mont->vector[0];
			mont->vector[0] = mont->vector[mont->ultimo-1];
			mont->ultimo= mont->ultimo -1;

			if (mont->ultimo > 0) Hundir(mont,0);
			
			return x ;
		}
	
	
}
int kesimo_mayor(int v[], int n, int k){
    int x;
    monticulo mont;
    crear_monticulo(v,n,&mont);
    for (int i=0;i<k;i++){
        x=eliminar_mayor(&mont); 
    }
    return x;

}
//FUNCIONES PARA COMPROBAR VECTORES
void testr(int v[],int tam,int k){
	
    int resultado;
    aleatorio(v,tam);   
    for(int i = 0; i < tam; i++)
		printf("%d ,", v[i]);

    printf("\n");
	resultado=kesimo_mayor(v,tam,k);
    printf("resultado %d \n",resultado);
	
}
void testasc(int v[],int tam,int k){
    int resultado;
    ascendente(v,tam);
    for(int i = 0; i < tam; i++)
		printf("%d ,", v[i]);

    printf("\n");
	resultado=kesimo_mayor(v,tam,k);
    printf("resultado %d \n",resultado);
    
}

//FUNCIONES PARA MEDIR TIEMPOS
double microsegundos(){
	struct timeval t;
	
	if (gettimeofday(&t,NULL) < 0)
		return 0.0;
		
	return (t.tv_usec + t.tv_sec * 1000000.0);
}
//FUNCIONES PARA MOSTRAR TABLAS
double tiempos(int n,int aa){
	
	double t1, t2, ta, tb, t;
	int k = 1000;
	
	
		int v[n];
		aleatorio(v, n);
		t1 = microsegundos();
		kesimo_mayor(v, n,aa);
		t2 = microsegundos();
		t = t2-t1;
		
		if (t < 500){
			t1 = microsegundos();
			for (int j = 0; j <= k; j++){
				aleatorio(v, n);
				kesimo_mayor(v, n,aa);
			}
			t2 = microsegundos();
			ta = t2 - t1;
			
			t1 = microsegundos();
			for (int j = 0; j <= k; j++){
				aleatorio(v, n);
			}
			t2 = microsegundos();
			tb = t2 - t1;
			t = (ta-tb)/k;
			printf("%15.4f *",t);
			
		}else{
			
		printf("%15.4f  ",t);	
			
		}

	
	return t;
}

void printVector(int v[], int n){
	int i;
	
	for(i = 0; i < n; i++)
		printf("%d, ", v[i]);
        printf("\n");
	
	}
void tabla(double (* x)(int),double (* y)(int),double (* z)(int),int k){
	double t;
	
	printf("%12s%15s%14s%14s%14s\n", "n", "t(n)", "t/c1","t/c2","t/c3");
	
	for (int n = 500; n <= 32000; n = n*2){
		printf("%12d", n);
		
		t = tiempos(n,k);
		
		printf(" %11.8f%15.8f%15.8f\n", t /(* x)(n), t /(* y)(n), t /(* z)(n));
	}	
	
}
	
int main(int argc, char **argv){
	int kbig [10] = {1,51,101,151,201,251,301,351,401,451};
	
    int tam10=10;
    int tam500=500;
	int v[tam10];
    int w[tam500];
    int k=3;
    inicializar_semilla();
    //Tests pedidos inicialmente
    printf("Test vector 10 elementos aleatorios \n");
    aleatorio(v,tam10);
	printVector(v,tam10);
    printf("El %d-esimo mayor es %d \n",k,kesimo_mayor(v,tam10,k));
    
    printf("Test vector 500 elementos ascendente \n");
    ascendente(w,tam500);
    printVector(w,tam500);
	for(int i = 0; i < 10; i++)
		printf("El %d-esimo mayor es %d \n",
                                kbig[i],kesimo_mayor(w,tam500,kbig[i]));
    //Complejidades
    printf("Calentamiento de la maquina\n");/*calentamiento de la maquina */
	tabla( pow1_2, pow1_5, pow2_2 ,5);
	tabla( pow1_2, pow1_5, pow2_2 ,5);
	tabla(pow1_2, pow1_5, pow2_2,5 );
	tabla( pow1_2, pow1_5, pow2_2 ,5);
	//
	
	printf("Tablas \n");
	printf("Aleatorio \n");
	tabla( pow0_8, pow0_8, pow1_8,5 );
    tabla(pow0_8,pow0_8, pow1_8,tam500/2);
	
	
	
    
   
}
