#ifndef DATA_H
#define DATA_H

typedef struct {
    double real;
    double imag;
} complex;

typedef struct {
    int length;
    complex* values;
} vector;

typedef struct {

    vector* rows;
} matrix;

typedef struct {
    matrix* cir;
} circuit;

void read_file(char filename[], char* lines);
int get_qubits(char* lines);
complex get_complex(char* parse);
vector get_vin(char* lines, int qubits, vector vin);
void get_order(char* lines, char* order);
circuit get_matrices(char* lines, int qubits, char* order, circuit all_circ, matrix m, vector row);
//void print_c(circuit all_circ, char* order, int qubits);

#endif