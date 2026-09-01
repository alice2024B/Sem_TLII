#include <stdio.h>
#include <string.h>

#define MAX 100

char simbolosPila[MAX][20];
int estadosPila[MAX];
int tope = -1;

/* Tabla LR del Ejercicio 1 */
int tablaLR1[5][4] =
{
    {2, 0, 0, 1},
    {0, 0, -1, 0},
    {0, 3, 0, 0},
    {4, 0, 0, 0},
    {0, 0, -2, 0}
};

/* Tabla LR del Ejercicio 2 */
int tablaLR2[5][4] =
{
    {2, 0, 0, 1},
    {0, 0, -1, 0},
    {0, 3, -3, 0},
    {2, 0, 0, 4},
    {0, 0, -2, 0}
};

/* Reglas del Ejercicio 2 */
int idReglas[2] = {3, 3};
int lonReglas[2] = {3, 1};


/* Agregar elemento a la pila */
void push(char simbolo[], int estado)
{
    tope++;

    strcpy(simbolosPila[tope], simbolo);
    estadosPila[tope] = estado;
}


/* Sacar elemento de la pila */
void pop()
{
    if (tope >= 0)
        tope--;
}


/* Obtener el estado del tope */
int top()
{
    return estadosPila[tope];
}


/* Mostrar la pila */
void muestraPila()
{
    int i;

    printf("$");

    for (i = 0; i <= tope; i++)
        printf("%s%d", simbolosPila[i], estadosPila[i]);

    printf("\n");
}


/* Obtener el siguiente simbolo */
int siguienteSimbolo(char entrada[], int *pos, char simbolo[])
{
    int i = 0;

    /* Identificador */
    if ((entrada[*pos] >= 'a' && entrada[*pos] <= 'z') ||
        (entrada[*pos] >= 'A' && entrada[*pos] <= 'Z'))
    {
        while ((entrada[*pos] >= 'a' && entrada[*pos] <= 'z') ||
               (entrada[*pos] >= 'A' && entrada[*pos] <= 'Z') ||
               (entrada[*pos] >= '0' && entrada[*pos] <= '9'))
        {
            simbolo[i] = entrada[*pos];
            i++;
            (*pos)++;
        }

        simbolo[i] = '\0';

        return 0;
    }

    /* Signo + */
    if (entrada[*pos] == '+')
    {
        simbolo[0] = '+';
        simbolo[1] = '\0';

        (*pos)++;

        return 1;
    }

    /* Fin de entrada */
    if (entrada[*pos] == '\0')
    {
        simbolo[0] = '$';
        simbolo[1] = '\0';

        return 2;
    }

    /* Simbolo no reconocido */
    simbolo[0] = entrada[*pos];
    simbolo[1] = '\0';

    (*pos)++;

    return -1;
}


/* Ejercicio 1
   E -> id + id
*/
void ejercicio1()
{
    char entrada[MAX];
    char simbolo[20];

    int pos = 0;
    int tipo;
    int fila;
    int columna;
    int accion;
    int aceptacion = 0;

    printf("\n=====================================\n");
    printf("          EJERCICIO 1\n");
    printf("=====================================\n");

    printf("Gramatica: E -> id + id\n");
    printf("Ingrese la entrada: ");

    scanf("%99s", entrada);

    tope = -1;
    push("", 0);

    tipo = siguienteSimbolo(entrada, &pos, simbolo);

    while (!aceptacion)
    {
        if (tipo < 0)
        {
            printf("\nPila: ");
            muestraPila();
            printf("Entrada: %s\n", simbolo);
            printf("Error: entrada no valida\n");
            break;
        }

        fila = top();
        columna = tipo;
        accion = tablaLR1[fila][columna];

        printf("\nPila: ");
        muestraPila();

        printf("Entrada: %s\n", simbolo);

        if (accion > 0)
        {
            printf("Accion: d%d\n", accion);

            push(simbolo, accion);

            tipo = siguienteSimbolo(entrada, &pos, simbolo);
        }
        else if (accion == -2)
        {
            printf("Accion: r1 -> E -> id + id\n");

            pop();
            pop();
            pop();

            fila = top();
            columna = 3;

            accion = tablaLR1[fila][columna];

            push("E", accion);
        }
        else if (accion == -1)
        {
            printf("Accion: r0\n");
            printf("Aceptacion\n");

            aceptacion = 1;
        }
        else
        {
            printf("Error: entrada no valida\n");
            break;
        }
    }
}


/* Ejercicio 2
   E -> id + E | id
*/
void ejercicio2()
{
    char entrada[MAX];
    char simbolo[20];

    int pos = 0;
    int tipo;
    int fila;
    int columna;
    int accion;
    int aceptacion = 0;
    int regla;
    int longitud;

    printf("\n=====================================\n");
    printf("          EJERCICIO 2\n");
    printf("=====================================\n");

    printf("Gramatica: E -> id + E | id\n");
    printf("Ingrese la entrada: ");

    scanf("%99s", entrada);

    tope = -1;
    push("", 0);

    tipo = siguienteSimbolo(entrada, &pos, simbolo);

    while (!aceptacion)
    {
        if (tipo < 0)
        {
            printf("\nPila: ");
            muestraPila();
            printf("Entrada: %s\n", simbolo);
            printf("Error: entrada no valida\n");
            break;
        }

        fila = top();
        columna = tipo;
        accion = tablaLR2[fila][columna];

        printf("\nPila: ");
        muestraPila();

        printf("Entrada: %s\n", simbolo);

        if (accion > 0)
        {
            printf("Accion: d%d\n", accion);

            push(simbolo, accion);

            tipo = siguienteSimbolo(entrada, &pos, simbolo);
        }
        else if (accion < 0)
        {
            if (accion == -1)
            {
                printf("Accion: r0\n");
                printf("Aceptacion\n");

                aceptacion = 1;
            }
            else
            {
                regla = -accion - 2;

                if (regla < 0 || regla >= 2)
                {
                    printf("Error: reduccion no valida\n");
                    break;
                }

                if (regla == 0)
                    printf("Accion: r1 -> E -> id + E\n");
                else
                    printf("Accion: r2 -> E -> id\n");

                longitud = lonReglas[regla];

                while (longitud > 0)
                {
                    pop();
                    longitud--;
                }

                fila = top();
                columna = idReglas[regla];

                accion = tablaLR2[fila][columna];

                push("E", accion);
            }
        }
        else
        {
            printf("Error: entrada no valida\n");
            break;
        }
    }
}


int main()
{
    int opcion;

    printf("=====================================\n");
    printf("      MINI ANALIZADOR SINTACTICO\n");
    printf("               LR(1)\n");
    printf("=====================================\n\n");

    printf("1. Ejercicio 1\n");
    printf("2. Ejercicio 2\n");
    printf("Seleccione una opcion: ");

    scanf("%d", &opcion);

    if (opcion == 1)
        ejercicio1();
    else if (opcion == 2)
        ejercicio2();
    else
        printf("Opcion no valida.\n");

    return 0;
}