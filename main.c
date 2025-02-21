#include <stdio.h>
#include <stdlib.h>
#include "tokenise.h"
// #include "utils.h"

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
    print_token_list(tokens);
};
