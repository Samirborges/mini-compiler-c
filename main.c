#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef enum
{
    TOKEN_INT,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_ASSIGN,
    TOKEN_SEMICOLON,
    TOKEN_EOF,
    TOKEN_ERROR
} TokenType;

typedef struct
{
    TokenType type;
    char lexeme[64];
} Token;

Token get_next_token();
char peak();
char advanced();

const char *source;
int pos = 0;

int main()
{
    source = "int x = 42;";
    Token t;

    do
    {
        t = get_next_token();
        printf("Token: %d, Lexeme: '%s'\n", t.type, t.lexeme);
    } while (t.type != TOKEN_EOF);

    return 0;
}

Token get_next_token()
{
    Token token;
    char c;
    int i = 0;

    // ignora os espaços
    while ((c = peak()) == ' ' || c == '\t' || c == '\n')
    {
        advanced();
    }

    // Comentários
    if (c == '/' && source[pos++] == '/')
    {
        advanced();
        advanced();
        while (peak() != '\n' && peak() != '\0')
        {
            advanced();
        }
        return get_next_token();
    }

    // Fim da string;
    if (c == '\0')
    {
        token.type = TOKEN_EOF;
        strcpy(token.lexeme, "");
        return token;
    }

    // Identificadores ou palavra-chave
    if (isalpha(c))
    {
        while (isalnum(peak()))
        {
            token.lexeme[i++] = advanced();
        }

        token.lexeme[i] = '\0';
        if (strcmp(token.lexeme, "int") == 0)
        {
            token.type = TOKEN_INT;
        }
        else
        {
            token.type = TOKEN_IDENTIFIER;
        }

        return token;
    }

    // Números
    if (isdigit(c))
    {
        while (isdigit(peak()))
        {
            token.lexeme[i++] = advanced();
        }
        token.lexeme[i] = '\0';
        token.type = TOKEN_INT;
        return token;
    }

    // Símbolos simples
    c = advanced();
    token.lexeme[0] = c;
    token.lexeme[1] = '\0';

    switch (c)
    {
    case '=':
        token.type = TOKEN_ASSIGN;
        return token;

    case ';':
        token.type = TOKEN_SEMICOLON;
        return token;
    }

    token.type = TOKEN_ERROR;
    return token;
}

char peak()
{
    return source[pos];
}

char advanced()
{
    return source[pos++];
}
