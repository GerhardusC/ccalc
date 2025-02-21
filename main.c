#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

// ENUMS
// TOKENISING
enum TokenKind {
    NUM,
    SYMBOL,
    INVALID,
};

// PARSING

// STRUCT DEFS
// TOKENISING
struct Token {
    struct Token *head;
    struct Token *next;
    char val[32];
    enum TokenKind kind;
};

// PARSING
struct TreeNode {
    struct TreeNode *root;
    struct TreeNode *children;
    int depth;
    // TODO!

};

// DECLARATIONS
// TOKENISING
int check_valid_character(char symbol);

struct Token* create_head(char val[], enum TokenKind kind);
struct Token* create_node(char val[], enum TokenKind kind);
struct Token* tokenise_input(char *input);

void insert_after(struct Token* target_node, struct Token* node_to_insert);
void print_list(struct Token *head);

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

// TOKENISING...
int check_valid_character(char symbol){
    switch (symbol){
        case '(':
        case ')':
        case '*':
        case '/':
        case '-':
        case '+':
            return 1;
        default:
            return 0;
    }
}



struct Token* create_head(char val[], enum TokenKind kind){
    struct Token *new_node = malloc(sizeof(struct Token));
    new_node->head = new_node;
    strcpy(new_node->val, val);
    new_node->kind = kind;
    new_node->next = NULL;
    return new_node;
}

struct Token* create_node(char val[], enum TokenKind kind){
    struct Token *new_node = malloc(sizeof(struct Token));
    strcpy(new_node->val, val);
    new_node->kind = kind;
    new_node->next = NULL;
    return new_node;
}

enum RespondToNumOutcome {
    NOT_A_NUMBER,
    CONTINUE,
    RETURN,
};

enum RespondToNumOutcome respond_to_number(char curr, char next, char *current_tok, int *cur_iter, int *cur_len, struct Token *last_token){
    if((int) curr >= (int) '0' && (int) curr <= (int) '9'){
        current_tok[*cur_iter] = curr;
        *cur_len = *cur_len + 1;
        *cur_iter = *cur_iter + 1;
        if(next == '\0'){
            char num_contents[*cur_len + 1];

            for(int j = 0; j < *cur_len; j++){
                num_contents[j] = current_tok[j];
                current_tok[j] = '\0';
            }
            num_contents[*cur_len] = '\0';
            struct Token *new_tok_for_num = create_node(num_contents, NUM);
            insert_after(last_token, new_tok_for_num);
            last_token = new_tok_for_num;
            return RETURN;
        }
        return CONTINUE;
    }
    return NOT_A_NUMBER;
}


void insert_staged_tokens(char *num_contents, struct Token **last_token, char curr){
    if(num_contents[0] != '\0'){
        struct Token *new_tok_for_num = create_node(num_contents, NUM);
        insert_after(*last_token, new_tok_for_num);
        *last_token = new_tok_for_num;
    }

    // create new node for token
    struct Token *new_tok_for_sym = create_node(&curr, SYMBOL);
    insert_after(*last_token, new_tok_for_sym);
    *last_token = new_tok_for_sym;
}

struct Token* tokenise_input(char *input){
    struct Token *head = create_head("head", INVALID);
    struct Token *last_token = head;

    char current_tok[32];
    int c_i = 0;
    int c_l = 0;
    int i = 0;
    while(input[i] != '\0'){
        char curr = input[i];
        i++;
        // Skip whitespace
        if(curr == ' ') continue;

        enum RespondToNumOutcome outcome = respond_to_number(curr, input[i], current_tok, &c_i, &c_l, last_token);

        switch (outcome){
            case RETURN:
                return head;
            case CONTINUE:
                continue;
            case NOT_A_NUMBER:
                break;
        }

        if(check_valid_character(curr) == 0) continue;
        // create new node for number
        char num_contents[c_l + 1];

        for(int j = 0; j < c_l; j++){
            num_contents[j] = current_tok[j];
            current_tok[j] = '\0';
        }
        num_contents[c_l] = '\0';
        c_l = 0;
        c_i = 0;

        insert_staged_tokens(num_contents, &last_token, curr);
    }
}

void insert_after(struct Token* target_node, struct Token* node_to_insert){
    node_to_insert->head = target_node->head;
    node_to_insert->next = target_node->next;
    target_node->next = node_to_insert;
}

void print_list(struct Token *head){
    struct Token *current_item = head;
    while(current_item != NULL){
        printf("%s\n", current_item->val);
        current_item = current_item->next;
    }
}

// PARSING...