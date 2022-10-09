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

    // id table과 buffer table의 인덱스
    int id_idx = 1;
    int str_idx = 1;
    int buffer_idx = 0;
    int string_idx = 0;
    int token_idx = 0;
    int cnt = 0;

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
                // 뒤에 알바벳이 다시 온다면 에러 출력 다른 문자라면 token list에 추가
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
                    // 중복 체크
                    for (cnt = 0; cnt < token_idx; cnt++)
                    {
                        if ((token_list[cnt].code_num == 1) && strcmp(token_list[cnt].data, string) == 0)
                            break;
                    }
                    if (cnt == token_idx)
                    {
                        // id code
                        token_list[token_idx].code_num = 1;
                        token_list[token_idx].idx = id_idx;
                        strcpy(token_list[token_idx].name, "ID");
                        if (strlen(string) > 10)
                            string[10] = '\0';
                        strcpy(token_list[token_idx].data, string);
                        token_idx++;
                        id_idx++;

                        memset(string, 0, max_len * sizeof(char));
                        string_idx = 0;
                    }
                    else
                    {
                        memset(string, 0, max_len * sizeof(char));
                        string_idx = 0;
                    }
                }
            }

            // 2) operator
            // 처음 덧,뺄셈 연산자가 들어왔다면
            if (buffer[i] == '+' || buffer[i] == '-')
            {
                string[string_idx] = buffer[i];
                string_idx++;
                i++;

                // +0, -0에 대한 오류 처리.
                if (buffer[i] == '0' && buffer[i + 1] != '.')
                {
                    string[string_idx] = buffer[i];
                    string_idx++;
                    i++;

                    // error code
                    token_list[token_idx].code_num = 0;
                    token_list[token_idx].idx = f_line;
                    strcpy(token_list[token_idx].data, string);
                    token_idx++;
                }

                // 정수 실수 처리
                else if ((buffer[i] >= '0' && buffer[i] <= '9'))
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

                    // 소수라면
                    if (buffer[i] == '.')
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
                        // +0.30같은 뒤에 0이 붙는 에러 처리
                        if (buffer[i - 1] == '0')
                        {
                            // error code
                            token_list[token_idx].code_num = 0;
                            token_list[token_idx].idx = f_line;
                            strcpy(token_list[token_idx].data, string);
                            token_idx++;
                        }
                        else // 실수 처리
                        {
                            // token_list에 저장
                            // float code
                            token_list[token_idx].code_num = 4;
                            strcpy(token_list[token_idx].data, string);
                            strcpy(token_list[token_idx].name, "FLOAT");
                            token_idx++;
                        }
                    }
                    else // 정수라면 정수처리
                    {
                        // token_list에 저장
                        // int code
                        token_list[token_idx].code_num = 3;
                        strcpy(token_list[token_idx].data, string);
                        strcpy(token_list[token_idx].name, "INT");
                        token_idx++;
                    }
                }
                else if (buffer[i] == '.') // +.13 같은 실수 처리
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
                    // +0.30같은 뒤에 0이 붙는 에러 처리
                    if (buffer[i - 1] == '0')
                    {
                        // error code
                        token_list[token_idx].code_num = 0;
                        token_list[token_idx].idx = f_line;
                        strcpy(token_list[token_idx].data, string);
                        token_idx++;
                    }
                    else // 실수 처리
                    {
                        // token_list에 저장
                        // float code
                        token_list[token_idx].code_num = 4;
                        strcpy(token_list[token_idx].data, string);
                        strcpy(token_list[token_idx].name, "FLOAT");
                        token_idx++;
                    }
                }
                // 단순 +, - 연산자 처리
                else
                {
                    if (string[0] == '+')
                    {
                        token_list[token_idx].code_num = 2;
                        strcpy(token_list[token_idx].data, string);
                        strcpy(token_list[token_idx].name, "PLUS");
                        token_idx++;
                    }
                    else
                    {
                        token_list[token_idx].code_num = 2;
                        strcpy(token_list[token_idx].data, string);
                        strcpy(token_list[token_idx].name, "MINUS");
                        token_idx++;
                    }
                }
                memset(string, 0, max_len * sizeof(char));
                string_idx = 0;
            }
            // '/', '*' , '=', ':' operator
            else if (buffer[i] == '/')
            {

                string[string_idx] = buffer[i];
                token_list[token_idx].code_num = 2;
                strcpy(token_list[token_idx].data, string);
                strcpy(token_list[token_idx].name, "DIVISION");
                token_idx++;
                i++;

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
                i++;

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
                i++;

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
                i++;

                memset(string, 0, max_len * sizeof(char));
                string_idx = 0;
            }
            // 3) INT, FLOAT
            if ((buffer[i] >= '0' && buffer[i] <= '9') || buffer[i] == '.')
            {
                // 00, 01, 02과 같이 앞에 0이 오는 것에 대한 오류 처리.
                if (buffer[i] == '0' && (buffer[i + 1] >= '0' && buffer[i + 1] <= '9'))
                {
                    string[string_idx] = buffer[i];
                    string_idx++;
                    i++;

                    // error code
                    token_list[token_idx].code_num = 0;
                    token_list[token_idx].idx = f_line;
                    strcpy(token_list[token_idx].data, string);
                    token_idx++;
                }
                // 정수 실수 처리
                else if ((buffer[i] >= '0' && buffer[i] <= '9'))
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
                    // 소수라면
                    if (buffer[i] == '.')
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
                        // +0.30같은 뒤에 0이 붙는 에러 처리
                        if (buffer[i - 1] == '0')
                        {
                            // error code
                            token_list[token_idx].code_num = 0;
                            token_list[token_idx].idx = f_line;
                            strcpy(token_list[token_idx].data, string);
                            token_idx++;
                        }
                        else // 실수 처리
                        {
                            // token_list에 저장
                            // float code
                            token_list[token_idx].code_num = 4;
                            strcpy(token_list[token_idx].data, string);
                            strcpy(token_list[token_idx].name, "FLOAT");
                            token_idx++;
                        }
                    }
                    else // 정수라면 정수처리
                    {
                        // token_list에 저장
                        // int code
                        token_list[token_idx].code_num = 3;
                        strcpy(token_list[token_idx].data, string);
                        strcpy(token_list[token_idx].name, "INT");
                        token_idx++;
                    }
                }
                else if (buffer[i] == '.') // +.13 같은 실수 처리
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
                    // +0.30같은 뒤에 0이 붙는 에러 처리
                    if (buffer[i - 1] == '0')
                    {
                        // error code
                        token_list[token_idx].code_num = 0;
                        token_list[token_idx].idx = f_line;
                        strcpy(token_list[token_idx].data, string);
                        token_idx++;
                    }
                    else // 실수 처리
                    {
                        // token_list에 저장
                        // float code
                        token_list[token_idx].code_num = 4;
                        strcpy(token_list[token_idx].data, string);
                        strcpy(token_list[token_idx].name, "FLOAT");
                        token_idx++;
                    }
                }
                // 메모리
                memset(string, 0, max_len * sizeof(char));
                string_idx = 0;
            }
            // 4) STRING
            if (buffer[i] == '"')
            {
                string[string_idx] = buffer[i];
                string_idx++;
                i++;
                // string 끝이 나올때 까지 문자열에 담기
                while (1)
                {
                    if (buffer[i] == '\n')
                    {
                        string[string_idx] = '\\';
                        string_idx++;
                        string[string_idx] = 'n';
                        string_idx++;
                        fgets(buffer, 1000, stdin);
                        i = 0;
                    }
                    else if (buffer[i] == '\t')
                    {
                        string[string_idx] = '\\';
                        string_idx++;
                        string[string_idx] = 't';
                        string_idx++;
                        i++;
                    }
                    else if (buffer[i] == '\\') // \에 대한 오류 처리
                    {
                        token_list[token_idx].code_num = 0;
                        token_list[token_idx].idx = f_line;
                        strcpy(token_list[token_idx].data, "\\");
                        token_idx++;
                        i++;
                    }
                    else
                    {
                        string[string_idx] = buffer[i];
                        string_idx++;
                        if (buffer[i] == '"')
                        {
                            i++;
                            break;
                        }
                        i++;
                    }
                }
                // 중복 체크
                for (cnt = 0; cnt < token_idx; cnt++)
                {
                    if ((token_list[cnt].code_num == 5) && strcmp(token_list[cnt].data, string) == 0)
                        break;
                }
                if (cnt == token_idx)
                {
                    // string code
                    token_list[token_idx].code_num = 5;
                    token_list[token_idx].idx = str_idx;
                    strcpy(token_list[token_idx].name, "STRING");
                    strcpy(token_list[token_idx].data, string);
                    token_idx++;
                    str_idx++;

                    memset(string, 0, max_len * sizeof(char));
                    string_idx = 0;
                }
                else
                {
                    memset(string, 0, max_len * sizeof(char));
                    string_idx = 0;
                }
            }
            // 5) SEMICOLON
            if (buffer[i] == ';')
            {
                token_list[token_idx].code_num = 2;
                strcpy(token_list[token_idx].name, "SEMICOLON");
                strcpy(token_list[token_idx].data, ";");
                token_idx++;
                i++;
            }
            // 문장 마지막에 ';'이 없을 경우 에러처리
            if (i == (strlen(buffer) - 1) && buffer[i - 1] != ';')
            {
                // error
                token_list[token_idx].code_num = 0;
                token_list[token_idx].idx = f_line;
                strcpy(token_list[token_idx].data, "';'이 없습니다.");
                token_idx++;
            }
        }
    } while (fgets(buffer, 1000, stdin) != NULL);

    // id table
    printf("index\tids\n");
    for (int i = 0; i < token_idx; i++)
    {
        if (token_list[i].code_num == 1)
            printf("%d\t\"%s\"\n", token_list[i].idx, token_list[i].data);
    }
    // String table
    printf("index\tstrings\n");
    for (int i = 0; i < token_idx; i++)
    {
        if (token_list[i].code_num == 5)
            printf("%d\t%s\n", token_list[i].idx, token_list[i].data);
    }
    // token 출력 처리
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