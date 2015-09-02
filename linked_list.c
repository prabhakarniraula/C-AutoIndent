#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/**----------------------creates linked list remembering position that require changes -------------*/

struct node
{
	unsigned int index;
	int org_size;
	char* string;
	struct node *next;

}*start=NULL;

unsigned int total_size;

void insert(unsigned int ind,char * str,int size )
{
	struct node *p=start,*new,*prev=NULL;
	new=(struct node *)malloc(sizeof(struct node));
	new->string=NULL;
	new->string=(char *)calloc((strlen(str)+10),sizeof(char));
	total_size+=strlen(str);

	if(start==NULL)
	{
		start=new;
		new->index=ind;
		strcpy(new->string,str);
		new->org_size=size;
		new->next=NULL;
		return;
	}
	else
	{
		while(p!=NULL )
		{
			if((p->index)>ind)
				break;
			else
			{
				prev=p;
				p=p->next;
			}
		}
		new->next=p;
		if(prev!=NULL)
			prev->next=new;
		else
			start=new;
		new->index=ind;
		new->org_size=size;
		strcpy(new->string,str);
		
	}
return;

}

void remove_front()
{
	struct node *ptr=NULL;

 	if(start==NULL)
 	{
  		return ;
 	}
	else 
 	{
		ptr=start;
  		start=start->next;
  		free(ptr);
  		return;
 	}
}

void remove_end()
{
	struct node *ptr=start,*prev=NULL;
		
	if(start==NULL)
	{
		return;
	}
	else if(start->next==NULL)
	{
		ptr=start;
		start=start->next;
		total_size-=strlen(ptr->string);
		free(ptr);
		return;

	}
	else
	{
		while(ptr->next!=NULL)
		{
			prev=ptr;
			ptr=ptr->next;
		}
		prev->next=NULL;
		total_size-=strlen(ptr->string);
		free(ptr);
		return;
	}
}

void print()
{
	struct node *ptr=start;
	if(start==NULL)
		return;
	while(ptr->next!=NULL)
	{
		printf("\n\nindex is %d and length = %d string is %s",ptr->index,strlen(ptr->string),ptr->string);
		ptr=ptr->next;
	}
		printf("\n\nindex is %d and length = %d string is %s",ptr->index,strlen(ptr->string),ptr->string);
}

unsigned int get_index()
{
	if(start==NULL)
		return (-1);
	return (start->index);

}

unsigned int get_last_index()
{
	struct node *ptr=start;
	
	if(start==NULL)
		return -1;

	while(ptr->next!=NULL)
		ptr=ptr->next;
	return ptr->index;

}

char * get_string()
{
	if(start==NULL)
		return NULL;
	return (start->string);
}

char *get_last_string()
{
	struct node *ptr=start; 

	if(start==NULL)
		return NULL;
	
	while(ptr->next!=NULL)
		ptr=ptr->next;
	return (ptr->string);
}

unsigned int get_org_size()
{
	if(start==NULL)
		return -1;
	return start->org_size;
}

unsigned int get_total_size()
{
	return total_size;
}
