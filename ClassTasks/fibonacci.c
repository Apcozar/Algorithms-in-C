#include <stdio.h>
#include <math.h>
#include <sys/time.h>


int fib1(int n){
	if (n < 2){
		
		return n;
		
	} else {
		return fib1(n-1) + fib1(n-2);	
	}
}

int fib2(int n){
	
	int i = 1;
	int j = 0;
		
	for (int k = 1; k <= n; k++){
		j = i+ j;
		i = j- i;
	} 
	
	return j;
}

int fib3(int n){
	
	int i = 1;
	int j = 0;
	int k = 0;
	int h = 1;
	int t = 0;
	
	while (n > 0){
		if ( (n%2) != 0){
			t = j*h;
			j = (i*h) +(k*j) + t;
			i = (i*k) + t;
		}
		t = h*h;
		h = (2*k*h)+t; 
		k = (k*k) +t;
		n = n / 2;
	}
	return j;

}

void test(){
	
	printf(" n\tfib1(n)\tfib2(n)\tfib3(n)\n");
	printf("---------------------------------- \n");
	for (int i=0; i < 16; i++){
		
		printf("%2u\t %5u\t %5u\t %5u\n", i, fib1(i), fib2(i), fib3(i));
	}
	
}

/*Obtener la hora en microsegundos*/
double microsegundos(){
	struct timeval t;
	
	if (gettimeofday(&t,NULL) < 0)
		return 0.0;
		
	return (t.tv_usec + t.tv_sec * 1000000.0);
	}
	



// TIEMPOS FIB1

void tiempos1(){
	double t1, t2, t, x, y, z;
	int k = 100000;
	printf("\t\t\t\t\tfib1 \n");
	printf("\n");
	printf("%12s%15s%14s%14s%14s\n", "n", "t(n)", "t/c1","t/c2","t/c3");
	printf("\n");
	for (int n = 2; n <= 32; n = n*2){
		t1 = microsegundos();
		fib1(n);
		t2 = microsegundos();
		t = t2-t1;
		
		if (t < 500){
			t1 = microsegundos();
		
			for (int j = 0; j <= k; j++)
				fib1(n);
			t2 = microsegundos();
			
			t = (t2-t1)/k;
			x = t / pow(1.1, n); y = t / pow((1+sqrt(5))/2, n); 
			z = t / pow(2, n);
			printf("%12d%15.4f * %11.6f%15.6f%15.8f\n", n, t, x, y, z);	
		}else{
			
			x = t / pow(1.1, n); y = t / pow((1+sqrt(5))/2, n); 
			z = t / pow(2, n);
			printf("%12d%15.4f%14.6f%15.6f%15.8f\n", n, t, x, y, z);
		}	
	}	
	printf("\n");
	printf("c1 = 1,1^n \n");
	printf("c2 = ((1+sqrt(5))/2)^n \n");
	printf("c3 = 2^n \n");
	printf("* Media de ejecutar %d veces el algoritmo \n", k);
}

// TIEMPOS FIB2

void tiempos2(){
	double t1, t2, t, x, y, z;
	int k = 1000;
	
	printf("\t\t\t\t\tfib2 \n");
	printf("\n");
	printf("%12s%15s%14s%14s%14s\n", "n", "t(n)", "t/c1","t/c2","t/c3");
	printf("\n");
	
	for (int n = 1000; n <= 100000000; n = n*10){
		t1 = microsegundos();
		fib2(n);
		t2 = microsegundos();
		t = t2-t1;
		
		if (t < 500){
			t1 = microsegundos();
		
			for (int j = 0; j <= k; j++)
				fib2(n);
			t2 = microsegundos();
			
			t = (t2-t1)/k;
			x = t / pow(n,0.8); y = t / n; z = t / n*log(n);
			printf("%12d%15.4f * %11.6f%15.6f%15.8f\n", n, t, x, y, z);	
		}else{
			x = t / pow(n,0.8); y = t / n; z = t / n*log(n);
			printf("%12d%15.4f%14.6f%15.6f%15.8f\n", n, t, x, y, z);
		}	
	}
	printf("\n");
	printf("c1 = n^0,8 \n");
	printf("c2 = n \n");
	printf("c3 = n*log(n)\n");
	printf("* Media de ejecutar %d veces el algoritmo \n", k);
}

// TIEMPOS FIB3

void tiempos3(){
	double t1, t2, t, x, y, z;
	int k = 1000;

	printf("\t\t\t\t\tfib3 \n");
	printf("\n");
	printf("%12s%15s%14s%14s%14s\n", "n", "t(n)", "t/c1","t/c2","t/c3");
	printf("\n");
	
	for (int n = 1000; n <= 100000000; n = n*10){
		t1 = microsegundos();
		fib3(n);
		t2 = microsegundos();
		t = t2-t1;
		
		if (t < 500){
			t1 = microsegundos();
			for (int j = 0; j <= k; j++)
				fib3(n);
			t2 = microsegundos();
	
			t = (t2-t1)/k;
			x = t / sqrt(log(n)); y = t / log(n); z = t / pow(n,0.5);
			printf("%12d%15.4f * %11.6f%15.6f%15.8f\n", n, t, x, y, z);	
		}else{
			
			x = t / sqrt(log(n)); y = t / log(n); z = t / pow(n,0.5);
			printf("%12d%15.4f%14.6f%15.6f%15.8f\n", n, t, x, y, z);
		}	
	}
	printf("\n");
	printf("c1 = sqrt(log(n)) \n");
	printf("c2 = log(n) \n");
	printf("c3 = n^0,5 \n");
	printf("* Media de ejecutar %d veces el algoritmo \n", k);
 }
 
int main(){

	test();
	printf("\n");
	tiempos1();
	printf("\n");
	tiempos2();
	printf("\n");
	tiempos3();
	
}