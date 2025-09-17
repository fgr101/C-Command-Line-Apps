#include <stdio.h>
#include <stdlib.h> // Contains the rand() function.
#include <time.h> // Time and random functions

void DrawPlainMap();
void RndTerrainMap();
void LessRndMap();
void LandWallsMap();
void TerrainIDMap();
void MapAndPlayer1();

void RollD6();

int f;
int i;
char al;

int TerrainID[4921];
int TerrainCounter;
int PositionPlayer;
int MapLoop;

int opciones;
int D6;

int main() {
	
	srand(time(NULL));
	 
	printf("[1] Draw Plain Map \n");
	printf("[2] Draw FULL Randomized Map \n");
	printf("[3] Draw LESS Randomized Map \n");
	printf("[4] Draw Land and Walls Randomized Map \n");
	printf("[5] Draw ID Terrain Map [Prototipe 0] \n");
	printf("[6] ID Terrain Map plus Player [Prototipe 1] \n");
	printf("\n\n");
		
	scanf("%d", &opciones);
	
	switch(opciones) {	   
	
		case 1: 
		
			DrawPlainMap();
			break;
    
		case 2:
		
			RndTerrainMap();
			break;
					
		case 3:
		
			LessRndMap();
			break;
			
		case 4:
		
			LandWallsMap();
		
		case 5:
		
			TerrainIDMap();
		
		case 6:
		
			MapAndPlayer1();
    }
              
	return 0;

}

//Draw Plain Map
void DrawPlainMap() {
	
	f = 0;
	i = 1;		
					
	do {
	
		do {
										
			al = 'w';
										
			printf ("%c", al);
			i++;
						
		} while (i < 134);
		
		printf ("\n");
		i = 1;
		f ++;
					
	} while (f < 37);
	
}

//Draw Full Random Terrain Map			
void RndTerrainMap() {
	
	f = 0;
	i = 1;		
				
	do {
		
		do {
			
			RollD6();
			
			switch(D6) {
				
				case 1: 
				
					al = 'w';
					break;
					
				case 2:
				
					al = '.';
					break;
					
				case 3:
				
					al = '#';
					break;
					
				case 4:
				
					al = ' ';
					break;
					
				case 5:
				
					al = 'x';
					break;
					
				case 6:
				
					al = '~';
					break;
					
			}
										
			printf ("%c", al);
			i++;
						
		} while (i < 134);
		
		printf ("\n");
		i = 1;
		f ++;
					
	} while (f < 37);
	
}

//Less Randomized Terrain Map
void LessRndMap() {
	
	f = 0;
	i = 1;		
				
	do {
		
		do {
			
			if (al == '#' || al == ' ') {
				
				RollD6(); 
				if (D6 < 5) {D6 = 7; goto SkipRolling;}
				
			}
			
			RollD6();
			SkipRolling:
			
			switch(D6) {
				
				case 1: 
				
					al = '.';
					break;
					
				case 2:
				
					al = '.';
					break;
					
				case 3:
				
					al = '#';
					break;
					
				case 4:
				
					al = ' ';
					break;
					
				case 5:
				
					al = '.';
					break;
					
				case 6:
				
					al = ' ';
					break;
					
				default:
				
					break;
					
			}
										
			printf ("%c", al);
			i++;
						
		} while (i < 134);
		
		printf ("\n");
		i = 1;
		f ++;
					
	} while (f < 37);
	
}

//Only land and walls Map
void LandWallsMap() {
	
	f = 0;
	i = 1;		
				
	do {
		
		do {
			
			if (al == '#') {
				
				RollD6(); 
				if (D6 < 5) {D6 = 7; goto SkipRolling;}
				
			}
			
			if (al == ' ') {
				
				RollD6(); 
				if (D6 < 4) {D6 = 7; goto SkipRolling;}
				
			}
			
			RollD6();
			SkipRolling:
			
			switch(D6) {
				
				case 1: 
				
					al = '#';
					break;
					
				case 2:
				
					al = ' ';
					break;
					
				case 3:
				
					al = ' ';
					break;
					
				case 4:
				
					al = ' ';
					break;
					
				case 5:
				
					al = ' ';
					break;
					
				case 6:
				
					al = ' ';
					break;
					
				default:
				
					break;
					
			}
										
			printf ("%c", al);
			i++;
						
		} while (i < 134);
		
		printf ("\n");
		i = 1;
		f ++;
					
	} while (f < 37);
	
}


//Sorting by terrain ID [Prototipe 0]

// This prototipe identifies each terrain and stores its D6 value in an
// array called TerrainID[]. The map is formed by 4921 terrains.

void TerrainIDMap() {
	
	f = 0;
	i = 1;
	
	printf("%d", TerrainCounter);
			
				
	do {
		
		do {
			
			if (al == '#') {
				
				RollD6(); 
				if (D6 < 5) {D6 = 7; goto SkipRolling;}
				
			}
			
			if (al == ' ') {
				
				RollD6(); 
				if (D6 < 4) {D6 = 7; goto SkipRolling;}
				
			
				
			}
			
			RollD6();
			SkipRolling:
			
			switch(D6) {
				
				case 1: 
				
					al = '#';
					break;
					
				case 2:
				
					al = ' ';
					break;
					
				case 3:
				
					al = ' ';
					break;
					
				case 4:
				
					al = ' ';
					break;
					
				case 5:
				
					al = ' ';
					break;
					
				case 6:
				
					al = ' ';
					break;
					
				default:
				
					break;
					
			}
			
			TerrainID[TerrainCounter] = D6;
										
			printf ("%c", al);
			i++;
			TerrainCounter ++;
						
		} while (i < 134);
		
		printf ("\n");
		i = 1;
		f ++;
					
	} while (f < 37);
	
	printf("%d", TerrainCounter);
	
}


//Sorting by terrain ID + Player [Prototipe 1]

// This prototipe identifies each terrain and stores its D6 value in an
// array called TerrainID[]. The map is formed by 4921 terrains. It adds
// a movable player that can walk around the map.

void MapAndPlayer1() {
	
	f = 0;
	i = 1;	

	PositionPlayer = 2987;
	
	printf("Position Player: %d | ", PositionPlayer);
	printf("Terrain Counter: %d \n", TerrainCounter);
				
	do {
		
		do {
			
			if (al == '#') {
				
				RollD6(); 
				if (D6 < 5) {D6 = 8; goto SkipRolling;}
				
			}
			
			if (al == ' ') {
				
				RollD6(); 
				if (D6 < 4) {D6 = 8; goto SkipRolling;}
				
			}
			
			RollD6();
			SkipRolling:
			
			switch(D6) {
				
				case 1: 
				
					al = '#';
					break;
					
				case 2:
				
					al = ' ';
					break;
					
				case 3:
				
					al = ' ';
					break;
					
				case 4:
				
					al = ' ';
					break;
					
				case 5:
				
					al = ' ';
					break;
					
				case 6:
				
					al = ' ';
					break;
				
					
				default:
				
					break;
					
			}
			
			TerrainID[TerrainCounter] = D6;
			
			i++;
			TerrainCounter ++;
						
		} while (i < 134);
		
		printf ("\n");
		i = 1;
		f ++;
					
	} while (f < 37);
	
	//printf("%d", TerrainCounter);
	
	
	// Loop to print player and the map...
	
	do {
				
		// Drawin the map...
		
		TerrainCounter = 0;
		
		do {
			
			
			switch(TerrainID[TerrainCounter]) {
				
				case 1: 
				
					al = '#';
					break;
					
				case 2:
				
					al = ' ';
					break;
					
				case 3:
				
					al = ' ';
					break;
					
				case 4:
				
					al = ' ';
					break;
					
				case 5:
				
					al = ' ';
					break;
					
				case 6:
				
					al = ' ';
					break;
				
				default:
				
					break;
			
			}
			
			if (TerrainCounter == PositionPlayer) {al = '@';} // Shows player position.
			printf ("%c", al);
			
			TerrainCounter ++;
			
		} while (TerrainCounter != 4921);
		
		
		//Askin and waiting for user input...
		scanf("%d", &opciones);
		
		switch(opciones) {
			
			case 0:
			
				break;
				
			case 1:
				
				PositionPlayer = PositionPlayer - 134;
				break;

			
			case 2:
				
				PositionPlayer = PositionPlayer + 134;
				break;
				
			case 3:
			
				PositionPlayer --;
				break;
				
			case 4:
			
				PositionPlayer ++;
				break;
				
			default:
			
				break;
			
		}

		
	} while (opciones != 7);
}



//Roll D6
void RollD6() {
	
	D6 = (rand() % 6) + 1;
		
}

