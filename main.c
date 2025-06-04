#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main() {
    char lines[1024];
    printf("Insert the init file name:\n");
    char init[100];
    scanf("%s", init);
    read_file(init, lines);  

    int qubits;
    qubits = get_qubits(lines);    

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

    char lines2[1024];
    printf("Insert the circ file name:\n");
    char circ[100];
    scanf("%s", circ);
    read_file(circ, lines2);
    char order[100];
    get_order(lines2, order);
    printf("Order: %s\n", order);

    circuit all_circ;
    all_circ.cir = malloc(strlen(order) * sizeof(matrix));
    if (!all_circ.cir) {
        fprintf(stderr, "malloc failed\n");
        return 1;
    }
    all_circ = get_matrices(lines2, qubits, order, all_circ, (matrix){0}, (vector){0});

    print_c(all_circ, order, qubits);
    for (size_t i = 0; i < strlen(order); i++) {
        for (int j = 0; j < len; j++) {
            free(all_circ.cir[i].rows[j].values);
        }
        free(all_circ.cir[i].rows);
    }
    free(all_circ.cir);

    return 0;              
}