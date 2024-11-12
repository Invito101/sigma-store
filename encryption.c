#include <stdio.h>
#include "headers.h"
#define SHIFT 3

char* encrypt(char *text) {
    static char encrypted[100];
    int i = 0;

    while (text[i] != '\0') {
        if (text[i] >= 'a' && text[i] <= 'z') {
            encrypted[i] = (text[i] - 'a' + SHIFT) % 26 + 'a';
        } else if (text[i] >= 'A' && text[i] <= 'Z') {
            encrypted[i] = (text[i] - 'A' + SHIFT) % 26 + 'A';
        } else {
            encrypted[i] = text[i]; 
        }
        i++;
    }
    encrypted[i] = '\0';
    return encrypted;
}

char* decrypt(char *text) {
    static char decrypted[100];
    int i = 0;

    while (text[i] != '\0') {
        if (text[i] >= 'a' && text[i] <= 'z') {
            decrypted[i] = (text[i] - 'a' - SHIFT + 26) % 26 + 'a';
        } else if (text[i] >= 'A' && text[i] <= 'Z') {
            decrypted[i] = (text[i] - 'A' - SHIFT + 26) % 26 + 'A';
        } else {
            decrypted[i] = text[i]; 
        }
        i++;
    }
    decrypted[i] = '\0';
    return decrypted;
}

