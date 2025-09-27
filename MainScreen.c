#include <stdio.h>

#ifdef _WIN32

	#include <windows.h>
	
#endif

int Options;

int main () {
	
	MainMenu:
	
	system("cls");
	
	printf("FGR SOFTWARE 0.1\n");
	printf("================\n\n");
	
	printf("1- Wallet Compare\n");
	printf("2- Payment Assistant\n");
	
	printf("\n77- Exit\n");
	
	printf("\n>> ");
	
	scanf("%d", &Options);
	
	switch(Options){
		
		case 1:
		
			system("WalletCompare.exe");
			break;
			
		case 2:
		
			system("PaymentAssistant.exe");
			break;
			
			
		case 77:
			
			printf("\nEnding...");
			return 0;
			break;
			
		default:
		
			goto MainMenu;
			break;
			
		}
		
	goto MainMenu;	
	return 0;
	
	}
