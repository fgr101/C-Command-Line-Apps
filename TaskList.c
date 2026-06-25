#include <stdio.h>
#include <string.h>
#include <unistd.h>

#ifdef _WIN32

	#include <windows.h> // Required for Sleep() on Windows 

#endif

#define MAX_STORAGE 20
#define MAX_CHARACTERS 300

// --- CONFIGURACIÓN CLOUDFLARE ---
const char *CF_API_TOKEN = "##########################";
const char *CF_ACCOUNT_ID = "########################";
const char *CF_NAMESPACE_ID = "#####################";
const char *CF_KEY_NAME = "#######################";

FILE *fptr; // Declares the file pointer globally

char TaskNote [MAX_STORAGE][MAX_CHARACTERS];
int TaskStatus[MAX_STORAGE]; 

int TaskNumber = 0;
int Opcion = 0;
char input;
char UserInput0[50];

//Functions

void AddTask();
void PrintNotes();
void MainMenu();
void ClearScreen();
void WaitKey();
void FlushBuffer();
void CheckFile();
void SaveData();
void Load();
void MarkAsDone();
void DeleteFiles();
void DeleteAllTasks();

int main() {
		
		CheckFile();
		MainMenu();
			
	}
	
void MainMenu() {
	
	int loop1 = 0;
	
	do {
		
		ClearScreen();
		
		printf("1. Add Task \n");
		printf("2. Show Tasks \n");
		printf("3. Mark as Done \n");
		printf("4. Delete all Tasks \n");
		printf("5. Delete Files \n");
		printf("6. Exit \n\n");
		
		printf("Choose an option: ");
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
			
				DeleteAllTasks();
				break;
				
			case 5:
			
				DeleteFiles();
				break;
			
			case 6:
				
				printf("Ending program...");
				loop1 = 7;
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

#ifdef _WIN32
    
    // Windows
    system("cls");

#else
    
    // Unix-like systems
    system("clear");

#endif

}
	
void AddTask() {
	
	FlushBuffer();
	printf("Task: ");
	
	// Lee hasta 100 caracteres o hasta el salto de línea
    fgets(TaskNote[TaskNumber], MAX_CHARACTERS, stdin);
    
    TaskStatus[TaskNumber] = 0;
    TaskNumber ++;
    SaveData();
    return;
	
	}
	
void PrintNotes() {
	
	printf("\n\n");
	
	for (int i = 0; i < MAX_STORAGE; i ++){
		
		if (TaskStatus[i] == 0) {printf("* %s", TaskNote[i]);}	
	
	}
	
	printf("\n\nTasks MARKED AS DONE: \n\n");
	
	for (int i = 0; i < MAX_STORAGE; i ++){
		
		if (TaskStatus[i] == 1) {printf("* %s", TaskNote[i]);}
	
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
    
   	for (int i= 0; i < MAX_STORAGE; i++) { fgets(TaskNote[i], MAX_CHARACTERS, fptr);}
    
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
	
	Opcion = 0;
	printf("\n\n");
	
	for (int i = 0; i < MAX_STORAGE; i ++) {
		
		if (TaskStatus[i] == 0) {printf("[%d] %s", i, TaskNote[i]);}	
	
	}
	
	printf("\n\nWhat task do you want to mark as done and finished? >> ");
	scanf("%d", &Opcion);
	
	if (Opcion <= MAX_STORAGE) {
		
		TaskStatus[Opcion] = 1; // STATUS 1 means DONE.
		printf("Task %d marked as finished.", Opcion);
				
		}
	
	WaitKey();
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
		
		for (int i = 0; i <= MAX_STORAGE; i++) { //BORRA TODAS LAS TAREAS QUE FUERON CARGADAS.
			
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
	return;
	
}

void DeleteAllTasks() {
		
	printf("\n");
	printf ("Are you sure you want to delete all the information stored? \n");
	printf("Write YES to confirm the action: ");
	scanf("%4s", &UserInput0);
				
	if (strcasecmp(UserInput0, "YES") == 0) {
		
		for (int i = 0; i <= MAX_STORAGE; i++) {
			
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


//NOTES

//TO DO
//=====

//* Mark tasks as finished.

// Version 0.1
//============

//* Add Task function added.
// * Print Notes function added.
// * MAX_STORAGE and MAX_CHARACTERS constants added.
// * Basic program structure created.
// * Data File creation (CheckFile Function).
// * Saving and Loading of text [tasks] and variables on SaveData and Load functions.
// * Useful functions ClearScreen(), WaitKey(), FlushBuffer(), etc.
//* Delete ALL tasks function added.
//* Delete DATA FILE function added.


