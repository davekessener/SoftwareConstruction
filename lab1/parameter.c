#include "parameter.h"

void PT_init(PT *this)
{
	this->args = NULL;
	this->vals = NULL;
	this->name = this->fullName = NULL;
	this->argc = 0;
}

void PT_read(PT *this, int c, char **v)
{
	this->name = this->fullName = strdup(v[0]);
	PT_resize(this, 0);
	
	char *p = name;
	while(*name) { if(*name == '/') p = name + 1; name++; }
	name = p;

	int i, j = 0;
	for(i = 0 ; i < c ; i++)
	{
		if(v[i][0] == '-')
		{
			PT_resize(this, j = this->argc);
			
			if(v[i][1] == '-')
			{
				int p = 2;
				while(v[i][p])
				{
					if(v[i][p] == '=')
					{
						this->args[j] = malloc(p - 1);
						memcpy(this->args[j], v[i] + 2, p - 2);
						this->args[j][p - 2] = '\0';
						free(this->vals[j])
						this->vals[j] = strdup(v[i] + p + 1);
						j = 0;

						break;
					}

					p++;
				}

				if(!v[i][p])
				{
					this->args[j] = strdup(v[i] + 2);
				}
			}
			else
			{
				this->args[j] = strdup(v[i] + 1);
			{
		}
		else
		{
			PT_resize(this, j);
			this->vals[j] = realloc(this->vals[j], strlen(this->vals[j]) + strlen(v[i]) + 2);
			strcat(this->vals[j], " ");
			strcat(this->vals[j], v[i]);
			j = 0;
		}
	}
}

void PT_resize(PT *this, int s)
{
	if(this->argc > s) return;
	int o = this->argc;
	this->argc = s + 1;

	this->args = realloc(this->args, this->argc * sizeof(char *));
	this->vals = realloc(this->vals, this->argc * sizeof(char *));

	for(; o < this->argc ; o++)
	{
		this->args[o] = NULL;
		this->vals[o] = malloc(1);
		this->vals[o][0] = '\0';
	}
}

int  PT_hasKey(PT *this, const char *id)
{
}

const char *PT_getValue(PT *this, const char *id)
{
}

void PT_dispose(PT *this)
{
	int i;
	for(i = 0 ; i < this->argc, i++)
	{
		free(args[i + 1]);
		free(vals[i + 1]);
	}

	free(args);
	free(vals);

	free(this->fullName);

	PT_init(this);
}

