template<class T>
class DataStruct 
{
  private:
    int size;
    int numVars;
    T *data;
    bool initialized;

  public:
    // constructors & destructor
    inline DataStruct()
    {
      size = 0;
      numVars = 0;
      data = NULL;
      initialized = false;
    };

    inline DataStruct(int _size, int _numVars)
    {
      data = new T[_size * _numVars];
      size = _size;
      numVars = _numVars;
      initialized = true;
    };

    inline ~DataStruct() 
    {
      if(initialized) delete[] data;
    };

    // accessors
    inline int getSize() const
    {
      return size;
    }

    inline T* getData() const
    {
      return data;
    }

    inline T getData(int i, int var) const
    {
      return data[var * size + i];
    }

    void setSize(int _size, int _numVars);

    inline DataStruct<T>& operator=(DataStruct<T> const &rhs)
    {
      this->setSize(rhs.getSize(), rhs.getNumVars());
      T *dataRHS = rhs.getData();

      // copy data
      for(int n = 0; n < size * numVars; n++)
      {
        data[n] = dataRHS[n];
      }

      return *this;
    }

    inline int getNumVars() const
    {
      return numVars;
    }
};

template<class T>
void DataStruct<T>::setSize(int _size, int _numVars)
{
  if(initialized)
  {
    if(_size != size || _numVars != numVars)
    {
      delete[] data;
      data = new T[_size * _numVars];
      size = _size;
      numVars = _numVars;
    }
  }else
  {
    data = new T[_size * _numVars];
    size = _size;
    numVars = _numVars;
    initialized = true;
  }
};

