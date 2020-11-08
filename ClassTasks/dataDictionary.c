#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define LONGITUD_CLAVE 30
#define LONGITUD_SINONIMOS 300
 
typedef struct {
	char clave [LONGITUD_CLAVE];
	char sinonimos [LONGITUD_SINONIMOS];
} item;

typedef struct entrada_ {
	int ocupada;
	char clave [LONGITUD_CLAVE];
	char sinonimos [LONGITUD_SINONIMOS];
} entrada;

typedef int pos;
typedef entrada *tabla_cerrada;


double pow1(int n){
	return n;
}

double pow0_8(int n){
	return pow(n,0.8);
}

double nlogn(int n){
	return n*log(n);
}

void inicializar_cerrada(tabla_cerrada *diccionario, int tam){
		
	for (int i = 0; i < tam; i++){
		(*diccionario)[i].ocupada = 0;
	}
}

pos buscar_cerrada(char *clave, tabla_cerrada diccionario, int tam,
	int *colisiones, int (*dispersion)(char *, int),
	unsigned int (*resol_colision)(int pos_ini, int num_intento)){
	
	int i = 0;
	int x = dispersion(clave, tam);
	(*colisiones) = 0;
	pos actual = x;
	
	while ((diccionario[actual].ocupada) &&
		   (strcmp(diccionario[actual].clave,clave))){
		(*colisiones)++;
		i++;
		actual = (x + (*resol_colision)(x,i)) % tam;
	
		
	}

	return actual;	
}
	
int insertar_cerrada(char *clave, char *sinonimos,
	tabla_cerrada *diccionario, int tam,
	int (*dispersion)(char *, int),
	unsigned int (*resol_colision)(int pos_ini, int num_intento)){	
	
	int colisiones = 0;	
	pos actual = buscar_cerrada(clave, *diccionario,
			tam,&colisiones,(*dispersion),(*resol_colision));
			
	if ((*diccionario)[actual].ocupada == 0){
		
		strcpy((*diccionario)[actual].clave, clave);
		strcpy((*diccionario)[actual].sinonimos, sinonimos);
		(*diccionario)[actual].ocupada = 1;
		
	}
	
	return colisiones;
}

unsigned int colisionLineal(int  pos_inicial, int num_intento){

	
	return  num_intento;
}

unsigned int colisionCuadratica(int pos_inicial, int num_intento){
	
	return num_intento * num_intento;
}

unsigned int  colisionDoble(int pos_inicial, int num_intento){
	
	return  num_intento+1 * (10007 - (pos_inicial % 10007));
}

unsigned int  colisionDobleTest(int pos_inicial, int num_intento){
	
	return num_intento+1 * (7- (pos_inicial % 7));
}
	
void mostrar_cerrada(tabla_cerrada diccionario, int tam){
	
	printf("**** TABLA CERRADA LINEAL\n {\n");
	for( int i= 0; i < tam ; i++){
		printf("%d-  ", i);
		if(diccionario[i].ocupada != 0)
			printf("(%s )", diccionario[i].clave);
		
		printf("\n");
	
	}
	printf("}\n");

}


int dispersionA(char *clave, int tamTabla) {
		
		int i, valor = clave[0], n = MIN(8, strlen(clave));
			for (i = 1; i < n; i++)
				valor += clave[i];
			return valor % tamTabla;
}

int dispersionB(char *clave, int tamTabla) {
	int i, n = MIN(8, strlen(clave));
	unsigned int valor = clave[0];
	for (i = 1; i < n; i++)
		valor = (valor<<5) + clave[i]; 
								/* el desplazamiento de 5 bits equivale a */
	return valor % tamTabla;        /* multipicar por 32 */
}

int ndispersion(char *clave, int tamTabla) {
	if (strcmp(clave, "ANA")==0) return 7;
	if (strcmp(clave, "JOSE")==0) return 7;
	if (strcmp(clave, "OLGA")==0) return 7;
	return 6;
}

char* claveAleatoria(item claves[], int tam){
		
	return claves[rand()%tam].clave;
	
}

int leer_sinonimos(item datos[]) {
	char c;
	int i, j;
	FILE *archivo;
	if ((archivo = fopen("sinonimos.txt", "r")) == NULL) {
		printf("Error al abrir â€™sinonimos.txtâ€™\n");
		return(EXIT_FAILURE);
	}
	for (i = 0; fscanf(archivo, "%s", datos[i].clave) != EOF; i++) {
		if ((c = fgetc(archivo)) != '\t') {
			printf("Error al leer el tabulador\n");
			return(EXIT_FAILURE);
		}
		for (j = 0; (c = fgetc(archivo)) != '\n'; j++) {
			if (j < LONGITUD_SINONIMOS - 1)
				datos[i].sinonimos[j] = c;
		}
		datos[i].sinonimos[MIN(j, LONGITUD_SINONIMOS -1)] = '\0';
	}
	if (fclose(archivo) != 0) {
		printf("Error al cerrar el fichero\n");
		return(EXIT_FAILURE);
	}
	return(i);
}
void test_buscar(char* clave, tabla_cerrada test, int tam,
	unsigned int (*resol_colision)(int pos_ini, int num_intento)){
		
		int  colisiones = 0;	
		pos posicion;
		posicion = buscar_cerrada(clave,test,tam,
			&colisiones,ndispersion,resol_colision);	
			
		if(!strcmp(test[posicion].clave,clave)){
			printf("Al buscar: %s encuentro: %s, colisiones: %d\n", 
			clave, test[posicion].clave, colisiones);
		}else{
			printf("Al buscar: %s no se ha encontrado, coisiones: %d\n",
			clave, colisiones);
		}
}
void test_cerrada( tabla_cerrada * test, int tam,
		unsigned int (*resol_colision)(int pos_ini, int num_intento)){
			int  colisiones_insertar=0;
			inicializar_cerrada(test,11);
			
			colisiones_insertar = insertar_cerrada
			("ANA","",test,tam,ndispersion,resol_colision);
			colisiones_insertar += insertar_cerrada
			("LUIS","",test,tam,ndispersion,resol_colision);
			colisiones_insertar += insertar_cerrada
			("JOSE","",test,tam,ndispersion,resol_colision);
			colisiones_insertar += insertar_cerrada
			("OLGA","",test,tam,ndispersion,resol_colision);
			colisiones_insertar += insertar_cerrada
			("ROSA","",test,tam,ndispersion,resol_colision);
			colisiones_insertar += insertar_cerrada
			("IVAN","",test,tam,ndispersion,resol_colision);

	        mostrar_cerrada(*test,tam);
	        printf("numero de colisiones : %d\n",colisiones_insertar);
	        
	        test_buscar("ANA",*test,tam,resol_colision);
	        test_buscar("LUIS",*test,tam,resol_colision);
			test_buscar("JOSE",*test,tam,resol_colision);
			test_buscar("OLGA",*test,tam,resol_colision);
			test_buscar("ROSA",*test,tam,resol_colision);
			test_buscar("IVAN",*test,tam,resol_colision);
			test_buscar("CARLOS",*test,tam,resol_colision);
}
int insertarSinonimos(item datos[], tabla_cerrada * diccionario,int tam,
	int (*dispersion)(char *, int),
	unsigned int (*resol_colision)(int , int )){
		
	int colisiones = 0;
	for (int i = 0; i< tam-1; i++){
		
		colisiones += insertar_cerrada(datos[i].clave, datos[i].sinonimos, 
					diccionario,tam, dispersion, resol_colision);
	
	}
	return colisiones;
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
//TABLAS
double tiempos(int n, tabla_cerrada   diccionario, item claves[], 
	int tamClav, int tamDicc, int (*dispersion)(char *, int),
	unsigned int (*resol_colision)(int , int )){
	double t1, t2, ta, tb, t;
	int k = 1000;
	int colisiones = 0;
		t1 = microsegundos();
			for(int i= 0; i< n ; i++){
				buscar_cerrada(claveAleatoria(claves, tamClav), diccionario,
								tamDicc,&colisiones,dispersion,resol_colision);
			}
		t2 = microsegundos();
		t = t2-t1;
		if (t < 500){
			t1 = microsegundos();
			for (int j = 0; j <= k; j++){
				for(int i= 0; i< n ; i++){
				buscar_cerrada(claveAleatoria(claves, tamClav), diccionario,
						tamDicc,&colisiones,dispersion,resol_colision);
				}
			}
			t2 = microsegundos(); ta = t2 - t1; t1 = microsegundos();
			for (int j = 0; j <= k; j++){
				for(int i= 0; i<n; i++)
					claveAleatoria(claves, tamClav);
			}
			t2 = microsegundos();
			tb = t2 - t1; t = (ta-tb)/k; printf("%15.4f *",t);
		}else{
			t1 = microsegundos();
			for(int i= 0; i<n; i++)
				claveAleatoria(claves, tamClav);
			t2 = microsegundos();
			t = t - (t2-t1); printf("%15.4f  ",t);	
		}
	return t;
}	
	
void tabla(tabla_cerrada diccionario, item claves[], 
	int tamClav, int tamDicc,int (*dispersion)(char *, int),
	unsigned int (*resol_colision)(int , int ),
	double (* x)(int),double (* y)(int),double (* z)(int)){
	
	double t;
	
	printf("%12s%15s%14s%14s%14s\n", "n", "t(n)", "t/n^0.8","t/n","t/n*log(n)");
	
	for (int n = 125; n <= 16000; n = n*2){
		printf("%12d", n);
		
		t = tiempos(n, diccionario, claves, tamClav, 
		tamDicc, dispersion, resol_colision);
		
		printf(" %11.8f%15.8f%15.8f\n", t /(* x)(n), t /(* y)(n), t /(* z)(n));
	}	
	
}
void mostrarTablas (tabla_cerrada * d, item claves[],
	int (*dispersion)(char *, int)){

	int colisiones = 0;
	
	inicializar_cerrada(d,38197);
	printf("***Dispersion cerrada lineal\n");
	colisiones = insertarSinonimos(claves, d, 19062 , 
					dispersion,colisionLineal);
	printf("Colisiones al insertar 19062 elementos: %d\n", colisiones);
	tabla(*d,claves,19062,38197,dispersion, colisionLineal, pow0_8,pow1,nlogn);
	tabla(*d,claves,19062,38197,dispersion, colisionLineal, pow0_8,pow1,nlogn);
	tabla(*d,claves,19062,38197,dispersion, colisionLineal, pow0_8,pow1,nlogn);
	tabla(*d,claves,19062,38197,dispersion, colisionLineal, pow0_8,pow1,nlogn);
    inicializar_cerrada(d,38197);
	printf("***Dispersion cerrada cuadratica\n");
	colisiones = insertarSinonimos(claves, d, 19062, 
			dispersion,colisionCuadratica);
	printf("Colisiones al insertar 19062 elementos: %d\n", colisiones);
	tabla(*d,claves,19062,38197,dispersion, colisionCuadratica, 
			pow0_8,pow1,nlogn);	
	
	inicializar_cerrada(d,38197);
	printf("***Dispersion cerrada doble\n");
	colisiones = insertarSinonimos(claves, d, 19062 , dispersion,colisionDoble);
	printf("Colisiones al insertar 19062 elementos: %d\n", colisiones);
	tabla(*d,claves,19062,38197,dispersion, colisionDoble, pow0_8,pow1,nlogn);	

} 

int main(){
	tabla_cerrada d;
	tabla_cerrada test = malloc(11 * sizeof(entrada));
	item * claves ;

	
	inicializar_semilla();
	
	test_cerrada(&test,11,colisionLineal);
	test_cerrada(&test,11,colisionCuadratica);
	test_cerrada(&test,11,colisionDobleTest);
	free(test);
	
	claves =  malloc (19062 * sizeof(item));
	d = malloc (38197 * sizeof(entrada));
	leer_sinonimos(claves);
	printf("***Dispersion A\n");
	mostrarTablas(&d,claves,dispersionA);
	printf("***Dispersion B\n");
	mostrarTablas(&d,claves,dispersionB);
	free(claves);
	free(d);
	
	return 0;
}
