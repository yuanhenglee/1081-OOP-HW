#ifndef QUEUE_H
#define QUEUE_H

template <typename T>
class QueueNode{
  public:
    T data;
    QueueNode *next;
    QueueNode(T x):data(x),next(NULL){}
};

template <typename T>
class Queue{
  public:
    Queue():head(NULL),tail(NULL){}
    Queue( Queue &); 
	~Queue(){
		while( !IsEmpty()  )
			dequeue();
	}
    void enqueue(T x);
    void dequeue();
    bool IsEmpty();
    T gethead(){return head->data;}
    Queue & operator=( const Queue &q2 );
    QueueNode<T> *head;
    QueueNode<T> *tail;
};


#endif 
