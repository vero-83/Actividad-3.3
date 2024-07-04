#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
#include <mpi.h>

#include "DataStructs.h"
#include "rk4.h"
#include "FluxFunctions.h"
#include "RHSoperator.h"

#ifdef _DOUBLE_
#define FLOATTYPE double
#else
#define FLOATTYPE float
#endif

// declare supporting functions
void write2File(DataStruct<FLOATTYPE> &X, DataStruct<FLOATTYPE> &U, std::string name);
FLOATTYPE calcL2norm(DataStruct<FLOATTYPE> &u, DataStruct<FLOATTYPE> &uinit);

int main(int narg, char **argv)
{
    MPI_Init(&narg, &argv);
    
    int numPoints =  80;
    FLOATTYPE k = 2.; // wave number

    if(narg != 3)
    {
        std::cout << "Wrong number of arguments. You should include:" << std::endl;
        std::cout << "    Num points" << std::endl;
        std::cout << "    Wave number" << std::endl;
        MPI_Finalize();
        return 1;
    }
    else
    {
        numPoints = std::stoi(argv[1]);
        k         = std::stod(argv[2]);
    }

    // solution data
    DataStruct<FLOATTYPE> u(numPoints, 3), f(numPoints, 3), xj(numPoints, 1);

    // flux function
    EulerFlux<FLOATTYPE> lf;

    // time solver
    RungeKutta4<FLOATTYPE> rk(u);

    // Initial Condition
    FLOATTYPE *datax = xj.getData();
    FLOATTYPE *dataU = u.getData();
    for(int j = 0; j < numPoints; j++)
    {
        // xj
        datax[j] = FLOATTYPE(j) / FLOATTYPE(numPoints-1);

        // init Uj
        dataU[j] = sin(k * 2. * M_PI * datax[j]);
    }

    DataStruct<FLOATTYPE> Uinit(numPoints, 3);
    Uinit = u;

    // Operator
    Central1D<FLOATTYPE> rhs(u, xj, lf);

    FLOATTYPE CFL = 2.4;
    FLOATTYPE dt = CFL * datax[1];

    // Output Initial Condition
    write2File(xj, u, "initialCondition.csv");

    FLOATTYPE t_final = 1.;
    FLOATTYPE time = 0.;
    DataStruct<FLOATTYPE> Ui(numPoints, 3); // temp. data

    // init timer
    double compTime = MPI_Wtime();

    // main loop
    while(time < t_final)
    {
        if(time + dt >= t_final) dt = t_final - time;

        // take RK step
        rk.initRK();
        for(int s = 0; s < rk.getNumSteps(); s++)
        {
            rk.stepUi(dt);
            Ui = *rk.currentU();
            rhs.eval(Ui);
            rk.setFi(rhs.ref2RHS());
        }
        rk.finalizeRK(dt);
        time += dt;
    }

    // finishe timer
    compTime = MPI_Wtime() - compTime;

    write2File(xj, u, "final.csv");

    // L2 norm
    FLOATTYPE err = calcL2norm(Uinit, u);
    std::cout << std::setprecision(4) << "Comp. time: " << compTime;
    std::cout << " sec. Error: " << err / k;
    std::cout << " kdx: " << k * datax[1] * 2. * M_PI;
    std::cout << std::endl;

    MPI_Finalize();
    return 0;
}

