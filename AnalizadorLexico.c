#include <stdio.h>
#include <string.h>
#include <ctype.h>

int esLetra(char c)
{
    return isalpha((unsigned char)c);
}

int esDigito(char c)
{
    return isdigit((unsigned char)c);
}

void mostrarToken(int tipo, char lexema[])
{
    switch (tipo)
    {
        case 0:
            printf("%-15s Tipo: %d - Identificador\n", lexema, tipo);
            break;

        case 1:
            printf("%-15s Tipo: %d - Entero\n", lexema, tipo);
            break;

        case 2:
            printf("%-15s Tipo: %d - Real\n", lexema, tipo);
            break;

        case 3:
            printf("%-15s Tipo: %d - Cadena\n", lexema, tipo);
            break;

        case 4:
            printf("%-15s Tipo: %d - Tipo\n", lexema, tipo);
            break;

        case 5:
            printf("%-15s Tipo: %d - OpSuma\n", lexema, tipo);
            break;

        case 6:
            printf("%-15s Tipo: %d - OpMul\n", lexema, tipo);
            break;

        case 7:
            printf("%-15s Tipo: %d - OpRelac\n", lexema, tipo);
            break;

        case 8:
            printf("%-15s Tipo: %d - OpOr\n", lexema, tipo);
            break;

        case 9:
            printf("%-15s Tipo: %d - OpAnd\n", lexema, tipo);
            break;

        case 10:
            printf("%-15s Tipo: %d - OpNot\n", lexema, tipo);
            break;

        case 11:
            printf("%-15s Tipo: %d - OpIgualdad\n", lexema, tipo);
            break;

        case 12:
            printf("%-15s Tipo: %d - Punto y coma\n", lexema, tipo);
            break;

        case 13:
            printf("%-15s Tipo: %d - Coma\n", lexema, tipo);
            break;

        case 14:
            printf("%-15s Tipo: %d - Parentesis izquierdo\n", lexema, tipo);
            break;

        case 15:
            printf("%-15s Tipo: %d - Parentesis derecho\n", lexema, tipo);
            break;

        case 16:
            printf("%-15s Tipo: %d - Llave izquierda\n", lexema, tipo);
            break;

        case 17:
            printf("%-15s Tipo: %d - Llave derecha\n", lexema, tipo);
            break;

        case 18:
            printf("%-15s Tipo: %d - Asignacion\n", lexema, tipo);
            break;

        case 19:
            printf("%-15s Tipo: %d - if\n", lexema, tipo);
            break;

        case 20:
            printf("%-15s Tipo: %d - while\n", lexema, tipo);
            break;

        case 21:
            printf("%-15s Tipo: %d - return\n", lexema, tipo);
            break;

        case 22:
            printf("%-15s Tipo: %d - else\n", lexema, tipo);
            break;

        case 23:
            printf("%-15s Tipo: %d - Fin de entrada\n", lexema, tipo);
            break;
    }
}

int palabraReservada(char palabra[])
{
    if (strcmp(palabra, "if") == 0)
        return 19;

    if (strcmp(palabra, "while") == 0)
        return 20;

    if (strcmp(palabra, "return") == 0)
        return 21;

    if (strcmp(palabra, "else") == 0)
        return 22;

    if (strcmp(palabra, "int") == 0)
        return 4;

    if (strcmp(palabra, "float") == 0)
        return 4;

    if (strcmp(palabra, "void") == 0)
        return 4;

    return 0;
}

void analizar(char fuente[])
{
    int i = 0;
    int j;
    char lexema[100];

    while (fuente[i] != '\0')
    {
        
        if (isspace((unsigned char)fuente[i]))
        {
            i++;
            continue;
        }

        if (fuente[i] == '/' && fuente[i + 1] == '/')
        {
            i += 2;

            while (fuente[i] != '\0' && fuente[i] != '\n')
            {
                i++;
            }

            continue;
        }

        if (fuente[i] == '/' && fuente[i + 1] == '*')
        {
            i += 2;

            while (fuente[i] != '\0' &&
                   !(fuente[i] == '*' && fuente[i + 1] == '/'))
            {
                i++;
            }

            if (fuente[i] != '\0')
            {
                i += 2;
            }

            continue;
        }

        /* Identificadores y palabras reservadas */
        if (esLetra(fuente[i]))
        {
            j = 0;

            while (esLetra(fuente[i]) || esDigito(fuente[i]))
            {
                lexema[j] = fuente[i];
                j++;
                i++;
            }

            lexema[j] = '\0';

            int tipo = palabraReservada(lexema);

            if (tipo != 0)
            {
                mostrarToken(tipo, lexema);
            }
            else
            {
                mostrarToken(0, lexema);
            }

            continue;
        }

        /* Enteros y reales */
        if (esDigito(fuente[i]))
        {
            j = 0;

            while (esDigito(fuente[i]))
            {
                lexema[j] = fuente[i];
                j++;
                i++;
            }

            if (fuente[i] == '.' && esDigito(fuente[i + 1]))
            {
                lexema[j] = fuente[i];
                j++;
                i++;

                while (esDigito(fuente[i]))
                {
                    lexema[j] = fuente[i];
                    j++;
                    i++;
                }

                lexema[j] = '\0';

                mostrarToken(2, lexema);
            }
            else
            {
                lexema[j] = '\0';

                mostrarToken(1, lexema);
            }

            continue;
        }

        /* Cadenas */
        if (fuente[i] == '"')
        {
            j = 0;
            lexema[j] = fuente[i];
            j++;
            i++;

            while (fuente[i] != '\0' && fuente[i] != '"')
            {
                lexema[j] = fuente[i];
                j++;
                i++;
            }

            if (fuente[i] == '"')
            {
                lexema[j] = fuente[i];
                j++;
                i++;

                lexema[j] = '\0';

                mostrarToken(3, lexema);
            }
            else
            {
                printf("Error: cadena sin cerrar\n");
            }

            continue;
        }

        /* Operadores de suma */
        if (fuente[i] == '+' || fuente[i] == '-')
        {
            lexema[0] = fuente[i];
            lexema[1] = '\0';

            mostrarToken(5, lexema);
            i++;
            continue;
        }

        /* Operadores de multiplicacion */
        if (fuente[i] == '*' || fuente[i] == '/')
        {
            lexema[0] = fuente[i];
            lexema[1] = '\0';

            mostrarToken(6, lexema);
            i++;
            continue;
        }

        /* Operadores relacionales */
        if (fuente[i] == '<' || fuente[i] == '>')
        {
            j = 0;
            lexema[j] = fuente[i];
            j++;
            i++;

            if (fuente[i] == '=')
            {
                lexema[j] = fuente[i];
                j++;
                i++;
            }

            lexema[j] = '\0';

            mostrarToken(7, lexema);
            continue;
        }

        /* Operadores de igualdad */
        if (fuente[i] == '=')
        {
            if (fuente[i + 1] == '=')
            {
                lexema[0] = '=';
                lexema[1] = '=';
                lexema[2] = '\0';

                mostrarToken(11, lexema);
                i += 2;
            }
            else
            {
                lexema[0] = '=';
                lexema[1] = '\0';

                mostrarToken(18, lexema);
                i++;
            }

            continue;
        }

        if (fuente[i] == '!')
        {
            if (fuente[i + 1] == '=')
            {
                lexema[0] = '!';
                lexema[1] = '=';
                lexema[2] = '\0';

                mostrarToken(11, lexema);
                i += 2;
            }
            else
            {
                lexema[0] = '!';
                lexema[1] = '\0';

                mostrarToken(10, lexema);
                i++;
            }

            continue;
        }

        if (fuente[i] == '&' && fuente[i + 1] == '&')
        {
            lexema[0] = '&';
            lexema[1] = '&';
            lexema[2] = '\0';

            mostrarToken(9, lexema);
            i += 2;
            continue;
        }

        if (fuente[i] == '|' && fuente[i + 1] == '|')
        {
            lexema[0] = '|';
            lexema[1] = '|';
            lexema[2] = '\0';

            mostrarToken(8, lexema);
            i += 2;
            continue;
        }

        if (fuente[i] == ';')
        {
            lexema[0] = ';';
            lexema[1] = '\0';

            mostrarToken(12, lexema);
            i++;
            continue;
        }

        if (fuente[i] == ',')
        {
            lexema[0] = ',';
            lexema[1] = '\0';

            mostrarToken(13, lexema);
            i++;
            continue;
        }

        if (fuente[i] == '(')
        {
            lexema[0] = '(';
            lexema[1] = '\0';

            mostrarToken(14, lexema);
            i++;
            continue;
        }

        if (fuente[i] == ')')
        {
            lexema[0] = ')';
            lexema[1] = '\0';

            mostrarToken(15, lexema);
            i++;
            continue;
        }

        if (fuente[i] == '{')
        {
            lexema[0] = '{';
            lexema[1] = '\0';

            mostrarToken(16, lexema);
            i++;
            continue;
        }
        
        if (fuente[i] == '}')
        {
            lexema[0] = '}';
            lexema[1] = '\0';

            mostrarToken(17, lexema);
            i++;
            continue;
        }
        if (fuente[i]== '$')
        {
            lexema[0]='$';
            lexema[1]='\0';

            mostrarToken(23, lexema);
            return;
        }

        /* Caracter no reconocido */
        printf("%-15c Error: caracter no reconocido\n", fuente[i]);
        i++;
    }
    
}

int main()
{
    char fuente[5000];
    char linea[500];
    int encontradoFin = 0;

    fuente[0] = '\0';

    printf("ANALIZADOR LEXICO\n");
    printf("Ingrese el programa fuente:\n");
    printf("Termine la entrada escribiendo $:\n\n");

    while(!encontradoFin && fgets(linea, sizeof(linea), stdin) !=NULL)
    {
        strcat(fuente, linea);

        if (strchr(linea, '$') !=NULL)
        {
            encontradoFin = 1;
        }
    }

    analizar(fuente);

    return 0;
}