#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "stack.h"


void push(char arr[])
{
  struct prev_songs_stk* tmp;
  tmp=(struct prev_songs_stk*)malloc(sizeof(struct prev_songs_stk));
  if(stk_p==NULL)
  {
    stk_p=tmp;
    stk_p->stk_top=-1;
    stk_p->stk_top++;
    strcpy(stk_p->previous_songs[stk_p->stk_top],arr); 
  }
  else
  {
    if(stk_p->stk_top==99)
    {
      printf("stack is full");
    }
    else
    {
      stk_p->stk_top++;
      strcpy(stk_p->previous_songs[stk_p->stk_top],arr);
    }    
  }
  
}
void pop()
{
  if(stk_p->stk_top==-1)
  {
    printf("stack is empty");
  }
  else
  {
    stk_p->stk_top--;
  }  
}
int is_stk_empty()
{
  if(stk_p==NULL)
  {
    printf("stack not created");
    return -1;
  }
  else if(stk_p->stk_top==-1)
  {
    return 1;
  }
  else 
  {
    return 0;
  }
}