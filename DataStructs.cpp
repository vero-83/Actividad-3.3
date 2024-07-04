#include "DataStructs.h"
#include <stdexcept>

template<class T>
void DataStruct<T>::setSize(int _size)
{
    if (initialized)
    {
        // check if it's the same size
        if (_size != size)
        {
            // this case isn't handled. For the time being
            // simple abort program!
            throw std::runtime_error("Trying to allocate an already allocated DataStruct. Aborting...");
        }
    }
    else
    {
        data = new T[_size * components];
        size = _size;
        initialized = true;
    }
}

// Necesario para que el compilador genere las instancias apropiadas
template class DataStruct<float>;
template class DataStruct<double>;


