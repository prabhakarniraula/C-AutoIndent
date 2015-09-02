#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/**---------naive functions to handle buffers---------*/

char* create_buffer(unsigned int size)
{
		return ((char *)calloc(size,sizeof(char)));
}

int append_buffer(char *dest_buffer,char *source,unsigned int curr_buff_size,unsigned int max_buff_size)
{
	int i=0;	

		if(max_buff_size <= (curr_buff_size + strlen(source)))
			return -1;

		while(source[i]!='\0')
		{
			dest_buffer[curr_buff_size]=source[i];
			i++;
			curr_buff_size++;
		}	

	return i;
}

FILE* copy_buffer(FILE *fp,char *buffer,unsigned int curr_buff_size)
{
	if(fp==NULL)
		return NULL;
	fwrite(buffer,sizeof(char),curr_buff_size,fp);
	
	return fp;
}

void free_buffer(char *buffer)
{
	free(buffer);
	buffer=NULL;
}
