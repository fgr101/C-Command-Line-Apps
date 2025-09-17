/*
 * CryptoTracking.c
 * 
 * Copyright 2024 ferna <ferna@ASUSNOVO>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <stdio.h>
#include <string.h> //*This is the library to work with strings.
#include <unistd.h> //*Include this for access function. Required for sleep() on Unix-like systems

void SaveData();
void Load();
void ShowPurchases();

float AMP[50];

FILE *fptr; // Declare the file pointer globally

int main() {
	
	//==================================================================
	// CREATES DATA FILE (IF IT DOESN'T EXIST)

	const char * filename = "data.dat";

	// Check if the file exists

	if (access(filename, F_OK) != -1) {
			
		//fptr = fopen(filename, "r+"); 
		Load();
			
	} else {
				
			// File doesn't exist, create a new file
				
			fptr = fopen(filename, "w+");
			printf("File does not exist. New file created. \n");
			fclose(fptr);
			
		}

	// Check if the file was opened successfully

	if (fptr == NULL) {
			
		printf("Error opening the file.\n");
		return 1; // indicate an error to the operating system

	}

	// Close the file
	//fclose(fptr);

	//==================================================================
	
	int x = 0;
	
	do {
		
		x ++; //statement
		
	} while (AMP[x]!= 0.000000);
		
	printf("Crypto Tracker 0.1 \n\n");
	
	printf("===================================== \n\n");
	
	ShowPurchases();

	printf("Add AMP purchase: \n");
	scanf("%f", &AMP[x]);
	
	printf("Last PURCHASED AMP: %f \n\n", AMP[x]);
	
	printf("===================================== \n");
	
	SaveData();
	
	return 0;
}


void SaveData() {
	
	printf("Saving...");
	
	// Save the variable to a file
	fptr = fopen("data.dat", "w+");
	
	if (fptr == NULL) {
		
		printf("Error opening file!\n");
		return;
	}

    // Write variables to the file
    
    int xloop = 0;
   	
   	do {
		
		fprintf(fptr, "%f\n", AMP[xloop]);
		xloop ++;
		
	} while (xloop != 51);
    
    //fprintf(fptr, "%f\n", SingleLessonPrice);
    //fprintf(fptr, "%f\n", GroupLessonPrice);
    //fprintf(fptr, "%f\n", DiscountValue);
        
	fclose(fptr);
	
	}
	
// LOAD Function

void Load() {
	
	printf("Loading...\n\n");
	
	 fptr = fopen("data.dat", "r");
	
    // Load the variable from the file
	
	if (fptr == NULL) {
		
		printf("Error opening file!\n");
    	return;

	}
	
	int xloop = 0;
   	
   	do {
		
		fscanf(fptr, "%f\n", &AMP[xloop]);
		xloop ++;
		
	} while (xloop != 51);
	
	fclose(fptr);
	    
}

void ShowPurchases(){
	
	int xloop = 0;
   	
   	do {
		
		printf("[%d] %f\n",xloop, AMP[xloop]);
		xloop ++;
		
	} while (AMP[xloop] != 0.000000);
	
	printf("\n\n");

}
