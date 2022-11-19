
#include "DataStructs.h"
#include <iostream>

DataStruct::DataStruct()
{
  size = 0;
  data = NULL;
  initialized = false;
};

DataStruct::DataStruct(int _size)
{
  data = new FLOATTYPE[_size];
  size = _size;
  initialized = true;
};

void DataStruct::setSize(int _size)
{
  if(initialized)
  {
    // check if it's the same size
    if(_size != size)
    {
      // this case isn't handled. For the time being
      // simple abort program!
      std::runtime_error("Trying to allocate an already allocated DataStruct. Aborting...");
    }
  }else
  {
    data = new FLOATTYPE[_size];
    size = _size;
    initialized = true;
  }
};

DataStruct::~DataStruct() 
{
  if(initialized) delete[] data;
};

DataStruct& DataStruct::operator=(DataStruct &rhs)
{
  this->setSize(rhs.getSize());
  FLOATTYPE *dataRHS = rhs.getData();

  // copy data
  for(int n = 0; n < size; n++)
  {
    data[n] = dataRHS[n];
  }

  return *this;
}