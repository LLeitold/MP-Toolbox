#include "dependencies.h"

void mexFunction(int nlhs,mxArray *plhs[],int nrhs, const mxArray *prhs[])
{
    if(nrhs != 2) {
        mexErrMsgIdAndTxt("MP:constructMpFromChar:nrhs",
                          "Two inputs required.");
    }

    if(nlhs != 1) {
        mexErrMsgIdAndTxt("MP:constructMpFromChar:nlhs",
                          "One outputs required.");
    }

    if(!mxIsClass(prhs[0], "char")  ||
       mxGetNumberOfElements(prhs[0]) == 0
      ) {
        mexErrMsgIdAndTxt("MP:constructMpFromChar:notChar",
                          "Input must be of type char.");
    }

    if(!mxIsDouble(prhs[1])  ||
       mxIsComplex(prhs[1])  ||
       mxGetNumberOfElements(prhs[1]) == 0
      ) {
        mexErrMsgIdAndTxt("MP:constructMpFromChar:notRealDouble",
                          "Input precision must be real and of type double.");
    }

    // input
    char *input_r;
    input_r = mxArrayToString(prhs[0]);
    double input_prec = mxGetScalar(prhs[1]);

    //output
    mxArray *outputMatrix;
    outputMatrix = mxCreateNumericMatrix(1,1,mxINT64_CLASS,mxREAL);
    long long *ip = (long long *)(mxGetData(outputMatrix));

    // allocate persistent memory
    mpreal temp = mpreal(0.0, input_prec, MPFR_RNDN);
    mpreal *array = (mpreal *)  mxCalloc(1, sizeof(temp));
    mexMakeMemoryPersistent(array);
    // load value to variable
    new (array) mpreal(input_r, input_prec, MPFR_RNDN);

    // copy adress to the output variable
    ip[0] = (long long)(long long *)array;

    plhs[0] = outputMatrix;
}