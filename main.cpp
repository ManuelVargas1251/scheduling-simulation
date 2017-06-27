/*
Manuel Vargas
Alish Shrestha
Project

how to compile
	make

how to run	
	./main
*/

#include <iostream>
#include <stdlib.h> 
#include <time.h>    
#include <vector>
#include <fstream>

using namespace std;

//my headers
#include "my_process.h"	//contains structure definition
//#include "round_robin.h"

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
	
	
	//will move this to each scheduling discipline for export
	//writing results to file for analysis
	//ofstream results;
   	//results.open ("results.json",std::ios_base::app);
	
	
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

//Round Robin Scheduling Discipline
//"processes" vector holds all processes from generate_processes
//processes are added to the "scheduler" vector every 50 cycles
//once complete, a process gets removed from scheduler vector and moved to "completed" vector
void round_robin(vector <my_process> processes, int quantum){
	int wait_time = 0;				//total wait time from all processes after they complete
	int penalty = 0;				//total context switch penalty cycles
	int completed_processes = 0;	//track how many processes have completed
	bool complete = false;			//checks if all 50 processes have been completely processed
	vector <my_process> scheduler;	//processes enter this vector every 50 cycles 
	
	//run until all processes have left the scheduler
	while(!complete){
		
		
		//this adds a process to the scheduler every 50 cycles
		//the new process is added to the back of the scheduler
		//this will stop when the vector of processes is empty
        //this happens every loop because each loop represents 50 cycles
		if(!processes.empty()){
			scheduler.push_back(processes.back());
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
            //this breaks out of the loop after the 50 p's are done
			if(completed_processes == 50){
				complete = true;
			}
			
			//store current proccess' final wait time to total wait time
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
        //except for the first process which is the current one (front of vector)
		for(unsigned i = 1; i < scheduler.size(); i++){
    		scheduler[i].wait_time += 50;
		}
		
		if(!scheduler.empty()){
            //if or else, process still needs to context switch
            penalty += 10;	//context switch penalty
        }
	}
	
	//writing results for analysis
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
	cout<<"~ Round Robin Complete ~"<<endl;
	cout<<"~ Average Wait Time: "<<wait_time/50<<endl;
	cout<<"~ Penalty: "<<penalty<<endl;
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
}

//FIFO Scheduling Discipline
void fifo(vector <my_process> processes){
    int wait_time = 0;              //total wait time from all processes after they complete
    int penalty = 0;				//total context switch penalty cycles
	int completed_processes = 0;	//track how many processes have completed
	bool complete = false;			//checks if all 50 processes have been completely processed
	vector <my_process> scheduler;	//processes enter this vector every 50 cycles
	
	
	//run until all processes have left
	while(!complete){
		
		//this adds a process to the scheduler every 50 cycles
		//the new process is added to the back of the scheduler
		//this will stop when the vector of processes is empty
		if(!processes.empty()){
			scheduler.push_back(processes.back());	//add process to scheduler vector
			//this happens every loop because each loop represents 50 cycles
			processes.pop_back();	//remove from processes' back
		}
        
        
        //front process is now being worked on
		//remove 50 cycles worth of processing from it
		scheduler.front().cycles -= 50;
        
        
        if(scheduler.front().cycles <= 0){

			completed_processes++;	//track how many processes have completed
			//cout<<"Processes Completed: "<<completed_processes<<endl;
			//cout<<"Process: "<<scheduler.front().process_id<<" complete."<<endl;
			
			//after all 50 processes are done
			if(completed_processes == 50){
				complete = true;
			}
			
			//store proccess' final wait time to total wait time
			wait_time = scheduler.front().wait_time;
			
			
			//pop current process
			scheduler.erase(scheduler.begin());
			scheduler.shrink_to_fit();
			//next process becomes the front of the scheduler
            
            if(!scheduler.empty()){
                penalty += 10;	//context switch penalty
            }
		}
		else{
			
            //keep current process in front
            //cannot context switch until current process is done
		}

		//every 50 cycles (one loop),
		//give each process in the scheduler a 50 cycle increase in wait time
        //except for the first process which is the current one (front of vector)
		for(unsigned i = 1; i < scheduler.size(); i++){
    		scheduler[i].wait_time += 50;
		}		
	}
    //writing results for analysis
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"~ FIFO Complete ~"<<endl;
    cout<<"~ Average Wait Time: "<<wait_time/50<<endl;
    cout<<"~ Penalty: "<<penalty<<endl;
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
}

//SRT Scheduling Discipline
void srt(vector <my_process> processes){
	int wait_time = 0;				//total wait time from all processes after they complete
	int penalty = 0;				//total context switch penalty cycles
	int completed_processes = 0;	//track how many processes have completed
	bool complete = false;			//checks if all 50 processes have been completely processed
	vector <my_process> scheduler;	//processes enter this vector every 50 cycles 
	
	//run until all processes have left the scheduler
	while(!complete){
		//this adds a process to the scheduler every 50 cycles
		//the new process is added to the back of the scheduler
		//this will stop when the vector of processes is empty
        //this happens every loop because each loop represents 50 cycles
		if(!processes.empty()){
			scheduler.push_back(processes.back());
			processes.pop_back();	//remove from processes' back
		

            //after the new process comes in,
            //we need to find the process with the least
            //cycles in the scheduler at this time
            //and switch it to the front of the vector

            //set an initial shortest cycle to start testing
            int shortest_index = 999;
            int shortest_cycle = scheduler.front().cycles;

            //this will iterate through the vector and store the location
            //of the process with the shortest cycles to test
            for(unsigned j = 0; j < scheduler.size(); j++){
                if(scheduler[j].cycles < shortest_cycle){
                    shortest_index = j;
                    shortest_cycle = scheduler[j].cycles;
                }
            }

            cout<<"shortest' cycle: "<<shortest_cycle<<endl;
            //cout<<"shortest' index: "<<shortest_index<<endl;


            //remove the front process and move it to the back
            scheduler.push_back(scheduler.front());
            //scheduler.erase(scheduler.begin());

            //copy short_cycle process to the front
            scheduler.front() = scheduler[shortest_index];

            //shortest_cycles += 3;
            //remove that process from it's former position

            scheduler.erase(scheduler.begin()+shortest_index);

            //context has switch = penalty
            if(!scheduler.empty()){
                penalty += 10;	//context switch penalty
            }
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
            //this breaks out of the loop after the 50 p's are done
			if(completed_processes == 50){
				complete = true;
			}
			
			//store current proccess' final wait time to total wait time
			wait_time = scheduler.front().wait_time;
			
			
			//pop current process
			scheduler.erase(scheduler.begin());
			scheduler.shrink_to_fit();
			//next process becomes the front of the scheduler
		}
		else{
			
			//done working with current process; 50 cycles have passed
			//push current process back
			//scheduler.push_back(scheduler[0]);
			//scheduler.erase(scheduler.begin());	//remove from front
			//scheduler.shrink_to_fit();
		}

		//every 50 cycles (one loop),
		//give each process in the scheduler a 50 cycle increase in wait time
        //except for the first process which is the current one (front of vector)
		for(unsigned i = 1; i < scheduler.size(); i++){
    		scheduler[i].wait_time += 50;
		}
	}
	
	//writing results for analysis
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
	cout<<"~ SRT Complete ~"<<endl;
	cout<<"~ Average Wait Time: "<<wait_time/50<<endl;
	cout<<"~ Penalty: "<<penalty<<endl;
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;    
}

int main(){
	int k = 50;            //number of processes
	int quantum = 50;      //how much time each process gets
	int discipline;        //user options 1, 2, or 3
	srand (time(NULL));	   //init random

	cout<<endl<<"Enter Scheduling Discipline Number"<<endl;
	cout<<"1 = Round Robin, 2 = FIFO, 3 = SJF"<<endl;
	cin>>discipline;
	
	//generate 50 process with varying cycles and memory
	//store result to "processes" vector
	vector <my_process> processes = generate_processes(k);
	
	//switch executes whichever discipline user wanted
    //each function passes processes vector
	switch(discipline){
		case 1:	//Round Robin
				//each process get quantum 50 before it's switched
				round_robin(processes, quantum);
				break;
		case 2: //First In First Out
				//first processes remain in front until completed
				fifo(processes);
				break;
		case 3:	//Shortest Remaining Time
				//process with shortest cycles get switched to
				srt(processes);
				break;
		default://if incorrect input, exit with error
				cout<<"error: must enter a 1, 2 or 3"<<endl;
				break;
	}
	return 0;
}
