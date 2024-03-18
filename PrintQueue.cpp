#include "PrintQueue.h"
#include <iostream>
#include <ostream>
using namespace std;

//************************************************
// Constructor. Generates an empty queue         *
//************************************************
PrintQueue::PrintQueue()
{
	front = nullptr;
	rear = nullptr;
	currentSize = 0;
}


void PrintQueue::enqueue(int num, int numberOfPages)
{
	if (isEmpty())   //if the queue is empty
	{	//make it the first element
		front = new PrintJobNode(num, numberOfPages);
		rear = front;
		currentSize++;

	}
	else  //if the queue is not empty
	{	//add it after rear
		rear->next = new PrintJobNode(num, numberOfPages);
		rear = rear->next;
		currentSize++;
	}
}

void PrintQueue::dequeue(int& num, int & pages)
{
	PrintJobNode* temp;
	if (isEmpty())
	{
		cout << "Attempting to dequeue on empty queue, exiting program...\n";
		exit(1);
	}
	else //if the queue is not empty
	{	//return front's value, advance front and delete old front
		num = front->PrintJobId;
		pages = front->numberOfPages;
		temp = front;
		front = front->next;
		delete temp;
		currentSize--;
	}
}

int PrintQueue::getCurrentSize() const
{
	return currentSize;
}

bool PrintQueue::isEmpty() const
{
	if (front == nullptr)
		return true;
	else
		return false;
}
//all functions after this line are newly added. 
PrintQueue:: PrintQueue( const PrintQueue& copy){ //copy constructor.
	front = copy.CreateClone(); //create a ddep copy and return its front.
	rear = front;  // stor the rear in the front. 
	while (rear != nullptr && rear->next != nullptr) { // keeep itierating the rear until it th end of queue.
		rear = rear->next;
	}
	currentSize = copy.currentSize; // copy the size.
 }
  


 PrintJobNode* PrintQueue::CreateClone() const {
	 if (front == nullptr) {
		 return nullptr;
	 }
	 PrintJobNode* headclone = new PrintJobNode(front->PrintJobId, front->numberOfPages, nullptr);//creat a front and make its varaibles equal to the current front varaibles.
	 PrintJobNode* ptr = front->next; // ptr is next node of front 
	 PrintJobNode* ptrclone = headclone;  // the front
	 while (ptr != nullptr) { // its not the end of queue.
		 ptrclone->next = new PrintJobNode(ptr->PrintJobId, ptr->numberOfPages, nullptr); //the node after front.
		 ptr = ptr->next; // this node is one node ahead pf ptrclone.
		 ptrclone = ptrclone->next; // move to next node
	 }
	 return headclone;
 }
 void PrintQueue::DeleteQueue() {
	 while (front != nullptr) { // until node is over
		 PrintJobNode* temp = front; //store front in temp
		 front = front->next;  // move to next
		 delete temp; //delete node
	 }
 }

 PrintQueue& PrintQueue::operator =(const PrintQueue& rhs) {
	 if (this != &rhs) {
		 DeleteQueue(); // Assuming this function deletes the current queue contents

		 // Create a deep copy of the queue
		 front = rhs.CreateClone();
		 rear = front;
		 while (rear != nullptr && rear->next != nullptr) { //locate the rear at the end of queue
			 rear = rear->next;
		 }
		
		 currentSize = rhs.currentSize; // copy the size.

		
		 
	 }

	 return *this; // Return a reference to the current PrintQueue
 }

 //delete function was created  because its used  = operatoor otherwise it will not be created and its content is just 
 //copied and pasted in destrurctor
 PrintQueue:: ~PrintQueue() {
	 DeleteQueue(); //use the delete queue function.
 }


 
 PrintJobNode* PrintQueue:: getfront() { //function to return front.
	 return front;

 }

 