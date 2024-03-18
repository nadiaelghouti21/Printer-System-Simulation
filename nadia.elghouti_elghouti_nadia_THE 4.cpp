//nadia elghouti
//30466
#include <iostream>
#include <iomanip>
#include <thread>
#include <ctime>
#include <sstream>
#include <mutex>
#include "PrintQueue.h"
#include <random>
#include <chrono>
#include <time.h>
using namespace std;

PrintQueue queue;
int id = 0;
mutex output_org;  // mutex to organize the output for each thread.
mutex queue_edit;  // mutex to enqueue or dequeue in each thread.
mutex controlid;   // mutex to control the access to the id varaible by each thread. 
int maxPrintJobs, min_t, max_t, min_pg, max_pg; //user inputs.

// random range function is taken from the homewrok sheet.
int random_range(const int& min, const int& max) {
	static mt19937 generator(time(0));
	uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

//printing the queue function.
ostream& operator <<(ostream& os, PrintQueue& queue) {
	PrintJobNode* current = queue.getfront(); // current is the front of queue 

	while (current != nullptr) { //while the next pointer is not null movve tot he next queue. 
		os << "Print Job ID : " << current->PrintJobId << ", Pages : " << current->numberOfPages << "\n"; //print the printjob id and nuber of pages of each node.
		current = current->next; 
	}

	return os; //return the ostream variable.
}

PrintQueue operator + (const PrintQueue& lhs, const PrintJobNode& rhs) {
	PrintQueue newQueue(lhs); // use of deep copy constructor to make newqueue a copy of lhs(original queue).
	newQueue.enqueue(rhs.PrintJobId, rhs.numberOfPages); // add to newqueue the information of new node.
	return newQueue;   //return the nequeue with addition of the rhs.
}


PrintQueue operator - (const PrintQueue& lhs, PrintJobNode& rhs) {
	PrintQueue newQueue(lhs); // use of deep copy constructor to make newqueue a copy of lhs(original queue).
	newQueue.dequeue(rhs.PrintJobId, rhs.numberOfPages);  // remove from newqueue the information of new node. 
	return newQueue;    //return the newqueue withuot the rhs node. 
}
/*the following function is disgned to comapere the id to the maxprintjobs but during thee comparioson
the id mutax is kept locked to take the exact value of id and restrict the interruption of id from any of the working threads. */
bool proceed (int maxPrintJobs, int id) {
	controlid.lock();
	bool p = false;
	if (maxPrintJobs > id) {
		p = true;
	}
	controlid.unlock();
	
	return p;
}

void user1() {


	this_thread::sleep_for(chrono::seconds(1)); //sleep the thread before the first printjob to ensure that all threads will work at the same time.

	while (proceed(maxPrintJobs, id)) {

		time_t tt = chrono::system_clock::to_time_t //calculation of the current time taken from the multithreading slides.
		(chrono::system_clock::now());
		tm* ptm = new struct tm;
		localtime_s(ptm, &tt);

		
		controlid.lock(); //use the id mutex to increment the id and create a local copy of it. 
		id++;
		int currentid = id;
		controlid.unlock();
		queue_edit.lock();
		int pg1 = random_range(min_pg, max_pg); // use this funtion to get a random number of pages in the minimum and maximum values entered by user. 
		queue = queue + PrintJobNode(currentid, pg1);  // use the + and = operetors to add the new id and number of pages generated to the existing queue

		output_org.lock(); // lock the printing mutex organizer. 
		cout << "User 1 sent new print job with ID " << currentid << " sent to the printer queue, number of pages: " << pg1 << " (print queue size: " << queue.getCurrentSize() << ") " << put_time(ptm, "%X");  
		// at the mean time the queue mutex is kept locked to get an accurate value of the queue size from the getCurrentSize function.
		cout << endl;
		queue_edit.unlock(); //unlock both mutex.
		output_org.unlock();
		this_thread::sleep_for(chrono::seconds(1));




	}



}
void user2() {
	
	
	this_thread::sleep_for(chrono::seconds(1)); //sleep the thread befor the first printjob to ensure that all threads will work at the same time.

	while (proceed(maxPrintJobs, id)) {

		time_t tt = chrono::system_clock::to_time_t //calculation of the current time taken from the multithreading slides.
		(chrono::system_clock::now());
		tm* ptm = new struct tm;
		localtime_s(ptm, &tt);


		controlid.lock(); //use the id mutex to increment the id and create a local copy of it. 
		id++;
		int currentid = id;
		controlid.unlock();
		queue_edit.lock();
		int pg2 = random_range(min_pg, max_pg); // use this funtion to get a random number of pages in the minimum and maximum values entered by user. 
		queue = queue + PrintJobNode(currentid, pg2);  // use the + and = operetors to add the new id and number of pages generated to the existing queue

		output_org.lock(); // lock the printing mutex organizer. 
		cout << "User 2 sent new print job with ID " << currentid << " sent to the printer queue, number of pages: " << pg2 << " (print queue size: " << queue.getCurrentSize() << ") " << put_time(ptm, "%X");
		// at the mean time the queue mutex is kept locked to get an accurate value of the queue size from the getCurrentSize function.
		cout << endl;
		queue_edit.unlock(); //unlock both mutex.
		output_org.unlock();
		this_thread::sleep_for(chrono::seconds(1));




	}


	
}

void user3() {
	

	this_thread::sleep_for(chrono::seconds(1)); //sleep the thread befor the first printjob to ensure that all threads will work at the same time.

	while (proceed(maxPrintJobs, id)) {// use the function to check if id is still less than maxprintjobs.

		time_t tt = chrono::system_clock::to_time_t //calculation of the current time taken from the multithreading slides.
		(chrono::system_clock::now());
		tm* ptm = new struct tm;
		localtime_s(ptm, &tt);


		controlid.lock(); //use the id mutex to increment the id and create a local copy of it. 
		id++;
		int currentid = id;
		controlid.unlock();
		queue_edit.lock();
		int pg3 = random_range(min_pg, max_pg); // use this funtion to get a random number of pages in the minimum and maximum values entered by user. 
		queue = queue + PrintJobNode(currentid, pg3);  // use the + and = operetors to add the new id and number of pages generated to the existing queue

		output_org.lock(); // lock the printing mutex organizer. 
		cout << "User 3 sent new print job with ID " << currentid << " sent to the printer queue, number of pages: " << pg3 << " (print queue size: " << queue.getCurrentSize() << ") " << put_time(ptm, "%X");
		// at the mean time the queue mutex is kept locked to get an accurate value of the queue size from the getCurrentSize function.
		cout << endl;
		queue_edit.unlock(); //unlock both mutex.
		output_org.unlock();
		this_thread::sleep_for(chrono::seconds(1));




	}


}
void printer() {
	int finished_jobs = 0;
	while (proceed(maxPrintJobs, finished_jobs)){  // compare function is used to check if finishedjobs is less than maxPrintJobs.
		if (!queue.isEmpty()) {  // check if queue is empty so it does not execute before any printjob is sent.
			// the below 3 lines is taken from the homework sheet to fine the current time.
			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
			tm* ptm = new struct tm;
			localtime_s(ptm, &tt);

			queue_edit.lock(); // lock the queue mutex to edit the queue. 
			PrintJobNode jn;
			queue = queue - jn;  // remove the first printjob added to the queue.
			output_org.lock(); // lock the printing mutex
			//printing the information of the printjob that was dequeued.
			cout << "The printer started to print the job with ID: " << jn.PrintJobId << ", number of pages : " << jn.numberOfPages << " (queue size is : " << queue.getCurrentSize() << ") " << put_time(ptm, "%X") << endl;
			
			int time = random_range(min_t, max_t);  // create a sleeping time in the range of minutes provived from user
			if (queue.isEmpty()) { // if no more elements in queue.
				cout << "The print queue is empty." << endl;
			}
			else {
				cout << "The print queue contains:" << endl;
				cout << queue; // print the elements in the queue using the << operator.
				cout << endl;
			}
			queue_edit.unlock(); // unlock the queue mutex
			this_thread::sleep_for(chrono::seconds(time));  // sleep for the random time calculated earlier (as the printing time).
			cout << endl;
			cout << "The printer finished printing the job with ID:" << jn.PrintJobId << ", number of pages: " << jn.numberOfPages << " " << put_time(ptm, "%X") << endl;
			output_org.unlock(); // unlock the output organizer mutex.
			finished_jobs++;  // incremment the finished jobs local variable.
		}



	}
	
	
}

int main() {

	cout << "Please enter the max number of print jobs: ";
	cin >> maxPrintJobs;
	cout << "Please enter the min and max values for the time range between two print jobs :" << endl;
	cout << "Min: ";
	cin >> min_t;
	cout << "Max: ";
	cin >> max_t;
	cout << "Please enter the min and max values for the number of pages in a print job :" << endl;
	cout << "Min number of pages :";
	cin >> min_pg;
	cout << "Max number of pages :";
	cin >> max_pg;
	//calculation of the local time taken from the homework sheet.
	time_t tt = chrono::system_clock::to_time_t
	(chrono::system_clock::now());
	tm* ptm = new struct tm;
	localtime_s(ptm, &tt);
	cout << "Simulation starts: " << put_time(ptm, "%X") << endl;
	

	thread prints(&printer);// creating the threads.
	thread u1(&user1);
	thread u2(&user2);
	thread u3(&user3);
	u1.join();
	u2.join();
	u3.join();
	prints.join(); // joining the printing thread the last becuase its the last to execute.
	
	time_t t = chrono::system_clock::to_time_t // creat new timme object for calculating tie at the end of the simulation. 
	(chrono::system_clock::now());
	tm* pm = new struct tm;
	localtime_s(pm, &t);
	cout << "End of the simulation at: " << put_time(pm, "%X") << endl;
		

	return 0;
} 