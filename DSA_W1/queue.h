#ifndef queue

struct playlist_que
{
  char playlist[100][50];
  int front;
  int rear;
};
struct playlist_que* que_p;//que_p points to our playlist queue
void enque(char arr[]);
void deque();
int is_que_empty();


#define queue
#endif