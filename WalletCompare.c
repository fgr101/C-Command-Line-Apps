#include <stdio.h>
#include <unistd.h>

//int BankNumber;
int BankID;
int Options;

float RecibidoReales[3];
float RecibidoUSDT[3];
float BRLtoUSDT[3];
float USDTtoBRL[3];
int MAX_STORAGE = 3;
int i;

FILE *FilePointer; // Declares the file pointer globally

void ClearScreen();
void AskForInformation();
void Save();
void Load();
void FileExists();

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
	
	printf ("Wallet Compare 0.1 \n\n");
	
	printf("\n %.2f", BRLtoUSDT[0]);
	printf("\n %.2f", BRLtoUSDT[1]);
	printf("\n %.2f", BRLtoUSDT[2]);
	printf("\n %.2f", BRLtoUSDT[3]);
	
	printf("\n\n1- Bank 1 \n");
	printf("2- Bank 2 \n");
	printf("3- Bank 3 \n\n");
	
	scanf("%d", &Options);

	switch (Options) {
	
		case 1:
			
			BankID = 1;
			AskForInformation();
			break;
		
		case 2:
		
			BankID = 2;
			AskForInformation();
			break;
			
		case 3:
		
			BankID = 3;
			AskForInformation();
			break;
					
		default:
		
			goto main;
			break;
			
	}
		

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
	fprintf(FilePointer, "%f", BRLtoUSDT[BankID]);
	fprintf(FilePointer, "%f", USDTtoBRL[BankID]);
	    
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
			
	i = 0;
	
	//Carga las variable desde el archivo...
	for (i = 0; i <= MAX_STORAGE; i++) {
		
		fscanf(FilePointer, "%f", &BRLtoUSDT[i]);
		fscanf(FilePointer, "%f", &USDTtoBRL[i]);
		
	}
	
	return;
	//fclose(FilePointer);		

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






// NOTES
// =====

//* Arreglar BUG de salvar datos, variables no cargan correctamente.
//* Que las variables queden guardadas en el programita.
 
