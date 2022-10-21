
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
  data = new double[_size];
  size = _size;
  initialized = true;
};

void DataStruct::setSize(int _size)
{
  if(initialized)
  {
    // this case isn't handled. For the time being
    // simple abort program!
    std::cout<<"Trying to allocate an already allocated DataStruct. Aborting..."<<std::endl;
    exit(0);
  }else
  {
    data = new double[_size];
    size = _size;
    initialized = true;
  }
};

DataStruct::~DataStruct() 
{
  if(initialized) delete[] data;
};

int DataStruct::getSize()
{
  return size;
};

double* DataStruct::getData()
{
  return data;
};

double DataStruct::getData(int i)
{
  return data[i];
};


DataStruct& DataStruct::operator=(DataStruct rhs)
{
  size = rhs.getSize();
  data = rhs.getData();
  initialized = true;
  return *this;
}