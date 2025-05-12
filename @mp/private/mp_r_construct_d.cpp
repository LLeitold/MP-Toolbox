#include "dependencies.h"

mxArray* constructMpFromDouble(const mxArray *inputMatrix, const mxArray *prec);

void mexFunction(int nlhs,       mxArray *plhs[],
                 int nrhs, const mxArray *prhs[])
{
    if(nrhs != 2) {
        mexErrMsgIdAndTxt("MP:constructMpFromDouble:nrhs",
                          "Two inputs required.");
    }

    if(nlhs != 1) {
        mexErrMsgIdAndTxt("MP:constructMpFromDouble:nlhs",
                          "One outputs required.");
    }

    if( !mxIsDouble(prhs[0]) ||
       mxIsComplex(prhs[0]) ||
       mxGetNumberOfElements(prhs[0]) == 0 ||
       !mxIsDouble(prhs[1]) ||
       mxIsComplex(prhs[1]) ||
       mxGetNumberOfElements(prhs[1]) == 0
      ) {
        mexErrMsgIdAndTxt("MP:constructMpFromDouble:notRealDouble",
                          "Input matrices must be real and of type double.");
    }

    plhs[0] = constructMpFromDouble(prhs[0],prhs[1]);
}

mxArray* constructMpFromDouble(const mxArray *inputMatrix, const mxArray *prec)
{
    mxArray *outputMatrix;
    mwSize   nfields = 0;
    mwSize   NStructElems = 0,MStructElems = 0;
    double   *input_value = NULL;

    nfields = mxGetNumberOfElements(inputMatrix);
    MStructElems = mxGetM(inputMatrix);
    NStructElems = mxGetN(inputMatrix);

    input_value = mxGetPr(inputMatrix);
    double input_prec = mxGetScalar(prec);
    mpreal temp = mpreal(input_value[0], input_prec, MPFR_RNDN);

    outputMatrix = mxCreateNumericMatrix(MStructElems,NStructElems,mxINT64_CLASS,mxREAL);
    long long *ip = (long long *)(mxGetData(outputMatrix));

    for(mwSize i = 0; i<=nfields-1;i++){
        mpreal *array = (mpreal *)  mxCalloc(1, sizeof(temp));
        mexMakeMemoryPersistent(array[0]);
        new (array) mpreal(input_value[i], input_prec, MPFR_RNDN);
        ip[i] = (long long)(long long *)array;
    }
    return outputMatrix;
}