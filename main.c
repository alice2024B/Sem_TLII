#include <stdio.h>
#include <ctype.h>

int esIdentificador(char palabra[])
{
    int i;
    if (!isalpha(palabra[0]))
    {
        return 0;
    }

    for (i = 1; palabra[i] != '\0'; i++)
    {
        if (!isalnum(palabra[i]))
        {
            return 0;
        }
    }
    return 1;
} 
int esReal(char palabra[])
{
    int i =0;
    int tieneDigitosDespues =0;

    if (!isdigit(palabra[0]))
    {
        return 0;
    }

    while (isdigit(palabra[i]))
    {
        i++;
    }

    if(palabra[i] != '.')
    {
        return 0;
    }

    i++;

    while(isdigit(palabra[i]))
    {
        tieneDigitosDespues = 1;
        i++;
    }
    if (tieneDigitosDespues && palabra[i] == '\0')
    {
        return 1;
    }
    return 0;
}
int main()
{
    char palabra[100];

    printf("Mini generador lexico\n");
    printf("Ingrese una palabra o numero: ");
    scanf("%s", palabra);

    if (esIdentificador(palabra))
    {
        printf("Es un identificador.\n");
    }
    else if (esReal(palabra))
    {
        printf("Es un numero real.\n");
    }
    else
    {
        printf("No es un identificador ni un numero real.\n");
    }
    return 0;
}