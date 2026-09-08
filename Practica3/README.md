# Práctica 3 - Analizador Sintáctico LR(1)
## Implementación usando Objetos
### Objetivo
Modificar el analizador sintáctico LR(1) de la práctica anterior para utilizar una pila de objetos en lugar de una pila de enteros.
Con esta modificación, los elementos que forman la pila se pueden representar mediante objetos y mostrar de una forma más parecida al análisis manual.

## Desarrollo
Para realizar esta práctica se modificó la pila utilizada en la práctica anterior.
Primero se creó la clase 'ElementoPila', que funciona como la clase base. Después se crearon las clases:
- Terminal 
- noTerminal
-  Estado
  
Estas tres clases heredan de `ElementoPila`.
También se modificaron las funciones `push`, `pop`, `top` y `muestra` de la clase 'pila' para trabajar con objetos de tipo 'ElementoPila*'.

## Clase ElementoPila
Esta clase sirve como base para los diferentes elementos que pueden almacenarse en la pila.
```
class ElementoPila
{
public:
    virtual void muestra() = 0;
    virtual ~ElementoPila() {}
};
```
El método `muestra()` es virtual para cada clase pueda mostrar su información de acuerdo con el tipo de objeto.

## Clase terminal
La clase `terminal` representa los símbolos terminales utilizados por el analizador.
```
class Terminal : public ElementoPila
{
private:
    string simbolo;

public:
    Terminal(string simbolo)
    {
        this->simbolo = simbolo;
    }

    void muestra()
    {
        cout << simbolo;
    }
};
```
Por ejemplo, los símbolos `id`, `+` y `$` pueden representarse mediante objetos de esta clase.

## Clase NoTerminal
La clase `NoTerminal` representa los símbolos no terminales de la gramática.
```
class NoTerminal : public ElementoPila
{
private:
    string simbolo;

public:
    NoTerminal(string simbolo)
    {
        this->simbolo = simbolo;
    }

    void muestra()
    {
        cout << simbolo;
    }
};
```
En los ejercicios de esta práctica, el no terminal utilizado es `E`.

## Clase Estado
La clase `Estado` representa los estados del analizador LR(1).
```
class Estado : public ElementoPila
{
private:
    int estado;

public:
    Estado(int estado)
    {
        this->estado = estado;
    }

    int getEstado()
    {
        return estado;
    }

    void muestra()
    {
        cout << estado;
    }
};
```
El estado se guarda como un número entero, pero ahora se almacena dentro de un objeto.

## Modificación de la Pila
En la práctica anterior la pila trabajaba con enteros. En esta práctica se modificó para almacenar objetos:

### Push
El método `push` recibe un objeto `ElementoPila*` y lo agrega a la pila.
```
void Pila::push(ElementoPila *x)
{
    lista.push_front(x);
}
```

### Pop
El método `pop` elimina y devuelve el elemento que se encuentra en el tope.
```
ElementoPila* Pila::pop()
{
    ElementoPila* x = *lista.begin();

    lista.erase(lista.begin());

    return x;
}
```

### Top
El método `top` permite consultar el elemento que se encuentra en el tope.
```
ElementoPila* Pila::top()
{
    return *lista.begin();
}
```

### Muestra
La función `muestra` recorre la pila y utiliza el método `muestra()` de cada objeto.
```
void Pila::muestra()
{
    list<ElementoPila*>::reverse_iterator it;

    cout << "Pila: ";

    for (it = lista.rbegin(); it != lista.rend(); it++)
    {
        (*it)->muestra();
    }

    cout << endl;
}
```
De esta forma, la pila puede contener diferentes tipos de objetos al mismo tiempo.

## Ejemplo de uso de la pila
Para comprobar que la pila funciona con objetos se pueden agregar diferentes elementos:
```
Pila pila;

pila.push(new Terminal("id"));
pila.push(new Estado(2));
pila.push(new Terminal("+"));
pila.push(new Estado(3));

pila.muestra();
```
En este caso, la pila contiene objetos de diferentes clases que heredan de `ElementoPila`.

## Modificación del Analizador Sintáctico
Después de comprobar el funcionamiento de la pila, se modificaron los ejercicios del analizador sintáctico LR(1) de la práctica anterior.
Los desplazamientos ahora agregan objetos `Terminal` y `Estado`.
Por ejemplo:
```
pila.push(new Terminal(lexico.simbolo));
pila.push(new Estado(accion));
```
Cuando se realiza una reducción, se eliminan los elementos correspondientes de la pila y se agrega el `NoTerminal` junto con el nuevo estado.
```
pila.push(new NoTerminal("E"));
pila.push(new Estado(accion));
```

## Ejercicio 1
### Gramática
```
E -> id + id
```
Se modificó el analizador para utilizar la pila de objetos en el análisis de la gramática.
La pila ahora muestra los símbolos y estados de una manera similar al análisis manual.

### Proceso
Durante el análisis se realizan desplazamientos y posteriormente una reducción de acuerdo con la tabla LR(1).
La reducción utilizada es:
```
E -> id + id
```
Al finalizar el análisis, la cadena es aceptada.

## Ejercicio 2
### Gramática
```
E -> id + E | id
```
En este ejercicio se mantiene el ciclo del analizador debido a la recursión de la gramática.
Las reducciones utilizan los objetos almacenados en la pila y posteriormente se realiza la transición correspondiente al no terminal `E`.
Las reglas utilizadas son:
```
E -> id + E
E -> id
```
El análisis continúa hasta encontrar una aceptación o una entrada no válida.

## Resultado
La modificación permite que la pila del analizador sintáctico LR(1) trabaje con objetos en lugar de utilizar únicamente enteros.
Los objetos utilizados son:
```
ElementoPila
    |
    +-- Terminal
    |
    +-- NoTerminal
    |
    +-- Estado
```
Los ejercicios del analizador sintáctico fueron adaptados para utilizar esta nueva estructura.

## Estructura del proyecto
```
Practica3/
│
├── README.md
├── elementoPila.h
├── terminal.h
├── noTerminal.h
├── estado.h
├── pila.h
├── pila.cpp
└── principal.cpp
```
## Conclusión
En esta práctica se modificó la implementación del analizador sintáctico LR(1) para utilizar una pila de objetos.
La clase `ElementoPila` permitió crear diferentes tipos de elementos dentro de la pila mediante las clases `Terminal`, `NoTerminal` y `Estado`.
Con esta modificación, la información de la pila se puede mostrar de una forma más clara y cercana al procedimiento realizado manualmente en el análisis LR(1).
