#include <stdio.h>  //biblioteca standar de C
#include <unistd.h> //biblioteca para poder usar la función "access" en CheckFile.
#include <string.h> //*This is the library to work with strings.

#ifdef _WIN32

	#include <windows.h> // Requerido para Sleep() y ClearScreen en Windows. 

#endif

int input;
float MontoFacturado;
float TotalFacturado;

void AdicionarTributo();
void CheckFile();
void WaitKey();
void Load();
void Save();
void ClearScreen();

//Pointers

FILE *fptr; //"fptr" pointer aplicado a todo el archivo.

int main() {
	
	ClearScreen();
	CheckFile();
	Load();	
	
	ProgramIni:
	input = 0;
		
	ClearScreen();
	printf("\nTributar 0.1");
	printf("\n============");
	
	printf("\n\nTotal facturado hasta la fecha: ARS $ %2.f", TotalFacturado);
	
	printf("\n\n1- Agregar Tributo");
	printf("\n7- Salir");
	
	printf("\n\nIngrese Opcion >> ");
	scanf("%d", &input);
	
	switch (input) {
		
		case 1:
			
			AdicionarTributo();
			Save();
			WaitKey();
			goto ProgramIni;
		
		case 7:
		
			Save();
			return 0;

		default:
		
			goto ProgramIni;
				
		}
		
	WaitKey();
	
	return 0;	
	
	}
	
void CheckFile() {
	
	printf("Check File");
	const char * filename = "TributarData.dat";
	
	if (access(filename, F_OK) != -1) {
		
		//Load(); //Carga el archivo
		
	} else {
		
		fptr = fopen (filename, "w+");
		printf("\nArchivo TributarData.dat inexistente.\n");
		printf("\nNuevo archivo TributarData.dat fue creado.\n");

		fclose(fptr);
		
		}
		
	}	
	
void AdicionarTributo() {
		
	printf("\n\nIngrese monto facturado >> ");
	scanf("%f", &MontoFacturado);
	printf("\nMonto facturado: %2.f", MontoFacturado);

	TotalFacturado += MontoFacturado;
	printf("\nValor total facturado: %2.f", TotalFacturado);			
	
	Save();
		
	}
	
void WaitKey() {
	
	// Loop until a key is pressed
			
	do {
			
		input = getchar();
		
	} while (input == '\n'); // Ignore newline characters

	//printf("\n Key '%c' pressed. Program continues...\n", input);

	return;
		
}

void Load() {
	
	//printf("\nCargando datos...");
	
	fptr = fopen ("TributarData.dat", "r"); //Carga datos del archivo.
	
		if (fptr == NULL) {
		
		printf("\nError abriendo el archivo...\n");
    	return;
	
		}
		
	// Variables a ser cargadas.
	//==================================================================	
	
	fscanf(fptr, "%f", &TotalFacturado);
    	
	}
	
void Save() {
	
	printf("\nGuardando...");
	
	// Abrir archivo para escribir.
	fptr = fopen("TributarData.dat", "w+");
	
	if (fptr == NULL) {
		
		printf("\nError abriendo archivo!\n");
		return;
		
	}

    // Escribir variables en el archivo.
    
    //fprintf(fptr, "%d\n", TimeDifferenceMODE);
    
    fprintf(fptr, "%f\n", TotalFacturado);
    //fprintf(fptr, "%f\n", GroupLessonPrice);
    //fprintf(fptr, "%f\n", NewSinglePriceBR);
    //fprintf(fptr, "%f\n", NewGroupPriceBR);
    //fprintf(fptr, "%f\n", DiscountValue);
    //fprintf(fptr, "%f\n", ArgPrice);
    //fprintf(fptr, "%f\n", USPrice);
	    
	fclose(fptr);
	
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
	


