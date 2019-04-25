#include <iostream>

#ifndef ARREGLO_INCLUDED
#define ARREGLO_INCLUDED

template <class T>
class Arreglo
{
    private:
        T * ptr;
        size_t tamanio;
    public:
        Arreglo ();
        Arreglo (size_t );
        Arreglo (Arreglo <T> &);
        size_t Tamanio ();
        T & operator [] (size_t);
        ~Arreglo ();        
};

template <class T>
Arreglo<T>::Arreglo ()
{
    ptr = new T();
    tamanio = 1;
}


template <class T>
Arreglo <T> :: Arreglo (const size_t tamanio_inicial)
{
    ptr = new T [tamanio_inicial];
    tamanio = tamanio_inicial;
}

template <class T>
Arreglo <T> :: Arreglo (Arreglo <T> & c)
{
    ptr = new T [c.Tamanio()];
    tamanio = c.Tamanio();

    for (size_t i = 0; i<tamanio; i++)
    {
        ptr [i] = c.Valor (i);
    }
}

template <class T>
size_t Arreglo <T> :: Tamanio ()
{
    return tamanio;
}

template <class T>
T & Arreglo <T> :: operator [] (size_t indice) 
{
    return ptr [indice];
}

template <class T>
Arreglo <T> :: ~Arreglo ()
{
    if (ptr)
        delete [] ptr;
}

#endif