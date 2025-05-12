#include "dependencies.h"

mxArray* constructMpFromMp(const mxArray *inputMatrix, const mxArray *prec);

void mexFunction(int nlhs,mxArray *plhs[],int nrhs, const mxArray *prhs[])
{
    if(nrhs != 2) {
    mexErrMsgIdAndTxt("MP:constructMpFromMp:nrhs",
                      "Two inputs are required.");
    }
    
    if(nlhs != 1) {
    mexErrMsgIdAndTxt("MP:constructMpFromMp:nlhs",
                      "One output is required.");
    }

    plhs[0] = constructMpFromMp(prhs[0],prhs[1]);
}

mxArray* constructMpFromMp(const mxArray *inputMatrix, const mxArray *prec)
{
    mxArray *outputMatrix;
    mwSize   nfields = 0;
    mwSize   NStructElems = 0,MStructElems = 0;

    nfields = mxGetNumberOfElements(inputMatrix);
    MStructElems = mxGetM(inputMatrix);
    NStructElems = mxGetN(inputMatrix);

    long long *x_in = (long long *)(mxGetData(inputMatrix));
    mpcomplex *x = (mpcomplex*)(x_in[0]);
    mpcomplex y = *x;
    double input_prec = mxGetScalar(prec);
    mpcomplex temp = mpcomplex(y, input_prec, input_prec, MPFR_RNDN);

    outputMatrix = mxCreateNumericMatrix(MStructElems,NStructElems,mxINT64_CLASS,mxREAL);
    long long *ip = (long long *)(mxGetData(outputMatrix));

    for(mwSize i = 0; i<=nfields-1;i++){
        mpcomplex *array = (mpcomplex *)  mxCalloc(1, sizeof(temp));
        mexMakeMemoryPersistent(array); 
        mpcomplex *x = (mpcomplex*)(x_in[0]);
        mpcomplex y = *x;
        new (array) mpcomplex(y, input_prec, input_prec, MPFR_RNDN);
        ip[i] = (long long)(long long *)array;
    }
    return outputMatrix;
}