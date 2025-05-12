// multiple precision library dependencies
#define ___MPLAPACK_MPLAPACK_INIT___

// C and C++ standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <limits>

// mex interface to matlab
#include "mex.h"

// The GNU Multiple Precision Arithmetic Library
#include "gmp.h"
#include "gmpxx.h"

// multiple-precision floating-point computations with correct rounding
#include "mpfr.h"

// multiple-precision complex numbers
#include "mpc.h"
#include "mpc_class.h"
// C++ wrapper for real and complex multiple precision types
#include "mpreal.h"
#include "mpcomplex.h"

// multiple precision blas and lapack implementations
#include "mplapack_config.h"
#include "mplapack_double.h"
#include "mplapack_gmp.h"
#include "mplapack_mpfr.h"
#include "mplapack_utils_mpfr.h"
#include "mpblas_mpfr.h"

// utility functions for reshaping the matrixes
#include "reorder.h"

// rounding flag to control rounding mode globaly in the future
mpfr_rnd_t rounding_mode = MPFR_RNDN;
