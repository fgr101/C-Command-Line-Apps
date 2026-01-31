#include <stdio.h>
#include <stdlib.h>
#include <string.h> //*This is the library to work with strings.

#ifdef _WIN32

	#include <windows.h> // Requerido para Sleep() y ClearScreen en Windows. 

#endif

void DelTempFiles();
void DelRecycleBin();
void KillTempFolder();
void UpdateWinget();
void CleanChrome();
void CleanStreamio();
void FlushDNS();
void ClearScreen();
void ShowMenu();
void WaitKey();
void BadServices();

char input;
int opcion;

int main() {
	
	ClearScreen();
	
	//printf("\ nAntes de usar este programa es necesario que se cierren todas las aplicaciones abiertas...");
	//WaitKey();
	
	ShowMenuINI:
	
	ClearScreen();
	ShowMenu();
	
	scanf("%d", &opcion);
    
    switch (opcion) {
		
		case 1:
		
			UpdateWinget();
			goto ShowMenuINI;
			break;
			
		case 2:
		
			DelTempFiles();
			goto ShowMenuINI;	
			break;
			
		case 3:
		
			KillTempFolder();
			goto ShowMenuINI;	
			break;			
				
		case 4:
		
			DelRecycleBin();
			goto ShowMenuINI;
			break;

		case 5:
			
			BadServices();
			goto ShowMenuINI;
			break;
			
		case 6:
		
			FlushDNS();
			goto ShowMenuINI;
			break;
			
		case 7:
		
			CleanChrome();
			goto ShowMenuINI;
			break;

		case 8:
		
			CleanStreamio();
			goto ShowMenuINI;
			break;
	
		case 9:
			
			ClearScreen();
			return 0;
			break;
			
		default:
		
			printf("DEFAULT");
			goto ShowMenuINI;
	
	}
	
}

// Función para limpiar la papelera de reciclaje...

void DelRecycleBin() {
	
	printf("\nLimpiando la papelera de reciclaje...\n");
    system("rd /s /q C:\\$Recycle.Bin");
    printf("\nPapelera de reciclaje vacía.\n");
    WaitKey();
    return;
	
}

// Función para limpiar archivos temporales...

void DelTempFiles() {
	
	printf("\nBorrando archivos temporales...");
	system("del /f /s /q %TEMP%\\*");
	printf("\nArchivos temporales eliminados!");
	WaitKey();
	return;
	
}

// Función para eliminar y recrear la carpeta temporal

void KillTempFolder() {
    
    printf("\nEliminando y recreando la carpeta temporal...\n");
    system("rd /s /q %temp%");
    system("md %temp%");
    printf("\nCarpeta temporal recreada.\n");
    WaitKey();
    return;
}

// Función para actualizar paquetes y programas con winget...

void UpdateWinget() {
	
    printf("\nActualizando paquetes con winget...\n");
    system("winget upgrade --all");
    printf("\nActualización completada.\n");
    WaitKey();
    return;
    
}

// Función para liberar la caché de DNS

void FlushDNS() {
	
    printf("Liberando la caché de DNS...\n");
    system("ipconfig /flushdns");
    printf("Caché de DNS liberada.\n");
    WaitKey();
    return;
    
}

// Función para limpiar la caché de Google Chrome

void CleanChrome() {
    
    printf("Limpiando la caché de Google Chrome...\n");
    system("rd /s /q \"%LOCALAPPDATA%\\Google\\Chrome\\User Data\\Default\\Cache\"");
    printf("Caché de Google Chrome limpiada.\n");
    WaitKey();
    return;

}

void CleanStreamio() {
    
    printf("Limpiando la caché de Streamio...\n");
    system("rd /s /q \"C:\\Users\\ferna\\AppData\\Roaming\\stremio\\stremio-server\\stremio-cache\"");
    printf("Caché de Streamio limpio.\n");
    WaitKey();
    return;

}

// Función para mostrar servicios innecesarios

void BadServices() {
    
    printf("Listando servicios innecesarios...\n");
    system("sc query state= all | findstr /i /C:\"Superfetch\" /C:\"Windows Search\" /C:\"Print Spooler\"");
    printf("Listado completado.\n");
    WaitKey();
    return;

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

void ShowMenu() {
    
    printf("=============================================\n");
    printf(" Limpia C 0.1 - Herramienta de mantenimiento \n");
    printf("=============================================\n");
    
    printf("\n1. Actualizar paquetes con winget\n");
    printf("2. Limpiar archivos temporales\n");
    printf("3. Eliminar y recrear la carpeta temporal\n");
    printf("4. Vaciar la papelera de reciclaje\n");
    printf("5. Mostrar servicios innecesarios\n");
    printf("6. Liberar la cache de DNS\n");
    printf("7. Limpiar la cache de Google Chrome\n");
    printf("8. Limpiar la cache de Streamio\n");
    printf("9. Salir\n");
    
    printf("\n=============================================\n");
    
    return;
 
 }


void WaitKey() {
	
	// Loop until a key is pressed
			
	do {
			
		input = getchar();
		
	} while (input == '\n'); // Ignore newline characters

	//printf("\n Key '%c' pressed. Program continues...\n", input);

	return;
		
}

