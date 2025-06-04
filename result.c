#include "result.h"
#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

complex multiply(complex c1, complex c2) {
    complex result;
    result.real = c1.real * c2.real - c1.imag * c2.imag;
    result.imag = c1.real * c2.imag + c1.imag * c2.real;
    return result;
}

complex sum(complex c1, complex c2) {
    complex result;
    result.real = c1.real + c2.real;
    result.imag = c1.imag + c2.imag;
    return result;
}

matrix get_product(circuit all_circ, int qubits, matrix product) {

}

vector get_vout(matrix product, vector vin, int qubits, vector vout) {

}