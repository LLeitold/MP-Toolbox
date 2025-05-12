#include "dependencies.h"

void constructMpFromMp(const mxArray *rMatrix, const mxArray *iMatrix,  const mxArray *outputMatrix, const mxArray *prec);

void mexFunction(int nlhs,mxArray *plhs[],int nrhs, const mxArray *prhs[])
{
    if(nrhs != 4) {
        mexErrMsgIdAndTxt("MP:constructMpFromMp:nrhs",
                          "Four inputs are required.");
    }

    if(nlhs != 0) {
        mexErrMsgIdAndTxt("MP:constructMpFromMp:nlhs",
                          "No output is required.");
    }

    if(mxGetM(prhs[0]) != mxGetM(prhs[1])) {
        mexErrMsgIdAndTxt("MP:constructMpFromMp:nrhs",
                          "Real and imaginary parts must be the same  M size.");
    }

    if(mxGetN(prhs[0]) != mxGetN(prhs[1])) {
        mexErrMsgIdAndTxt("MP:constructMpFromMp:nrhs",
                          "Real and imaginary parts must be the same N size.");
    }

    constructMpFromMp(prhs[0], prhs[1], prhs[2], prhs[3]);
}

void constructMpFromMp(const mxArray *rMatrix, const mxArray *iMatrix,  const mxArray *outputMatrix, const mxArray *prec)
{
    mwSize   nfields = 0;
    mwSize   NStructElems = 0,MStructElems = 0;

    nfields = mxGetNumberOfElements(rMatrix);
    MStructElems = mxGetM(rMatrix);
    NStructElems = mxGetN(rMatrix);

    long long *xr_in = (long long *)(mxGetData(rMatrix));
    long long *xi_in = (long long *)(mxGetData(iMatrix));
    long long *out_in = (long long *)(mxGetData(outputMatrix));
    double input_prec = mxGetScalar(prec);

    for(mwSize i = 0; i<=nfields-1;i++){
        mpreal *xr = (mpreal*)(xr_in[i]);
        mpreal *xi = (mpreal*)(xi_in[i]);
        mpcomplex *out  = (mpcomplex*)(out_in[i]);

        *out = mpcomplex(*xr, *xi, input_prec, input_prec, MPFR_RNDN);
    }
}