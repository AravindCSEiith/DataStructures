#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "queue.h"
#include "stack.h"
#include "temp_queue.h"
//check_presence(char arr[]) is the funtion that checks whether arr is present in list or not 
void check_presence(char arr[])
{
  struct node* p;
  p=root;
  while (p!=NULL)
  {
    //strcmp():compares two strings. predefined function from string.h, and returns '0' if strings are same
    if(strcmp(arr,p->song_frm_lib)==0)
    {
      printf("Found, Enqueued\n");
      enque(arr);
      break;
    }
    else
    {
      p=p->way;
     
    }
    
  }
  if(p==NULL)
  {
    printf("Not Found in the song library\n");
  }
  
}
//play_next will run when the user wants the next song to be played
void play_next()
{
  if(is_que_empty()==0)
  {
    printf("Playing %s\n",que_p->playlist[que_p->front]);
    push(que_p->playlist[que_p->front]);
    deque();
  }
  else 
  {
    printf("Sorry, playlist completed, please try previous songs\n");
  }
}
//play_prev_sngs(int k) will run when the user wants the previous songs to be played 
void play_prev_sngs(int k)
{
  int a=k;
  //num_of_pre_sngs_played counts the number of previous songs played, and I used this variable to know number of dequeues(for temporary_queue) and pushs(for stack) after playing previous songs. 
  int num_of_pre_sngs_played=0;
  while(a!=0)
  {
    if(is_stk_empty()==0)
    {
      printf("playing %s\n",stk_p->previous_songs[stk_p->stk_top]);
      t_enque(stk_p->previous_songs[stk_p->stk_top]);
      pop();
      a--;
      num_of_pre_sngs_played++;
    }
    else
    {
      printf("There aren't %d previous songs\n",k);
      a=0;
    }
  }
  while(num_of_pre_sngs_played!=0)
  {
    push(t_que_p->temp_prev_songs_store[t_que_p->t_front]);
    t_deque();
    num_of_pre_sngs_played--;
  }


}


int main()
{
  
  printf("Enter all songs(as strings), end with '-1'\n");
  //sng_lst is the variable in which the songs entered by user are stored
  char sng_lst[50]="-1";
  //ended: I introduced this to stop taking songs when user enters '-1' 
  char ended[50]="-1";
  
  do
  {
    scanf("%s",sng_lst);
    if(strcmp(sng_lst,ended)!=0)
    {
      append(sng_lst);
    }
  }while(strcmp(sng_lst,ended)!=0);
  printf("All songs entered!\n");
  printf("Create Playlist, end with '-1'\n");
  do
  {
    scanf("%s",sng_lst);
    if(strcmp(sng_lst,ended)!=0)
    {
      check_presence(sng_lst);
    }
    
  }while(strcmp(sng_lst,ended)!=0);
  printf("Playlist Ready!\n");
  char action[3]="n";
  
  while(strcmp(action,"e")!=0)
  {
    //I didn't directly provide an option p:k. But once the user enters p, the program asks user for number of previous songs 
    printf("Play next song, previous songs or end?n/p/e\n");
    scanf("%s",action);
    int pre_sngs_to_play=0;
    if(strcmp(action,"e")==0)
    {
      printf("Bye\n");
      break;
    }
    else if(strcmp(action,"n")==0)
    {
      play_next();
    }
    else if(strcmp(action,"p")==0)
    {
      printf("Enter the number of previous songs you want to be played:");
      scanf("%d",&pre_sngs_to_play);
      play_prev_sngs(pre_sngs_to_play);
    }
  }


  return 0;
}