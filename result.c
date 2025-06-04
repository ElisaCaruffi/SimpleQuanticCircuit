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

void m_mult(matrix m1, matrix m2, matrix *res, int qubits) {
    int len = (int)pow(2, qubits);
    for (int i = 0; i < len; i++) {                                         // iterates rows
        for (int j = 0; j < len; j++) {                                     // iterates columns
            complex c = {0.0, 0.0};
            for (int k = 0; k < len; k++) {
                c = c_sum(c, c_multiply(m1.rows[i].values[k], m2.rows[k].values[j]));
            }
            res -> rows[i].values[j] = c;
        }
    }

}

void copy_vector(vector* out, vector in, int qubits) {
    int len = (int)pow(2, qubits);
    for (int i = 0; i<len; i++) {
        out -> values[i] = in.values[i];
    }
}

void copy_matrix(matrix* out, matrix in, int qubits) {
    int len = (int)pow(2, qubits);
    for (int i = 0; i<len; i++) {
        copy_vector(&out -> rows[i], in.rows[i], qubits);
    }
}

void m_print(matrix m, int qubits) {
    int len = (int)pow(2, qubits);
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            printf("%lf + %lfi  ", m.rows[i].values[j].real, m.rows[i].values[j].imag);
        }
        printf("\n");
    }
    printf("\n\n");
}

matrix get_product(circuit all_circ, int qubits, matrix temp, matrix result, char* order) {
    copy_matrix(&temp, all_circ.cir[0], qubits);
    for (int index = 0; index < strlen(order) - 1; index++) {                       
        m_mult(temp, all_circ.cir[index + 1], &result, qubits);
        copy_matrix(&temp, result, qubits);
    }
    return result;
}

vector get_vout(matrix product, vector vin, int qubits, vector vout) {
    int len = (int)pow(2, qubits);
    for (int i = 0; i < len; i++) {                                         // iterates rows
        for (int j = 0; j < len; j++) {                                     // iterates columns
            complex c = {0.0, 0.0};
            for (int k = 0; k < len; k++) {
                c = c_sum(c, c_multiply(m1.rows[i].values[k], m2.rows[k].values[j]));
            }
            res -> rows[i].values[j] = c;
        }
    }
}
