#include "mex.h"

#include "gmp.h"
#include "gmpxx.h"
#include "mpfr.h"
#include "mpc_class.h"
#include "mplapack_config.h"
#include "mplapack_double.h"
#include "mplapack_gmp.h"
#include "mplapack_mpfr.h"
#include "mplapack_utils_mpfr.h"
#include "mpreal.h"
#include "mpcomplex.h"
#include "mpblas_mpfr.h"

std::vector<mpfr::mpreal> mxArray2vector(const mxArray* array);
std::vector<mpfr::mpcomplex> mxArray2complexVector(const mxArray* array);

// int vector2mxArray(const mxArray* array, const mpreal* vector);
int vector2mxArray(const mxArray* array, const std::vector<mpfr::mpreal> vector_in);
int vector2mxArray(const mxArray* array, const std::vector<mpfr::mpcomplex> vector_in);

std::vector<mpfr::mpreal> mxArray2vector(const mxArray* array) {
    // inputs:
    // array: 2D mpreal array created by the mp constructor
    // m: number of rows in the array
    // n: number of columns in the array
    // (m by n array)
    // output:
    // vector: 1D (m * n) std::vector<mpfr::mpreal>

    // Get input array sizes
    mwSize nfields = mxGetNumberOfElements(array);
    mwSize MStructElems = mxGetM(array);
    mwSize NStructElems = mxGetN(array);

    // create a temporaty mpreal object
    long long *temp_in= (long long *)(mxGetData(array));
    mpreal *temp_p = (mpreal*)(temp_in[0]);
//     mexPrintf("temp_p precision in reorder: %d\n", temp_p->get_prec());
    mpreal temp = mpreal(*temp_p, temp_p->get_prec(), MPFR_RNDN);
    mpfr_prec_t precision = temp.get_prec();
//     mexPrintf("precision in reorder: %d\n", precision);

    // Set default precision
    mpfr_set_default_prec(precision);
    
    // Allocate memory for the result vector
    std::vector<mpfr::mpreal> vector_out;
    vector_out.reserve(int(MStructElems) * int(NStructElems));
    for(int i = 0; i < int(MStructElems) * int(NStructElems); i++){
        vector_out.emplace_back(0.0, precision);
    }

    // Flatten the 2D mxArray into a 1D std::vector<mpfr::mpreal>
    for(mwSize i = 0; i<=nfields-1;i++){
        temp_p = (mpreal*)(temp_in[i]);
        temp = mpreal(*temp_p, precision, MPFR_RNDN);
        vector_out[i] = temp; 
    }

    // Return the 1D vector
    return vector_out;
}

std::vector<mpfr::mpcomplex> mxArray2complexVector(const mxArray* array){
//     #include "mpcomplex.h"
    // inputs:
    // array: 2D mpcomplex array created by the mp constructor
    // m: number of rows in the array
    // n: number of columns in the array
    // (m by n array)
    // output:
    // vector: 1D (m * n) mpcomplex column vector
    mpcomplex *temp_mpcomplex;

    // Get input array sizes
    mwSize nfields = mxGetNumberOfElements(array);
    mwSize MStructElems = mxGetM(array);
    mwSize NStructElems = mxGetN(array);

    // create a temporaty mpcomplex object
    long long *temp_in= (long long *)(mxGetData(array));
    mpcomplex *temp_p = (mpcomplex*)(temp_in[0]);
    mpfr_prec_t precision = temp_p->get_prec_re();
    mpcomplex temp = mpcomplex(*temp_p, precision, precision, MPFR_RNDN);

    // Set default precision
    mpcomplex::set_default_prec(precision); // set default mpcomplex precision

    // Allocate memory for the result vector
    std::vector<mpfr::mpcomplex> vector_out;
    vector_out.reserve(int(MStructElems) * int(NStructElems));
    for(int i = 0; i < int(MStructElems) * int(NStructElems); i++){
        vector_out.emplace_back(0.0, 0.0, precision, precision, MPFR_RNDN);
    }

    // Flatten the 2D array into a 1D vector
    for(mwSize i = 0; i<=nfields-1;i++){
        temp_p = (mpcomplex*)(temp_in[i]);
        temp = mpcomplex(*temp_p, precision, precision, MPFR_RNDN);
        vector_out[i] = temp; // Convert pointer mxArray to std::vector<mpfr::mpcomplex>
    }

    // Return the 1D vector
    return vector_out;
}

/// Function to convert a 1D vector back to a 2D array in column-major order
int vector2mxArray(const mxArray* array, const std::vector<mpfr::mpreal> vector_in) {
    // Inputs:
    // vector_in: 1D column-major order std::vector<mpfr::mpreal>
    // Output:
    // mxArray
    // n: number of rows
    // m: number of columns

    // Get input array sizes
    mwSize nfields = mxGetNumberOfElements(array);
    mwSize MStructElems = mxGetM(array);
    mwSize NStructElems = mxGetN(array);

    long long *outr_in= (long long *)(mxGetData(array));
    for(mwSize i = 0; i<nfields; i++){
        mpreal* outr = (mpreal*)(outr_in[i]);
        *outr = vector_in[i];
    }
    return 0;
}

int vector2mxArray(const mxArray* array, const std::vector<mpfr::mpcomplex> vector_in) {
    // Inputs:
    // vector_in: 1D column-major order std::vector<mpfr::mpcomplex>
    // n: number of rows
    // m: number of columns
    // Output:
    // mxArray

    // Get input array sizes
    mwSize nfields = mxGetNumberOfElements(array);
    mwSize MStructElems = mxGetM(array);
    mwSize NStructElems = mxGetN(array);

    long long *outr_in= (long long *)(mxGetData(array));
    for(mwSize i = 0; i<nfields; i++){
        mpcomplex* outr = (mpcomplex*)(outr_in[i]);
        *outr = vector_in[i];
    }
    return 0;
}

std::vector<mpfr::mpreal> allocate_mpreal_vector(const int length, const mpfr_prec_t precision, const mp_rnd_t mode){
    // Inputs:
    // length: length of the vector
    // prec: precision
    // mode: rounding mode

        std::vector<mpfr::mpreal> vector_out;
        vector_out.reserve(length);
        for(int i = 0; i < length; i++){
        vector_out.emplace_back(0.0, precision, mode);
        }

    return vector_out;
}

std::vector<mpfr::mpcomplex> allocate_mpcomplex_vector(const int length, const mpfr_prec_t precision, const mp_rnd_t mode){
    // Inputs:
    // length: length of the vector
    // precision: precision
    // mode: rounding mode

    std::vector<mpfr::mpcomplex> vector_out;
    vector_out.reserve(length);
    for(int i = 0; i < length; i++){
        vector_out.emplace_back(0.0, 0.0, precision, precision, mode);
    }
    
    return vector_out;
}
