#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "queue.h"


void enque(char arr[])
{
  struct playlist_que* tmp;
  tmp=(struct playlist_que*)malloc(sizeof(struct playlist_que));
  if(que_p==NULL)
  {
    que_p=tmp;
    que_p->front=0;
    que_p->rear=0;
    strcpy(que_p->playlist[que_p->rear],arr);
    que_p->rear++;
  }
  else
  {
    if((que_p->rear-que_p->front==99)||(que_p->front-que_p->rear==1))
    {
      printf("queue is full");
    }
    else
    {
      strcpy(que_p->playlist[que_p->rear],arr);
      if(que_p->rear==99)
      {
        que_p->rear=0;
      }
      else
      {
        que_p->rear++;
      }
    }    
  }
  
}
void deque()
{
  if(que_p==NULL)
  {
    printf("que is empty");
  }
  else if(que_p->rear==que_p->front)
  {
    printf("que is empty");
  }
  else
  {
    if(que_p->front==99)
    {
      que_p->front=0;
    }
    else{
      que_p->front++;
    }
  }  
}
int is_que_empty()
{
  if(que_p==NULL)
  {
    printf("Queue not created");
    return -1;
  }
  else if(que_p->front==que_p->rear)
  {
    return 1;
  }
  else return 0;
}