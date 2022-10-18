#ifndef _RHS_OPERATOR
#define _RHS_OPERATOR

#include "DataStructs.h"
#include "FluxFunctions.h"

class Operator
{
public:
  Operator();
  ~Operator();

  virtual void eval() = 0;
};

class Central1D : public Operator
{
private:

  // structure containing the RHS values
  DataStruct RHS;
  
  // reference to current solution
  DataStruct &U;

  // reference to mesh 
  // TODO: change to a mesh structure
  DataStruct &mesh;

  // reference to flux function
  FluxFunction &F;

public:
  Central1D(DataStruct &_U, DataStruct &_mesh, FluxFunction &_F);
  ~Central1D();

  virtual void eval();
};

#endif // _RHS_OPERATOR