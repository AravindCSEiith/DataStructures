#ifndef list


struct node
{
  char song_frm_lib[50];
  struct node* way;//'way' provides route to next node
};
struct node* root;//root points to the first node of our linked list(of songs library) 
void append(char arr[]);


#define list
#endif