#include "result.h"
#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

complex c_multiply(complex c1, complex c2) {                                                // multiplies complexes
    complex result;                                                                         // output
    result.real = c1.real * c2.real - c1.imag * c2.imag;                                    // real part
    result.imag = c1.real * c2.imag + c1.imag * c2.real;                                    // imaginary part
    return result;                                                                          // returns product
}

complex c_sum(complex c1, complex c2) {                                                     // sums complexes
    complex result;                                                                         // output
    result.real = c1.real + c2.real;                                                        // real part
    result.imag = c1.imag + c2.imag;                                                        // imaginary part
    return result;                                                                          // returns product
}

void m_mult(matrix m1, matrix m2, matrix *res, int qubits) {                                // multiplies two matrices
    int len = (int)pow(2, qubits);                                                          // number of columns or rows
    for (int i = 0; i < len; i++) {                                                         // iterates rows
        for (int j = 0; j < len; j++) {                                                     // iterates columns
            complex c = {0.0, 0.0};                                                         // initializes complex
            for (int k = 0; k < len; k++) {                                                 // iterates both
                c = c_sum(c, c_multiply(m1.rows[i].values[k], m2.rows[k].values[j]));       // gets the complex
            }
            res -> rows[i].values[j] = c;                                                   // assigns the complex
        }
    }

}

void copy_vector(vector* out, vector in, int qubits) {                                      // copies the vector
    int len = (int)pow(2, qubits);                                                          
    for (int i = 0; i<len; i++) {
        out -> values[i] = in.values[i];
    }
}

void copy_matrix(matrix* out, matrix in, int qubits) {                                      // copies the matrix
    int len = (int)pow(2, qubits);
    for (int i = 0; i<len; i++) {
        copy_vector(&out -> rows[i], in.rows[i], qubits);
    }
}



matrix get_product(circuit all_circ, int qubits, matrix temp, matrix result, char* order) {     // multiplies all matrices
    copy_matrix(&temp, all_circ.cir[0], qubits);                                                // copies matrix in temp
    for (int index = 0; index < strlen(order) - 1; index++) {                                   // iterates the circuit
        m_mult(temp, all_circ.cir[index + 1], &result, qubits);                                 // multiplicates
        copy_matrix(&temp, result, qubits);                                                     // copies the matrix in temp
    }
    return result;                                                                              // returns the product
}

vector get_vout(matrix product, vector vin, int qubits, vector vout) {                          // multiplicates the product for the input vector
    int len = (int)pow(2, qubits);                                                              // number of rows or columns
    for (int i = 0; i < len; i++) {                                                             // iterates rows
        complex c = {0.0, 0.0};                                                                 // initializes complex
        for (int j = 0; j < len; j++) {                                                         // iterates columns
            c = c_sum(c, c_multiply(product.rows[i].values[j], vin.values[j]));                 // get the complex
        }
        vout.values[i] = c;                                                                     // assigns the complex
    }
    return vout;                                                                                // return output vector
}
