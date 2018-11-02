/**
 * Funzione menù principale che richiama i sottomenù per la gestiore dei prodotti, degli utenti e delle preferenze.
 * @return 0 alla fine dell'esecuzione al SO
 */

#include <stdio.h>
#include <stdlib.h>
/*include mie librerie*/
#include "gestoreStringhe.h"

/*MENU PRINCIPALE*/
int main(void)
{
	short controlloInput=0;
	char stringa_input [50];
	short uscita = 0;
	//MENU PRINCIPALE DEL GESTORE UTENTI
	do{
		puts("AMAZON MENU PRINCIPALE\n\n");
		puts("[1]\tGestione UTENTI\n");
		puts("[2]\tGestione PRODOTTI\n");
		puts("[3]\tGestione PREFERENZE\n");
		puts("[4]\tUscita\n");
		do
		{
			controlloInput=inserisciNumero(stringa_input,0,5);
		}while(controlloInput==0);
		switch (atoi(stringa_input)) {
			case 1:
				gestoreUtenti();
			break;
			case 2:
				gestoreProdotti();
			break;
			case 3:
				gestorePreferenze();
			break;
			case 4:
				uscita =1;
				break;
			default:
				puts("Valore inserito non valido! Ripetere l'inserimento:\n");
				scanf("%s", stringa_input);
		}
	}while (uscita == 0);
	printf("\nCHIUSURA AMAZON\n");
	printf("\nGrazie per la visita|\n");
	system ("pause");
	return 0;
}
