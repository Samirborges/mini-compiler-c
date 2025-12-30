#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef enum
{
    TOKEN_INT,
    TOKEN_PLUS,
    TOKEN_IF,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LESS,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
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
const char *token_type_to_string(TokenType type);

const char *source;
int pos = 0;

int main()
{
    source = "if (x < 10) {\nx = x + 1;\n}";
    Token t;

    do
    {
        t = get_next_token();
        printf("Token: %s, Lexeme: '%s'\n", token_type_to_string(t.type), t.lexeme);
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
        else if (strcmp(token.lexeme, "if") == 0)
        {
            token.type = TOKEN_IF;
        }
        else
        {
            token.type = TOKEN_IDENTIFIER;
        }

        return token;
    }

    // Identificar qualquer caractere imprimível que não seja alfanumérico ou espaço
    if (ispunct(c))
    {
        // Símbolos compostos
        if (c == '<')
        {
            token.lexeme[0] = advanced();
            token.lexeme[1] = '\0';
            token.type = TOKEN_LESS;
            return token;
        }
        else if (c == '+')
        {
            token.lexeme[0] = advanced();
            token.lexeme[1] = '\0';
            token.type = TOKEN_PLUS;
            return token;
        }
        else if (c == '(')
        {
            token.lexeme[0] = advanced();
            token.lexeme[1] = '\0';
            token.type = TOKEN_LPAREN;
            return token;
        }
        else if (c == ')')
        {
            token.lexeme[0] = advanced();
            token.lexeme[1] = '\0';
            token.type = TOKEN_RPAREN;
            return token;
        }
        else if (c == '{')
        {
            token.lexeme[0] = advanced();
            token.lexeme[1] = '\0';
            token.type = TOKEN_LBRACE;
            return token;
        }
        else if (c == '}')
        {
            token.lexeme[0] = advanced();
            token.lexeme[1] = '\0';
            token.type = TOKEN_RBRACE;
            return token;
        }
    }

    // Números
    if (isdigit(c))
    {
        while (isdigit(peak()))
        {
            token.lexeme[i++] = advanced();
        }
        token.lexeme[i] = '\0';
        token.type = TOKEN_NUMBER;
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

const char *token_type_to_string(TokenType type)
{
    switch (type)
    {
    case TOKEN_INT:
        return "TOKEN_INT";
    case TOKEN_IF:
        return "TOKEN_IF";
    case TOKEN_LPAREN:
        return "TOKEN_LPAREN";
    case TOKEN_RPAREN:
        return "TOKEN_RPAREN";
    case TOKEN_LESS:
        return "TOKEN_LESS";
    case TOKEN_LBRACE:
        return "TOKEN_LBRACE";
    case TOKEN_RBRACE:
        return "TOKEN_RBRACE";
    case TOKEN_IDENTIFIER:
        return "TOKEN_IDENTIFIER";
    case TOKEN_NUMBER:
        return "TOKEN_NUMBER";
    case TOKEN_ASSIGN:
        return "TOKEN_ASSIGN";
    case TOKEN_SEMICOLON:
        return "TOKEN_SEMICOLON";
    case TOKEN_EOF:
        return "TOKEN_EOF";
    case TOKEN_ERROR:
        return "TOKEN_ERROR";
    case TOKEN_PLUS:
        return "TOKEN_PLUS";
    default:
        return "UNKNOWN_TOKEN";
    }
}
