#include <stdio.h>
#include <string.h>
#include <unistd.h>

#ifdef _WIN32

	#include <windows.h> // Required for Sleep() on Windows 

#endif

#define MAX_STORAGE 20
#define MAX_CHARACTERS 300

// Definimos los códigos ANSI como macros para poder usarlos como LOCATE.
//=======================================================================

#define CLEAR_SCREEN "\033[2J"
#define RESET_CURSOR "\033[H"
#define COLOR_RESET  "\033[0m"
#define COLOR_BOLD   "\033[1m"
#define COLOR_BLUE   "\033[34m"

// Estilos

#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define UNDERLINE   "\033[4m"

// Colores Estándar

#define BLACK       "\033[30m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"

// Colores Brillantes (se ven mejor en muchas consolas modernas)

#define B_BLACK     "\033[90m"
#define B_RED       "\033[91m"
#define B_GREEN     "\033[92m"
#define B_YELLOW    "\033[93m"
#define B_BLUE      "\033[94m"
#define B_MAGENTA   "\033[95m"
#define B_CYAN      "\033[96m"
#define B_WHITE     "\033[97m"

// Colores de fondo.....

#define BG_BLACK    "\033[40m"
#define BG_RED      "\033[41m"
#define BG_GREEN    "\033[42m"
#define BG_YELLOW   "\033[43m"
#define BG_BLUE     "\033[44m"
#define BG_MAGENTA  "\033[45m"
#define BG_CYAN     "\033[46m"
#define BG_WHITE    "\033[47m"

//======================================================================

void locate();
void clean_screen();

// --- CONFIGURACIÓN CLOUDFLARE ---
//const char *CF_API_TOKEN = "##########################";
//const char *CF_ACCOUNT_ID = "########################";
//const char *CF_NAMESPACE_ID = "#####################";
//const char *CF_KEY_NAME = "#######################";

FILE *fptr; // Declares the file pointer globally

char TaskNote [MAX_STORAGE][MAX_CHARACTERS];
//int TaskStatus[MAX_STORAGE]; 
unsigned char TaskStatus[MAX_STORAGE]; 

int TaskNumber = 0;
int Opcion = 0;
char input;
char UserInput0[50];

//Functions

void AddTask();
void PrintNotes();
void MainMenu();
void PrintLeftMenu();
void ClearScreen();
void WaitKey();
void FlushBuffer();
void CheckFile();
void SaveData();
void Load();
void MarkAsDone();
void DeleteFiles();
void DeleteAllTasks();
void MarkAsPriority();

int main() {
		
		CheckFile();
		MainMenu();
			
	}
	
void MainMenu() {
	
	int loop1 = 0;
	
	do {
		
		clean_screen();

		// Dibujamos una especie de interfaz
		
		locate(2, 1);
		printf(COLOR_BOLD BG_GREEN WHITE "=== GESTOR DE TAREAS v0.2 ===" COLOR_RESET);
	
		//ClearScreen();

		locate(1, 3);	
		printf(BOLD GREEN "1. Add Task");
		printf("\n2. Show Tasks");
		printf("\n3. Mark as Done");
		printf("\n4. Mark as a Priority");
		printf("\n5. Delete all Tasks");
		printf("\n6. Delete Files");
		printf("\n7. Exit");
		
		PrintNotes();
		
		locate(1, 11);
		printf(B_GREEN "Choose an option: ");
		scanf("%d", &Opcion);
		
		switch (Opcion) {
			
			case 1:
				
				AddTask();				
				break;
				
			case 2:
			
				PrintNotes();
				WaitKey();
				break;
			
			case 3:
			
				MarkAsDone();
				break;
			
			case 4:
			
				MarkAsPriority();
				break;
				
			case 5:
			
				DeleteAllTasks();
				break;
				
			case 6:
			
				DeleteFiles();
				break;
			
			case 7:
				
				printf("Ending program...");
				printf(COLOR_RESET);	
				loop1 = 7;
				ClearScreen();
				break;
			
			default:
				
				printf("\nInsert one of the options above.");
				WaitKey();
				break;			
			
			}
				
	} while (loop1 != 7);
	
	}
	
//CLS Function

void ClearScreen() {

printf(CLEAR_SCREEN RESET_CURSOR);

//#ifdef _WIN32
    
    // Windows
//    system("cls");

//#else
    
    // Unix-like systems
//    system("clear");

//#endif

}
	
void AddTask() {
	
	FlushBuffer();
	printf("Task: ");
	
	// Lee hasta 100 caracteres o hasta el salto de línea
	fgets(TaskNote[TaskNumber], MAX_CHARACTERS, stdin);

	if (strcmp(TaskNote[TaskNumber], "") != 0) {
    
		TaskStatus[TaskNumber] = 0;
		TaskNumber ++;
		SaveData();
    
	}
	
    return;
		
	}
	
void PrintNotes() {
	
	int LinesAdded = 0;
	
	printf(RESET_CURSOR);	
	locate (40, 1);
			
	printf(BG_RED WHITE "DO THIS FIRST:");
	printf(COLOR_RESET);
	
	for (int i = 0; i < MAX_STORAGE; i ++){

		if (strcmp(TaskNote[i], "") != 0) {
				
			locate (40, (3 + LinesAdded));
			
			if (TaskStatus[i] == 2) {
				
				printf(WHITE "[!] %s", TaskNote[i]); 
				LinesAdded ++;
			
			}	
		
		}
	
	}
	
	LinesAdded = 0;
	locate (40, 10);
	
	printf(BG_BLUE WHITE "OTHER GENERAL TASKS:");
	printf(COLOR_RESET);
	
	for (int i = 0; i < MAX_STORAGE; i ++){
		
		if (strcmp(TaskNote[i], "") != 0) {
			
			locate (40, (12 + LinesAdded));
			
			if (TaskStatus[i] == 0) {
				
				printf(WHITE "* %s", TaskNote[i]);
				LinesAdded ++;	
			
			}
			
		}
	
	}	
	
	LinesAdded = 0;
	locate (40, 20);
	
	printf(BG_CYAN WHITE "DONE AND FINISHED:");
	printf(COLOR_RESET);
	
	for (int i = 0; i < MAX_STORAGE; i ++){
		
		if (strcmp(TaskNote[i], "") != 0) {

			locate (40, (22 + LinesAdded));
			
			if (TaskStatus[i] == 1) {
				
				printf(WHITE "[OK] %s", TaskNote[i]);
				LinesAdded++;
			
			
			}
		
		}
	
	}
	
	return;
	
}

void WaitKey() {
	
	// Loop until a key is pressed
	
	printf("\n\nInput 0 and press enter to continue.");
			
	do {
			
		input = getchar();
		
	} while (input == '\n'); // Ignore newline characters

	//printf("\n Key '%c' pressed. Program continues...\n", input);

	return;

}

void FlushBuffer() {
	
    int c; // Declaramos una variable para guardar temporalmente cada carácter
    while ((c = getchar()) != '\n' && c != EOF);
    
    return;
    
	//int c;: Usamos un int en lugar de un char porque la constante EOF (End Of File) suele ser -1, y un 
	//int puede representarlo correctamente.
	//getchar(): Esta función lee el siguiente carácter disponible en el búfer de entrada.
	
	//while (...): Es un bucle que se repite una y otra vez con una condición doble:
		//(c = getchar()) != '\n': "Sigue leyendo y guardando caracteres mientras lo que leas no sea un salto de línea". 
	//Es decir, limpia todo lo que el usuario escribió de más.
	
	//&& c != EOF: "Y también detente si llegas al final del archivo o hay un error". Esto evita que el bucle sea infinito 
	//si no hay más datos. 
	
	//; (punto y coma al final): Nota que el while no tiene cuerpo { }. Esto significa: "No hagas nada, solo sigue leyendo 
	//caracteres hasta que se cumpla la condición de parada".
	
}

void CheckFile() {
	
	//==================================================================
	// CREATES DATA FILE (IF IT DOESN'T EXIST)

	const char * filename = "TaskList.dat";

	// Check if the file exists

	if (access(filename, F_OK) != -1) {
		
		Load();
		
	} else {
			
			// File doesn't exist, create a new file
			
			fptr = fopen(filename, "w+");
			printf("File does not exist. New file created. \n");
			fclose(fptr);
		
		}

	// Check if the file was opened successfully
	if (fptr == NULL) 

	{
		
		printf("Error opening the file.\n");
		return; // indicate an error to the operating system

	}

	// Close the file
	//fclose(fptr);

	//==================================================================
	
	return;
	
}

void SaveData() {
	
	printf("Saving...");
	
	// Save the variable to a file
	fptr = fopen("TaskList.dat", "w+");
	
	if (fptr == NULL) {
		
		printf("Error opening file!\n");
		return;
	}

    // Write variables to the file
    //==================================================================
    
    // Config variables
    //=================
    
    fprintf(fptr, "%d\n", TaskNumber);
    
    //printf("Config: Time Difference MODE [%d]\n", TimeDifferenceMODE);
    
    //Values and Prices
    //=================

	for (int i= 0; i < MAX_STORAGE; i++) {fprintf(fptr, "%u ", TaskStatus[i]);}
	fprintf(fptr, "\n"); // <--- para que las tareas empiecen en una línea nueva	
	for (int i= 0; i < MAX_STORAGE; i++) {fprintf(fptr, "%s", TaskNote[i]);}
    
    //fprintf(fptr, "%f\n", GroupLessonPrice);
    //fprintf(fptr, "%f\n", NewSinglePriceBR);
    //fprintf(fptr, "%f\n", NewGroupPriceBR);
    //fprintf(fptr, "%f\n", DiscountValue);
    //fprintf(fptr, "%f\n", ArgPrice);
    //fprintf(fptr, "%f\n", USPrice);
    
    //printf("Single lesson price saved: %.2f\n", SingleLessonPrice);
    //printf("Group lesson price saved: %.2f\n", GroupLessonPrice);
	//printf("Single lesson price for new students saved: %.2f\n", NewSinglePriceBR);
    //printf("Group lesson price for new students saved: %.2f\n", NewGroupPriceBR);
	//printf("Discount value saved: %.2f\n", DiscountValue);
	//printf("Argentina's price saved: %.2f\n", ArgPrice);
	//printf("United States price saved: %.2f\n", USPrice);
	    
	fclose(fptr);
	
	}
	
// LOAD Function
void Load() {
	
	printf("Loading...");
	
	 fptr = fopen("TaskList.dat", "r");
	
    // Load the variable from the file
	
	if (fptr == NULL) {
		
		printf("Error opening file!\n");
    	return;

	}
		
    // Read variables from the file
    //==================================================================
    
    
    // Config variables
    //=================

    fscanf(fptr, "%d", &TaskNumber);
    //printf("Config: Time Difference MODE loaded [%d]\n", TimeDifferenceMODE);
  
    //Tasks, TO DO list.
    //==================  

   	for (int i= 0; i < MAX_STORAGE; i++) {fscanf(fptr, "%hhu", &TaskStatus[i]);} 
   	
   	// FGETC(FPTR): Consume el último espacio o salto de línea que dejó el fscanf.
   	fgetc(fptr);
   	   		
   	for (int i= 0; i < MAX_STORAGE; i++) {fgets(TaskNote[i], MAX_CHARACTERS, fptr);}
    
    //fscanf(fptr, "%f", &SingleLessonPrice);
    //fscanf(fptr, "%f", &GroupLessonPrice);
    //fscanf(fptr, "%f", &NewSinglePriceBR);
    //fscanf(fptr, "%f", &NewGroupPriceBR);
    //fscanf(fptr, "%f", &DiscountValue);
    //fscanf(fptr, "%f", &ArgPrice);
    //fscanf(fptr, "%f", &USPrice);

    //printf("Single lesson price loaded: %.2f\n", SingleLessonPrice);
    //printf("Group lesson price loaded: %.2f\n", GroupLessonPrice);
    //printf("Single lesson price for new students loaded: %.2f\n", NewSinglePriceBR);
    //printf("Group lesson price for new students loaded: %.2f\n", NewGroupPriceBR);
    //printf("Discount value loaded: %.2f\n", DiscountValue);
    //printf("Argentina's price loaded: %.2f\n", ArgPrice);
    //printf("United States price loaded: %.2f\n", USPrice);


	fclose(fptr);
	ClearScreen();
	    
}

void MarkAsDone() {
	
	ClearScreen();
	PrintLeftMenu();
	
	int LinesAdded = 0;	
	printf(RESET_CURSOR);	
	
	Opcion = 0;
	
	locate (40, 1);
	printf(BG_RED WHITE "DO THIS FIRST:");
	printf(COLOR_RESET);
	
	for (int i = 0; i < MAX_STORAGE; i ++){
		
		if (strcmp(TaskNote[i], "") != 0) {
			
			locate (40, (3 + LinesAdded));
			
			if (TaskStatus[i] == 2) {
				
				printf(WHITE "[%d] %s", i, TaskNote[i]);
				LinesAdded ++;
				
			}
			
		}
	
	}
	
	LinesAdded = 0;
	
	locate (40, 10);
	printf(BG_BLUE WHITE "OTHER GENERAL TASKS:");
	printf(COLOR_RESET);
	
	for (int i = 0; i < MAX_STORAGE; i ++){
		
		if (strcmp(TaskNote[i], "") != 0) {
			
			locate (40, (12 + LinesAdded));
			
			if (TaskStatus[i] == 0) {
				
				printf(WHITE "[%d] %s", i, TaskNote[i]);
				LinesAdded++;
				
				}	
		
		}
		
	}
	
	//for (int i = 0; i < MAX_STORAGE; i ++) {
		
	//	if (TaskStatus[i] == 0 || TaskStatus[i] == 2) {printf("[%d] %s", i, TaskNote[i]);}	
	
	//}
	
	locate (40, (15 + LinesAdded));
	printf("Write task number >> ");
	scanf("%d", &Opcion);
	
	if (Opcion <= MAX_STORAGE) {
		
		TaskStatus[Opcion] = 1; // STATUS 1 means DONE.
		printf("Task %d marked as finished.", Opcion);
				
		}
	
	SaveData();
	//WaitKey();
	return;
	
	}
	
void DeleteFiles() {
	
	printf("\n");
	printf ("Are you sure you want to delete all DATA FILES? \n");
	printf("Write YES to confirm the action: ");
	scanf("%4s", &UserInput0);
				
	if (strcasecmp(UserInput0, "YES") == 0) {
		
		#ifdef _WIN32
	
			system("del TaskList.dat");

		#else
	
			system("rm TaskList.dat");  // Comando para Linux/Unix/macOS

		#endif
		
		for (int i = 0; i < MAX_STORAGE; i++) { //BORRA TODAS LAS TAREAS QUE FUERON CARGADAS.
			
			strcpy(TaskNote[i], "");
			TaskStatus[i] = 0;
					
		}
		
		printf("\n");
		printf("All DATA FILES have been deleted. ");
		printf("\n");
			
	} else {
			
		printf("\n"); 
		printf("The action ha been canceled... ");
			
		}
	
	WaitKey();
	CheckFile();
	
	return;
	
}

void DeleteAllTasks() {
		
	printf("\n");
	printf ("Are you sure you want to delete all the information stored? \n");
	printf("Write YES to confirm the action: ");
	scanf("%4s", &UserInput0);
				
	if (strcasecmp(UserInput0, "YES") == 0) {
		
		for (int i = 0; i < MAX_STORAGE; i++) {
			
			strcpy(TaskNote[i], "");
			TaskStatus[i] = 0;
					
		}
		
		printf("\n");
		printf("All tasks have been deleted. ");
		printf("\n");
		
	} else {
			
		printf("\n"); 
		printf("The action ha been canceled... ");
			
		}
	
	WaitKey();
	return;
		
}

void MarkAsPriority() {
	
	Opcion = 0;
	printf("\n\n");
	
	for (int i = 0; i < MAX_STORAGE; i ++) {
		
		if (TaskStatus[i] == 0) {printf("[%d] %s", i, TaskNote[i]);}	
	
	}
	
	printf("\n\nWhat task do you want to mark as A PRIORITY? >> ");
	scanf("%d", &Opcion);
	
	if (Opcion <= MAX_STORAGE) {
		
		TaskStatus[Opcion] = 2; // STATUS 2 means PRIORITY.
		printf("Task %d marked as important and a priority.", Opcion);
		
		}
	
	SaveData();
	WaitKey();
	return;
	
	}
	
// Nuestra función LOCATE multiplataforma
// Nota: En ANSI es (Fila, Columna)

void locate(int x, int y) {
	
    printf("\033[%d;%dH", y, x);

}

void clean_screen() {
	
    printf(CLEAR_SCREEN);
    printf(RESET_CURSOR);
    
}

void PrintLeftMenu() {
	
	clean_screen();

	// Dibujamos una especie de interfaz
		
	locate(2, 1);
	printf(COLOR_BOLD BG_GREEN WHITE "=== GESTOR DE TAREAS v0.2 ===" COLOR_RESET);
	
	//ClearScreen();

	locate(1, 3);	
	printf(BOLD GREEN "1. Add Task");
	printf("\n2. Show Tasks");
	printf("\n3. Mark as Done");
	printf("\n4. Mark as a Priority");
	printf("\n5. Delete all Tasks");
	printf("\n6. Delete Files");
	printf("\n7. Exit");
	
	
	}
	
//NOTES

//TO DO
//=====



//======================================================================

// Version 0.2
//============

// * Optimized Memory: Switched TaskStatus from 'int' to 'unsigned char' (75% RAM savings per status).
// * Processing Efficiency: Removed system() calls, replaced with direct ANSI escape sequences for instant UI rendering.
// * Robust Persistence: Implemented safe loading with '%hhu' and manual buffer clearing (fgetc) to prevent data corruption.
// * Enhanced Data Structure: Added space-separated saving to ensure reliable data parsing during file loading.
// * Memory Safety: Fixed array boundary conditions (Off-by-one errors) in all deletion and clearing functions.
// * Advanced ANSI UI: Added a full suite of macros for professional colors (B_RED, BG_GREEN, etc.) and styles (BOLD, UNDERLINE).
// * Visual Categorization: Tasks are now dynamically filtered into three distinct blocks: "PRIORITY", "GENERAL", and "DONE".
// * Non-Linear Rendering: Utilized coordinate-based positioning (locate function) to create a multi-column dashboard layout.
// * Visual Feedback System: Implemented status-specific prefixes ([!], *, [OK]) and color coding for better task tracking.
// * Cross-Platform Compatibility: Fully portable terminal handling for modern Windows, Linux, and macOS environments.

// Version 0.1
//============

// * Add Task function added.
// * Print Notes function added.
// * MAX_STORAGE and MAX_CHARACTERS constants added.
// * Basic program structure created.
// * Data File creation (CheckFile Function).
// * Saving and Loading of text [tasks] and variables on SaveData and Load functions.
// * Useful functions ClearScreen(), WaitKey(), FlushBuffer(), etc.
// * Delete ALL tasks function added.
// * Delete DATA FILE function added.
// * Mark tasks as finished.


