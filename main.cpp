//Manuel Vargas
//Project

//how to compile
//	make

//how to run	
//	./main

#include <iostream>
#include <stdlib.h> 
#include <time.h>    
#include <vector>
#include <fstream>

using namespace std;

//my headers
#include "my_process.h"	//contains structure definition

//generate k processes and returns vector with all processes
vector <my_process> generate_processes(int k){
	int i = 0;	//counter
	double total_cycles;	//sum of all processes cycles
	double total_memory;	//sum of all processes memory
	
	//cout<<endl;		//formatting
	
	//create vector of type my_process (my struct definition)
	vector <my_process> my_processes;
	
	
	//cout<<"----------------"<<endl;	//formatting
	
	while(i!=k){
		my_process first(i);	//create instance of my_process with i as the process_id
		my_processes.push_back(first);	//push new object into vector
		
		total_cycles += my_processes[i].cycles;	//add current cycles to total
		total_memory += my_processes[i].memory;	//add current memory to total
		
		
		//print from vector each attribute of process
		//cout<<"process_id: "<<my_processes[i].process_id<<endl;
		//cout<<"cycles: "<<my_processes[i].cycles<<endl;
		//cout<<"memory: "<<my_processes[i].memory<<" kb"<<endl;
		//cout<<"----------------"<<endl;
		
		i++;
	}
	//my_processes now stores all process objects
	
	
	/*
	//give results
	cout<<endl<<"~Results~"<<endl;
	results << "{\n";
	
	//Cycles Mean
	double cycle_mean = total_cycles/i;			
	cout<<"~cycle mean: "<<cycle_mean<<endl;
	results << "\t\"cycle mean\" : "<<"\""<<cycle_mean<<"\""<<endl;
	
	//Memory Mean
	double memory_mean = total_memory/i;
	cout<<"~memory mean: "<<memory_mean<<endl<<endl;
	results << "\t\"memory mean\" : "<<"\""<<memory_mean<<"\""<<endl;
	*/
	
	return my_processes;	//return vector of datatype my_process
}

//"processes" vector holds all processes from generate_processes
//processes are added to the "scheduler" vector every 50 cycles
//once complete, a process gets removed from scheduler vector and moved to "completed" vector
void round_robin(vector <my_process> processes, int quantum){
	int wait_time = 0;				//total wait time from all processes after they complete
	int penalty = 0;				//total context switch penalty cycles
	int completed_processes = 0;	//track how many processes have completed
	bool complete = false;			//checks if all 50 processes have been completely processed
	
	vector <my_process> scheduler;	//processes enter this vector every 50 cycles
	vector <my_process> completed;	//once a process is done in the scheduler, it is pushed into the 
	
	
	//run until all processes have left
	while(!complete){
		
		
		//this adds a process to the scheduler every 50 cycles
		//the new process is added to the back of the scheduler
		if(!processes.empty()){
			scheduler.push_back(processes.back());	//add process to scheduler vector
			//this happens every loop because each loop represents 50 cycles
			processes.pop_back();	//remove from processes' back
		}
		
		
		//front process is now being worked on;
		//remove 50 cycles worth of processing
		scheduler.front().cycles -= 50;
		
	
		//remove process if it has zero or less cycles
		if(scheduler.front().cycles <= 0){

			completed_processes++;	//track how many processes have completed
			//cout<<"Processes Completed: "<<completed_processes<<endl;
			//cout<<"Process: "<<scheduler.front().process_id<<" complete."<<endl;
			
			//after all 50 processes are done
			if(completed_processes == 50){
				complete = true;
			}
			
			//push process to completed vector
			//we need to store the processes so we can analyze the wait time
			wait_time = scheduler.front().wait_time;
			
			
			//pop current process
			scheduler.erase(scheduler.begin());
			scheduler.shrink_to_fit();
			//next process becomes the front of the scheduler
		}
		else{
			
			//done working with current process; 50 cycles have passed
			//push current process back
			scheduler.push_back(scheduler[0]);
			scheduler.erase(scheduler.begin());	//remove from front
			scheduler.shrink_to_fit();
		}

		//every 50 cycles (one loop),
		//give each process in the scheduler a 50 cycle increase in wait time
		for(unsigned i = 0; i < scheduler.size(); i++){
    		scheduler[i].wait_time += 50;
		}
		
		
		
		//if or else, process still needs to context switch
		penalty += 10;	//context switch penalty
	
	}
	
	//writing results for analysis
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
	cout<<"~ Round Robin Complete ~"<<endl;
	cout<<"~ Average Wait Time: "<<wait_time/50<<endl;
	cout<<"~ Penalty: "<<penalty<<endl;
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
}

int main(){
	int k = 50;				//number of processes
	int quantum = 50;		//how much time each process gets
	int disciplines;		//user options 1, 2, or 3
	srand (time(NULL));		//init random

	//switch that can switch which scheduling method to use
	cout<<endl<<"Enter Scheduling Discipline Number"<<endl;
	cout<<"1 = Round Robin, 2 = SRT, 3 = SJF"<<endl;
	cin>>disciplines;
	
	//generate 50 process with varying cycles and memory
	//store result to "processes" vector
	vector <my_process> processes = generate_processes(k);
	
	
	switch(disciplines){
		case 1:	//run "processes" through round_robin with quantum 50
				round_robin(processes, quantum);
				break;
		case 2:
				break;
		case 3:
				break;
	}


	return 0;
}