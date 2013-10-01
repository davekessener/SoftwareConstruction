#define EVAL_C
#include "evaluate.h"
#undef EVAL_C

int evaluate(const char *src)
{
	P parser;
	P_init(&parser);

#define TADD(s,i) TABLE_add(&parser.symtable,s,i)
	TADD("+", TOK_PLUS);
	TADD("-", TOK_MINUS);
	TADD("*", TOK_AST);
	TADD("/", TOK_SLASH);
	TADD("**", TOK_EXP);
	TADD("log", TOK_LOG);
	TADD("lg", TOK_LOG);
	TADD("ln", TOK_LN);
	TADD("sin", TOK_SIN);
	TADD("cos", TOK_COS);
	TADD("tan", TOK_TAN);
	TADD("(", TOK_OP);
	TADD(")", TOK_CP);
	TADD("pi", TOK_PI);
	TADD("e", TOK_E);
	TADD("#^", TOK_RUP);
	TADD("#v", TOK_RDOWN);
	TADD("#-", TOK_ROUND);
	TADD("##", TOK_ROUND);
#undef TADD

	TKN_load(&parser.tokenizer, src);

	evalAS(&parser);

	if(*parser.tokenizer.cp)
	{
		fprintf(stderr, "ERR: Expected EOS, but found '%.16s' ...\nAbort.\n", parser.tokenizer.cp);
		P_dispose(&parser);
		return 1;
	}

	P_dispose(&parser);

	return 0;
}

void setEvalOutput(void (*fn)(const char *))
{
	if(fn != NULL)
	{
		pFn = fn;
	}
}

// # --------------------------------------------------------------------------- 

void stdEvalPrint(const char *out)
{
	printf("%s\n", out);
}

// # =========================================================================== 

void inline pushToken(P *p, int i) { TOK t; t.type = i; t.val = 0.0; P_print(p, t); }
T inline getToken(P *p) { return TKN_get(&p->tokenizer, &p->symtable); }

void evalAS(P *p)
{
	T t;

	evalMD(p);

	t = getToken(p);

	while(t.type == TAG_TAG)
	{
		if(t.data.tag == TOK_PLUS)
		{
			evalMD(p);
			pushToken(p, SM_OP_ADD);
		}
		else if(t.data.tag == TOK_MINUS)
		{
			evalMD(p);
			pushToken(p, SM_OP_SUB);
		}
		else
		{
			break;
		}
	
		t = getToken(p);
	}

	TKN_unget(&p->tokenizer);
}

void evalMD(P *p)
{
	T t;

	evalE(p);

	t = getToken(p);

	while(t.type == TAG_TAG)
	{
		if(t.data.tag == TOK_AST)
		{
			evalE(p);
			pushToken(p, SM_OP_MUL);
		}
		else if(t.data.tag == TOK_SLASH)
		{
			evalE(p);
			pushToken(p, SM_OP_DIV);
		}
		else
		{
			break;
		}
	
		t = getToken(p);
	}

	TKN_unget(&p->tokenizer);
}

void evalE(P *p)
{
	T t;

	evalU(p);

	t = getToken(p);

	if(t.type == TAG_TAG && t.data.tag == TOK_EXP)
	{
		evalE(p);
		pushToken(p, SM_OP_EXP);
	}
	else
	{
		TKN_unget(&p->tokenizer);
	}
}

void evalU(P *p)
{
	T t = getToken(p);

	if(t.type == TAG_TAG)
	{
		switch(t.data.tag)
		{
			case TOK_PLUS:
				evalTL(p);
				return;
			case TOK_MINUS:
				evalTL(p);
				pushToken(p, SM_OP_NEG);
				return;
		}
	}

	TKN_unget(&p->tokenizer);

	evalTL(p);
}

void evalTL(P *p)
{
	T t = getToken(p);

	if(t.type == TAG_TAG)
	{
		switch(t.data.tag)
		{
#define TLP(i) evalC(p);pushToken(p,i)
			case TOK_RUP:
				TLP(SM_OP_RUP);
				return;
			case TOK_RDOWN:
				TLP(SM_OP_RDWN);
				return;
			case TOK_ROUND:
				TLP(SM_OP_RND);
				return;
			case TOK_SIN:
				TLP(SM_OP_SIN);
				return;
			case TOK_COS:
				TLP(SM_OP_COS);
				return;
			case TOK_TAN:
				TLP(SM_OP_TAN);
				return;
			case TOK_LOG:
				TLP(SM_OP_LOG);
				return;
			case TOK_LN:
				TLP(SM_OP_LN);
				return;
#undef TLP
		}
	}

	TKN_unget(&p->tokenizer);

	evalC(p);
}

void evalC(P *p)
{
	T t;
	TOK tok;

	tok.type = SM_OP_PUSH;

	t = getToken(p);

	if(t.type == TAG_NONE) return;

	if(t.type == TAG_VALUE)
	{
		tok.val = t.data.val;
		P_print(p, tok);
	}
	else
	{
		if(t.data.tag == TOK_PI)
		{
			tok.val = M_PI;
			P_print(p, tok);
		}
		else if(t.data.tag == TOK_E)
		{
			tok.val = M_E;
			P_print(p, tok);
		}
		else if(t.data.tag == TOK_OP)
		{
			evalAS(p);
			t = getToken(p); 
			assert(t.type==TAG_TAG&&t.data.tag==TOK_CP);
		}
		else if(t.data.tag == TOK_CP)
		{
			TKN_unget(&p->tokenizer);
		}
		else
		{
			fprintf(stderr, "ERR: Unexpected token '%d'.\nAbort.\n", t.data.tag);
			exit(1);
		}
	}
}

// # --------------------------------------------------------------------------- 

void P_init(P *this)
{
	TABLE_init(&this->symtable);
	TKN_init(&this->tokenizer);
}

void P_print(P *this, TOK t)
{
	char buf[512];

	if(t.type == SM_OP_PUSH)
	{
		sprintf(buf, "%s %Lg", SM_OP_INS[SM_OP_PUSH], t.val);
	}
	else
	{
		sprintf(buf, "%s", SM_OP_INS[t.type]);
	}

	pFn(buf);
}

void P_dispose(P *this)
{
	TABLE_dispose(&this->symtable);
	TKN_dispose(&this->tokenizer);
}

