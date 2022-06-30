#ifndef temp_queue


struct temp_prev_songs_store_que
{
  char temp_prev_songs_store[100][50];
  int t_front;
  int t_rear;
};
struct temp_prev_songs_store_que* t_que_p;
//t_que_p points to our temporary previous songs queue
void t_enque(char arr[]);
void t_deque();


#define temp_queue
#endif