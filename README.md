# MP-Toolbox
Multiple-precision arithmetic Toolbox for MATLAB

The **Multiple-precision arithmetic Toolbox for MATLAB** provides MATLAB users with a comprehensive suite of functions to perform arithmetic operations with arbitrary precision. This toolbox is designed for researchers and engineers who need higher precision calculations than what MATLAB’s native double precision offers.

## Overview

Modern applications—from numerical analysis to computational science—often demand arithmetic with precision beyond the standard floating-point representation. This toolbox implements multiple-precision arithmetic routines, including basic operations (addition, subtraction, multiplication, division) as well as advanced functions (exponentiation, logarithms, trigonometric functions, and more). The toolbox is built to be user-friendly, easily integrated into your MATLAB projects, and extendable for custom precision requirements.

## Features

- **Arbitrary Precision Calculation:** Support for computations with a user-defined number of digits.
- **Seamless MATLAB Integration:** Functions are designed to be used just like native MATLAB operations.
- **Modular Design:** Easily extend or customize the functions for specialized applications.
- **Compatibility:** Works with modern versions of MATLAB (R2022b is recommended).

## Installation
1. **Clone the Repository:**

   ```bash
   git clone https://github.com/LLeitold/MP-Toolbox.git
   ```
   
2. **Download the binary files (for Windows x64)** [link](https://www.dropbox.com/scl/fi/5e8sz8ukzw95v2wc3jip5/MP-Toolbox-binary.zip?rlkey=82mrj6wjv3zh316omm1miqiim&st=wcvxzue9&dl=0)
   - You can also download and compile the binaries from source [link](https://github.com/nakatamaho/mplapack.git)

3. **Copy the binaries to MP Toolbox/@mp/private**
 
4. **Add to MATLAB Path:**
   In MATLAB, navigate to the directory and add the toolbox to your path:

   ```matlab
   addpath(genpath('path/to/MP Toolbox'))
   ```
5. **Compilation:**
   - Navigate to the `mex` directory:

     ```matlab
     cd path/to/MP Toolbox/mex
     ```

   - Run the provided build script:

     ```matlab
     mex_make
     ```

## Getting Started

### Setting the Precision

Before performing multiple-precision arithmetic, set the desired number of significant digits:

```matlab
% Set the default precision to 150 digits
mp.setDefaultPrecision(150);
```

### Creating Multiple-precision Numbers

Convert regular numeric inputs or strings into multiple-precision format:

```matlab
a = mp('3.1415926535897932384626433832795028841971693993751', 150);
b = mp(2.7182818284590452353602874713526624977572470936999, 150);
```

### Basic Arithmetic Operations

Perform arithmetic operations just as you would with MATLAB’s standard data types:

```matlab
% Addition
c = a + b;

% Multiplication
d = a * b;

% Division
e = a / b;

disp(c);
```

## Contributing

Contributions are welcome! If you would like to contribute enhancements or bug fixes, please follow these guidelines:

1. **Fork the Repository:** Click the "Fork" button at the top of the repository page.
2. **Clone Your Fork:**

   ```bash
   git clone https://github.com/yourusername/multiprecision-toolbox.git
   ```

3. **Create a Feature Branch:**

   ```bash
   git checkout -b feature/my-new-feature
   ```

4. **Commit and Push:**

   ```bash
   git commit -am 'Add new feature'
   git push origin feature/my-new-feature
   ```

5. **Submit a Pull Request:** Once your changes are ready, submit a pull request for review.

## Issue Reporting

If you encounter issues or have feature requests, please open a new issue in the [Issues section](https://github.com/LLeitold/MP-Toolbox/issues).

## Contact

For questions, comments, or support, please contact [László Leitold](mailto:leitold.laszlo@mogi.bme.hu) or open an issue in the repository.

## Acknowledgments

- Thanks to Ben Barrowes for creating the original [Multiple Precision Toolbox for MATLAB](https://www.mathworks.com/matlabcentral/fileexchange/6446-multiple-precision-toolbox-for-matlab) without his work this toolbox would not exist.
- Thanks to Maho Nakata for creating the [mplapack](https://github.com/nakatamaho/mplapack.git) library contributing to the robustness and speed of our toolbox.
- Special thanks to contributors and peer reviewers who helped improve this project.

---

This README is intended to serve as both an introduction and a comprehensive guide to using the **Multiple-precision arithmetic Toolbox for MATLAB**. For further questions or more details, please refer to the documentation or contact the project maintainers. Enjoy high-precision computing with MATLAB!
