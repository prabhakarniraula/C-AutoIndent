#include<ctype.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "linked_list.c"

/**----------------compares with tokens and changes accordingly-----------------*/

char * cmp_token(char *source)
{
     	unsigned int length,i,j,k,l,tab_count=0,case_count=0,question_mark_count=0,passive_mode=0,apostrophe_count=0,quotation_mark_count=0,bracket_count=0,round_bracket_count=0,equal_count=0,single_line_comment=0,multiline_comment=0;
	char *cptr=NULL,*needle=NULL,*temp=NULL;
	char *keywords[]={"do","if","while","for","else",
			  "auto","double","int","struct",
			  "break","long","switch",
			  "case","enum","register","typedef",
			  "char","extern","return","union",
			  "const","float","short","unsigned",
			  "continue","signed","void",
			  "default","goto","sizeof","volatile",
			  "static","==","!=","&&","||",
			  ">=","<=","/*","*/","//"
			 };					   

	length=strlen(source);	

	for(i=0;i<length;i++)
	{
	  if(passive_mode==0)
	  {
		if(source[i]=='#')
		{
		   cptr=(char *)calloc((2+tab_count+1),sizeof(char));
		   strcat(cptr,"\n");
		   for(j=0;j<tab_count;j++)
			strcat(cptr,"\t");
		   strcat(cptr,"#");
		   strcat(cptr,"\0");
		   insert(i,cptr,1);
		   free(cptr);
		}
		else if(source[i]=='{')
		{
		   cptr=(char *)calloc((5+(2*(tab_count))+2),sizeof(char));
		   
		   if(equal_count==0)
		   {
		   	strcat(cptr,"\n");
		   	for(j=0;j<tab_count;j++)
				strcat(cptr,"\t");
		   	strcat(cptr,"{");
		   	tab_count++;
		   	strcat(cptr,"\n");
		   	for(j=0;j<tab_count;j++)
				strcat(cptr,"\t");
		   	strcat(cptr,"\0");
		   	insert(i,cptr,1);
		  }
		  else
		  {
			strcat(cptr,"{");
			insert(i,cptr,1);
		  }
		   	free(cptr);
		}
		
		else if(source[i]==';')
		{
		    if(round_bracket_count==0)
		    {
		   	cptr=(char *)calloc(2+tab_count+1,sizeof(char));
		   	strcat(cptr,";");
		   	strcat(cptr,"\n");
		   	for(j=0;j<tab_count;j++)
				strcat(cptr,"\t");
		   	strcat(cptr,"\0");
		   	insert(i,cptr,1);
		   	free(cptr);
		    }
		    if(equal_count>0)
			equal_count=0;
		}

		else if(source[i]==':')
		{
		   cptr=(char *)calloc(4+tab_count+1,sizeof(char));
		   strcat(cptr," : ");
		   if(question_mark_count==0)
		   {
			if(case_count==1)
			{
				tab_count++; 
			}
		   	strcat(cptr,"\n");
		   	for(j=0;j<tab_count;j++)
				strcat(cptr,"\t");
		   }
		   if(question_mark_count>0)
			question_mark_count--;
		   strcat(cptr,"\0");
		   insert(i,cptr,1);
		   free(cptr);
	
		}
		else if(source[i]=='}')
		{ 
		   cptr=(char *)calloc(5+(2*tab_count)+1,sizeof(char));
		   if(equal_count==0)
		   {
		  	 if(tab_count>0)	
		   		tab_count--;
		  	 strcat(cptr,"\n");
		  	 for(j=0;j<tab_count;j++)
				strcat(cptr,"\t");
		 	 strcat(cptr,"}");
		   	 strcat(cptr,"\n");
		  	 for(j=0;j<tab_count;j++)
			 strcat(cptr,"\t");
		  	 strcat(cptr,"\0");
		  	 insert(i,cptr,1);
		  }
		  else
		  {
			strcat(cptr,"}");
			insert(i,cptr,1);
		  }
		   free(cptr);
		}
		else if(source[i]=='?')
		{
		   question_mark_count++;
		   cptr=(char *)calloc(4,sizeof(char));
		   strcat(cptr," ? ");
		   strcat(cptr,"\0");
		   insert(i,cptr,1);
		   free(cptr);
		}
		else if(source[i]=='(')
		{
		   round_bracket_count++;
		}
		else if(source[i]==')')
		{
			if(round_bracket_count>0)
				round_bracket_count--;
			if(equal_count>0)
				equal_count=0;
		}
		else if(source[i]=='=')
		{
			equal_count++;
		}
	  }
    		if(source[i]=='\'')
		{
			if(apostrophe_count==1)
			{
				apostrophe_count=0;
				passive_mode--;
			}
			else
			{
				passive_mode++;
				apostrophe_count=1;
			}
		}
		else if(source[i]=='"')
		{
			if(quotation_mark_count==1)
			{
				quotation_mark_count=0;
				passive_mode--;
			}
			else
			{
				quotation_mark_count=1;
				passive_mode++;
			}
		}
		else if(source[i]=='[')
		{
			passive_mode++;
			bracket_count++;
		}
		else if(source[i]==']')
		{
			if(passive_mode>0 && bracket_count>0)
			{
				passive_mode--;
				bracket_count--;
			}
		}
		else if(source[i]=='\n')
		{
			if(passive_mode>0 && single_line_comment>0)
			{
				passive_mode--;
				single_line_comment=0;

			}
				cptr=(char *)calloc(3+tab_count,sizeof(char));
                                strcat(cptr,"\n");
                                for(j=0;j<tab_count;j++)
                                        strcat(cptr,"\t");
                                strcat(cptr,"\0");
                                insert(i,cptr,1);
				free(cptr);
		}
	
	for(l=0;l<41;l++)
	{
		cptr=source;
		needle=keywords[l];

		while(cptr!=NULL)
		{
			cptr=strstr(cptr,needle);
			if(cptr!=NULL && (cptr-source)==i )
			{
			   if(((source[i+strlen(needle)]=='\0')  || 
				(source[i+strlen(needle)]==' ')  ||
				(source[i+strlen(needle)]==',')  ||
				(source[i+strlen(needle)]==')')  ||
				 ((isdigit(source[i+strlen(needle)])==0) &&
				(isalpha(source[i+strlen(needle)])==0)   &&
				(source[i+strlen(needle)]!='_') ) ) 
						&&
				(((i-1)==-1) ||(source[i-1]==' ')                       ||
				(source[i-1]=='(')||(source[i-1]==',')                  ||
			        ((isdigit(source[i-1]==0)) && (isalpha(source[i-1]==0)) &&
				(source[i-1]!='_'))) )
			   {
				temp=calloc((strlen(needle)+3),sizeof(char));
				if(get_last_string()[1]=='#')
					strcat(temp,"\n");
				strcat(temp,needle);
				strcat(temp,"\0");
				insert(cptr-source,temp,strlen(needle));
				free(temp);
				cptr+=strlen(needle);
				if(l==12)
				{
					case_count++;
				}
				else if(l==9 && case_count>0)
				{
					case_count--;
					if(tab_count>0)
						tab_count--;
				}
		
				else if(l==38)
				{
					multiline_comment++;
					passive_mode++;
				}
				else if(l==39)
				{
					if(multiline_comment>0 && passive_mode>0)
					{
						multiline_comment=0;
						passive_mode--;
					}
				}
				else if(l==40)
				{
					single_line_comment++;
					passive_mode++;
				}
			  	break;
			   }
			   else
				if(cptr!=NULL)
					cptr++;
			}
			else
			{	
				if(cptr!=NULL)
					cptr++;
				if(cptr-source>i)
					break;
			}
		}
		
	}
	}
	cptr=NULL;
	cptr=(char *)calloc(strlen(source)+get_total_size(),sizeof(char));
	if(cptr == NULL)
	{
		printf("Error allocating Memory...!!!");
		exit(0);
	}
	for(i=0,k=0;k<length;i++,k++)
	{
		if(k!= get_index())
		{
			cptr[i]=source[k];
			cptr[i+1]='\0';
		
		
		}
		else
		{
			j=strlen(get_string());
			cptr[i]='\0';
			strcat(cptr,get_string());
			if(get_org_size()>1)
				k+=(get_org_size()-1);
			remove_front();
			i+=j-1;
		}
	}
	cptr[i]='\0';
	FILE *fp=fopen("newfile.c","w");
	fwrite(cptr,sizeof(char),strlen(cptr),fp);
	return cptr;
}
