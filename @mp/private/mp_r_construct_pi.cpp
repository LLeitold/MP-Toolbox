#include "dependencies.h"

void mexFunction(int nlhs,mxArray *plhs[],int nrhs, const mxArray *prhs[]){

    if(nrhs != 1) {
        mexErrMsgIdAndTxt("MP:constructMpPi:nrhs",
                          "One inputs required.");
    }

    if(nlhs != 1) {
        mexErrMsgIdAndTxt("MP:constructMpPi:nlhs",
                          "One outputs required.");
    }

    if( !mxIsDouble(prhs[0]) ||
       mxIsComplex(prhs[0]) ||
       mxGetNumberOfElements(prhs[0]) == 0
      ) {
        mexErrMsgIdAndTxt("MP:constructMpFromDouble:notRealDouble",
                          "Input value must be real and of type double.");
    }

    // input
    double input_prec = mxGetScalar(prhs[0]);

    //output
    mxArray *outputMatrix;
    outputMatrix = mxCreateNumericMatrix(1,1,mxINT64_CLASS,mxREAL);
    long long *ip = (long long *)(mxGetData(outputMatrix));

    // allocate persistent memory
    mpreal temp = mpreal(0, input_prec, MPFR_RNDN);
    mpreal *pi = (mpreal *)  mxCalloc(1, sizeof(temp));
    mexMakeMemoryPersistent(pi[0]);
    new (pi) mpreal(0, input_prec, MPFR_RNDN);

    // load pi to variable
    *pi = const_pi(input_prec, MPFR_RNDN);

    // copy pi adress to the output array
    ip[0] = (long long)(long long *)pi;

    plhs[0] = outputMatrix;
}