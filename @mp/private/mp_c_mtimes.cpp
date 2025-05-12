#include "dependencies.h"

void mexFunction( int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[] )
{
    if(nrhs!=7) {
        mexErrMsgTxt("7 inputs required.");
    } else if(nlhs!=0) {
        mexErrMsgTxt("This function does inplace calculations, no return object is needed!");
    }

    mpcomplex *xr,*yr,*outr,temp;
    int *in1, *in2, *in3;
    int s1,s2,s3;
    int *input_prec;

    long long *xr_in= (long long *)(mxGetData(prhs[0]));
    long long *yr_in= (long long *)(mxGetData(prhs[1]));
    long long *outr_in= (long long *)(mxGetData(prhs[2]));

    in1 = (int*) mxGetData(prhs[3]);
    s1 = *in1;  // M

    in2 = (int*) mxGetData(prhs[4]);
    s2 = *in2;  // N

    in3 = (int*) mxGetData(prhs[5]);
    s3 = *in3;  // K

    input_prec = (int*) mxGetPr(prhs[6]);
    mpfr_prec_t precision = static_cast<mpfr_prec_t>(*input_prec);
    mpcomplex::set_default_prec(precision); // set default mpcomplex precision

    mpcomplex alpha = mpcomplex(1.0, 0.0, precision, precision, MPFR_RNDN);
    mpcomplex beta  = mpcomplex(0.0, 0.0, precision, precision, MPFR_RNDN);

    std::vector<mpfr::mpcomplex> C;
    C.reserve(s1 * s2);
    for(int i = 0; i < s1 * s2; i++){
        C.emplace_back(0.0, 0.0, precision, precision, MPFR_RNDN);
    }

    std::vector<mpfr::mpcomplex> A = mxArray2complexVector(prhs[0]); // first matrix in row vector form
    std::vector<mpfr::mpcomplex> B = mxArray2complexVector(prhs[1]); // second matrix in row vector form

    Cgemm("n", "n", s1, s2, s3, alpha, A.data(), s1, B.data(), s3, beta, C.data(), s1);

    vector2mxArray(prhs[2], C);
}
