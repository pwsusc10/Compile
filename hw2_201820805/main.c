#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lex.yy.c"

#define max_len 100
#define id_len 11

// token
typedef struct
{
  char data[11];
  enum number type;
} Token;

// simbol
typedef struct
{
  char name[11];
  enum number type;
  char value[11];
} Simbol;

Token cur;
Token next;
Token token;
Simbol *Simbol_table;
int simbol_num = 0;
int n = 0;

// Symbol_table에 있나 check
Simbol check(char *name)
{
  Simbol temp;
  for (int i = 0; i < simbol_num; i++)
  {
    // 있다면
    if (strcmp(Simbol_table[i].name, name) == 0)
    {
      strcpy(temp.name, Simbol_table[simbol_num].name);
      temp.type = Simbol_table[simbol_num].type;
      strcpy(temp.value, Simbol_table[simbol_num].value);

      return temp;
    }
  }
  // 없다면
  return temp;
}

// function
void handle_PLUS();
void handle_SUB();
void handle_MUL();
void handle_DIV();
void handle_MOD();

// 시작
void express()
{
  if (token.type == SYMBOL)
  {
    printf("name\ttype\tvalue\n");
    for (int i = 0; i < simbol_num; i++)
    {
      printf("%s\t%s\t%s\n", Simbol_table[i].name, Simbol_table[i].type, Simbol_table[i].value);
    }
    return;
  }
  else if (token.type == IDEN)
  {
    Simbol temp = check(token.data);
    // simbol이 없다면
    if (strcmp(temp.name, "") == 0)
    {
      strcpy(Simbol_table[simbol_num].name, yytext);
      strcpy(Simbol_table[simbol_num].type, IDEN);
      strcpy(Simbol_table[simbol_num].value, "value");
      simbol_num++;
    }
    // 있다면
    else
    {
      printf("exist\n");
    }
  }
  else if (token.type == NUM)
  {
    strcpy(cur.data, token.data);
    cur.type = token.type;

    token.type = yylex();
    strcpy(token.data, yytext);

    switch (token.type)
    {
    case ADD:
      handle_PLUS();
      break;
    case SUB:
      handle_SUB();
      break;
    case MUL:
      handle_MUL();
      break;
    case DIV:
      handle_DIV();
      break;
    case MOD:
      handle_MOD();
      break;
    default:
      break;
    }
    return;
  }
  else if (token.type == REAL)
  {
    strcpy(cur.data, token.data);
    cur.type = token.type;

    token.type = yylex();
    strcpy(token.data, yytext);

    switch (token.type)
    {
    case ADD:
      handle_PLUS();
      break;
    case SUB:
      handle_SUB();
      break;
    case MUL:
      handle_MUL();
      break;
    case DIV:
      handle_DIV();
      break;
    case MOD:
      handle_MOD();
      break;
    default:
      break;
    }
    return;
  }
}

void handle_PLUS()
{
  token.type = yylex();
  strcpy(token.data, yytext);

  if (cur.type == NUM)
  {
    if (token.type == NUM)
    {
      int a = atoi(cur.data) + atoi(token.data);
      sprintf(cur.data, "%d", a);
      strcpy(token.data, cur.data);
      token.type = cur.type;
      express();
      return;
    }
    else
    {
      double a = atoi(cur.data) + atof(token.data);
      sprintf(cur.data, "%f", a);
      strcpy(token.data, cur.data);
      token.type = cur.type;
      express();
      return;
    }
  }
  else
  {
    if (token.type == NUM)
    {
      double a = atof(cur.data) + atoi(token.data);
      sprintf(cur.data, "%f", a);
      strcpy(token.data, cur.data);
      token.type = cur.type;
      express();
      return;
    }
    else
    {
      double a = atof(cur.data) + atof(token.data);
      sprintf(cur.data, "%f", a);
      strcpy(token.data, cur.data);
      token.type = cur.type;
      express();
      return;
    }
  }
}

void handle_SUB()
{
  token.type = yylex();
  strcpy(token.data, yytext);

  if (cur.type == NUM)
  {
    if (token.type == NUM)
    {
      int a = atoi(cur.data) - atoi(token.data);
      sprintf(cur.data, "%d", a);
      strcpy(token.data, cur.data);
      token.type = cur.type;
      express();
      return;
    }
    else
    {
      double a = atoi(cur.data) - atof(token.data);
      sprintf(cur.data, "%f", a);
      strcpy(token.data, cur.data);
      token.type = cur.type;
      express();
      return;
    }
  }
  else
  {
    if (token.type == NUM)
    {
      double a = atof(cur.data) - atoi(token.data);
      sprintf(cur.data, "%f", a);
      strcpy(token.data, cur.data);
      token.type = cur.type;
      express();
      return;
    }
    else
    {
      double a = atof(cur.data) - atof(token.data);
      sprintf(cur.data, "%f", a);
      strcpy(token.data, cur.data);
      token.type = cur.type;
      express();
      return;
    }
  }
}

void handle_MUL()
{
  token.type = yylex();
  strcpy(token.data, yytext);

  if (cur.type == NUM)
  {
    if (token.type == NUM)
    {
      int a = atoi(cur.data) * atoi(token.data);
      sprintf(cur.data, "%d", a);
      strcpy(token.data, cur.data);
      token.type = cur.type;
      express();
      return;
    }
    else
    {
      double a = atoi(cur.data) * atof(token.data);
      sprintf(cur.data, "%f", a);
      strcpy(token.data, cur.data);
      token.type = cur.type;
      express();
      return;
    }
  }
  else
  {
    if (token.type == NUM)
    {
      double a = atof(cur.data) * atoi(token.data);
      sprintf(cur.data, "%f", a);
      strcpy(token.data, cur.data);
      token.type = cur.type;
      express();
      return;
    }
    else
    {
      double a = atof(cur.data) * atof(token.data);
      sprintf(cur.data, "%f", a);
      strcpy(token.data, cur.data);
      token.type = cur.type;
      express();
      return;
    }
  }
}

void handle_DIV()
{
  token.type = yylex();
  strcpy(token.data, yytext);

  if (cur.type == NUM)
  {
    if (token.type == NUM)
    {
      int a = atoi(cur.data) / atoi(token.data);
      sprintf(cur.data, "%d", a);
      strcpy(token.data, cur.data);
      token.type = cur.type;
      express();
      return;
    }
    else
    {
      double a = atoi(cur.data) / atof(token.data);
      sprintf(cur.data, "%f", a);
      strcpy(token.data, cur.data);
      token.type = cur.type;
      express();
      return;
    }
  }
  else
  {
    if (token.type == NUM)
    {
      double a = atof(cur.data) / atoi(token.data);
      sprintf(cur.data, "%f", a);
      strcpy(token.data, cur.data);
      token.type = cur.type;
      express();
      return;
    }
    else
    {
      double a = atof(cur.data) / atof(token.data);
      sprintf(cur.data, "%f", a);
      strcpy(token.data, cur.data);
      token.type = cur.type;
      express();
      return;
    }
  }
}

void handle_MOD()
{
  token.type = yylex();
  strcpy(token.data, yytext);

  if (cur.type == NUM)
  {
    if (token.type == NUM)
    {
      int a = atoi(cur.data) % atoi(token.data);
      sprintf(cur.data, "%d", a);
      strcpy(token.data, cur.data);
      token.type = cur.type;
      express();
      return;
    }
    else
    {
      printf("error 실수의 나머지는 구할 수 없습니다.\n");
      token.type = ENDFILE;
      return;
    }
  }
  else
  {
    printf("error 실수의 나머지는 구할 수 없습니다.\n");
    token.type = ENDFILE;
    return;
  }
}

int main()
{
  Simbol_table = malloc(sizeof(Simbol) * 11);
  printf("start\n");

  // ctrl + d가 들어올 때 까지 반복.
  while ((token.type = yylex()) != ENDFILE)
  {
    // 초기화
    strcpy(cur.data, "");
    cur.type = 0;

    // 토큰에 저장
    strcpy(token.data, yytext);

    express();

    printf("%s\n", cur.data);
  }

  // 끝.
  yywrap();
  {
    printf("End of FLEX\n");
    return 1;
  }
}