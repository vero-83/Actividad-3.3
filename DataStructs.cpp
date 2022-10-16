
#include "DataStructs.h"

DataStruct::DataStruct()
{
  size = 0;
  data = NULL;
};

DataStruct::DataStruct(int size)
{
  data = new double(size);
};

DataStruct::~DataStruct() 
{
  delete data;
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