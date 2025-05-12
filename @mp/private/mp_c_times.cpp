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
    if(ex == 1 && ey > 1){
        for(mwSize i=0;i<ey;i++)
        {
            xr = (mpcomplex*)(xr_in[0]);
            yr = (mpcomplex*)(yr_in[i]);
            outr = (mpcomplex*)(outr_in[i]);

            *outr = *xr * *yr;
        }
    }else if(ex > 1 && ey == 1){
        for(mwSize i=0;i<ex;i++)
        {
            xr = (mpcomplex*)(xr_in[i]);
            yr = (mpcomplex*)(yr_in[0]);
            outr = (mpcomplex*)(outr_in[i]);

            *outr = *xr * *yr;
        }
    }else if(k!=0){
        for(mwSize j=0;j<=k;j++){
            for(mwSize i=0;i<ey;i++)
            {
                xr = (mpcomplex*)(xr_in[i+(j*ey)]);
                yr = (mpcomplex*)(yr_in[i]);
                outr = (mpcomplex*)(outr_in[i+(j*ey)]);

                *outr = *xr * *yr;
            }
        }
    }else if(ex == ex){
        for(mwSize i=0;i<ex;i++)
        {
            xr = (mpcomplex*)(xr_in[i]);
            yr = (mpcomplex*)(yr_in[i]);
            outr = (mpcomplex*)(outr_in[i]);

            *outr = *xr * *yr;
        }
    }else{
        mexWarnMsgIdAndTxt("mp_r_times:MatrixMismatch",
                           "The sizes of the input matrixes are not consistent.");
    }
}