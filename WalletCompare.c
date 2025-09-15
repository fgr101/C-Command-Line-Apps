#include <stdio.h>

//int BankNumber;
int BankID;
int Options;

float RecibidoReales[3];
float RecibidoUSDT[3];
float BRLtoUSDT[3];
float USDTtoBRL[3];

void ClearScreen();
void AskForInformation();
void Save();

FILE *FilePointer; // Declares the file pointer globally

#ifdef _WIN32
	
	#include <windows.h> // Required for Sleep() on Windows 

#endif

int main () {
	
	//system("dir /w");
	
	main:
	
	Options = 0;
	ClearScreen();
	
	printf ("Wallet Compare 0.1 \n\n");
	
	printf("1- Bank 1 \n");
	//printf("2- Bank 2 \n");
	//printf("3- Bank 3 \n\n");
	
	scanf("%d", &Options);

	switch (Options) {
	
		case 1:
			
			BankID = 1;
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
		
		FilePointer = fopen("compare.dat", "w+"); //Crea el POINTER hacia el archivo.
		
		if (FilePointer == NULL){ // Si el archivo da error...
			
			printf("Error opening file!\n");
			
		}
		
		//Guarda las variable en el archivo...
		
	    fprintf(FilePointer, "%f\n", BRLtoUSDT[BankID]);
	    fprintf(FilePointer, "%f\n", USDTtoBRL[BankID]);
	    
	    //Cierra el archivo...
	    
    	fclose(FilePointer);
			
		}

