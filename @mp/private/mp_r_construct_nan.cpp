#include "dependencies.h"

void mexFunction(int nlhs,mxArray *plhs[],int nrhs, const mxArray *prhs[])
{
    if(nrhs != 1) {
        mexErrMsgIdAndTxt("MP:constructMpNaN:nrhs",
                          "One inputs required.");
    }

    if(nlhs != 1) {
        mexErrMsgIdAndTxt("MP:constructMpNaN:nlhs",
                          "One outputs required.");
    }

    if(!mxIsDouble(prhs[0])  ||
       mxGetNumberOfElements(prhs[1]) == 0
      ) {
        mexErrMsgIdAndTxt("MP:constructMpNaN:notDouble",
                          "Input must be of type double.");
    }

    // input
    char input_r[] = "NaN\0";
    double input_prec = mxGetScalar(prhs[0]);

    //output
    mxArray *outputMatrix;
    outputMatrix = mxCreateNumericMatrix(1,1,mxINT64_CLASS,mxREAL);
    long long *ip = (long long *)(mxGetData(outputMatrix));

    // allocate persistent memory
    mpreal temp = mpreal(0, input_prec, MPFR_RNDN);
    mpreal *a = (mpreal *)  mxCalloc(1, sizeof(temp));
    mexMakeMemoryPersistent(a[0]);
    new (a) mpreal(0, input_prec, MPFR_RNDN);

    // load nan to variable
    *a = mpreal(input_r, input_prec, MPFR_RNDN);

    // copy pi adress to the output array
    ip[0] = (long long)(long long *)a;

    plhs[0] = outputMatrix;
}