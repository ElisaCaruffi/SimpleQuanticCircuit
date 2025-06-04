#include "result.h"
#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

complex c_multiply(complex c1, complex c2) {
    complex result;
    result.real = c1.real * c2.real - c1.imag * c2.imag;
    result.imag = c1.real * c2.imag + c1.imag * c2.real;
    return result;
}

complex c_sum(complex c1, complex c2) {
    complex result;
    result.real = c1.real + c2.real;
    result.imag = c1.imag + c2.imag;
    return result;
}

matrix m_mult(matrix m1, matrix m2, matrix result, int qubits) {
    int len = (int)pow(2, qubits);
    for (int i = 0; i < len; i++) {                                         // iterates rows
        for (int j = 0; j < len; j++) {                                     // iterates columns
            complex c = {0.0, 0.0};
            for (int k = 0; k < len; k++) {
                c = c_sum(c, c_multiply(m1.rows[i].values[k], m2.rows[k].values[j]));
            }
            result.rows[i].values[j] = c;
        }
    }
    return result;
}

matrix get_product(circuit all_circ, int qubits, matrix temp, char* order) {
    for (int index = 0; index < strlen(order) - 1; index++) {                       // iterates matrices
        temp = m_mult(all_circ.cir[index], all_circ.cir[index + 1], temp, qubits);
        all_circ.cir[index + 1]  = temp;
    }
    return all_circ.cir[strlen(order) - 1];
}
/*
vector get_vout(matrix product, vector vin, int qubits, vector vout) {

}
*/