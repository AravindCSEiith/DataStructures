#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


struct node
{
  int node_id;
  int time_stmp;
  char ev_type;//this can take 3 possible values, n(not yet infected), i(infected), r(recovered)
};
int give_inf_t_stmp()//this gives the trial at which head comes, and gives -1 if it we didn't get head in all 5 trials
{
  int num=0;
  int j;
  for(unsigned i=0; i<5;i++)
  {
    num=rand()%2;
    if(num==1)//1 implies head
    {
      j=i;
      break;
    }
    else
    {
      j=i;
    }
  }
  
  if(num==1)
  {
    return j+1;
  }
  else
  {
    return -1;
  }

}

void insert_heap(struct node arr[], int* p, struct node nd)//insert node into heap
{
  arr[*p]=nd;//putting the element to be inserted at the last position
  *p=*p+1;//updating number of elements in heap
  int num=*p;
  int num1=num/2;
  while( num!=1 && arr[num-1].time_stmp<arr[num1-1].time_stmp)//restoring min_heap property
  {
    struct node nd1;
    nd1=arr[num-1];
    arr[num-1]=arr[num1-1];
    arr[num1-1]=nd1;
    num=num1;
    num1=num/2;
  }
}
void delete_hp_root(struct node arr[],int* p, struct node infected[], struct node recovered[], struct node tot_nod_set[])
{
  if(arr[0].ev_type=='i')//deleting from S and inserting into I
  {
    infected[arr[0].node_id-1]=arr[0];
    tot_nod_set[arr[0].node_id-1].node_id=0;
    tot_nod_set[arr[0].node_id-1].time_stmp=-1;
    tot_nod_set[arr[0].node_id-1].ev_type='n';
  }
  else if(arr[0].ev_type=='r')//deleting from I and inserting into R
  {
    recovered[arr[0].node_id-1]=arr[0];
    infected[arr[0].node_id-1].node_id=0;
    
    infected[arr[0].node_id-1].ev_type='n';
  }
  //deleting root and placing the last element at root position
  arr[0]=arr[*p-1];
  arr[*p-1].node_id=0;
  arr[*p-1].ev_type='n';
  arr[*p-1].time_stmp=-1;
  *p=*p-1;
  int num=0;
  //moving the root to appropriate position(i.e. heapifying)
  while(1)
  {
    if(arr[0].node_id==110)
    {
      break;
    }
    struct node nd1;
    if(num>200||2*num+1>200||2*num+2>200)
    {
      break;
    }
    if(arr[2*(num)+1].time_stmp==-1)
    {
      break;
    }
    else if(arr[2*(num)+2].time_stmp==-1)
    {
      if(arr[num].time_stmp>arr[2*num+1].time_stmp)
      {
        nd1=arr[num];
        arr[num]=arr[2*num+1];
        arr[2*num+1]=nd1;
      }
      break;
    }
    else
    {
      if(arr[2*(num)+1].time_stmp<arr[2*(num)+2].time_stmp)
      {
        if(arr[num].time_stmp>arr[2*num+1].time_stmp)
        {
          nd1=arr[num];
          arr[num]=arr[2*num+1];
          arr[2*num+1]=nd1;
          num=2*num+1;
        }
        else
        {
          break;
        }
      }
      else
      {
        if(arr[num].time_stmp>arr[2*num+2].time_stmp)
        {
          nd1=arr[num];
          arr[num]=arr[2*num+2];
          arr[2*num+2]=nd1;
          num=2*num+2;
        }
        else
        {
          break;
        }
      }
    }
    
  }
}

int main(void) 
{
  struct node ver[100];//vertices
  for (unsigned i=0;i<100;i++)//initialising vertices
  {
    ver[i].node_id=i+1;
    ver[i].time_stmp=-1;
  }
  struct node edge[5000][2];//edges
  for (unsigned i=0;i<5000;i++)//initialising edges
  {
    edge[i][0].node_id=0;
    edge[i][0].time_stmp=-2;
    edge[i][1].node_id=0;
    edge[i][1].time_stmp=-2;
  }
  srand(time(NULL));
  int k=0;
  for (unsigned i=0; i<100; i++)
  {
    for (unsigned j=i+1; j<100; j++)
    {
       int num;
       num=rand()%2;//checking if edge is present b/w vertices
       if (num==1)
       {
         edge[k][0]=ver[i];
         edge[k][1]=ver[j];
         k++;
       }
    }
  }
  struct node S[100];//susceptible, the presence of a node with node_id nd_id is given by S[nd_id-1](if S[nd_id-1].node_id=0 implies node with node_id nd_id is not in S, if it is in S then S[nd_id-1].node_id=nd_id) 
  for(unsigned i=0; i<100; i++)
  {
    S[i].node_id=i+1;
    S[i].time_stmp=-1;
    S[i].ev_type='n';
  }
  struct node I[100];//Infected, the presence of a node with node_id nd_id is given by I[nd_id-1](if I[nd_id-1].node_id=0 implies node with node_id nd_id is not in I, if it is in I then I[nd_id-1].node_id=nd_id)
  for(unsigned i=0; i<100; i++)
  {
    I[i].node_id=0;
    I[i].time_stmp=-1;
    I[i].ev_type='n';
  }
  struct node R[100];//Recovered, the presence of a node with node_id nd_id is given by R[nd_id-1](if R[nd_id-1].node_id=0 implies node with node_id nd_id is not in R, if it is in R then R[nd_id-1].node_id=nd_id)
  for(unsigned i=0; i<100; i++)
  {
    R[i].node_id=0;
    R[i].time_stmp=-1;
    R[i].ev_type='n';
  }
  struct node min_heap[200];//implementing min_heap as an array
  for(unsigned i=0; i<200; i++)
  {
    min_heap[i].node_id=0;
    min_heap[i].ev_type='n';
    min_heap[i].time_stmp=-1;
  }
  int nd_cnt_hp=0;
  int* node_count_of_heap=&nd_cnt_hp;//this tells the number of elements present in min_heap
  
  int init_id=rand()%100+1;//generating the node id of element to be infected first
  struct node inf[100];//stores the infection events
  struct node rec[100];//stores the recovery events
  for(unsigned i=0; i<100; i++)//initialising infection event storing array
  {
    inf[i].node_id=0;
    inf[i].time_stmp=-1;
    inf[i].ev_type='n';
  }
  for(unsigned i=0; i<100; i++)//initialising recovery event storing array
  {
    rec[i].node_id=0;
    rec[i].time_stmp=-1;
    rec[i].ev_type='n';
  }
  int rec_time;//recovery_time of node_id after it gets infected
  int in_re_c=0;
  int min_distance[100];//stores the shortest distance of each node from first infected node
  for(unsigned i=0;i<100;i++)//initialising min_distance array
  {
    min_distance[i]=0;
  }
  inf[0].node_id=S[init_id-1].node_id;
  inf[0].time_stmp=0;
  inf[0].ev_type='i';
  rec[0].node_id=S[init_id-1].node_id;
  rec_time=rand()%5+1;
  rec[0].time_stmp=rec_time;
  rec[0].ev_type='r';
  S[init_id-1].ev_type='i';
  insert_heap(min_heap, node_count_of_heap, inf[0]);//inserting infection event
  insert_heap(min_heap, node_count_of_heap, rec[0]);//inserting recovery event
  inf[0].node_id=0;
  inf[0].time_stmp=-1;
  inf[0].ev_type='n';
  rec[0].node_id=0;
  rec[0].time_stmp=-1;
  rec[0].ev_type='n';
  
  
  while(min_heap[0].node_id!=0)//loop that deletes element one by one from min_heap and inserts the nearest element that is nearest to the deleting node
  {     
    if(min_heap[0].ev_type=='i')
    {
      for(unsigned i=0;edge[i][0].node_id!=0;i++)
      {   
        if(edge[i][0].node_id<min_heap[0].node_id)
        {
          if(min_heap[0].node_id==edge[i][1].node_id)
          {
            if(S[edge[i][0].node_id-1].ev_type=='n'&&S[edge[i][0].node_id-1].node_id!=0)
            {
              rec_time=give_inf_t_stmp();
              if(rec_time!=-1)
              {
                inf[in_re_c].node_id=edge[i][0].node_id;
                inf[in_re_c].ev_type='i';
                inf[in_re_c].time_stmp=min_heap[0].time_stmp+rec_time;
                rec[in_re_c].node_id=edge[i][0].node_id;
                rec[in_re_c].ev_type='r';
                rec[in_re_c].time_stmp=inf[in_re_c].time_stmp+rand()%5+1;
                in_re_c++;                
                S[edge[i][0].node_id-1].ev_type='i';
                min_distance[edge[i][0].node_id-1]=min_distance[edge[i][1].node_id-1]+1;
              }
            }
          }          
        }
        else if(edge[i][0].node_id==min_heap[0].node_id)
        {
          if(S[edge[i][1].node_id-1].ev_type=='n'&&S[edge[i][1].node_id-1].node_id!=0)
          {
            rec_time=give_inf_t_stmp();
            if(rec_time!=-1)
            {
              inf[in_re_c].node_id=edge[i][1].node_id;
              inf[in_re_c].ev_type='i';
              inf[in_re_c].time_stmp=min_heap[0].time_stmp+rec_time;
              rec[in_re_c].node_id=edge[i][1].node_id;
              rec[in_re_c].ev_type='r';
              rec[in_re_c].time_stmp=inf[in_re_c].time_stmp+rand()%5+1;
              in_re_c++;                
              S[edge[i][1].node_id-1].ev_type='i';
              min_distance[edge[i][1].node_id-1]=min_distance[edge[i][0].node_id-1]+1;
            }
          }
        }
      }
      
      delete_hp_root(min_heap, node_count_of_heap, I, R, S);
      for(unsigned i=0;inf[i].node_id!=0;i++)
      {
        insert_heap(min_heap, node_count_of_heap, inf[i]);
        insert_heap(min_heap, node_count_of_heap, rec[i]);
        inf[i].node_id=0;
        inf[i].time_stmp=-1;
        inf[i].ev_type='n';
        rec[i].node_id=0;
        rec[i].time_stmp=-1;
        rec[i].ev_type='n';
      }
    }
    else if(min_heap[0].ev_type=='r')
    {
      delete_hp_root(min_heap, node_count_of_heap, I, R, S);
    }    
    in_re_c=0;    
  }
  
  int max=R[0].time_stmp;//max stores the max(recovery times of all nodes)
  for(unsigned i=0;i<100;i++)
  {
    if(max<R[i].time_stmp)
    {
      max=R[i].time_stmp;
    }
  }
  int T_stmp[max+1];//This stores time_stamp values necessary for us to create table
  for(unsigned i=0;i<max+1;i++)
  {
    T_stmp[i]=i;
  }
  int R_cou[max+1];//R_cou[i] stores the number of nodes that are recovered till time i
  int I_cou[max+1];//I_cou[i] stores the number of nodes with infection at time i
  for(unsigned i=0;i<max+1;i++)//initialising recovery count array and infected count array
  {
    R_cou[i]=0;
    I_cou[i]=0;
  }
  for(unsigned i=0; i<max+1; i++)
  {
    if(i!=0)
    {
      R_cou[i]=R_cou[i-1]+R_cou[i];
      
    }
    for(unsigned j=0; j<100; j++)
    {
      if(R[j].time_stmp==i)
      {
        R_cou[i]++;
      }
    }
    
    for(unsigned j=0; j<100; j++)
    {
      if(I[j].time_stmp==i)
      {
        I_cou[i]++;
      }
    }
    if(i!=0)
    {
      
      I_cou[i]=I_cou[i-1]+I_cou[i]-(R_cou[i]-R_cou[i-1]);
    }
  }
  printf("|-----------------------------------------------|\n");
  printf("| Time_stamp | Suspected | Infected | Recovered |\n");
  printf("|-----------------------------------------------|\n");
  for(unsigned i=0;i<max+1;i++)
  {
    printf("|      %d     |     %d     |     %d    |     %d     |\n",T_stmp[i],100-I_cou[i]-R_cou[i],I_cou[i],R_cou[i]);
  }
  printf("|--------------------------------------------------|\n");
  printf("\n\n\n");
  printf("|--------------------------------------------------|\n");
  printf("|   node_id   |infected_time_stamp|shortest distance|\n");
  printf("|--------------------------------------------------|\n");
  for(unsigned i=0; i<100; i++)
  {
    printf("|      %d      |         %d         |        %d        |\n",R[i].node_id,I[i].time_stmp,min_distance[i]);
  }
  printf("|----------------------------------------------------|\n");  
 
  return 0;
}