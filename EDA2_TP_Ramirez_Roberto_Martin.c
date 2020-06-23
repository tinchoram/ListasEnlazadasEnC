//Autor: Ramirez Roberto Martin
//Compilador: mingw32-gcc.exe IDE:Code::Blocks 17.12
//email: tinchoram@gmail.com
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//DEFINICION DE STRUCTs
struct FechaVen {
                    char month[9];
                    unsigned char year;
                };

typedef struct Person{

    char tratamiento[6];
    char first_name[13];
    char second_name[2];
    char last_name[12];
    char phone_number[10];
    char email[44];
    char address[24];
    char city[26];
    char deparment[15];
    char postal_code[6];
    char occupation[81];
    char company[36];
    char credit_card[11];
    char credit_card_number[17];
    char credit_card_cvv[4];
    struct FechaVen date_exp;
    char sex[10];
    char type_blood[4];
    float weight;
    float height;


}PERSONA;

//Defino Struct para Lista enlazada
typedef struct Node{
    struct Person p;
    int id;
    struct Node * next;
}NODO;


//-----------DEFINICION DE FUNCIONESs-------------------


//Funcion para crear un nuevo nodo, recibe una persona retorna un nuevo nodo
NODO * CreateNodo(PERSONA **p, int id, NODO **newNodo){
    //printf("VOY a CREAR \n");
    NODO * newNode;
    newNode = malloc( sizeof(NODO) );
    newNode->next = newNodo;
    newNode->id = id;
    strcpy( newNode->p.tratamiento , (*p)->tratamiento );
    strcpy( newNode->p.first_name , (*p)->first_name );
    strcpy( newNode->p.second_name , (*p)->second_name );
    strcpy( newNode->p.last_name , (*p)->last_name );
    strcpy( newNode->p.phone_number , (*p)->phone_number );
    strcpy( newNode->p.email , (*p)->email );
    strcpy( newNode->p.address , (*p)->address );
    strcpy( newNode->p.city , (*p)->city );
    strcpy( newNode->p.deparment , (*p)->deparment );
    strcpy( newNode->p.postal_code , (*p)->postal_code );
    strcpy( newNode->p.occupation , (*p)->occupation );
    strcpy( newNode->p.company , (*p)->company );
    strcpy( newNode->p.credit_card , (*p)->credit_card );
    strcpy( newNode->p.credit_card_number , (*p)->credit_card_number );
    strcpy( newNode->p.credit_card_cvv , (*p)->credit_card_cvv );
    strcpy( newNode->p.date_exp.month , (*p)->date_exp.month );
    newNode->p.date_exp.year = (*p)->date_exp.year ;
    strcpy( newNode->p.sex , (*p)->sex );
    strcpy( newNode->p.type_blood , (*p)->type_blood );
    newNode->p.weight = (*p)->weight ;
    newNode->p.height = (*p)->height ;

    return newNode;
}


//Funcion para Cargar y ordenar el archivo Datos.bin, se ejecuta al iniciar el programa
NODO * loadData(){
    printf("Cargando DATA... \n");
    //leo el archivo:
    FILE *arch;
    arch=fopen("Datos.bin","rb");
    if (arch==NULL)
        exit(1);

    PERSONA *p = malloc(sizeof(PERSONA));

    //inicializo tamaño de lista y ID
    int listSize = 0;
    int id = 1;
    NODO *start = NULL, * current;
    NODO * newNodo = NULL;

     //Recorro el archivo y cargo un nodo por registro
     while ( fread( p, sizeof( PERSONA ), 1, arch ) ){

        //Si es el primer Registros
        if(!start){
        //printf("Es el primero");
        start = CreateNodo(&p,id,newNodo);
        //incremento lista y ID
        listSize++;
        id++;
        //printf("NODO next: %d", start->next);
        //break;
        }
        else{//Todos los otros registros
            current = start;
            while ( current->next && ( strcmp( current->p.last_name, p->last_name ) < 0 || strcmp(current->p.last_name, p->last_name)==0 && strcmp(current->p.first_name, p->first_name)<=0 ) ) {
                        //printf("Apellido: %s : %s \n", current->p.last_name, p->last_name);
                        current = current->next;

                    }
            newNodo = current->next;
            current->next = CreateNodo(&p,id,newNodo);
            //incremento lista y ID
            listSize++;
            id++;
        }
     }
    fclose(arch);
    printf("Se cargaron: %d",listSize );
    return start;
}


//Funcion para Imprimir la lista de TODAS las personas, recibe el inicio de la lista
void leerData(NODO **start){

    NODO *Actual=*start;
    int salir=0;
    //Recorro toda la lista e imprimo cada registro
    printf("-----------------LISTA COMPLETA---------------------- \n");
    while(Actual){
        printf("\n ID:%d", Actual->id);
        printf("\n Tratamiento:%s", Actual->p.tratamiento);
        printf("\n Nombre:%s", Actual->p.first_name);
        printf("\n Sugundo nombre:%s", Actual->p.second_name);
        printf("\n Apellido:%s", Actual->p.last_name);
        printf("\n Telefono:%s", Actual->p.phone_number);
        printf("\n email:%s", Actual->p.email);
        printf("\n Direccion:%s", Actual->p.address);
        printf("\n Ciudad:%s", Actual->p.city);
        printf("\n Deparmento:%s", Actual->p.deparment);
        printf("\n postal_code:%s", Actual->p.postal_code);
        printf("\n occupation:%s", Actual->p.occupation);
        printf("\n Compania:%s", Actual->p.company);
        printf("\n Tarjeta credito:%s", Actual->p.credit_card);
        printf("\n Card number:%s", Actual->p.credit_card_number);
        printf("\n CVV:%s", Actual->p.credit_card_cvv);
        printf("\n mes exp:%s", Actual->p.date_exp.month);
        printf("\n ano exp:%c", Actual->p.date_exp.year);
        printf("\n Sexo:%s", Actual->p.sex);
        printf("\n Tipo Sangre:%s", Actual->p.type_blood);
        printf("\n Peso:%f", Actual->p.weight);
        printf("\n Altura:%f", Actual->p.height);
        Actual = Actual->next;

        //Esto es para que no imprima todos los datos juntos!!!! o para salir y dejar de listar!
        printf("\n\nPresione una tecla para continuar o letra \"s\" para volver al menu\n");
        salir = getch();
        if(salir == 's'){break;}

    }


}

//Funcion ObtenerID devuelve el ultimo id+1 para crear un nuevo nodo

int ObtenerID(NODO **start){

    NODO * current = *start;
    int id=0;

    while(current){

                if(current->id > id ){
                    id = current->id;

        }

        current = current->next;
    }
    id++;
    return id;

}


//Funcion para crear un nuevo nodo a partir de los datos ingresados
int AddNodo(NODO **start){
    int listSize = 1;
    int id = 0;
    NODO * current = *start;
    NODO * newNodo = NULL;
    PERSONA *p = malloc(sizeof(PERSONA));

    //Solicit el ingreso de datos para el nuevo registro
    printf("--------------------------------------- \n");
    printf("ALTA de Persona \n");

    //printf("ingrese ID mayor a 5000: ");
    //scanf("%d", &id );

    id = ObtenerID(start);
    printf("ID de creacion: %d \n",id);
    printf("-----------------Ingrese datos----------- \n");
    printf("ingrese Tratamiento: ");
    scanf("%s", p->tratamiento );
    //printf("\n Tratamiento:%s", (*p).tratamiento);

    printf("ingrese Nombre: ");
    scanf("%s", p->first_name );

    //printf("ingrese segundo Nombre: ");
    //scanf("%s", p->second_name );

    printf("ingrese Apellido: ");
    scanf("%s", p->last_name );

    printf("ingrese Ciudad: ");
    scanf("%s", p->city );

    printf("ingrese Telefono: ");
    scanf("%s", p->phone_number );

    //Recorro la lista para agregar el nuevo nodo al Final!
    while ( current->next && ( strcmp( current->p.last_name, p->last_name ) < 0 || strcmp(current->p.last_name, p->last_name)==0 && strcmp(current->p.first_name, p->first_name)<=0 ) ) {
                        current = current->next;

                    }
            //llegue al final y agrego el nuevo nodo!
            newNodo = current->next;
            current->next = CreateNodo(&p,id,newNodo);

    //Retorno el nuevo tamaño de la lista
    return listSize;
}

//Funcion para eliminar un nodo
NODO * DeleteNodo(NODO **start){

    NODO * current = *start;
    NODO * back = *start;
    NODO * newstart = *start;
    int id=0;
    int flag = 0;
    //Solicit el ID del registros a Eliminar
    printf("---ELIMINAR Persona por ID \n");
    printf("\ningrese ID de Persona a Eliminar: ");
    scanf("%i", &id );

        //Recorro la lista y comtemplo los 3 casos posibles
        while(current){
        //Busco el ID ingresado
        if(current->id == id){
            //Si es el primer Registro
            if(current==back){
               //printf("Es el primero\n");
               newstart = current->next;
               free(current);
               printf("Nodo ElIMINADO! \n");
               return newstart;
            } //Si es el Ultimo Registro
            else if(current->next==NULL){
                //printf("Es el Ultimo \n");

                //printf("ID current: %d", current->id);
                //printf("ID back: %d", back->id);

                back->next= NULL;
                free(current);
                printf("Nodo ELIMINADO! \n");
                return newstart;
            }
            else{ //Esta en el medio
                //printf("Esta en el medio");
                back->next = current->next;
                free(current);
                printf("Nodo ELIMINADO! \n");
                return newstart;
            }
        }
        //Guardo el anterior pero a partir de la segunda vuelta!
        //Esto lo hago para poder tener registro del nodo anterior
        if(flag==1){
                back = current;
                    }
        current = current->next;
        //Como ya dio la primer vuelta, activo el registro de Back
        flag = 1;
    }
    printf("ID no Encontrado! \n");
    printf("\n\nPresione una tecla para continuar\n");
    getch();

    return newstart;

}

//Modificar Registro
void ModificarData(NODO **start){
    NODO * current = *start;
    int id=0;
    char phone_number[10];
    //Solicito el ingreso del ID y el telefono a modificar
    printf("---Modificar Telefono de persona \n");
    printf("\ningrese ID de Persona a Modificar: ");
    scanf("%d", &id );
    printf("\ningrese Nuevo Telefono: ");
    scanf("%s", &phone_number );

    //Recorro la lista
    while(current){
        //Cuando coincide el ID hago la modificacion
        if(current->id == id){
            printf("--------------------------------------- \n");
            printf("\nSe MODIFICARA el numero de telefono de: \n");
            printf("--------------------------------------- \n");
            printf("ID: %d \n", current->id);
            printf("Nombre: %s \n", current->p.first_name);
            printf("Apellido: %s \n", current->p.last_name);
            printf("Email: %s \n", current->p.email);
            printf("-------------Modificacion------------ \n");
            printf("Telefono borrado: %s \n", current->p.phone_number);
            printf("Telefono Nuevo: %s \n",phone_number );
            printf("--------------------------------------- \n");
            strcpy( current->p.phone_number , phone_number );
        }
        current = current->next;
    }

    printf("\n\nPresione una tecla para continuar\n");
    getch();

}

//Buscar nodo por ID: Agregue eta opcion para tener un mejor manejo de los nodos!
// y realizar busquedas mas especificas
void BurcarId(NODO **start){

    NODO * current = *start;
    int id=0;
    printf("---Buscar Persona por ID \n");
    printf("\ningrese ID de Persona: ");
    scanf("%i", &id );

    while(current){
        if(current->id == id){
            printf("--------------------------------------- \n");
            printf("\nDATOS: \n");
            printf("--------------------------------------- \n");
            printf("ID: %d \n", current->id);
            printf("Nombre: %s \n", current->p.first_name);
            printf("Apellido: %s \n", current->p.last_name);
            printf("Email: %s \n", current->p.email);
            printf("Telefono: %s \n", current->p.phone_number);
            printf("Ciudad: %s \n", current->p.city);
            printf("--------------------------------------- \n");
            break;
        }
        current = current->next;
    }

    printf("\n\nPresione una tecla para continuar\n");
    getch();


}

//Lista registros por filtros
void BurcarData (NODO **start){
    NODO * current = *start;
    int menu = 0;

    printf("1 - Buscar Personas por APELLIDO \n");
    printf("2 - Buscar Personas por CIUDAD \n");
    printf("Ingrese opcion:  ");
    scanf("%i", &menu);

    if(menu == 1){
                    char value_last[12];
                    int total = 1;
                    int salir=0;
                    printf("--------------------------- \n");
                    printf("Buscar Personas por APELLIDO \n");
                    printf("ingrese APELLIDO: ");
                    scanf("%s", &value_last );

                    while(current){

                        //printf("value: %s == Ciudad:%s \n",value_city, current->p.city);

                        if(strcmp(value_last, current->p.last_name )== 0){
                            //printf("IGUALEESSSSSSS \n");
                            //printf("value: %s == Ciudad:%s \n",value_city, current->p.city);
                            printf("-----------------Resultado: %d -----------------\n", total);
                            printf("ID: %d \n", current->id);
                            printf("Nombre: %s \n", current->p.first_name);
                            printf("Apellido: %s \n", current->p.last_name);
                            printf("Email: %s \n", current->p.email);
                            printf("Telefono: %s \n", current->p.phone_number);
                            printf("Ciudad: %s \n", current->p.city);
                            total++;

                            //Descomentar esta 3 lineas para visualizar resultados de a uno!!!
                            //printf("\n\nPresione una tecla para continuar o letra \"s\" para volver al menu\n");
                            //salir = getch();
                            //if(salir == 's'){break;}
                        }
                        current = current->next;

                    }
                    printf("\n\nPresione una tecla para continuar\n");
                    getch();

    }
    else if(menu == 2){

                    char value_city[26];
                    int total = 1;
                    int salir=0;
                    printf("--------------------------- \n");
                    printf("Buscar Personas por CIUDAD \n");
                    printf("ingrese CIUDAD: ");
                    scanf("%s", &value_city );

                    while(current){

                        //printf("value: %s == Ciudad:%s \n",value_city, current->p.city);

                        if(strcmp(value_city, current->p.city )== 0){
                            //printf("IGUALEESSSSSSS \n");
                            //printf("value: %s == Ciudad:%s \n",value_city, current->p.city);
                            printf("-----------------Resultado: %d -----------------\n", total);
                            printf("ID: %d \n", current->id);
                            printf("Nombre: %s \n", current->p.first_name);
                            printf("Apellido: %s \n", current->p.last_name);
                            printf("Email: %s \n", current->p.email);
                            printf("Telefono: %s \n", current->p.phone_number);
                            printf("Ciudad: %s \n", current->p.city);
                            total++;

                            //Descomentar esta 3 lineas para visualizar resultados de a uno!!!
                            //printf("\n\nPresione una tecla para continuar o letra \"s\" para volver al menu\n");
                            //salir = getch();
                            //if(salir == 's'){break;}
                        }
                        current = current->next;

                    }
                    printf("\n\nPresione una tecla para continuar\n");
                    getch();

    }
    else{
        printf("\n\nOpcion incorrecta\n");
    }

}

//Libero memoria al salir
void MemeryFree(NODO **start){
    NODO * current = *start, *freenode;
    printf("Liberando recursos...\n");
    while(current){
        //printf("ID: %d \n", current->id);
        freenode = current;
        current = current->next;
        free(freenode);

    }

    printf("\nGracias vuelva pronto\n");
}


//Funcion muestra el Menu en pantalla
void showMenu(){
        //--------MENU---------------
        printf("\n-----------------MENU---------------------------\n");
        printf("---Seleccione la opcion deseada---\n\n");
        printf(" 1 - Agregar un nuevo registro \n");
        printf(" 2 - Modificar registro \n");
        printf(" 3 - Eliminar un registro \n");
        printf(" 4 - Listado de todos los registros en pantalla\n");
        printf(" 5 - Listar un conjunto de registros seleccionados en pantalla \n");
        printf(" 6 - Buscar por ID \n");
        printf(" 0 - Salir \n\n");
        printf("Ingrese la opcion deseada: ");
}


//MAIN INICIA el PROGRAMA
void main(){
    int menu=0;
    NODO *start = NULL, * current;

    printf("-------------------------------------------------------------\n");
    printf("            EDA II - Trabajo Practico \n");
    printf("-------------------------------------------------------------\n");
    printf("Alumno:     Ramirez Roberto Martin \n");
    printf("-------------------------------------------------------------\n");
    printf("            INICIO \n");
    printf("-------------------------------------------------------------\n");

    //Cargo la Data
    start = loadData();
    int totalnodos = 0;
    //leerData(&start);

        do{
        showMenu();
        scanf("%d",&menu);
        //-------- OPCIONES MENU---------------
        if(menu==1){printf("1 - Agregar un nuevo registro \n"); totalnodos = AddNodo(&start); printf("\n Se agrego %d nodo correctamente \n",totalnodos );}
        if(menu==2){printf("Opcion 2 \n"); ModificarData(&start);}
        if(menu==3){printf("Opcion 3 \n"); start = DeleteNodo(&start);}
        if(menu==4){printf("Opcion 4 \n"); leerData(&start);}
        if(menu==5){printf("Opcion 5 \n"); BurcarData(&start);}
        if(menu==6){printf("Opcion 6 \n"); BurcarId(&start);}
        if(menu==0){MemeryFree(&start);}

        }while(menu!=0);

}
