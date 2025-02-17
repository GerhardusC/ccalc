#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// ENUMS
enum TokenKind {
    NUM,
    SYMBOL,
    INVALID,
};

// STRUCT DEFS
struct Token {
    struct Token *head;
    struct Token *next;
    char val[32];
    enum TokenKind kind;
};


// DECLARATIONS
int check_valid_character(char symbol);
int parse_int(char *string);

struct Token* create_head(char val[], enum TokenKind kind);
struct Token* create_node(char *val, enum TokenKind kind);
struct Token* parse_input(char *input);

void insert_after(struct Token* target_node, struct Token* node_to_insert);
void print_list(struct Token *head);


// -------------------- MAIN ----------------------
int main () {
    // parse_input("!100+2000*3(1+2)-32");
    int num = parse_int("1234651");
    // printf("0: %d, 1: %d", (int) '0', (int) '1');
    printf("%d", num);
}

// FUNCTION DEFINITIONS

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

        amount += normalised_val * powf(10., (length - j));
    }
    return amount;
};

struct Token* create_head(char val[], enum TokenKind kind){
    struct Token *new_node = malloc(sizeof(struct Token));
    new_node->head = new_node;
    strcpy(new_node->val, val);
    new_node->kind = kind;
    new_node->next = NULL;
    return new_node;
}

struct Token* create_node(char *val, enum TokenKind kind){
    struct Token *new_node = malloc(sizeof(struct Token));
    strcpy(new_node->val, val);
    new_node->kind = kind;
    new_node->next = NULL;
    return new_node;
}

struct Token* parse_input(char *input){
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
        // Input is a number.
        if((int) curr >= (int) '0' && (int) curr <= (int) '9'){
            current_tok[c_i] = curr;
            c_l++;
            c_i++;
            if(input[i] == '\0'){
                char num_contents[c_l + 1];

                for(int j = 0; j < c_l; j++){
                    num_contents[j] = current_tok[j];
                    current_tok[j] = '\0';
                }
                num_contents[c_l] = '\0';
                struct Token *new_tok_for_num = create_node(num_contents, NUM);
                insert_after(last_token, new_tok_for_num);
                last_token = new_tok_for_num;
                return head;
            }
            continue;
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

        // create new node for number
        if(num_contents[0] != '\0'){
            struct Token *new_tok_for_num = create_node(num_contents, NUM);
            insert_after(last_token, new_tok_for_num);
            last_token = new_tok_for_num;
        }

        // create new node for token
        struct Token *new_tok_for_sym = create_node(&curr, SYMBOL);
        insert_after(last_token, new_tok_for_sym);
        last_token = new_tok_for_sym;
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
