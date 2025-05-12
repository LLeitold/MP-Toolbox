#include "dependencies.h"

void mexFunction( int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[] )
{
    mpreal *xr, *yr, *outr;
    mwSize *in1, *in2, *in3, *in4;
    mwSize ex,ey,k,flag;

    in1 = (mwSize*) mxGetData(prhs[3]);
    ex = *in1;

    in2 = (mwSize*) mxGetData(prhs[4]);
    ey = *in2;

    in3 = (mwSize*) mxGetData(prhs[5]);
    k = *in3;
    k = k-1;

    in4 = (mwSize*) mxGetData(prhs[6]);
    flag = *in4;

    long long *xr_in= (long long *)(mxGetData(prhs[0]));
    long long *yr_in= (long long *)(mxGetData(prhs[1]));
    long long *outr_in= (long long *)(mxGetData(prhs[2]));

    /* Mathematical operation */
    if(ex == 1 && ey > 1){
        for(mwSize i=0;i<ey;i++)
        {
            xr = (mpreal*)(xr_in[0]);
            yr = (mpreal*)(yr_in[i]);
            outr = (mpreal*)(outr_in[i]);

            *outr = *xr - *yr;
        }
    }else if(ex > 1 && ey == 1){
        for(mwSize i=0;i<ex;i++)
        {
            xr = (mpreal*)(xr_in[i]);
            yr = (mpreal*)(yr_in[0]);
            outr = (mpreal*)(outr_in[i]);

            *outr = *xr - *yr;
        }
    }else if(k!=0 && flag==0){
        for(mwSize j=0;j<=k;j++){
            for(mwSize i=0;i<ey;i++)
            {
                xr = (mpreal*)(xr_in[i+(j*ey)]);
                yr = (mpreal*)(yr_in[i]);
                outr = (mpreal*)(outr_in[i+(j*ey)]);

                *outr = *xr - *yr;
            }
        }
    }else if(k!=0 && flag==1){
        for(mwSize j=0;j<=k;j++){
            for(mwSize i=0;i<ey;i++)
            {
                xr = (mpreal*)(xr_in[i]);
                yr = (mpreal*)(yr_in[i+(j*ey)]);
                outr = (mpreal*)(outr_in[i+(j*ey)]);

                *outr = *xr - *yr;
            }
        }
    }else if(ex == ex){
        for(mwSize i=0;i<ex;i++)
        {
            xr = (mpreal*)(xr_in[i]);
            yr = (mpreal*)(yr_in[i]);
            outr = (mpreal*)(outr_in[i]);

            *outr = *xr - *yr;
        }
    }else{
        mexWarnMsgIdAndTxt("mp_mulc:MatrixMismatch",
                           "The sizes of the input matrixes are not consistent.");
    }
}