#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "tokenise.h"

// PARSING
struct TreeNode {
    struct TreeNode *root;
    struct TreeNode *children;
    int depth;
    // TODO!

};
// -------------------- MAIN ----------------------
int main () {
    struct Token *tokens = tokenise_input("!100+2000*3(1+2)-32+(1-2-3+4592)*3");
    print_list(tokens);
    // int num = parse_int("1234651");
    // printf("%d", num);
    // int num1;
    // printf("Enter num 1: \n");
    // scanf("%d", &num1);
    // int num2;
    // printf("Enter num 2: \n");
    // scanf("%d", &num2);
    // printf("%d\n", int_pow_to_uint(num1, num2));
    // printf("%d\n", pow_to_uint(5, 4));
};

// FUNCTION DEFINITIONS



// PARSING...