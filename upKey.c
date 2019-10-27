#include<stdio.h>

extern int upCount(char command[]){
	int count=0; 
	if(command[0]=='')
	{
		for(int i=0; i<100; i++)
		{
			if(command[i]=='')
				count++;
		}
	}
	return count;
}
