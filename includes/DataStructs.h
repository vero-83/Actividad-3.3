#ifndef _DATA_STRUCTS
#define _DATA_STRUCTS

#include <cstddef>

class DataStruct 
{
  private:
    int size;
    double *data;

  public:

    // constructors & destructor
    DataStruct();

    DataStruct(int size);

    ~DataStruct();

    // accessors
    int getSize();
    double* getData();
    double getData(int i);

};

#endif // _DATA_STRUCTS