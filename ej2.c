#include<stdlib.h>
#include<stdio.h>
#include<math.h>

typedef struct{
    int n;
    double *coeficiente;
}Polinomio;

void imprime_polinomio(Polinomio *Pi){

        printf("Orden del polinomio: %d\n", Pi->n);
        for(int i=0; i<((Pi->n)-1); i++){
        printf("%.2lf * x ^ %d + ", *(Pi->coeficiente+i), i);
        }
        printf("%.2lf * x ^ %d\n", *(Pi->coeficiente+(Pi->n-1)), (Pi->n-1));

}

Polinomio *creaPolinomio(int x){
        Polinomio *Pol=malloc(sizeof(Polinomio));
        Pol->coeficiente=malloc(10*sizeof(double));
        Pol->n=x;
        for(int i=0; i<x; i++){
            *(Pol->coeficiente+i)=x+i;
        }

        return Pol;
}

void setCoef(int a, double c, Polinomio *Psc){
            Psc->n=a;
            for(int i=0; i<a; i++){
                *(Psc->coeficiente+i)=c+i;
            }

}
double getCoef(int n, Polinomio *Pi){
         double last;
         last=*(Pi->coeficiente+(n-1));
         return last;
}
double especializa(double x, Polinomio *Pi){
            int factores=Pi->n;
            double resultado=0;
            double coef[Pi->n];
            for(int i=0; i<factores; i++){
                coef[i]=*(Pi->coeficiente+i);
                resultado+=(pow(x, i)* coef[i]);
            }

            return resultado;
}
Polinomio  *suma(Polinomio *P2, Polinomio *P3){
           Polinomio *Ps=malloc(sizeof(Polinomio));
           Ps->coeficiente=(double*)malloc(10*sizeof(double));
           int a, b;
           a=P2->n;
           b=P3->n;
           if(a>b){
            Ps->n=a;
            for(int i=0; i<b; i++){
                *(Ps->coeficiente+i)=*(P2->coeficiente+i)+*(P3->coeficiente+i);

            }
            for(int i=b; i<a; i++){
                *(Ps->coeficiente+i)=*(P2->coeficiente+i);
            }
           }else{
           Ps->n=b;
            for(int i=0; i<a; i++){
                *(Ps->coeficiente+i)=*(P2->coeficiente+i)+*(P3->coeficiente+i);
            }
            for(int i=a; i<b; i++){
                *(Ps->coeficiente+i)=*(P3->coeficiente+i);
            }
           }
           return Ps;
}
Polinomio *multiplica(Polinomio *P6, Polinomio *P7){
           Polinomio *Pm=malloc(sizeof(Polinomio));
           Pm->coeficiente=(double *)malloc(10*sizeof(double));
           int c, d;
           c=P6->n;
           d=P7->n;
           if(c>d){
            Pm->n=c;
            for(int i=0; i<d; i++){
                *(Pm->coeficiente+i)=*(P6->coeficiente+i)* *(P7->coeficiente+i);
            }
            for(int i=d; i<c; i++){
                *(Pm->coeficiente+i)=*(P6->coeficiente+i);
            }
           }else{
           Pm->n=d;
            for(int i=0; i<c; i++){
                *(Pm->coeficiente+i)=*(P6->coeficiente+i)* *(P7->coeficiente+i);
            }
            for(int i=c; i<d; i++){
                *(Pm->coeficiente+i)=*(P7->coeficiente+i);
            }
           }
           return Pm;
}
Polinomio *deriv(Polinomio *Pd){
          int a=Pd->n;
          for(int i=0; i<a; i++){
            *(Pd->coeficiente+i)=*(Pd->coeficiente+i)*i;
          }
          return Pd;
}
void imprime_derivada(Polinomio *Pi){
        printf("Orden del polinomio: %d\n", Pi->n);
        for(int i=0; i<((Pi->n)-1); i++){
        printf("%.2lf * x ^ %d + ", *(Pi->coeficiente+i), i-1);
        }
        printf("%.2lf * x ^ %d\n", *(Pi->coeficiente+(Pi->n-1)), (Pi->n-2));
}

double ceropol(Polinomio *Pc, double a, double b, double epsilon){
               double raiz=(a+b)/2;
               double resa=especializa(a, Pc);
               double resb=especializa(b, Pc);
               double resc=especializa(raiz, Pc);
               if(raiz>0){
               while(raiz>epsilon){
                    raiz=(a+raiz)/2;
                    resc=especializa(raiz, Pc);
                 }
                 return raiz;
               }
               if(raiz<0){
               while(raiz<(epsilon*-1)){
                    raiz=(b+raiz)/2;
                    resc=especializa(raiz, Pc);
                 }
                 return raiz;
               }
}
int ej2(){
        printf("Ingrese el orden del polinomio:\n");
        int y;
        scanf("%d", &y);
        Polinomio *P1;
        P1=creaPolinomio(y);
        imprime_polinomio(P1);
        setCoef(5, 3, P1);
        imprime_polinomio(P1);
        printf("El ultimo coeficiente del polinomio es: %.2lf\n", getCoef(5, P1));
        printf("Ingrese el punto en el que quiere calcular el polinomio: \n");
        double z;
        scanf("%lf", &z);
        printf("El polinomio en el punto x=%.2lf da: %.2lf\n", z, especializa(z, P1));
        int a, b, c, d;
        Polinomio *P2, *P3, *P4;
        printf("Ingrese el orden del primer polinomio a sumar: \n");
        scanf("%d", &a);
        P2=creaPolinomio(a);
        imprime_polinomio(P2);
        printf("Ingrese el orden del segundo polinomio a sumar: \n");
        scanf("%d", &b);
        P3=creaPolinomio(b);
        imprime_polinomio(P3);
        P4=suma(P2, P3);
        imprime_polinomio(P4);
        printf("ingrese el orden del primer polinomio a multiplicar\n");
        scanf("%d", &c);
        P2=creaPolinomio(c);
        imprime_polinomio(P2);
        printf("Ingrese el orden del segundo polinomio a multiplicar\n");
        scanf("%d", &d);
        P3=creaPolinomio(d);
        imprime_polinomio(P3);
        P4=multiplica(P2, P3);
        imprime_polinomio(P4);
        Polinomio *P5;
        P5=deriv(P4);
        imprime_derivada(P5);
        double e, f, g, h;
        printf("Ingrese el primer valor negativo en donde busca la raiz: \n");
        scanf("%lf", &e);
        printf("Ingrese el segundo valor del intervalo en donde busca la raiz: \n");
        scanf("%lf", &f);
        g=0.000001;
        h=ceropol(P4, e, f, g);
        printf("La raiz del polinomio esta en el punto: %.2lf", h);
        return 0;
}
