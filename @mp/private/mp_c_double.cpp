#include "dependencies.h"

void mexFunction( int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[] )
{
    // variable declaration
    mpcomplex *x, x_var;
    double *pr, *pi;

    long long *xr_in = (long long *)(mxGetData(prhs[0]));
    plhs[0] = mxCreateDoubleMatrix(1, 1, mxCOMPLEX);
    pr = mxGetPr(plhs[0]);
    pi = mxGetPi(plhs[0]);

    // convert mpcomplex to double complex
    x = (mpcomplex*)(xr_in[0]);
    pr[0] = (double)x->real();
    pi[0] = (double)x->imag();
}