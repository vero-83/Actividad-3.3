#ifndef _RUNGE_KUTTA
#define _RUNGE_KUTTA

class RungeKutta4 
{
  private:

    // reference to solution (Un)
    double *Un;

  public:

    // default constructor
    RungeKutta4();

    // default destructor
    ~RungeKutta4();
};

#endif // _RUNGE_KUTTA 