#include "dependencies.h"

void mexFunction( int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[] )
{
    // variable declaration
    mpreal *xr;
    double *pr;

    long long *xr_in = (long long *)(mxGetData(prhs[0]));
    plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);  
    pr = mxGetPr(plhs[0]);
    xr = (mpreal*)(xr_in[0]);
    *pr = (double)(*xr);
}