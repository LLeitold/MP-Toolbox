#include "dependencies.h"

void mexFunction(int nlhs,mxArray *plhs[],int nrhs, const mxArray *prhs[])
{
    if(nrhs != 2) {
        mexErrMsgIdAndTxt("MP:constructMpInf:nrhs",
                          "Two inputs required.");
    }

    if(nlhs != 1) {
        mexErrMsgIdAndTxt("MP:constructMpInf:nlhs",
                          "One outputs required.");
    }

    if(!mxIsClass(prhs[0], "char")  ||
       mxGetNumberOfElements(prhs[0]) == 0
      ) {
        mexErrMsgIdAndTxt("MP:constructMpInf:notChar",
                          "Input must be of type char.");
    }

    if(!mxIsDouble(prhs[1])  ||
       mxGetNumberOfElements(prhs[1]) == 0
      ) {
        mexErrMsgIdAndTxt("MP:constructMpInf:notDouble",
                          "Input must be of type double.");
    }

    // input
    char *sign = mxArrayToString(prhs[0]);
    double input_prec = mxGetScalar(prhs[1]);

    //output
    mxArray *outputMatrix;
    outputMatrix = mxCreateNumericMatrix(1,1,mxINT64_CLASS,mxREAL);
    long long *ip = (long long *)(mxGetData(outputMatrix));

    // allocate persistent memory
    mpreal temp = mpreal(0, input_prec, MPFR_RNDN);
    mpreal *a = (mpreal *)  mxCalloc(1, sizeof(temp));
    mexMakeMemoryPersistent(a[0]);
    new (a) mpreal(0, input_prec, MPFR_RNDN);

    // load inf to variable
    if (strcmp(sign, "+") == 0) {
        *a = const_infinity(1, input_prec, MPFR_RNDN);
    }
    else {
        *a = const_infinity(-1, input_prec, MPFR_RNDN);
    }

    // copy pi adress to the output array
    ip[0] = (long long)(long long *)a;

    plhs[0] = outputMatrix;
}