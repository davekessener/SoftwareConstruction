#include "tokenizer.h"

void TKN_init(TKN *this)
{
	this->src = NULL;
	this->cp  = NULL;
	this->pp  = NULL;
}

void TKN_load(TKN *this, const char *init)
{
	this->src = strdup(init);
	this->cp  = this->src;
	this->pp  = this->src;

	int i, l;
	for(i = 0, l = strlen(this->src) ; i < l ; i++)
	{
		if(this->src[i] >= 'A' && this->src[i] <= 'Z')
		{
			this->src[i] -= 'A' - 'a';
		}
	}

	deleteWhitespace(this->src);
}

T	 TKN_get(TKN *this, TABLE *table)
{
	assert(this->src!=NULL);
	assert(this->cp!=NULL);
	assert(table!=NULL);

	this->pp = this->cp;
	
	T t;
	t.type = TAG_NONE;

	char c = *this->cp;
	char buf[T_BUF_SIZE], *tmp;
	int p = 0, r;
	
	if(c == '\0') return t;

	if(c >= '0' && c <= '9')
	{
		t.type = TAG_VALUE;
		t.data.val = evalNumber(&this->cp);
	}
	else
	{
		while(c)
		{
			buf[p++] = c;
			buf[p] = '\0';
	
			r = TABLE_find(table, buf);

			if(r == 0)
			{
				assert(t.type==TAG_TAG);
				
				this->cp = tmp;
	
				break;
			}
			else if(r == -1)
			{
			}
			else if(r > 0)
			{
				t.type = TAG_TAG;
				t.data.tag = r;
				tmp = this->cp + 1;
			}
	
			c = *++this->cp;
		}
	}

	return t;
}

void TKN_unget(TKN *this)
{
	this->cp = this->pp;
}

void TKN_dispose(TKN *this)
{
	free(this->src);
}

// # ==========================================================================

void TABLE_init(TABLE *this)
{
	this->ids  = NULL;
	this->vals = NULL;
	this->c    = 0;
}

void TABLE_add(TABLE *this, const char *id, int v)
{
	this->ids = realloc(this->ids, ++this->c * sizeof(char *));
	this->vals = realloc(this->vals, this->c * sizeof(int));

	this->ids[this->c - 1]  = strdup(id);
	this->vals[this->c - 1] = v;
}

int  TABLE_find(TABLE *this, const char *id)
{
	int r = 0;

	int i;
	for(i = 0 ; i < this->c ; i++)
	{
		if(strcmp(this->ids[i], id) == 0)
		{
			r = this->vals[i];
			break;
		}
		else if(memcmp(this->ids[i], id, strlen(id)) == 0)
		{
			r = -1;
		}
	}

	return r;
}

void TABLE_dispose(TABLE *this)
{
	int i;
	for(i = 0 ; i < this->c ; i++)
	{
		free(this->ids[i]);
	}

	free(this->ids);
	free(this->vals);

	TABLE_init(this);
}

// # ==========================================================================

int inline isIn(const char *l, char c) { while(*l) { if(*l == c) return 1; l++; } return 0; }

long double evalNumber(char **src)
{
	const char *digits = (const char *) "fedcba9876543210";
	char *line = *src;

	long double val = 0.0;
	int base = 10, off = 1;
	int dec = 0, f = 0;

	char c = *line++;

	if(c == '0')
	{
		c = *line++;
		if(c == 'x')
		{
			c = *line++;
			base = 16;
		}
		else if(c == 'b')
		{
			c = *line++;
			base = 2;
		}
		else if(c != '.')
		{
			base = 8;
		}
		else
		{
			f = 1;
		}
	}

	while(c && (c == '.' || isIn(digits + 16 - base, c)))
	{
		if(c == '.')
		{
			dec = 1;
			c = *line++;
			continue;
		}

		int v = c;
		if(c >= '0' && c <= '9') v -= '0';
		if(c >= 'a' && c <= 'f') v -= 'a' - 10;

		assert(v<16);

		if(dec)
		{
			off *= base;
			val += (long double)v / off;
		}
		else
		{
			val *= base;
			val += v;
		}

		f = 1;
		c = *line++;
	}

	assert(f);

	*src = line - 1;

	return val;
}

void deleteWhitespace(char *src)
{
	int i, p = 0, l = strlen(src) + 1;
	char *tmp = malloc(strlen(src) + 1);

	for(i = 0 ; i < l ; i++)
	{
		if(src[i] != ' ' && src[i] != '\t' && src[i] != '\n')
		{
			tmp[p++] = src[i];
		}
	}

	strncpy(src, tmp, l);
	free(tmp);
}

