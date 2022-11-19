#ifndef _DATA_STRUCTS
#define _DATA_STRUCTS

#include <cstddef>

#ifdef _DOUBLE_
#define FLOATTYPE double
#else
#define FLOATTYPE float
#endif

class DataStruct 
{
  private:
    int size;
    FLOATTYPE *data;
    bool initialized;

  public:

    // constructors & destructor
    DataStruct();

    DataStruct(int size);

    ~DataStruct();

    // accessors
    inline int getSize()
    {
      return size;
    }

    inline FLOATTYPE* getData()
    {
      return data;
    }

    inline FLOATTYPE getData(int i)
    {
      return data[i];
    }

    void setSize(int _size);

    DataStruct& operator=(DataStruct &d);

};

#endif // _DATA_STRUCTS