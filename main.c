#include "data.h"
#include "result.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main() {
    // gets the lines of the init file
    char lines[1024];
    printf("Insert the init file name:\n");
    char init[100];
    scanf("%s", init);
    read_file(init, lines);  
    // gets the qubits from the init file
    int qubits;
    qubits = get_qubits(lines);    
    // gets the input vector from the init file
    int len = (int)pow(2, qubits);
    vector vin;
    vin.values = malloc(len * sizeof(complex));
    vin = get_vin(lines, qubits, vin);
    for (int i = 0; i<vin.length; i++) {
        if (vin.values[i].imag < 0) {
            printf("%lf - %lfi\n", vin.values[i].real, -vin.values[i].imag);
        } else
        printf("%lf + %lfi\n", vin.values[i].real, vin.values[i].imag);
    }

    // gets the lines of the circ file
    char lines2[1024];
    printf("Insert the circ file name:\n");
    char circ[100];
    scanf("%s", circ);
    read_file(circ, lines2);
    // gets the order from the circ file
    char order[100];
    get_order(lines2, order);

    // inverts the order of the circuit
    for (int i = 0; i < strlen(order) / 2; i++) {
        char temp = order[i];
        order[i] = order[strlen(order) - 1 - i];
        order[strlen(order) - 1 - i] = temp;
    }
    printf("Order: %s\n", order);
    // gets the matrices from the circ file
    circuit all_circ;
    all_circ.cir = malloc(strlen(order) * sizeof(matrix));
    if (!all_circ.cir) {
        fprintf(stderr, "malloc failed\n");
        return 1;
    }
    all_circ = get_matrices(lines2, qubits, order, all_circ, (matrix){0}, (vector){0});
    //print_c(all_circ, order, qubits);
    // multiplies the matrices
    matrix product;
    product.rows = malloc(len * sizeof(vector));
    for (int i = 0; i < len; i++) {
        product.rows[i].values = malloc(len * sizeof(complex));
    }
    matrix result;
    result.rows = malloc(len * sizeof(vector));
    for (int i = 0; i < len; i++) {
        result.rows[i].values = malloc(len * sizeof(complex));
    }
    matrix temp;
    temp.rows = malloc(len * sizeof(vector));
    for (int i = 0; i < len; i++) {
        temp.rows[i].values = malloc(len * sizeof(complex));
    }
    product = get_product(all_circ, qubits, temp, result, order);
    //m_mult(all_circ.cir[0], all_circ.cir[1], &product, qubits);
    /*
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            printf("%lf + %lfi ", product.rows[i].values[j].real, product.rows[i].values[j].imag);
        }
        printf("\n");
    }
    */
    
    // gets the output vector
    vector vout;
    vout.values = malloc(len * sizeof(complex));
    vout = get_vout(product, vin, qubits, vout);
    for (int i = 0; i<len; i++) {
        printf("%lf + %lfi\n", vout.values[i].real, vout.values[i].imag);
    }
    // frees memory
    for (int i = 0; i < len; i++) {
        free(temp.rows[i].values);
    }
    free(temp.rows);
    for (int i = 0; i < len; i++) {
        free(product.rows[i].values);
    }
    free(product.rows);

    return 0;              
}