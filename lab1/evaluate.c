#define EVAL_C
#include "evaluate.h"
#undef EVAL_C

int evaluate(const char *src)
{
	P parser;
	P_init(&parser);

	TABLE_add(&parser.symtable, "+", TOK_PLUS);
	TABLE_add(&parser.symtable, "-", TOK_MINUS);
	TABLE_add(&parser.symtable, "*", TOK_AST);
	TABLE_add(&parser.symtable, "/", TOK_SLASH);
	TABLE_add(&parser.symtable, "**", TOK_EXP);
	TABLE_add(&parser.symtable, "log", TOK_LOG);
	TABLE_add(&parser.symtable, "lg", TOK_LOG);
	TABLE_add(&parser.symtable, "ln", TOK_LN);
	TABLE_add(&parser.symtable, "sin", TOK_SIN);
	TABLE_add(&parser.symtable, "cos", TOK_COS);
	TABLE_add(&parser.symtable, "tan", TOK_TAN);
	TABLE_add(&parser.symtable, "(", TOK_OP);
	TABLE_add(&parser.symtable, ")", TOK_CP);
	TABLE_add(&parser.symtable, "pi", TOK_PI);
	TABLE_add(&parser.symtable, "e", TOK_E);
	TABLE_add(&parser.symtable, "#^", TOK_RUP);
	TABLE_add(&parser.symtable, "#v", TOK_RDOWN);
	TABLE_add(&parser.symtable, "#-", TOK_ROUND);
	TABLE_add(&parser.symtable, "##", TOK_ROUND);

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
	evalMD(p);

	T t = getToken(p);

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
	evalE(p);

	T t = getToken(p);

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
	evalU(p);

	T t = getToken(p);

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
			case TOK_RUP:
				evalC(p);
				pushToken(p, SM_OP_RUP);
				return;
			case TOK_RDOWN:
				evalC(p);
				pushToken(p, SM_OP_RDWN);
				return;
			case TOK_ROUND:
				evalC(p);
				pushToken(p, SM_OP_RND);
				return;
			case TOK_SIN:
				evalC(p);
				pushToken(p, SM_OP_SIN);
				return;
			case TOK_COS:
				evalC(p);
				pushToken(p, SM_OP_COS);
				return;
			case TOK_TAN:
				evalC(p);
				pushToken(p, SM_OP_TAN);
				return;
			case TOK_LOG:
				evalC(p);
				pushToken(p, SM_OP_LOG);
				return;
			case TOK_LN:
				evalC(p);
				pushToken(p, SM_OP_LN);
				return;
		}
	}

	TKN_unget(&p->tokenizer);

	evalC(p);
}

void evalC(P *p)
{
	TOK tok;
	tok.type = SM_OP_PUSH;

	T t = getToken(p);

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

