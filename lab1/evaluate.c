#include "evaluate.h"

int evaluate(const char *src, long double *r)
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

	TKN_load(&parser.tokenizer, src);

	evalAS(&parser);

	if(*parser.tokenizer.cp)
	{
		fprintf(stderr, "ERR: Expected EOS, but found '%.16s' ...\nAbort.\n", parser.tokenizer.cp);
		return 1;
	}

	DS stack;
	DS_init(&stack);

	if(P_eval(&parser, &stack))
	{
		return 2;
	}

	if(stack.i != 1)
	{
		return 3;
	}

	*r = DS_pop(&stack);

	return 0;
}

// # =========================================================================== 

void inline pushToken(P *p, int i) { TOK t; t.type = i; t.val = 0.0; P_push(p, t); }
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
			pushToken(p, OP_ADD);
		}
		else if(t.data.tag == TOK_MINUS)
		{
			evalMD(p);
			pushToken(p, OP_SUB);
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
			pushToken(p, OP_MUL);
		}
		else if(t.data.tag == TOK_SLASH)
		{
			evalE(p);
			pushToken(p, OP_DIV);
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
		pushToken(p, OP_EXP);
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
				pushToken(p, OP_NEG);
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
			case TOK_SIN:
				evalC(p);
				pushToken(p, OP_SIN);
				return;
			case TOK_COS:
				evalC(p);
				pushToken(p, OP_COS);
				return;
			case TOK_TAN:
				evalC(p);
				pushToken(p, OP_TAN);
				return;
			case TOK_LOG:
				evalC(p);
				pushToken(p, OP_LOG);
				return;
			case TOK_LN:
				evalC(p);
				pushToken(p, OP_LN);
				return;
		}
	}

	TKN_unget(&p->tokenizer);

	evalC(p);
}

void evalC(P *p)
{
	TOK tok;
	tok.type = OP_CONST;

	T t = getToken(p);

	if(t.type == TAG_NONE) return;

	if(t.type == TAG_VALUE)
	{
		tok.val = t.data.val;
		P_push(p, tok);
	}
	else
	{
		if(t.data.tag == TOK_PI)
		{
			tok.val = M_PI;
			P_push(p, tok);
		}
		else if(t.data.tag == TOK_E)
		{
			tok.val = M_E;
			P_push(p, tok);
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
	this->tkns = NULL;
	this->c    = 0;

	TABLE_init(&this->symtable);
	TKN_init(&this->tokenizer);
}

int  P_eval(P *this, DS *stack)
{
	long double v1, v2;

	while(this->c > 0)
	{
		TOK t = P_poll(this);

		if(t.type == OP_CONST)
		{
			DLOG("%s %Lg\n", OP_LOGS[OP_CONST], t.val);
			DS_push(stack, t.val);
		}
		else
		{
			DLOG("%s\n", OP_LOGS[t.type]);
			v1 = DS_pop(stack);

			switch(t.type)
			{
				case OP_NEG:
					DS_push(stack, -v1);
					break;
				case OP_LOG:
					DS_push(stack, (long double) log10((double) v1));
					break;
				case OP_LN:
					DS_push(stack, (long double) log((double) v1));
					break;
				case OP_SIN:
					while(v1 > 2.0 * M_PI) v1 -= 2.0 * M_PI;
					while(v1 < 0.0) v1 += 2.0 * M_PI;
					DS_push(stack, (long double) sin((double) v1));
					break;
				case OP_COS:
					while(v1 > 2.0 * M_PI) v1 -= 2.0 * M_PI;
					while(v1 < 0.0) v1 += 2.0 * M_PI;
					DS_push(stack, (long double) cos((double) v1));
					break;
				case OP_TAN:
					while(v1 > 2.0 * M_PI) v1 -= 2.0 * M_PI;
					while(v1 < 0.0) v1 += 2.0 * M_PI;
					DS_push(stack, (long double) tan((double) v1));
					break;
				default:
					v2 = DS_pop(stack);
					
					switch(t.type)
					{
						case OP_ADD:
							DS_push(stack, v2 + v1);
							break;
						case OP_SUB:
							DS_push(stack, v2 - v1);
							break;
						case OP_MUL:
							DS_push(stack, v2 * v1);
							break;
						case OP_DIV:
							DS_push(stack, v2 / v1);
							break;
						case OP_EXP:
							DS_push(stack, (long double) pow((double) v2, (double) v1));
							break;
						default:
							return 1;
					}
			}
		}
	}

	return 0;
}

void P_push(P *this, TOK t)
{
	this->tkns = realloc(this->tkns, ++this->c * sizeof(T));
	this->tkns[this->c - 1] = t;
}

TOK	 P_poll(P *this)
{
	assert(this->c>0);

	TOK t = this->tkns[0];
	memmove(this->tkns, this->tkns + 1, --this->c * sizeof(T));
	return t;
}

void P_dispose(P *this)
{
	free(this->tkns);
	TABLE_dispose(&this->symtable);
	TKN_dispose(&this->tokenizer);

	P_init(this);
}

