#include "dependencies.h"

#define MPFR_FORMAT "%+.30Re"
#define __MPLAPACK_BUFLEN__ 1024

void sprintnum(char *buf, mpreal rtmp);

void mexFunction( int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[] )
{
    mxClassID classType;
    classType = mxGetClassID(prhs[0]);

    if(classType != mxINT64_CLASS) {
        mexErrMsgIdAndTxt("MP:display:nrhs_type",
                          "Wrong type of input.");
    }

    char buffer[__MPLAPACK_BUFLEN__];
    mpfr_t *xr;
    long long *xr_in= (long long *)(mxGetData(prhs[0]));
    xr = (mpfr_t*)(xr_in[0]);
    mpreal a = mpreal(*xr);
    mpfr_snprintf(buffer, __MPLAPACK_BUFLEN__ , MPFR_FORMAT, mpfr_ptr(a));
    plhs[0] = mxCreateString(buffer);
}