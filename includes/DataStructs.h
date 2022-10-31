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
    int getSize();
    FLOATTYPE* getData();
    FLOATTYPE getData(int i);

    void setSize(int _size);

    DataStruct& operator=(DataStruct &d);

};

#endif // _DATA_STRUCTS