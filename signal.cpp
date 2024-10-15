#include <iostream>
#include <csignal>
#include <unistd.h>

using namespace std;

void custom_handler(int signal){
    cout << "SIGINT cant be handled as usual, its custom bro\n";
}

int main() {
    signal(SIGINT, custom_handler);
    while(1) {
        cout << "Running..\n";
        sleep(1);
    }
}
// C program to show thread functions 

#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 

void* func(void* arg) 
{ 
	// detach the current thread 
	// from the calling thread 
	pthread_detach(pthread_self()); 

	printf("Inside the thread\n"); 

	// exit the current thread 
	pthread_exit(NULL); 
} 

void fun() 
{ 
	pthread_t ptid; 

	// Creating a new thread 
	pthread_create(&ptid, NULL, &func, NULL); 
	printf("This line may be printed"
		" before thread terminates\n"); 

	// The following line terminates 
	// the thread manually 
	// pthread_cancel(ptid); 

	// Compare the two threads created 
	if(pthread_equal(ptid, pthread_self())) 
		printf("Threads are equal\n"); 
	else
		printf("Threads are not equal\n"); 

	// Waiting for the created thread to terminate 
	pthread_join(ptid, NULL); 

	printf("This line will be printed"
		" after thread ends\n"); 

	pthread_exit(NULL); 
} 

// Driver code 
int main() 
{ 
	fun(); 
	return 0; 
} 

#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;

void* thread(void* arg)
{
    // Wait (P operation)
    sem_wait(&mutex);
    std::cout << "\nEntered.." << std::endl;

    // Critical section
    sleep(4);

    // Signal (V operation)
    std::cout << "\nJust Exiting..." << std::endl;
    sem_post(&mutex);

    return nullptr;
}

int main()
{
    // Initialize the semaphore with a value of 1
    sem_init(&mutex, 0, 1);

    pthread_t t1, t2;

    // Create thread 1
    pthread_create(&t1, nullptr, thread, nullptr);

    // Delay to allow thread 1 to enter the critical section
    sleep(2);

    // Create thread 2
    pthread_create(&t2, nullptr, thread, nullptr);

    // Wait for threads to complete
    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);

    // Destroy the semaphore
    sem_destroy(&mutex);

    return 0;
}
