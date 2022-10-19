#include "RHSoperator.h"

RHSOperator::RHSOperator()
{

}


RHSOperator::~RHSOperator()
{

}


Central1D::Central1D(DataStruct &_U, 
                     DataStruct &_mesh, 
                     FluxFunction &_F):
U(_U), mesh(_mesh), F(_F)
{
  RHS = DataStruct(_U.getSize());
}

Central1D::~Central1D()
{

}

void Central1D::eval()
{
  // the BC should be included in the mesh
  // momentarily done here by hand
  double *dataRHS = RHS.getData();
  const double *dataU = U.getData();
  const double *dataMesh = mesh.getData();
  const int len = U.getSize();

  for(int j = 0; j < len-1; j++)
  {
    double dx;
    if(j == 0)
    {
      dx = dataMesh[len-1] - dataMesh[len-2];
      dx += dataMesh[1] - dataMesh[0];
      dataRHS[0] = (F.computeFlux(dataU[1]) - F.computeFlux(dataU[len-1]))/dx;
    }
    else
    {
      dx = dataMesh[j+1] - dataMesh[j-1];
      dataRHS[j] = (F.computeFlux(dataU[j+1]) - F.computeFlux(dataU[j-1]))/dx;
    }
  }

  dataRHS[len-1] = dataRHS[0];
}