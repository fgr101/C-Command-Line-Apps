#include <stdio.h>
#include <stdlib.h>
#include <string.h> //*This is the library to work with strings.
#include <time.h>

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
void MenuServicios();
void ServicesDeactivate();
void RunCleanManager();
void AboutLimpia();
void AutoCleaning();
void NewEntryFile();

char input;
int opcion;
int SwitchAuto;

char fecha[50];
int ActionNumber;
char ActionText[300];

FILE *fptr; // Declare the file pointer globally

int main() {
	
	ClearScreen();
	
	//printf("\ nAntes de usar este programa es necesario que se cierren todas las aplicaciones abiertas...");
	//WaitKey();
	
	ShowMenuINI:
	
	SwitchAuto = 0;
	ClearScreen();
	ShowMenu();
	
	scanf("%d", &opcion);
    
    switch (opcion) {
		
		case 1:
			
			ActionNumber = opcion;
			UpdateWinget();
			goto ShowMenuINI;
			break;
			
		case 2:
			
			ActionNumber = opcion;
			DelTempFiles();
			goto ShowMenuINI;	
			break;
			
		case 3:
			
			ActionNumber = opcion;
			KillTempFolder();
			goto ShowMenuINI;	
			break;			
				
		case 4:
		
			ActionNumber = opcion;
			DelRecycleBin();
			goto ShowMenuINI;
			break;

		case 5:
			
			ActionNumber = opcion;
			BadServices();
			goto ShowMenuINI;
			break;
			
		case 6:
		
			ActionNumber = opcion;
			FlushDNS();
			goto ShowMenuINI;
			break;
			
		case 7:
		
			ActionNumber = opcion;
			CleanChrome();
			goto ShowMenuINI;
			break;

		case 8:
			
			ActionNumber = opcion;	
			CleanStreamio();
			goto ShowMenuINI;
			break;
			
		case 9:
			
			ActionNumber = opcion;
			MenuServicios();
			goto ShowMenuINI;
			break;
			
		case 10:
			
			ActionNumber = opcion;
			RunCleanManager();
			WaitKey();
			opcion = 0;
			goto ShowMenuINI;
			break;
		
		case 11:
		
			AboutLimpia();
			goto ShowMenuINI;
			break;
		
		case 12:
		
			SwitchAuto = 1;
			ActionNumber = opcion;
			AutoCleaning();
			goto ShowMenuINI;
			break;
		
		case 13:
			
			ClearScreen();
			goto End;
			break;
			
		default:
		
			printf("DEFAULT");
			opcion = 0;
			goto ShowMenuINI;
	
	}
	
	End:
	return 0;

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
    printf("7. Limpiar cache de Google Chrome\n");
    printf("8. Limpiar cache de Streamio\n");
	printf("9. Desactivar servicios no esenciales\n");
	printf("10. Abrir 'Limpiador de Disco' de Windows\n");
	printf("11. Sobre Limpia C\n");
    printf("12. Limpiar automaticamente el sistema. \n");
    printf("13. Salir\n");
    
    printf("\n============================================\n");
    
    return;
 
 } 

void MenuServicios() {
	
	DeactivateMenuINI: 
	opcion = 0;
	ClearScreen();
    
    printf("=============================================\n");
    printf(" Limpia C 0.1 - Herramienta de mantenimiento \n");
    printf("=============================================\n");
    
    printf("\n1. Desactivar Telemetria de Windows\n");
    printf("2. Desactivar Servicios de Fax\n");
    printf("3. Desactivar Servicios de Telefonia\n");
    printf("4. Desactivar Servicios de Impresora\n");
    printf("5. Desactivar Servicios de Windows Search\n");
    printf("6. Desactivar Biometria\n");
    printf("7. Desactivar Servicios de Xbox\n");
    printf("8. Desactivar Servicios de Google Update\n");
	printf("10. Salir\n");
    
    printf("\n=============================================\n");
    
	scanf("%d", &opcion);
	
	switch (opcion) {
		
		case 1:
			
			ActionNumber = 101;	
			ServicesDeactivate("DiagTrack"); // Telemetría
			break;
	
		case 2:
			
			ActionNumber = 102;	
			ServicesDeactivate("Fax");       // Fax
			break;
	
		case 3:
			
			ActionNumber = 103;	
			ServicesDeactivate("TapiSrv");   // Teléfono
			ServicesDeactivate("PhoneSvc");
			break;
	
		case 4:
	
			ActionNumber = 104;	
			ServicesDeactivate("Spooler");   // Servicio de impresión
			break;
	
		case 5:
			
			ActionNumber = 105;	
			ServicesDeactivate("Wsearch");   // Windows Search
			break;
			
		case 6:
			
			ActionNumber = 106;	
			ServicesDeactivate("WbioSrvc");   // Biometria
			break;
			
		case 7:
			
			ActionNumber = 107;	
			ServicesDeactivate("XblGameSave");   // Servicios de Xbox.
			ServicesDeactivate("XboxNetApiSvc");
			ServicesDeactivate("XboxGipSvc");
			ServicesDeactivate("XblAuthManager");
			break;
			
		case 8:
			
			ActionNumber = 108;	
			ServicesDeactivate("GoogleUpdaterInternalService144.0.7547.0");   // Servicios de Google Update.
			ServicesDeactivate("GoogleUpdaterService144.0.7547.0");
			ServicesDeactivate("gupdate");
			break;
			

		case 10:
		
			return;
			
	}
    
    NewEntryFile();
    WaitKey();
    goto DeactivateMenuINI;
 
 }

void ServicesDeactivate(const char *NombreServicio) {
	
	printf("\nDesactivando el servicio %s...\n", NombreServicio);
    
    //sprintf es una función muy útil en C que permite formatear una cadena de texto 
    //y almacenarla en un arreglo de caracteres. Es como printf, pero en lugar de 
    //imprimir en la consola, guarda el resultado en una variable.
    
    //char mensaje[100];
	//int edad = 25;
	//sprintf(mensaje, "Tengo %d años.", edad);
	// Ahora `mensaje` contiene "Tengo 25 años."
    
    char comando[256];
    
    sprintf(comando, "sc stop \"%s\"", NombreServicio);
    system(comando); // Detener el servicio
    sprintf(comando, "sc config \"%s\" start=disabled", NombreServicio);
    system(comando); // Deshabilitar el servicio
    printf("Servicio %s desactivado.\n", NombreServicio);
    
    opcion = 0;
    
    return;
    
}

// Función para limpiar la papelera de reciclaje...

void DelRecycleBin() {
	
	printf("\nLimpiando la papelera de reciclaje...\n");
    system("rd /s /q C:\\$Recycle.Bin");
    printf("\nPapelera de reciclaje vacia.\n");
    NewEntryFile();
    WaitKey();
    return;
	
}

// Función para limpiar archivos temporales...

void DelTempFiles() {
	
	printf("\nBorrando archivos temporales...");
	system("del /f /s /q %TEMP%\\*");
	printf("\nArchivos temporales eliminados!");
	NewEntryFile();
	WaitKey();
	return;
	
}

// Función para eliminar y recrear la carpeta temporal

void KillTempFolder() {
    
    printf("\nEliminando y recreando la carpeta temporal...\n");
    system("rd /s /q %temp%");
    system("md %temp%");
    printf("\nCarpeta temporal recreada.\n");
    NewEntryFile();
    WaitKey();
    return;
}

// Función para actualizar paquetes y programas con winget...

void UpdateWinget() {
	
	printf("\n* La opcion 'Actualizar paquetes con winget' actualizara los programas instalados en Windows\n");
    printf("a su version mas reciente. Si usted no desea actualizar o no sabe como esto puede afectar\n");
    printf("el uso cotidiano de sus aplicaciones por favor evite utilizar esta opcion.\n\n");
	
	printf("Seguro quiere actualizar aplicaciones y programas en su PC? Ingrese el numero [197] para\n");
	printf("confirmar la accion. Cero [0] o cualquier otro numero para cancelar...\n\n");
		
	printf(">> ");
	scanf("%d", &opcion);
	
	if (opcion != 197) {
		
		printf ("\n\nAccion cancelada...\n");
	    NewEntryFile();		
		return;
		
	} else { 
		
	    NewEntryFile();
		printf ("\n\nAccion confirmada...\n");
		
	}
	
    printf("\nActualizando paquetes con winget...\n");
    system("winget upgrade --include-unknown");
    system("winget upgrade --all --include-unknown");
    printf("\nActualización completada.\n");
    NewEntryFile();
    WaitKey();
    return;
    
}

// Función para liberar la caché de DNS

void FlushDNS() {
	
    printf("Liberando la cache de DNS...\n");
    system("ipconfig /flushdns");
    printf("Cache de DNS liberada.\n");
    NewEntryFile();
    WaitKey();
    return;
    
}

// Función para limpiar la caché de Google Chrome

void CleanChrome() {
    
    printf("Limpiando la cache de Google Chrome...\n");
    system("rd /s /q \"%LOCALAPPDATA%\\Google\\Chrome\\User Data\\Default\\Cache\"");
    printf("LOCAL APP DATA >> Google Chrome >> Cache [BORRADO]\n");
    system("rd /s /q \"%LOCALAPPDATA%\\Google\\Chrome\\User Data\\Default\\Service Worker\\CacheStorage\"");
    printf("LOCAL APP DATA >> Google Chrome >> CacheStorage [BORRADO]\n");
    printf("Cache de Google Chrome borrado.\n");
    NewEntryFile();
    WaitKey();
    return;

}

void CleanStreamio() {
    
    printf("Limpiando la cache de Streamio...\n");
    system("rd /s /q \"C:\\Users\\ferna\\AppData\\Roaming\\stremio\\stremio-server\\stremio-cache\"");
    printf("Cache de Streamio limpio.\n");
    NewEntryFile();
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

void WaitKey() {
	
	// Loop until a value is inserted
	
	if (SwitchAuto != 1) {
		
		printf("\nIngresa '0' (cero) para continuar >> ", input);
			
		do {
			
			input = getchar();
		
		} while (input == '\n'); // Ignore newline characters

		return;
	
	}
		
}

void RunCleanManager() {
	
	printf("Abriendo el 'Limpiador de Disco de Windows'...");
	NewEntryFile();
	system("cleanmgr.exe"); // Opens the Cleaner Manager
	return;

}

void AboutLimpia() {
    
    ClearScreen();
    
    printf("=============================================\n");
    printf(" Limpia C 0.1 - Herramienta de mantenimiento \n");
    printf("=============================================\n");
    
    printf("\n* Para que el programa funcione correctamente es necesario que se ejecute en modo\n");
    printf(" 'Administrador de Sistema' para que pueda realizar todas las acciones. De lo contrario\n");
    printf("  Windows negara la mayoria de los comandos que intente aplicar el programa.\n\n");
    
    printf("* La opcion 'Actualizar paquetes con winget' actualizara los programas instalados en Windows\n");
    printf("  a su version mas reciente. Si usted no desea actualizar o no sabe como esto puede afectar\n");
    printf("  el uso cotidiano de sus aplicaciones por favor evite utilizar esta opcion.\n\n");
    
    printf("* Cierra todos los programas en uso antes de iniciar procesos de limpieza en este programa.\n");
    printf("  Especialmente a la hora de limpiar archivos de Google Chrome y otra aplicaciones.\n");


    WaitKey();
    
    return;
 
 }
 
 void AutoCleaning() {
	
	ClearScreen();
	 
	printf("\nLimpiando el sistema automaticamente...\n");
	
	DelTempFiles();
	DelRecycleBin();
	FlushDNS();
	CleanChrome();
	
	printf("Limpieza automatica finalizada...\n");
	SwitchAuto = 0;
	NewEntryFile();	
	WaitKey();

}

//void SaveData() {
	
	//printf("Saving...");
	
	// Save the variable to a file
	//fptr = fopen("DataFile.dat", "w+");
	
	//if (fptr == NULL) {
		
		//printf("Error opening file!\n");
		//return;
	//}

    // Write variables to the file
    //==================================================================
    
    // Config variables
    //=================
    
    //fprintf(fptr, "%d\n", TimeDifferenceMODE);
    
    //printf("Config: Time Difference MODE [%d]\n", TimeDifferenceMODE);
    
    //Values and Prices
    //=================
    
    //fprintf(fptr, "%f\n", SingleLessonPrice);
    //fprintf(fptr, "%f\n", GroupLessonPrice);
    //fprintf(fptr, "%f\n", NewSinglePriceBR);
    //fprintf(fptr, "%f\n", NewGroupPriceBR);
    //fprintf(fptr, "%f\n", DiscountValue);
    //fprintf(fptr, "%f\n", ArgPrice);
    //fprintf(fptr, "%f\n", USPrice);
    
    //printf("Single lesson price saved: %.2f\n", SingleLessonPrice);
    //printf("Group lesson price saved: %.2f\n", GroupLessonPrice);
	//printf("Single lesson price for new students saved: %.2f\n", NewSinglePriceBR);
   // printf("Group lesson price for new students saved: %.2f\n", NewGroupPriceBR);
	//printf("Discount value saved: %.2f\n", DiscountValue);
	//printf("Argentina's price saved: %.2f\n", ArgPrice);
	//printf("United States price saved: %.2f\n", USPrice);

	    
	//fclose(fptr);
	
	//}
	
void NewEntryFile() {
	
	if (SwitchAuto != 1) {
		
		printf("\nAnotando modificaciones en 'registro.txt'...");
	
		switch (ActionNumber) {
			
			case 1:
			
				strcpy (ActionText, "Actualizacion de paquetes con winget");
				break;
		
			case 2:
		
				strcpy (ActionText, "Limpieza de archivos temporales");
				break;
			
			case 3:
		
				strcpy (ActionText, "Carpeta temporal eliminada y recreada");
				break;
		
			case 4:
		
				strcpy (ActionText, "Papelera de reciclaje vacia");
				break;
			
			case 6:
		
				strcpy (ActionText, "Cache de DNS liberado");
				break;
			
			case 7:
		
				strcpy (ActionText, "Cache de Google Chrome borrado");
				break;
			
			case 8:
		
				strcpy (ActionText, "Cache de Streamio borrado");
				break;
				
			case 9:
		
				strcpy (ActionText, "Limpiador de disco de Windows abierto");
				break;
			
			case 12:
		
				strcpy (ActionText, "Limpieza automatica del sistema");
				break;
			
			case 101: 

    			strcpy (ActionText, "Desactivado Telemetria de Windows");
    			break;
			
			case 102:
			
				strcpy (ActionText, "Desactivado Servicios de Fax");
				break;
			
			case 103:
				
				strcpy (ActionText, "Desactivado Servicios de Telefonia");
				break;
				
			case 104:
			
				strcpy (ActionText, "Desactivado Servicios de Impresora");
				break;
    
			case 105:
			
				strcpy (ActionText, "Desactivado Servicios de Windows Search");
				break;
				
			case 106:
			
				strcpy (ActionText, "Desactivado Servicios de Biometria");
				break;
				
			case 107:
			
				strcpy (ActionText, "Desactivado Servicios de Xbox");
				break;
				
			case 108:
			
				strcpy (ActionText, "Desactivado Servicios de Google Update");
				break;
			
		}
	
		// Save the variable to a file
		fptr = fopen("registro.txt", "a");
	
		if (fptr == NULL) {
		
			printf("Error abriendo archivo!\n");
			return;
		
		}
	
		//==============================================================
		// REQUESTING DATE AND TIME
		
		time_t now = time(NULL); 
		struct tm *local = localtime(&now);

		strftime(fecha, sizeof(fecha), "%d-%m-%Y", local);
        
		//==============================================================
		// Write variables to the file

		fprintf(fptr, "\n* %s | %20s", fecha, ActionText);
		fclose(fptr);
		
	}
		
	return;
	
}

//======================================================================
//                               Notas 
//======================================================================

// Version 0.1

//* Estructura general del programa creada.
//* Actualización de paquetes con winget
//* Limpiar archivos temporales.
//* Eliminar y recrear la carpeta temporal.
//* Vaciar la papelera de reciclaje.
//* Mostrar servicios innecesarios.
//* Liberar la cache de DNS.
//* Limpiar cache de Google Chrome.
//* Limpiar cache de Streamio.
//*	Desactivar servicios no esenciales.
//*	Abrir 'Limpiador de Disco' de Windows.
//* Limpiar automaticamente el sistema.
//*	Apartado agregado con anotaciones "Sobre Limpia".
//* Las acciones del usuario quedan registradas en 'registro.txt' para
//  su posterior consulta.

//======================================================================
