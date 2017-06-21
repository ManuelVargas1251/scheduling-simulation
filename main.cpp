//Manuel Vargas
//Project

//how to compile
//	g++ project.cpp -o p

//how to run	
//	./p

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
	
	//writing results to file for analysis
	ofstream results;
	results.open ("results.json",std::ios_base::app);
	
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

//processes holds all processes
//after 50 cycles, a new process is added to the queue vector from processes vector
void round_robin(vector <my_process> processes, int quantum){
	int wait_time = 0;
	int penalty = 0;
	int completed_processes = 0;
	vector <my_process> scheduler;
	bool complete = false;
	
	//run until all processes have left
	while(!complete){
		
		if(!processes.empty()){
			scheduler.push_back(processes.back());	//add process to scheduler vector
			//this happens every loop because each loop represents 50 cycles
			processes.pop_back();	//remove from processes' back
		}
		
		//process is now being worked on;
		//remove 50 cycles worth of processing
		scheduler.front().cycles -= 50;
		
	
		//remove process if it has zero or less cycles
		if(scheduler.front().cycles <= 0){

			completed_processes++;	//track how many processes have completed
			//cout<<"Processes Completed: "<<completed_processes<<endl;
			
			//after all 50 processes are done
			if(completed_processes == 50){
				complete = true;
			}
			
			//pop current process
			scheduler.erase(scheduler.begin());

			//when process ends, scheduler must switch
			penalty += 10;		//context switch penalty
			wait_time += 10;	//total wait time
		}
		else{
			//push current process back if .cycles > 0
			scheduler.push_back(scheduler[0]);
			scheduler.erase(scheduler.begin());	//remove from front
			scheduler.shrink_to_fit();
		}

		wait_time += 50;	//each loop counts as 50 cycles
	}
	
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
	cout<<"~ Round Robin Complete ~"<<endl;
	cout<<"~ wait time: "<<wait_time<<endl;
	cout<<"~ penalty: "<<penalty<<endl;
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
}

int main(){
	int k = 50;				//number of processes
	int quantum = 50;		//how much time each process gets
	int disciplines;		//user options 1, 2, or 3
	srand (time(NULL));		//init random

	//make a switch that can switch which scheduling method to use
	//cout<<"Enter Scheduling Discipline Number:\n";
	//cout<<"1. Round Robin, 2.SRT, 3. SJF"
	//cin>>disciplines;
	
	//generate 50 process with varying cycles and memory
	//store result to processes vector
	vector <my_process> processes = generate_processes(k);
	
	//run processes through round_robin
	round_robin(processes, quantum);
	
	
	//example usage of vector
	//cout<<"49: "<<processes[49].cycles<<endl;

	return 0;
}