using namespace std;

#include "Queue.h"
#include "AnsiPrint.h"

template <typename T>
Queue<T>::Queue( Queue &q2 ):head(NULL),tail(NULL){
  QueueNode<T> *cur = q2.head;
  while(1){
    enqueue( cur->data );
    if( cur == q2.tail )
      break;
    cur = cur->next; 
  }
} 


template <typename T>
void Queue<T>::enqueue(T x){
  QueueNode<T> *newNode;
  try{
    newNode = new QueueNode<T>(x);
  }catch ( bad_alloc& ba){
    cerr << "bad_alloc caught: " << ba.what() << '\n';
  }
  if (IsEmpty()){
    tail = newNode;
    head = tail;
  }
  else{
    tail->next = newNode;
    tail = tail->next;      
  }
}

template <typename T>
void Queue<T>::dequeue(){
  try{
    if (IsEmpty())
      throw("Attempt to dequeue empty queue");
  }catch(const char *err){
    AnsiPrint(err,red,yellow,true,false);
    cout<<endl;
    return;
  }
  head = head->next;
  if( !head )
	  tail =NULL;
}

template <typename T>
bool Queue<T>::IsEmpty(){
  return( head == NULL && tail == NULL );
}

template <typename T>
Queue<T>&
Queue<T>::operator=(const Queue &q2){
  while( !IsEmpty() )
    dequeue();
  QueueNode<T> *cur = q2.head;
  while(1){
    enqueue( cur->data );
    if( cur == q2.tail )
      break;
    cur = cur->next; 
  }
  return *this;
}


