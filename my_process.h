#ifndef MY_PROCESS_H
#define MY_PROCESS_H

struct my_process {

	int process_id;	//random from 10,000
	int cycles;		//from 1,000, 11,000
	int memory;		//1KB to 100KB with a mean memory footprint of 20KB.
  
	//constructor
	my_process(int i){
		process_id = i;				//get num from i
		cycles = get_cycles();		//get num from function
		memory = get_memory();		//get num from function
	}
  
	//get random cycles
	//from 1,000 to 11,000 with mean of 6000
	int get_cycles(){
		int cycles;

		//trying to get a 6000 mean
		if(rand() % 2 == 0)
			cycles = rand() % 4999+6001; 	//returns 6001 through 11000
		else
			cycles = rand() % 6000+1001;  	//returns 1000 through 6000

		return cycles;
	}
  
	//get random memory
	//from 1KB to 100KB with mean of 20kb
	int get_memory(){
		int mem;
		
		//if the random number = 0, return a number btwn 21KB through 100KB
		//this is less likely and will let memory be less than 20 the majority of the time
		if(rand() % 5 == 0)
            mem = rand() % 79+21;		//returns 21KB through 100KB
        else
            mem = rand() % 20+1;		//returns 1KB through 20KB

		return mem;
	}
};

#endif