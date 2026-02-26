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
void MenuServicios();
void ServicesDeactivate();
void RunCleanManager();
void AboutLimpia();
void AutoCleaning();

char input;
int opcion;
int SwitchAuto;

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

			MenuServicios();
			goto ShowMenuINI;
			break;
			
		case 10:
		
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
			AutoCleaning();
			goto ShowMenuINI;
			break;
		
		case 13:
			
			ClearScreen();
			goto End;
			break;
			
		default:
		
			printf("DEFAULT");
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
				
			ServicesDeactivate("DiagTrack"); // Telemetría
			break;
	
		case 2:
			
			ServicesDeactivate("Fax");       // Fax
			break;
	
		case 3:
			
			ServicesDeactivate("TapiSrv");   // Teléfono
			ServicesDeactivate("PhoneSvc");
			break;
	
		case 4:
	
			ServicesDeactivate("Spooler");   // Servicio de impresión
			break;
	
		case 5:
	
			ServicesDeactivate("Wsearch");   // Windows Search
			break;
			
		case 6:
		
			ServicesDeactivate("WbioSrvc");   // Biometria
			break;
			
		case 7:
		
			ServicesDeactivate("XblGameSave");   // Servicios de Xbox.
			ServicesDeactivate("XboxNetApiSvc");
			ServicesDeactivate("XboxGipSvc");
			ServicesDeactivate("XblAuthManager");
			break;
			
		case 8:
			
			ServicesDeactivate("GoogleUpdaterInternalService144.0.7547.0");   // Servicios de Google Update.
			ServicesDeactivate("GoogleUpdaterService144.0.7547.0");
			ServicesDeactivate("gupdate");
			break;
			

		case 10:
		
			return;
			
	}
    
    WaitKey();
    return;
 
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
	
	printf("\n* La opcion 'Actualizar paquetes con winget' actualizara los programas instalados en Windows\n");
    printf("a su version mas reciente. Si usted no desea actualizar o no sabe como esto puede afectar\n");
    printf("el uso cotidiano de sus aplicaciones por favor evite utilizar esta opcion.\n\n");
	
	printf("Seguro quiere actualizar aplicaciones y programas en su PC? Ingrese el numero [197] para\n");
	printf("confirmar la accion. Cero [0] o cualquier otro numero para cancelar...\n\n");
		
	printf(">> ");
	scanf("%d", &opcion);
	
	if (opcion != 197) {
		
		printf ("\n\nAccion cancelada...\n");		
		return;
		
	} else { 
		
		printf ("\n\nAccion confirmada...\n");
		
	}
	
    printf("\nActualizando paquetes con winget...\n");
    system("winget upgrade --include-unknown");
    system("winget upgrade --all --include-unknown");
    printf("\nActualización completada.\n");
    WaitKey();
    return;
    
}

// Función para liberar la caché de DNS

void FlushDNS() {
	
    printf("Liberando la cache de DNS...\n");
    system("ipconfig /flushdns");
    printf("Cache de DNS liberada.\n");
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
    WaitKey();
    return;

}

void CleanStreamio() {
    
    printf("Limpiando la cache de Streamio...\n");
    system("rd /s /q \"C:\\Users\\ferna\\AppData\\Roaming\\stremio\\stremio-server\\stremio-cache\"");
    printf("Cache de Streamio limpio.\n");
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
	system("cleanmgr.exe"); // Opens the Cleaner Manager
	return;

}

void AboutLimpia() {
    
    ClearScreen();
    
    printf("* Para que el programa funcione correctamente es necesario que se ejecute en modo\n");
    printf("'Administrador de Sistema' para que pueda realizar todas las acciones. De lo contrario\n");
    printf("Windows negara la mayoria de los comandos que intente aplicar el programa.\n\n");
    
    printf("* La opcion 'Actualizar paquetes con winget' actualizara los programas instalados en Windows\n");
    printf("a su version mas reciente. Si usted no desea actualizar o no sabe como esto puede afectar\n");
    printf("el uso cotidiano de sus aplicaciones por favor evite utilizar esta opcion.\n\n");

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
		
	WaitKey();

}
