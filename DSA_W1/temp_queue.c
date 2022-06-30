#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "temp_queue.h"


void t_enque(char arr[])
{
  struct temp_prev_songs_store_que* tmp1;
  tmp1=(struct temp_prev_songs_store_que*)malloc(sizeof(struct temp_prev_songs_store_que));
  if(t_que_p==NULL)
  {
    t_que_p=tmp1;
    t_que_p->t_front=0;
    t_que_p->t_rear=0;
    strcpy(t_que_p->temp_prev_songs_store[t_que_p->t_rear],arr);
    t_que_p->t_rear++;
  }
  else
  {
    if((t_que_p->t_rear-t_que_p->t_front==99)||(t_que_p->t_front-t_que_p->t_rear==1))
    {
      printf("queue is full");
    }
    else
    {
      strcpy(t_que_p->temp_prev_songs_store[t_que_p->t_rear],arr);
      if(t_que_p->t_rear==99)
      {
        t_que_p->t_rear=0;
      }
      else
      {
        t_que_p->t_rear++;
      }
    }    
  }

}
void t_deque()
{
  if(t_que_p==NULL)
  {
    printf("temporary que is empty");
  }
  else if(t_que_p->t_rear==t_que_p->t_front)
  {
    printf(" temporary que is empty");
  }
  else
  {
    if(t_que_p->t_front==99)
    {
      t_que_p->t_front=0;
    }
    else{
      t_que_p->t_front++;
    }
  }  
}