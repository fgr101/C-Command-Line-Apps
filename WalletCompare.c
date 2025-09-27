#include <stdio.h>
#include <unistd.h>

//int BankNumber;
int BankID;
int Options;

float RecibidoReales[4];
float RecibidoUSDT[4];
float BRLtoUSDT[4];
float USDTtoBRL[4];
char BankName[4][20];
int MAX_STORAGE = 4;

int i;
int f;
float MaxValue;
int BestApp;

FILE *FilePointer; // Declares the file pointer globally

void ClearScreen();
void AskForInformation();
void Save();
void Load();
void FileExists();
void DeleteData();
void Reports();
void WaitKey();

char input;
char UserInput[10];

#ifdef _WIN32
	
	#include <windows.h> // Required for Sleep() on Windows 

#endif

int main () {
	
	printf("Checking if file exists...");
	FileExists(); //Checks if file exists...
	printf("Ok...");
	
	printf("Loading data...");
	Load(); //Loads variables from the file...
	printf("Ok...");

	main:
	
	Options = 0;
	ClearScreen();
	
	printf ("Wallet Compare 0.1 \n");
	printf ("====== ======= === \n");
	
	i = 0;
	
	for (i = 0; i < MAX_STORAGE; i++) {
		
		printf("\n App %d | %s --> Pays each USD: BRL $%.3f", i + 1, BankName[i], BRLtoUSDT[i]);
		printf(" | Pays each BRL: USD $%.3f", USDTtoBRL[i]);
		
	}
	
	printf("\n\n"); // Printing bank names in the menu.
	
	for (i = 0; i < MAX_STORAGE; i++) { 
	
		if (BankName[i][20] != '\0') { // --> '\0' se usa para representar un caracter vacio. [PASAR AL CUADERNO] 
			
			printf("%d- Input Values for %s\n", i + 1, BankName[i]);
		
		} else { 
			
			f = i + 1;
			printf("%d- Input Values for App %d \n", f, i + 1);
			
		}
	
	}

	printf("\n5- Reports\n");
	printf("6- Delete Data File \n");
	printf("77- Exit \n\n");
	
	scanf("%d", &Options);

	switch (Options) {
	
		case 1:
			
			BankID = 0;
			AskForInformation();
			break;
		
		case 2:
		
			BankID = 1;
			AskForInformation();
			break;
			
		case 3:
		
			BankID = 2;
			AskForInformation();
			break;
			
		case 4:
		
			BankID = 3;
			AskForInformation();
			break;
			
		case 5:
		
			Reports();
			goto main;
			break;
			
		case 6:
		
			Options = 0;
			printf ("\n Input 1235 to confirm the action >> "); 
			scanf ("%d", &Options);
				
			if (Options == 1235) {
					
				DeleteData();
				printf("\nAll variables and data file have been succesfully deleted!");
				WaitKey();
				break;
				
			} else {
				
				printf("\nThe input wasn't 1235 so the action has been cancelled...");
				WaitKey();
			}
			
			break;

		case 77:
			
			Save();
			printf("\nEnding...");
			return 0;
			break;
					
		default:
		
			goto main;
			break;
			
	}
		
goto main;
return 0;

}

//CLS Function
void ClearScreen() {

#ifdef _WIN32
    
    // Windows
    system("cls");

#else
    
    // Unix-like systems
    system("clear");

#endif

}

//Ask for currencies exchange rates and app information.

void AskForInformation() {
	
	printf("App, FinTech or Bank Name:\n");
	scanf("%20s", UserInput);
	
	strcpy(BankName[BankID], UserInput);
	
	printf("The ID to be stored is %s. \n", BankName[BankID]);
		
	printf ("Cantidad de REALES: ");
	scanf("%f", &RecibidoReales[BankID]);
		
	printf ("Valor recibido en USDT: ");
	scanf ("%f", &RecibidoUSDT[BankID]);

	BRLtoUSDT[BankID] = RecibidoReales[BankID] / RecibidoUSDT[BankID];  
	printf("\n\n Te pagan cada USDT: R$%.2f", BRLtoUSDT[BankID]);

	USDTtoBRL[BankID] = RecibidoUSDT[BankID] / RecibidoReales[BankID];  
	printf("\n Te pagan cada REAL en USDT: USDT $%.2f", USDTtoBRL[BankID]);
	
	Save();
	
	}
	
void Save() {

	printf("Saving...");
		
	//Abre y crea el POINTER hacia el archivo para escribir en él.
	FilePointer = fopen("compare.dat", "w+");
		
	// Si el archivo da error...
	if (FilePointer == NULL){
			
		printf("Error opening file!\n");
			
	}
		
	//Guarda las variable en el archivo...
		
		fprintf(FilePointer, "%20s\n", BankName[0]);
		fprintf(FilePointer, "%20s\n", BankName[1]);
		fprintf(FilePointer, "%20s\n", BankName[2]);
		fprintf(FilePointer, "%20s\n", BankName[3]);
		fprintf(FilePointer, "%20s\n", BankName[4]);

	
		fprintf(FilePointer, "%f\n", BRLtoUSDT[0]);
		fprintf(FilePointer, "%f\n", BRLtoUSDT[1]);
		fprintf(FilePointer, "%f\n", BRLtoUSDT[2]);
		fprintf(FilePointer, "%f\n", BRLtoUSDT[3]);
		fprintf(FilePointer, "%f\n", BRLtoUSDT[4]);
		
		fprintf(FilePointer, "%f\n", USDTtoBRL[0]);
		fprintf(FilePointer, "%f\n", USDTtoBRL[1]);
		fprintf(FilePointer, "%f\n", USDTtoBRL[2]);		
		fprintf(FilePointer, "%f\n", USDTtoBRL[3]);
		fprintf(FilePointer, "%f\n", USDTtoBRL[4]);
	    
	//Cierra el archivo...
	fclose(FilePointer);
			
}
		
void Load() {
			
	//printf("Loading...");
			
	FilePointer = fopen ("compare.dat", "r");
			
	// Si el archivo da error...
	if (FilePointer == NULL){
			
		printf("Error opening file!\n");
			
	} 			
	
	//Carga las variable desde el archivo...
	
	fscanf(FilePointer, "%20s\n", &BankName[0]);
	fscanf(FilePointer, "%20s\n", &BankName[1]);
	fscanf(FilePointer, "%20s\n", &BankName[2]);
	fscanf(FilePointer, "%20s\n", &BankName[3]);
	fscanf(FilePointer, "%20s\n", &BankName[4]);
	
	fscanf(FilePointer, "%f\n", &BRLtoUSDT[0]);
	fscanf(FilePointer, "%f\n", &BRLtoUSDT[1]);
	fscanf(FilePointer, "%f\n", &BRLtoUSDT[2]);
	fscanf(FilePointer, "%f\n", &BRLtoUSDT[3]);
	fscanf(FilePointer, "%f\n", &BRLtoUSDT[4]);
		
	fscanf(FilePointer, "%f\n", &USDTtoBRL[0]);
	fscanf(FilePointer, "%f\n", &USDTtoBRL[1]);
	fscanf(FilePointer, "%f\n", &USDTtoBRL[2]);		
	fscanf(FilePointer, "%f\n", &USDTtoBRL[3]);
	fscanf(FilePointer, "%f\n", &USDTtoBRL[4]);
		
	fclose(FilePointer);

}

void FileExists() {
	
	//==================================================================
	// CREATES DATA FILE (IF IT DOESN'T EXIST)

	const char * filename = "compare.dat";

	// Check if the file exists

	if (access(filename, F_OK) != -1) {
		
		printf("Data file is ok. Continue... \n");
		return;
		
	} else {
			
			// File doesn't exist, create a new file
			
			FilePointer = fopen(filename, "w+");
			printf("File does not exist. New file created. \n");
			fclose(FilePointer);
			return;
		
		}

	// Check if the file was opened successfully
	if (FilePointer == NULL) {
		
		printf("Error opening the file.\n");
		return;

	}

	//Close the file
	fclose(FilePointer);

	//==================================================================
	
}

void DeleteData() {

	for (i = 0; i <= MAX_STORAGE; i++) {
			
		BRLtoUSDT[i] = 0;
		USDTtoBRL[i] = 0;
		strcpy(BankName[i], "");
	}
		
	printf("\nRemoving file...");

	#ifdef _WIN32
		
		// Windows
		system("del compare.dat");

	#else
		
		// Unix-like systems
		system("rm compare.dat");

	#endif

	printf("\nRemoving file OK...");
	
}

void Reports() {
	
	// Initialize MaxValue and BestApp
	
	MaxValue = -1.00; // Use a sentinel value that cannot be exceeded by valid data like BRLtoUSDT[i]
	BestApp = -1;  // Indicates no best app yet
	
	for (i = 0; i < MAX_STORAGE; i++) {
		
		if (USDTtoBRL[i] > MaxValue) {
			
			MaxValue = USDTtoBRL[i];
			BestApp = i;
		
		}
	
	}
	
	printf("\nThe best app is number %d, %s. It gives you USDT $%.3f for each BRL.\n", BestApp + 1, BankName[BestApp], USDTtoBRL[BestApp]);
	printf("The exchange rate for each USDT is 1 USDT = R$%.2f BRL.\n\n", BRLtoUSDT[BestApp]);
	
	WaitKey();
	
}

void WaitKey() {
	
	// Loop until a key is pressed
	
	printf("\nInput any number to continue >> ");
			
	do {
			
		input = getchar();
		
	} while (input == '\n'); // Ignore newline characters

	return;

}

// NOTES
// =====

// Que también calcule el interest que cobran cada una de las aplicaciones.


// =====================================================================

// DONE
// ====

// V.0.1
// -----

// Hay que escribir 1235 para confirmar y poder borrar todas las 
// variable en la opción 6. [OK] 100%

// Se puede agregar los nombres de las apps, por ejemplo BELO, 
// TAKENOS, etc. [OK] 100%

//* Arreglar BUG de datos que no quedan bien guardados, se borran los 
// valores. Variables no cargan correctamente. [OK] 100%
