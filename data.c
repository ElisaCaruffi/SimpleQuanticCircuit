#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void read_file(char filename[], char* lines) {                                          // reads the file
    FILE *file = fopen(filename, "r");                                                  // opens file
    if (file == NULL) {                                                                 // if file doesn't exist
        perror("Error opening file");                                                   // error 
    }
    char temp[1024];                                                                    // temporary array
    temp[0] = '\0';                                                                    // initializes the array
    char *line = NULL;                                                                  // pointer to the first line
    size_t len = 0;                                                                     // line's lenght
    while (getline(&line, &len, file) != -1) {                                          // returns -1 if file ends
        if (strncmp(line, "#", 1) == 0) {                                               // if line starts with #
            strcat(temp, line);                                                         // concatenates the line in the array       
        }                                                      
    }
    fclose(file);                                                                       // closes file
    strcpy(lines, temp);                                                                // copies array
}

int get_qubits(char* lines) {                                                           // gets the number of qubits
    if (strncmp(lines, "#qubits", 7) == 0) {                                            // if the line starts with #qubits
        int start = 7;                                                                  // starts from the 8th character
        while (lines[start] == '\t' || lines[start] == '\n' || lines[start] == ' ') {   // skips spaces and tabs
            start++;                                                                    // moves to the next character
        }
        int end = start + 1;                                                            // starts from the next character
        while (lines[end] != ' ' && lines[end] != '\t' && lines[end] != '\n') {         // skips spaces and tabs
            end++;                                                                      // moves to the next character
        }
        char str[100];                                                                  // array
        int len = end - start;                                                          // length of the string
        strncpy(str, &lines[start], len);                                               // copies the string
        str[len] = '\0';                                                                // adds null terminator
        for (int i = 0; i < len; i++) {                                                 // iterates the string
            if (isdigit(str[i]) == 0) {                                                 // if a character is not a digit
                fprintf(stderr, "File format not valid\n");                             // error
                return -1;                                                              // returns -1 s
            }
        }
        int qubits = (int)strtol(str, NULL, 10);                                        // converts string to integer   
        return qubits;                                                                  // returns the number of qubits
    }
    else {                                                                              // if the line doesn't start with #qubits
        fprintf(stderr, "File format not valid\n");                                     // error
        return -1;                                                                      // returns -1 if the line doesn't start with #qubits
    };                                                                                   
}

vector get_vin(char* lines, int qubits, vector vin) {                                   // gets the input vector
    int index = 0;                                                                      // index of the input vector
    int start = 0;                                                                      // first character
    while (start < strlen(lines)) {                                                     // while start is less than the length
        if (strncmp(&lines[start], "#init", 5) == 0) {                                  // if the line starts with #init
            start += 5;                                                                 // increases start by 5
            while (lines[start] == ' ' || lines[start] == '\t') {                       // skips spaces and tabs
                start++;                                                                // moves to the next character
            }                                                             
            int end = start + 1;                                                        // starts from the next character
            while (lines[end] != '\n' && lines[end] != '\0') {                          // skips spaces and tabs
                end++;                                                                  // moves to the next character  
            }
            char str[100];                                                              // array
            int len = end - start;                                                      // length of the string
            strncpy(str, &lines[start], len);                                           // copies the string
            str[len] = '\0';                                                            // adds null terminator
            
            int count = 0;                                                              // counter of values
            char *p;                                                                    // pointer
            char *token = strtok_r(str, ", ", &p);                                      // splits the string
            char *tokens[100];                                                          // array of tokens
            while (token != NULL) {                                                     // while there are tokens
                tokens[count] = token;                                                  // adds token to the array
                count++;                                                                // increases count  
                token = strtok_r(NULL, ", ", &p);                                       // gets the next token
            }
            if (count != (int)pow(2, qubits)) {                                         // if values is not equal to 2^qubits
                perror("Input vector not valid");                                       // error
            }
            else {                                                                      // else
                vin.length = count;                                                     // sets the length
                for (int i = 0; i < count; i++) {                                       // iterates the tokens
                    char *t = tokens[i];                                                //assigns token to t                                                            
                    complex value;                                                      // initializes complex number   
                    char temp1[100];                                                    // temporary array for real part
                    char temp2[100];                                                    // temporary array for imaginary part
                    int i = 1;                                                          // starts from the second character
                    int k = 0;                                                          // index of the temporary array    
                    while (t[i] != '+' && t[i] != '-' && t[i] != ']') {                 // while the character is not +, - or ]
                        temp1[k] = t[i];                                                // adds character to the temporary array
                        k++;                                                            // increases index
                        i++;                                                            // moves to the next character
                    } 
                    temp1[k] = '\0';                                                    // adds null terminator
                    if (t[i] == ']') {                                                  // if the character is ]
                        value.real = strtod(temp1, NULL);                               // converts string to double
                        value.imag = 0.0;                                               // sets imaginary part to 0
                        vin.values[index] = value;                                      // adds value to the input vector
                        index++;                                                        // increases index
                        continue;                                                       // skips to the next iteration
                    }   
                    temp2[0] = t[i];                                                    // adds character                                                            
                    i++;                                                                // moves to the next character
                    int j = 1;                                                          // index of the temporary array 
                    if (t[i] == 'i') {                                                  // if the character is i
                        i++;                                                            // moves to the next character
                    }
                    while (t[i] != ']' && t[k] != '\0') {                               // while the character is not ] or null
                        temp2[j] = t[i];                                                // adds character
                        i++;                                                            // moves to the next character
                        j++;                                                            // increases index
                    }
                    temp2[j] = '\0';                                                    // adds null terminator
                    value.real = strtod(temp1, NULL);                                   // converts string to double
                    value.imag = strtod(temp2, NULL);                                   // converts string to double
                    vin.values[index] = value;                                          // adds value to the input vector
                    index++;                                                            // increases index
                }                           
            }  
            break;                                                                      // breaks the loop
        }
        while (lines[start] != '\n' && lines[start] != '\0') {                          // skips spaces and tabs
            start++;                                                                    // moves to the next character
        }
        if (lines[start] == '\n') {                                                     // if the line ends
            start++;                                                                    // moves to the next character
        }
    }
    return vin;                                                                         // returns the input vector   
}

void get_order(char* lines, char* order) {                                              // gets the order of the circuit
    int index = 0;                                                                      // index of the lines
    while (lines[index] != '\0') {                                                      // while the lines doesn't end
        char *l = &lines[index];                                                        // pointer to the current line
        if (strncmp(l, "#circ", 5) == 0) {                                              // if the line starts with #circ
            int start = 5;                                                              // starts from the 6th character  
            while (l[start] != '\t' && l[start] != ' ') {                               // skips spaces and tabs   
                start++;                                                                // moves to the next character
            }
            int end = start + 1;                                                        // starts from the next character
            while (l[end] != '\n' && l[end] != '\0') {                                  // skips spaces and tabs
                end++;                                                                  // moves to the next character
            }
            int len = end - start;                                                      // length of the string
            char str[100];                                                              // array
            strncpy(str, &l[start], len);                                               // copies the string
            str[len] = '\0';                                                            // adds null terminator
            int i = 0;                                                                  // index of the string
            int j = 0;                                                                  // index of the order
            while (str[i] != '\0') {                                                    // while the string doesn't end
                if (isalpha(str[i]) != 0) {                                             // if the character is a letter
                    order[j] = str[i];                                                  // adds character to the order
                    j++;                                                                // increases index
                }
                i++;                                                                    // moves to the next character
            }   
            order[j] = '\0';                                                            // adds null terminator       
        }
        while (lines[index] != '\n' && lines[index] != '\0') {                          // skips spaces and tabs    
            index++;                                                                    // moves to the next character
        }
        if (lines[index] == '\n') {                                                     // if the line ends   
            index++;                                                                    // moves to the next character
        }
    }
}

circuit get_matrices(char* lines, int qubits, char* order, circuit circuit, matrix m, vector row) {
    int count = 0;                                                                      // counter of matrices
    int index = 0;                                                                      // index of the lines
    while (lines[index] != '\0') {                                                      // while lines doesn't end
        char *l = &lines[index];                                                        // pointer to the current line
        if (strncmp(l, "#define", 7) == 0) {                                            // if the line starts with #define
            count++;                                                                    // increases counter
        }
        while (lines[index] != '\n' && lines[index] != '\0') {                          // skips spaces and tabs  
            index++;                                                                    // moves to the next character   
        }
        if (lines[index] == '\n') {                                                     // if the line ends 
            index++;                                                                    // moves to the next character
        }
    }
    if (count != strlen(order)) {                                                      // if the quantity isn't equal to the length of the order
        fprintf(stderr, "File format not valid\n");                                    // error
        return circuit;                                                                // returns circuit
    }
    else {                                                                             // else
        int i = 0;                                                                     // index of the lines
        int j = 0;
        while (lines[i] != '\0') {                                                     // while lines doesn't end
            char *l = &lines[i];                                                       // pointer to the current line
            if (strncmp(l, "#define", 7) == 0) {                                       // if the line starts with #define
                int start = 8;                                                         // starts from the 9th character
                while (l[start] == ' ' || l[start] == '\t') {                          // skips spaces or tabs
                    start++;                                                           // moves to the next character 
                }
                int end = start + 1;                                                   // starts from the next character
                while (l[end] != ' ' && l[end] != '\t') {                              // skips spaces and tabs       
                    end++;                                                             // moves to the next character     
                }
                int len = end - start;                                                 // length of the string
                char str[100];                                                         // array
                strncpy(str, &l[start], len);                                          // copies the string
                str[len] = '\0';                                                       // adds null terminator

                if (strlen(str) == 1 && str[0] == order[j]) {                          // if the order matches the string
                    int s = end;                                                       // starts from the next character
                    while (l[s] != '[' && l[s] != '\0') {                              // skips spaces, tabs and (                     
                        s++;                                                           // moves to the next character         
                    }
                    s++;
                    int e = s;                                                         // starts from the next character
                    while (l[e] != ']' && l[e] != '\0') {                              // while the character is not )
                        e++;                                                           // moves to the next character       
                    }
                    int mat_l = e - s;                                                 // length of the matrix
                    char mat[100];                                                     // array for the matrix
                    strncpy(mat, &l[s], mat_l);                                        // copies the matrix
                    mat[mat_l] = '\0';                                                 // adds null terminator
                    int count_r = 0;                                                   // counter of rows       
                    char *p_r;                                                         // pointer for strtok_r           
                    char *token_r = strtok_r(mat, ")", &p_r);                          // splits the matrix into rows              
                    char *tokens_r[100];                                               // array of tokens for rows
                    int rows = 0;                                                      // counter of rows
                    while (token_r != NULL) {                                          // while there are tokens  
                        while (*token_r == ' ' || *token_r == '(') {
                            token_r++;
                        }     
                        tokens_r[count_r] = token_r;                                   // adds token to the array              
                        count_r++;                                                     // increases counter
                        rows++;                                                        // increases rows          
                        token_r = strtok_r(NULL, ")", &p_r);                           // gets the next token             
                    }
                    if (rows != (int)pow(2, qubits)) {                                 // if the number of rows is not 2^qubits              
                        fprintf(stderr, "File format not valid\n");                    // error        
                        return circuit;                                                // returns circuit    
                    }
                    else {                                                             // else                                               
                        for (int k = 0; k < rows; k++) {                               // while k is less than rows
                            char *r = tokens_r[k];                                     // pointer to the current row
                            int count_c = 0;                                           // counter of columns
                            char *p_c;                                                 // pointer for strtok_r
                            char *token_c = strtok_r(r, ",", &p_c);                    // splits the row into columns
                            char *tokens_c[100];                                       // array of tokens for columns
                            int columns = 0;                                           // counter of columns
                            while (token_c != NULL) {                                  // while there are tokens   
                                tokens_c[count_c] = token_c;                           // adds token to the array                  
                                count_c++;                                             // increases counter
                                columns++;                                             // increases columns             
                                token_c = strtok_r(NULL, ",", &p_c);                   // gets the next token                   
                            }
                            if (columns != rows) {                                     // if the number of columns is not the number of rows
                                fprintf(stderr, "File format not valid\n");            // error
                                return circuit;                                        // returns circuit
                            }
                            else {                                                     // else
                                //complex c;                                             // initializes complex number
                                for (int y = 0; y < columns; y++) {
                                    char *temp = tokens_c[y];
                                    printf("temp: %s\n", temp);                                     
                                }
                            }                            
                        }
                    }
                    j++;                                                               // moves to the next character in the order
                    if (order[j] == '\0') {                                            // if the order ends
                        return circuit;                                                // returns circuit
                    }                   
                }
                while (lines[i] != '\n' && lines[i] != '\0') {                          // skips spaces and tabs
                    i++;                                                                // moves to the next character
                }
                if (lines[i] == '\n') {                                                 // if the line ends
                    i++;                                                                // moves to the next character
                }
            }
            else {                                                                      // if the line doesn't start with #define
                i++;                                                                    // moves to the next character
            }
        }
    }
    return circuit;                                                                     // returns circuit
}