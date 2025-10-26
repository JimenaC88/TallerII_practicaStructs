#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
typedef struct Lista{
       char *nombre_legislador;
       struct Lista *sgte;
}listas;
typedef struct legisladores{

       char *nombre;
       char voto;

}Legisladores;
listas *crear_legislador(Legisladores *leg){
        listas *primer_legislador=malloc(sizeof(listas));
        primer_legislador->nombre_legislador=malloc(10*sizeof(char));
        primer_legislador->nombre_legislador=leg->nombre;
        primer_legislador->sgte=NULL;
        return primer_legislador;
}
void insertar(Legisladores *leg, listas *lista){
       while(lista->sgte!=NULL){
        lista=lista->sgte;
       }
       lista->sgte=crear_legislador(leg);

}
void suprime(Legisladores *leg, listas **lista){
            if(*lista==NULL){
                return;
            }
            if(*lista!=NULL&&strcmp((*lista)->nombre_legislador, leg->nombre)==0){
                    listas *temp=*lista;
                    *lista=temp->sgte;
                    free(temp);
                    return;

            }
            listas *actual=*lista;
            listas *anterior=NULL;
            if(actual->sgte==NULL&&strcmp(actual->nombre_legislador, leg->nombre)==0){
                free(actual);
                actual=NULL;
                return;
            }
            while(actual!=NULL&&strcmp(actual->nombre_legislador, leg->nombre)!=0){
                anterior=actual;
                actual=actual->sgte;
            }
            if(actual==NULL){
                return;
            }
            anterior->sgte=actual->sgte;
            free(actual);

}

bool miembro(Legisladores *leg){
             char asistencia;
             printf("El legislador %s esta presente? S/N\n", leg->nombre);
             scanf("%c", &asistencia);
             while(asistencia!='S'&&asistencia!='N'){
                printf("Ingrese S o N\n");
                scanf("%c", &asistencia);
             }
             if(asistencia=='S'){
                return true;
             }
             if(asistencia=='N'){
                return false;
             }
}
void votacion(Legisladores *leg){
     char voto;
     if(miembro(leg)==true){
        printf("ingrese el voto del legislador F/C\n");
        scanf("%c", &voto);
        while(voto!='F'&&voto!='C'){
            printf("ingrese F/C\n");
            scanf("%c", &voto);
        }
     }
     leg->voto=voto;
}
void muestra(listas *lista){
     while(lista!=NULL){
        printf(" %s \n", lista->nombre_legislador);
        lista=lista->sgte;
     }
}
int main(){
    listas *lista_buenos=NULL;
    listas *lista_malos=NULL;
    char salir;
    int cont_cb=0;
    int cont_cm=0;
    char entrada;
    while(salir!='E'){
        Legisladores *legislador=malloc(sizeof(Legisladores));
        legislador->nombre=malloc(10*sizeof(char));
        printf("Ingrese el nombre del legislador:\n");
        scanf("%s", legislador->nombre);
        votacion(legislador);
        if(legislador->voto=='F'){
            cont_cm++;
            if(lista_malos==NULL){
                lista_malos=crear_legislador(legislador);
                suprime(legislador, &lista_buenos);
            }else{
            suprime(legislador, &lista_malos);
            insertar(legislador, lista_malos);
            suprime(legislador, &lista_buenos);
            }
        }else if(legislador->voto=='C'){
            cont_cb++;
            if(lista_buenos==NULL){
                lista_buenos=crear_legislador(legislador);
                suprime(legislador, &lista_malos);
            }else{
            suprime(legislador, &lista_buenos);
            insertar(legislador, lista_buenos);
            suprime(legislador, &lista_malos);
            }
        }

        printf("Desea ingresar otro senador S/N: \n");
        scanf("%c", &entrada);
        while(entrada!='S'&&entrada!='N'){
            printf("Ingrese S o N \n");
            scanf("%c", &entrada);
        }
        if(entrada=='N'){
            printf("Los chicos buenos son: \n");
            muestra(lista_buenos);
            printf("\n");
            printf("Los chicos malos son: \n");
            muestra(lista_malos);
        if(cont_cb>cont_cm){
            printf("LOS CHICOS BUENOS HAN GANADO\n");
        }else if(cont_cb<cont_cm){
            printf("LOS CHICOS MALOS HAN GANADO\n");
        }else if(cont_cb==cont_cm){
            printf("LOS CHICOS BUENOS HAN EMPATADO CON LOS MALOS \n");
        }
        cont_cb=0;
        cont_cm=0;
        printf("DESEA REALIZAR OTRA VOTACION? (ingrese E para salir) \n");
        scanf(" %c", &salir);
        }

    }
    return 0;
}
