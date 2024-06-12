#include<stdio.h> 
#include<iostream>
#include <fstream>
using namespace std;

int main(){
	//initiate file variable
	ifstream inFile;
	//other variable
	int count, time, remain, time_quantum,  var, data;
	int flag=0, limit=30, wait_time=0, turnaround_time=0, num_of_interrupts=0, num_of_jobs=0, arrival_time=30;
	int rt[30], total_process[29] = {0}; 
	
	//initiate arrival time
	int at[] = 	{1, 45, 81, 165, 247, 303, 402, 403, 446, 517,
				527, 538, 617, 618, 714, 724, 732, 740, 772, 783,
				864, 879, 930, 1004, 1100, 1151, 1249, 1289, 1309, 1403};
				
	cout<<"Your job list :\n";
	
	for(var = 1; var <= limit; var++){
		
		//the purpose is the check weither looping is okay or not
		cout << "" << var;
		
		//preparing array for the file
		char nambuf[30];
		
  		std::snprintf(nambuf, sizeof(nambuf), "jobs/job%d.txt", var);
  		std::ifstream inFile;
  		
		//open file
  		inFile.open(nambuf);
		
		//check file 
		if (!inFile) {
        	cout << " Unable to open file";
        	exit(1); // terminate with error
    	}
		
		//read data from file .txt    
    	while (inFile >> data) {
    		//calculate total process from data
        	total_process[var-1] += data;
        	++data;
    	}
    	
    	//close file
    	inFile.close();
    	
    	//print total process
		cout << " Burst time = " << total_process[var-1] << endl;    	 
	}
	
		remain = limit; 
	
		for(count = 0; count < limit; count++) { 
    		rt[count] = total_process[count]; 
		}
	
		cout << endl << endl;
		cout << "Enter Time Quantum:\t"; 
		//get time quantum from user
		cin >> time_quantum; 
  
		cout << "\n______________________________________________________________\n";	
		cout << "| Job \t|  Burst time  |  Waiting time  |  Turn around time  |";
		cout << "\n|_______|______________|________________|____________________|\n";
	
		for(time=0, count=0; remain != 0;) { 
	
		    if(rt[count] <= time_quantum && rt[count] > 0) {  // condition when rt is less than or equal to time quantum
    			time += rt[count]; 
    			rt[count] = 0; 
    			flag = 1; 
    			num_of_interrupts++;
    		}
		 
    		else if(rt[count] > 0) {  //condition when rt is more than 0 / more than time quantum
    			rt[count] -= time_quantum; 
    			time += time_quantum; 
    			num_of_interrupts++;
    		}
		 
    		if(rt[count] == 0 && flag == 1) { //to print all the info
    			remain--; 
	  
	  			printf ("|  %d\t|     %d      |     %d      |\t%d\t     |", count+1, total_process[count], time-at[count], time-at[count]-total_process[count]);
	  			printf("\n|_______|______________|________________|____________________|\n");
		 
      			wait_time += time - at[count] - total_process[count]; 
      			turnaround_time += time - at[count]; 
      			flag = 0; 
      			num_of_jobs++;
    		}
		 
    		if(count == limit-1) 
      			count = 0; 
    		else if(at[count+1] <= time) 
      			count++; 
    		else 
      			count=0; 
  		} 
  		
  		cout << endl << endl;
  		cout << "Average Waiting Time= " << wait_time*1.0/limit << endl; 
  		cout << "Avg Turnaround Time = " << turnaround_time*1.0/limit << endl; 
		cout << "Number of interrupts = " << num_of_interrupts * num_of_jobs;
  
  
	return 0;
}
