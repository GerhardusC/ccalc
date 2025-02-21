#ifndef TOKENISE_H_INCLUDED
#define TOKENISE_H_INCLUDED

enum TokenKind {
    NUM,
    SYMBOL,
    INVALID,
};

struct Token {
    struct Token *head;
    struct Token *next;
    char val[32];
    enum TokenKind kind;
};

enum RespondToNumCharOutcome {
    NOT_A_NUMBER,
    CONTINUE,
    RETURN,
};

int check_valid_character(char symbol);

struct Token* create_head_token(char val[], enum TokenKind kind);
struct Token* create_token(char val[], enum TokenKind kind);
struct Token* tokenise_input(char *input);

enum RespondToNumCharOutcome respond_to_num_char(char curr, char next, char *current_tok, int *cur_iter, int *cur_len, struct Token *last_token);

void insert_token_after(struct Token* target_node, struct Token* node_to_insert);
void insert_staged_tokens(char *num_contents, struct Token **last_token, char curr);
void print_token_list(struct Token *head);

#endif