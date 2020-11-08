#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

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
void descendente(int v[],int n){
	
	int i;
	
	for(i = 0; i < n; i++)
		v[i] = n - i;
	
}

void inicializar_semilla(){
	srand(time(NULL));
}

//FUNCIONES PARA COMPROBAR VECTORES

int esOrdenada (int v[],int n){
	int i;
	
	for(i = 0; i < n-1; i++){
		if (v[i]>v[i+1]) {
			return 0;	
		}
	}
	return 1;	
}
void printVector(int v[], int n){
	int i;
	
	for(i = 0; i < n-1; i++)
		printf("%d, ", v[i]);
	
	printf("%d \n", v[n-1]);
	printf("Â¿Ordenado? %d \n", esOrdenada(v,n));	
	}
//Funciones testear algoritmo
void test(int v[], int tam, void (* genVector)(int *, int), 
							void (* ord)(int *, int)){
	
	
	
	(* genVector)(v, tam);
	printf("Vector desordenado: \n");
	printVector(v,tam);
	(* ord)(v, tam);
	printf("Vector ordenado: \n");
	printVector(v, tam);
	printf("\n");

	}
void testAlgoritmos(void (* ord)(int *, int)){
	int tam = 10;
	int vector[tam];
	
	printf("Aleatorio \n");
	test(vector, tam, aleatorio, (* ord) );
	printf("Ascendente \n");
	test(vector, tam, ascendente, (* ord) );
	printf("Descendente \n");
	test(vector, tam, descendente, (* ord) );
	




}
//FUNCIONES PARA ORDENAR VECTORES
void ordenar (int v[], int n){
	
	int incrementos [11] = {88573,29524,9841,3280,1093,364,121,40,13,4,1};
	int tmp,j,incr;
	
	for (int i =0; i<11;i++){
		incr = incrementos[i];

		for (int a = incr; a<n;a++){
			tmp= v[a];
			j=a;
			while (j >= incr && v[j-incr] > tmp){
				v[j]=v[j-incr];
				j= j-incr;
			}
			v[j] =tmp;
		}
	}
}
//FUNCIONES PARA MEDIR TIEMPOS
double microsegundos(){
	struct timeval t;
	
	if (gettimeofday(&t,NULL) < 0)
		return 0.0;
		
	return (t.tv_usec + t.tv_sec * 1000000.0);
}
//FUNCIONES PARA MOSTRAR TABLAS
double tiempos(int n, void (* genVector)(int *, int), 
							void (* ord)(int *, int)){
	
	double t1, t2, ta, tb, t;
	int k = 1000;
	
	
		int v[n];
		(* genVector)(v, n);
		t1 = microsegundos();
		(* ord)(v, n);
		t2 = microsegundos();
		t = t2-t1;
		
		if (t < 500){
			t1 = microsegundos();
			for (int j = 0; j <= k; j++){
				(* genVector)(v, n);
				(* ord)(v, n);
			}
			t2 = microsegundos();
			ta = t2 - t1;
			
			t1 = microsegundos();
			for (int j = 0; j <= k; j++){
				(* genVector)(v, n);
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
void tabla(void (* genVector)(int *, int), 
		void (* ord)(int *, int),
		double (* x)(int),double (* y)(int),double (* z)(int)){
	double t;
	
	printf("%12s%15s%14s%14s%14s\n", "n", "t(n)", "t/c1","t/c2","t/c3");
	
	for (int n = 500; n <= 32000; n = n*2){
		printf("%12d", n);
		
		t = tiempos(n,(* genVector),(* ord));
		
		printf(" %11.8f%15.8f%15.8f\n", t /(* x)(n), t /(* y)(n), t /(* z)(n));
	}	
	
}

int main(int argc, char **argv){
	
	inicializar_semilla();
	
	
	/*calentamiento de la maquina */
	tabla(aleatorio, ordenar, pow1_2, pow1_5, pow2_2 );
	tabla(aleatorio, ordenar, pow1_2, pow1_5, pow2_2 );
	tabla(aleatorio, ordenar, pow1_2, pow1_5, pow2_2 );
	tabla(aleatorio, ordenar, pow1_2, pow1_5, pow2_2 );
	//
	printf("Test Ordenar \n");
	testAlgoritmos( ordenar);
	printf("Tablas \n");
	printf("Aleatorio \n");
	tabla(aleatorio, ordenar, pow0_8, pow1_2, pow2_2 );
	printf("Ascendente \n");
	tabla(ascendente, ordenar,pow0_5, pow1_2, pow1_2 );	
	printf("Descendente \n");
	tabla(descendente, ordenar, pow1_5, pow2, pow2_2 );
	
	

}
