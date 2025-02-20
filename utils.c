#include "utils.h"

int pow_to_uint(int base, int exponent){
    if(exponent == 0){
        return 1;
    }
    if(exponent < 0){
        return 0;
    }
    return mul_self(base, exponent, 1);

};

int mul_self(int base, int exp,  int acc){
    if(exp <= 0){
        return acc;
    }
    return mul_self(base, exp - 1, acc * base);
}

int parse_int(char *string){
    int amount = 0;
    int length = 0;
    // Count length.
    while(string[length] != '\0'){
        length++;
    }
    // Calculate from other end.
    for(int j = length; j > 0; j--){
        char current = string[j - 1];
        int normalised_val = ((int) current - ((int) '0'));

        amount += normalised_val * pow_to_uint(10, (length - j));
    }
    return amount;
};

