#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"

void append(char arr[])
{
  struct node* tmp;
  tmp =(struct node*)malloc(sizeof(struct node));
  //strcpy(dest, arr):used to copy a string from address arr into dest. This is a predefined function string.h
  strcpy(tmp->song_frm_lib,arr);
  
    tmp->way=NULL;
    if(root==NULL)
    {
      root=tmp;
    }
    else
    {
      struct node* var;
      var=root;
      while(var->way!=NULL)
      {
        var=var->way;
      }
      var->way=tmp;
    }
   
}