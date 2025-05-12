#include "dependencies.h"

#define MPFR_FORMAT "%+.4Re"
#define __MPLAPACK_BUFLEN__ 1024

void mexFunction( int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[] )
{
    mxClassID classType;
    classType = mxGetClassID(prhs[0]);

    if(classType != mxINT64_CLASS) {
        mexErrMsgIdAndTxt("MP:display:nrhs_type",
                          "Wrong type of input.");
    }

    char buffer_r[__MPLAPACK_BUFLEN__];
    char buffer_i[__MPLAPACK_BUFLEN__];

    long long *x_in= (long long *)(mxGetData(prhs[0]));
    mpcomplex *x = (mpcomplex*)(x_in[0]);
    mpcomplex y = *x; 

    mpreal xr = y.real();
    mpreal xi = y.imag();

    mpfr_snprintf(buffer_r, __MPLAPACK_BUFLEN__ , MPFR_FORMAT, mpfr_ptr(xr));
    mpfr_snprintf(buffer_i, __MPLAPACK_BUFLEN__ , MPFR_FORMAT, mpfr_ptr(xi));
    char *buffer = (char *) malloc(strlen(buffer_r) + strlen(buffer_i) + 4);
    strcpy(buffer, buffer_r);
    strcat(buffer, " ");
    strcat(buffer, buffer_i);
    strcat(buffer, " i");

    plhs[0] = mxCreateString(buffer);
}