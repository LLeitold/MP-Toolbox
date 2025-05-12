#include "dependencies.h"

void mexFunction(int nlhs,mxArray *plhs[],int nrhs, const mxArray *prhs[])
{
    if(nrhs != 3) {
        mexErrMsgIdAndTxt("MP:constructMpFromChar:nrhs",
                          "Three inputs required.");
    }

    if(nlhs != 1) {
        mexErrMsgIdAndTxt("MP:constructMpFromChar:nlhs",
                          "One output is required.");
    }

    if(!mxIsClass(prhs[0], "char")  ||
       mxGetNumberOfElements(prhs[0]) == 0
      ) {
        mexErrMsgIdAndTxt("MP:constructMpFromChar:notChar",
                          "Input must be of type char.");
    }

    if(!mxIsClass(prhs[1], "char")  ||
       mxGetNumberOfElements(prhs[1]) == 0
      ) {
        mexErrMsgIdAndTxt("MP:constructMpFromChar:notChar",
                          "Input must be of type char.");
    }

    if(!mxIsDouble(prhs[2])  ||
       mxIsComplex(prhs[2])  ||
       mxGetNumberOfElements(prhs[2]) == 0
      ) {
        mexErrMsgIdAndTxt("MP:constructMpFromChar:notRealDouble",
                          "Input precision must be real and of type double.");
    }

    // input
    char *input_r;
    char *input_i;
    input_r = mxArrayToString(prhs[0]);
    input_i = mxArrayToString(prhs[1]);
    double input_prec = mxGetScalar(prhs[2]);

    //output
    mxArray *outputMatrix;
    outputMatrix = mxCreateNumericMatrix(1,1,mxINT64_CLASS,mxREAL);
    long long *ip = (long long *)(mxGetData(outputMatrix));

    // allocate persistent memory
    mpcomplex temp = mpcomplex(0.0, 0.0, input_prec, input_prec, MPFR_RNDN);
    mpcomplex *array = (mpcomplex *)  mxCalloc(1, sizeof(temp));
    mexMakeMemoryPersistent(array);
    // load value to variable
    new (array) mpcomplex(input_r, input_i, input_prec, input_prec, MPFR_RNDN);

    // copy adress to the output variable
    ip[0] = (long long)(long long *)array;

    plhs[0] = outputMatrix;
}