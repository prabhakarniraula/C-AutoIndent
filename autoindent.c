#include "buffer.c"
#include "token.c"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


/**--------reads file in buffer passes to compare tokens and saves it in a file -----------*/


int main(int argc,char *argv[])
{
	unsigned int ans,max_buff_size=0,curr_buff_size=0;
	char *buffer=NULL,*ans_buffer=NULL,
	     *new_filename=(char *)calloc(20,sizeof(char)),
	     *temp=(char *)calloc(2000,sizeof(char)),
	     *temp1=(char *)calloc(3,sizeof(char));
	FILE *source_fp=NULL;
	char temp_char[2]="a";	

	if(argc<2 || argc>2)
	{
		printf("\nUSAGE : ./a.out Filename");	
		exit(0);
	}

	source_fp=fopen(argv[1],"r");

	if(source_fp==NULL)
	{
		printf("\nERROR Opening File......!!!");
		exit(1);
	}

	if(fseek(source_fp,0L,SEEK_END)==0)
	{
		max_buff_size=ftell(source_fp);
		if(max_buff_size==-1)
		{
			printf("\n ERROR Occured.....!!!");
			exit(2);
		}	
	}

	buffer=create_buffer(max_buff_size);

	if (fseek(source_fp, 0L, SEEK_SET) != 0)
	{
		printf("\n ERROR Occured......!!!");
		exit(3);
	}

	while(feof(source_fp)==0)
	{
		fscanf(source_fp,"%s",temp);
		strcat(temp," \0");
		curr_buff_size+=append_buffer(buffer,temp,curr_buff_size,max_buff_size);
		if(strstr(temp,"//")!=NULL  || strstr(temp,"\"")!=NULL || strstr(temp,"\'")!=NULL)
		{
			do{
				fscanf(source_fp,"%c",&temp_char[0]);
				strcpy(temp1,temp_char+0);
				curr_buff_size+=append_buffer(buffer,temp1,curr_buff_size,max_buff_size);
			  }while(temp_char[0] != '\n');
			
		}
		free(temp);
		temp=(char *)calloc(2000,sizeof(char));
	}
	fclose(source_fp);
	source_fp=NULL;
	ans_buffer=cmp_token(buffer);

	printf("\n\n\t 1.Create a new file \n\n\t 2.Change existing file \n\n\t\t Enter Your choice :");
	scanf("%d",&ans);

	switch(ans)
	{
		case 1:
			printf("\n\n\t\t Enter New File Name : ");
			scanf("%s",new_filename);
			break;

		case 2:
			new_filename=argv[1];
			break;
			
	}

	source_fp=fopen(new_filename,"w");
	fwrite(ans_buffer,1,strlen(ans_buffer),source_fp);

	printf("\n File Created......!!!");

return 0;
}
