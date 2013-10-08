#include "tokenizer.h"

void TKN_init(TKN *this)
{
	this->src = NULL;
	this->cp  = NULL;
	this->pp  = NULL;
}

void TKN_load(TKN *this, const char *init)
{
	int i, l;

	this->src = strdup(init);
	this->cp  = this->src;
	this->pp  = this->src;

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
	T t;
	char c, buf[T_BUF_SIZE], *tmp;
	int p = 0, r;

	assert(this->src!=NULL);
	assert(this->cp!=NULL);
	assert(table!=NULL);

	this->pp = this->cp;
	
	t.type = TAG_NONE;

	c = *this->cp;
	
	if(c == '\0') return t;

	if(c >= '0' && c <= '9')
	{
		t.type = TAG_VALUE;
		t.data.val = evalNumber((const char **) &this->cp);
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
				if(t.type == TAG_TAG)
				{
					this->cp = tmp;
				}
	
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

