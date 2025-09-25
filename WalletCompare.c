#include <stdio.h>
#include <unistd.h>

//int BankNumber;
int BankID;
int Options;

float RecibidoReales[4];
float RecibidoUSDT[4];
float BRLtoUSDT[4];
float USDTtoBRL[4];
int MAX_STORAGE = 4;

int i;
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

	//system("dir /w");
	
	main:
	
	Options = 0;
	ClearScreen();
	
	printf ("Wallet Compare 0.1 \n");
	printf ("====== ======= === \n\n");
	
	i = 0;
	
	for (i = 0; i < MAX_STORAGE; i++) {
		
		printf("\n\n App %d --> Pays each USD: BRL $%.3f", i, BRLtoUSDT[i]);
		printf("\n App %d --> Pays each BRL: USD $%.3f", i, USDTtoBRL[i]);
		
	}
	
	printf("\n\n1- Input Values for App 1 \n");
	printf("2- Input Values for App 2 \n");
	printf("3- Input Values for App 3 \n");
	printf("4- Input Values for App 4 \n");
	printf("5- Reports\n");
	printf("6- Delete Data File \n");
	printf("7- Exit \n\n");
	
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
		
			DeleteData();
			break;
		
		case 7:
			
			Save();
			printf("\nEnding...");
			return 0;
			break;
					
		default:
		
			goto main;
			break;
			
	}
		
goto main;
printf("RETURN 0");
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
		
	
	
		fprintf(FilePointer, "%f\n", BRLtoUSDT[0]);
		fprintf(FilePointer, "%f\n", BRLtoUSDT[1]);
		fprintf(FilePointer, "%f\n", BRLtoUSDT[2]);
		fprintf(FilePointer, "%f\n", BRLtoUSDT[3]);
		
		fprintf(FilePointer, "%f\n", USDTtoBRL[0]);
		fprintf(FilePointer, "%f\n", USDTtoBRL[1]);
		fprintf(FilePointer, "%f\n", USDTtoBRL[2]);		
		fprintf(FilePointer, "%f\n", USDTtoBRL[3]);
		
	//int i;
			
	//for (i = 0; i <= MAX_STORAGE; i++) {
		
		//fprintf(FilePointer, "%f", BRLtoUSDT[i]);
		//fprintf(FilePointer, "%f", USDTtoBRL[i]);
		
	//}
	    
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
	
	fscanf(FilePointer, "%f\n", &BRLtoUSDT[0]);
	fscanf(FilePointer, "%f\n", &BRLtoUSDT[1]);
	fscanf(FilePointer, "%f\n", &BRLtoUSDT[2]);
	fscanf(FilePointer, "%f\n", &BRLtoUSDT[3]);
		
	fscanf(FilePointer, "%f\n", &USDTtoBRL[0]);
	fscanf(FilePointer, "%f\n", &USDTtoBRL[1]);
	fscanf(FilePointer, "%f\n", &USDTtoBRL[2]);		
	fscanf(FilePointer, "%f\n", &USDTtoBRL[3]);
	
	//int i;
	
	//for (i = 0; i <= MAX_STORAGE; i++) {
		
		//fscanf(FilePointer, "%f", &BRLtoUSDT[i]);
		//fscanf(FilePointer, "%f", &USDTtoBRL[i]);
		
	//}
	
	fclose(FilePointer);		
	//return;

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

int i;

for (i = 0; i <= MAX_STORAGE; i++) {
		
	BRLtoUSDT[i] = 0;
	USDTtoBRL[i] = 0;
		
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
	
	printf("\nThe best app is number %d. It gives you USDT $%.3f for each BRL.\n", BestApp, USDTtoBRL[BestApp]);
	printf("The exchange rate for each USDT is 1 USDT = R$%.2f BRL.\n\n", BRLtoUSDT[BestApp]);
	
	WaitKey();
	
}

void WaitKey() {
	
	// Loop until a key is pressed
	
	printf("\n- Input any number to continue >> ");
			
	do {
			
		input = getchar();
		
	} while (input == '\n'); // Ignore newline characters

	//printf("\n Key '%c' pressed. Program continues...\n", input);

	return;

}

// NOTES
// =====

// Que tengas que escribir 1235 para confirmar y poder borrar todas las 
// variable en la opción 6.

// Que se le pueda agregar los nombres a la app, por ejemplo BELO, 
// TAKENOS, etc.

// =====================================================================

// DONE
// ====

// V.0.1

//* Arreglar BUG de datos que no quedan bien guardados, se borran los 
// valores. Variables no cargan correctamente. [OK] 100%
