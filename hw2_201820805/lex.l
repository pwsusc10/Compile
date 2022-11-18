%{
	// lex.yy.c의 앞부분에 그대로 복사되는 부분
	// 자료구조, 변수 및 상수 정의

	enum number {ENDFILE, OPEN, CLOSE, LESS, LESS_EQ, MORE, MORE_EQ, IDEN, NUM, REAL, STR, ASSIGN, ADD, SUB, MUL, DIV, MOD,COMMA, SUBSTR, AST, SYMBOL};
%}

letter [A-Za-z]
digit [0-9]

%%
EOF																			return(ENDFILE);
"("																			return(OPEN);
")"																			return(CLOSE);
"<"																			return(LESS);
"<="																		return(LESS_EQ);
">"																			return(MORE);
">="																		return(MORE_EQ);
{digit}+																return(NUM);
{digit}+("."){digit}+										return(REAL);
("\"")({letter}|{digit})*("\"")					return(STR);
"="																			return(ASSIGN);
"+"																			return(ADD);
"-"																			return(SUB);
"*"																			return(MUL);
"/"																			return(DIV);
"%"																			return(MOD);
","																			return(COMMA);
"SUB"																		return(SUBSTR);
"$ast"																	return(AST);
"$symbol"																return(SYMBOL);
({letter}|"_")({letter}|{digit}|"_")*		return(IDEN);
[\t\n]																	;
" "																			;
%%