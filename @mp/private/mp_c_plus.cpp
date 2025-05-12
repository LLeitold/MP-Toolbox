#include "dependencies.h"

void mexFunction( int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[] )
{
    mpcomplex *xr,*yr,*outr;
    mwSize *in1, *in2, *in3;
    mwSize ex,ey,k;

    in1 = (mwSize*) mxGetData(prhs[3]);
    ex = *in1;

    in2 = (mwSize*) mxGetData(prhs[4]);
    ey = *in2;

    in3 = (mwSize*) mxGetData(prhs[5]);
    k = *in3;
    k = k-1;

    long long *xr_in= (long long *)(mxGetData(prhs[0]));
    long long *yr_in= (long long *)(mxGetData(prhs[1]));
    long long *outr_in= (long long *)(mxGetData(prhs[2]));

    /* Mathematical operation */
    //Check if the input is [matrix]+[scalar]
    if(ex == 1 && ey > 1){
        for(mwSize i=0;i<ey;i++)
        {
            xr = (mpcomplex*)(xr_in[0]);
            yr = (mpcomplex*)(yr_in[i]);
            outr = (mpcomplex*)(outr_in[i]);

            *outr = *xr + *yr;
        }
        //Check if the input is [sclar]+[matrix]
    }else if(ex > 1 && ey == 1){
        for(mwSize i=0;i<ex;i++)
        {
            xr = (mpcomplex*)(xr_in[i]);
            yr = (mpcomplex*)(yr_in[0]);
            outr = (mpcomplex*)(outr_in[i]);

            *outr = *xr + *yr;
        }
        //Check if inputs have the same number of elemetns (matrix sizes should  been fixed on the matlab side)
    }else if(ex == ex){
        for(mwSize i=0;i<ex;i++)
        {
            xr = (mpcomplex*)(xr_in[i]);
            yr = (mpcomplex*)(yr_in[i]);
            outr = (mpcomplex*)(outr_in[i]);

            *outr = *xr + *yr;
        }
    }else{
        mexWarnMsgIdAndTxt("mp_c_plus:MatrixMismatch",
                           "The sizes of the input matrixes are not consistent.");
    }
}