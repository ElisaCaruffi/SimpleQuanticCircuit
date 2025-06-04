#ifndef RESULT_H
#define RESULT_H

complex multiply(complex c1, complex c2);
complex sum(complex c1, complex c2);
matrix get_product(circuit all_circ, int qubits, matrix product);
vector get_vout(matrix product, vector vin, int qubits, vector vout);

#endif