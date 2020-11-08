#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>

#define TAM 128000

typedef struct {
	int vector[TAM];
	int ultimo;
} monticulo;

double nlogn(int n){
	return n*log(n);
}

void aleatorio(int v[], int n){ 

	int i, m = 2*n+1;
	for (i = 0; i < n; i++)
		v[i] = (rand() % m) - n;
}

void ascendente(int v[], int n){
	int i;
	
	for(i = 0; i < n; i++)
		v[i] = i;
	
}
void descendente(int v[],int n){
	
	int i;
	
	for(i = 0; i < n; i++)
		v[i] = n - i;
}

void ini_monticulo(monticulo * mont){
	mont->ultimo = 0;
	}
	
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
int monticulo_vacio (monticulo* mont){
	
	return mont->ultimo == 0;
	
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

void inicializar_semilla() {
	srand(time(NULL));
}

double microsegundos(){
	struct timeval t;
	
	if (gettimeofday(&t,NULL) < 0)
		return 0.0;
		
	return (t.tv_usec + t.tv_sec * 1000000.0);
}

void ord_monticulo(int  a[TAM], int x){
	monticulo mont;
	
	ini_monticulo(&mont);
	crear_monticulo(a,x,&mont);
	
	
	for (int i=x-1; i>=0 ; i--){
		a[i] = eliminar_mayor(&mont);
	
	}		
} 
//Tablas ordenacion
double tiempo(int n, void (* tipoVector)(int[], int)){
	
	double t1, t2, ta, tb, t;
	int k = 1000;
	int vector[n];
	
		(* tipoVector)(vector, n);
		t1 = microsegundos();
		ord_monticulo(vector,n);
		t2 = microsegundos();
		t = t2-t1;
		
		if (t < 500){
			t1 = microsegundos();
			for (int j = 0; j <= k; j++){
				(* tipoVector)(vector, n);
				ord_monticulo(vector,n);
			}
			t2 = microsegundos();
			ta = t2 - t1;
			
			t1 = microsegundos();
			for (int j = 0; j <= k; j++){
				(* tipoVector)(vector, n);
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
	
void tabla(void (* tipoVector)(int[], int)){
	double t, x, y, z;
	
	printf("%12s%15s%14s%14s%14s\n", "n", "t(n)", "t/c1","t/c2","t/c3");
	
	for (int n = 500; n <= 32000; n = n*2){
		printf("%12d", n);
		
		t = tiempo(n,(* tipoVector));
		
		x = t / n;
		z = t / pow(n,1.3);
		y = t / nlogn(n);
		printf(" %11.6f%15.6f%15.6f\n", x, y, z);
	}	
	
}
//Tablas crearMont
double tiempoCrearMont(int n){
	
	double t1, t2, ta, tb, t;
	int k = 1000;
	int vector[n];
	monticulo mont;
		ascendente(vector, n);
		ini_monticulo(&mont);
		
		t1 = microsegundos();
		crear_monticulo(vector, n, &mont);
		t2 = microsegundos();
		t = t2-t1;
		
		if (t < 500){
			t1 = microsegundos();
			for (int j = 0; j <= k; j++){
				ini_monticulo(&mont);
				crear_monticulo(vector, n, &mont);
			}
			t2 = microsegundos();
			ta = t2 - t1;
			
			t1 = microsegundos();
			for (int j = 0; j <= k; j++){
				ini_monticulo(&mont);
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
	
void tablaCrearMont(){
	double t, x, y, z;
	
	printf("%12s%15s%14s%14s%14s\n", "n", "t(n)", "t/c1","t/c2","t/c3");
	
	for (int n = 500; n <= 32000; n = n*2){
		printf("%12d", n);
		
		t = tiempoCrearMont(n);
		
		x = t / pow(n,0.8);
		y = t / n;
		z = t / pow(n,1.2);
		printf(" %11.6f%15.6f%15.6f\n", x, y, z);
	}	
	
}
void testMont(){
	monticulo mont;
	int v[TAM];
	int x = 10;
	
	inicializar_semilla();	descendente(v,x);
	printf("Vector: ");
	for (int i = 0; i<x; i++)
		printf("%d ", v[i]);
	printf("\n");
	ini_monticulo(&mont); crear_monticulo(v,x,&mont);
	printf("Monticulo: ");
	for (int i =0; i< mont.ultimo ;i++)
		printf("%d ",mont.vector[i]);
	printf("\n\n");  eliminar_mayor(&mont);
	printf("Monticulo sin el mayor: ");
		
	for (int i =0; i< mont.ultimo ;i++){
		printf("%d ",mont.vector[i]);
		}
	printf("\n\n");
	printf("Vector desordenado: ");
	for (int i = 0; i<x; i++)
		printf("%d ", v[i]);
	printf("\n"); ord_monticulo(v,x);
	printf("Vector ordenado: ");
	for (int i = 0; i<x; i++)
		printf("%d ", v[i]);
	printf("\n\n");
}

	
int main(){
	inicializar_semilla();
	
	testMont();
	
	printf("calentamos..\n");
	tabla(ascendente);tabla(ascendente);tabla(ascendente);
	
	printf("Tabla de tiempos de crear monticulo\n");
	tablaCrearMont();
	
	printf("Tabla de tiempos de ordenar vector ascendente\n");
	tabla(ascendente);
	
	printf("Tabla de tiempos de ordenar vector descendente\n");
	tabla(descendente);
	
	printf("Tabla de tiempos de ordenar vector aleatorio\n");
	tabla(aleatorio);
	}
	
