#ifndef _FLUX_FUNCTIONS
#define _FLUX_FUNCTIONS

#include "DataStructs.h"

// base class for flux functions
template<class T>
class FluxFunction
{
  public:
    FluxFunction();

    // in U; out F
    virtual void computeFlux(DataStruct<T> &U, DataStruct<T> &F) = 0;

    // same as above but at the node level
    virtual T computeFlux(const T &Ui) = 0;
};

template<class T>
class LinearFlux : public FluxFunction<T>
{
  private:
    T c;

  public:
    LinearFlux();

    // in U; out F
    virtual void computeFlux(DataStruct<T> &U, DataStruct<T> &F);

    // same as above but at the node level
    virtual T computeFlux(const T &Ui);
};

template<class T>
class EulerFlux : public FluxFunction<T>
{
  public:
    EulerFlux() {}

    virtual void computeFlux(DataStruct<T> &U, DataStruct<T> &F)
    {
        int numPoints = U.getSize();
        for (int j = 0; j < numPoints; ++j)
        {
            T rho = U(j, 0);
            T rhou = U(j, 1);
            T rhoE = U(j, 2);
            T p = (0.4) * (rhoE - 0.5 * (rhou * rhou) / rho);
            
            F(j, 0) = rhou;
            F(j, 1) = (rhou * rhou) / rho + p;
            F(j, 2) = (rhoE + p) * (rhou / rho);
        }
    }

    virtual T computeFlux(const T &Ui)
    {
        // Not used in this context
        return T();
    }
};

#endif // _FLUX_FUNCTIONS

