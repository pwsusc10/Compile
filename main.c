#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define max_len 100
#define id_len 11

typedef struct
{
    char data[max_len];
    char name[15];
    // 0: error, 1: id, 2: operator, 3: int, 4: float, 5: string, 6: etc
    int code_num;
    int idx;

} token;

int main(void)
{
    token token_list[max_len];

    // file line number
    int f_line = 0;

    // symbol table과 buffer table의 인덱스
    int symbol_idx = 1;
    int buffer_idx = 0;
    int string_idx = 0;
    int token_idx = 0;

    char buffer[max_len];
    char string[max_len];

    memset(buffer, 0, max_len * (sizeof(char)));
    memset(string, 0, max_len * (sizeof(char)));

    fgets(buffer, 1000, stdin);

    do
    {
        f_line++;

        int i = 0;
        // 구현
        while (i < strlen(buffer))
        {
            if (buffer[i] == ' ' || buffer[i] == '\n')
                i++;
            // 1) Identifier
            // 처음 알파벳이 들어왔다면
            if ((buffer[i] >= 'A' && buffer[i] <= 'Z') || (buffer[i] >= 'a' && buffer[i] <= 'z'))
            {
                string[string_idx] = buffer[i];
                string_idx++;
                // 알파벳 다 빼주기
                while (1)
                {
                    i++;
                    if ((buffer[i] >= 'A' && buffer[i] <= 'Z') || (buffer[i] >= 'a' && buffer[i] <= 'z'))
                    {
                        string[string_idx] = buffer[i];
                        string_idx++;
                    }
                    else
                        break;
                }
                // 알파벳 다음 숫자가 온다면
                if ((buffer[i] >= '0' && buffer[i] <= '9'))
                {
                    string[string_idx] = buffer[i];
                    string_idx++;
                    // 숫자 다 빼주기
                    while (1)
                    {
                        i++;
                        if ((buffer[i] >= '0' && buffer[i] <= '9'))
                        {
                            string[string_idx] = buffer[i];
                            string_idx++;
                        }
                        else
                            break;
                    }
                }
                // 뒤에 알바벳이 다시 온다면 에러 출력 다른 문자라면 symbol table에 추가
                if ((buffer[i] >= 'A' && buffer[i] <= 'Z') || (buffer[i] >= 'a' && buffer[i] <= 'z'))
                {
                    // error
                    token_list[token_idx].code_num = 0;
                    token_list[token_idx].idx = f_line;
                    strcpy(token_list[token_idx].data, string);
                    token_idx++;

                    // string 초기화
                    memset(string, 0, max_len * sizeof(char));
                    string_idx = 0;
                }
                else
                {
                    // id code
                    token_list[token_idx].code_num = 1;
                    token_list[token_idx].idx = symbol_idx;
                    strcpy(token_list[token_idx].name, "ID");
                    strcpy(token_list[token_idx].data, string);
                    token_idx++;
                    symbol_idx++;

                    memset(string, 0, max_len * sizeof(char));
                    string_idx = 0;
                }
            }

            // 2) operator
            // 처음 덧,뺄셈 연산자가 들어왔다면
            if (buffer[i] == '+' || buffer[i] == '-')
            {
                string[string_idx] = buffer[i];
                string_idx++;
                i++;

                if ((buffer[i] >= '0' && buffer[i] <= '9'))
                {
                    string[string_idx] = buffer[i];
                    string_idx++;
                    // 숫자 다 빼주기
                    while (1)
                    {
                        i++;
                        if ((buffer[i] >= '0' && buffer[i] <= '9'))
                        {
                            string[string_idx] = buffer[i];
                            string_idx++;
                        }
                        else
                            break;
                    }

                    // token_list에 저장
                    // int code
                    token_list[token_idx].code_num = 3;
                    strcpy(token_list[token_idx].data, string);
                    strcpy(token_list[token_idx].name, "INT");
                    token_idx++;

                    memset(string, 0, max_len * sizeof(char));
                    string_idx = 0;
                }
                else
                {
                    if (string[0] == '+')
                    {
                        token_list[token_idx].code_num = 2;
                        strcpy(token_list[token_idx].data, string);
                        strcpy(token_list[token_idx].name, "PLUS");
                        token_idx++;

                        memset(string, 0, max_len * sizeof(char));
                        string_idx = 0;
                    }
                    else
                    {
                        token_list[token_idx].code_num = 2;
                        strcpy(token_list[token_idx].data, string);
                        strcpy(token_list[token_idx].name, "MINUS");
                        token_idx++;

                        memset(string, 0, max_len * sizeof(char));
                        string_idx = 0;
                    }
                }
            }
            // '/', '*' operator
            else if (buffer[i] == '/')
            {

                string[string_idx] = buffer[i];
                token_list[token_idx].code_num = 2;
                strcpy(token_list[token_idx].data, string);
                strcpy(token_list[token_idx].name, "DIVISION");
                token_idx++;

                memset(string, 0, max_len * sizeof(char));
                string_idx = 0;
            }
            else if (buffer[i] == '*')
            {

                string[string_idx] = buffer[i];
                token_list[token_idx].code_num = 2;
                strcpy(token_list[token_idx].data, string);
                strcpy(token_list[token_idx].name, "MULTI");
                token_idx++;

                memset(string, 0, max_len * sizeof(char));
                string_idx = 0;
            }
            else if (buffer[i] == '=')
            {

                string[string_idx] = buffer[i];
                token_list[token_idx].code_num = 2;
                strcpy(token_list[token_idx].data, string);
                strcpy(token_list[token_idx].name, "ASSIGN");
                token_idx++;

                memset(string, 0, max_len * sizeof(char));
                string_idx = 0;
            }
            else if (buffer[i] == ':')
            {

                string[string_idx] = buffer[i];
                token_list[token_idx].code_num = 2;
                strcpy(token_list[token_idx].data, string);
                strcpy(token_list[token_idx].name, "COLON");
                token_idx++;

                memset(string, 0, max_len * sizeof(char));
                string_idx = 0;
            }
        }
    } while (fgets(buffer, 1000, stdin) != NULL);

    for (int i = 0; i < token_idx; i++)
    {
        switch (token_list[i].code_num)
        {
        // error
        case 0:
            printf("Error. line %d      %s\n", token_list[i].idx, token_list[i].data);
            break;
        case 1:
            printf("<%s, %d>            %s\n", token_list[i].name, token_list[i].idx, token_list[i].data);
            break;
        case 2:
            printf("<%s, >              %s\n", token_list[i].name, token_list[i].data);
            break;
        case 3:
            printf("<%s, %s>            %s\n", token_list[i].name, token_list[i].data, token_list[i].data);
            break;
        case 4:
            printf("<%s, %s>            %s\n", token_list[i].name, token_list[i].data, token_list[i].data);
            break;
        case 5:
            printf("<%s, %d>            %s\n", token_list[i].name, token_list[i].idx, token_list[i].data);
            break;
        }
    }
    return 0;
}