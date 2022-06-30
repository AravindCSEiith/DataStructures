#ifndef stack


struct prev_songs_stk
{
  char previous_songs[100][50];
  int stk_top;
};
struct prev_songs_stk* stk_p;
//stk_p points to our previous songs stack
void push(char arr[]);
void pop();
int is_stk_empty();


#define stack
#endif