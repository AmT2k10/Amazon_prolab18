/*
 * gestoreStringhe.c
 *
 *  Created on: 03 ago 2018
 *      Author: Andrea
 */

#include "gestoreStringhe.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
 * isNumero è una funzione che controlla se la stringa ricevuta come parametro
 * sia o meno un numero. Essa restituisce 0 se la funzione non è un numero,
 * 1 altrimenti */
	short isNumero(char* inputString)
	{
		unsigned int i=0;
		while(inputString[i] != '\0')
		{
			if (isdigit(inputString[i]))
			{
				i++;
			}
			else
			{
				return 0;
			}
		}
		return 1;
	}

	/*
	 * isNumeroDec è una funzione che controlla se la stringa ricevuta come parametro
	 * sia o meno un numero decimale. Essa restituisce 0 se la funzione non è un numero,
	 * 1 altrimenti */
	short isNumeroDec(char* inputString)
	{
		unsigned int i=0;
		while(inputString[i] != '\0')
		{
			if (isdigit(inputString[i]) || (inputString[i]=='.'))
			{
				i++;
			}
			else
			{
				return 0;
			}
		}
		return 1;
	}



	/*
	 * Inseriscistringa spazi prende una stringa da input con gli spazi
	 */
	short inserisciStringaSpazi (char* inputString, int dim)
	{
		fflush(stdin);
		fgets(inputString, dim, stdin);
		inputString [strlen(inputString) - 1] = '\0';
		if  ((strlen(inputString)>0) && (strlen(inputString)< dim))
		{
			return 1;
		}
		else
		{
			puts("\n**INPUT ERRATO,riprovare\n");
			return 0;
		}
	}

	/*
		 * Inseriscistringa spazi prende una stringa da input con gli spazi per i nomi di persone
		 */
		short inserisciStringaSpaziNome (char* inputString, int dim)
		{
			int i;
			fflush(stdin);
			fgets(inputString, dim, stdin);
			inputString [strlen(inputString) - 1] = '\0';
			if  ((strlen(inputString)>0) && (strlen(inputString)< dim))
			{
				//return 1;
				for(i=0; i<dim; i++)
				{
					if(isdigit(inputString[i]))
					{
						puts("\n**INPUT ERRATO,riprovare\n");
						return 0;
					}
				}
			}
			else
			{
				puts("\n**INPUT ERRATO,riprovare\n");
				return 0;
			}
			return 1;
		}

	/*
		 * Inseriscistringa spazi prende una stringa da input senza gli spazi
		 */
	short inserisciStringa (char* inputString, int dim)
	{
		scanf("%s", inputString);
		if  ((strlen(inputString)>0) && (strlen(inputString)< dim))
		{
			return 1;
		}
		else
		{
			puts("\n**INPUT ERRATO,riprovare\n");
			return 0;
		}
	}

	/*
	 * Funzione che permette l'inserimento di un valore compreso tra due valori limite
	 */
	short inserisciNumero (char* inputString, int limiteInf, int limiteSup)
	{
		scanf("%s", inputString);
		if (isNumero(inputString) && (atoi(inputString)>limiteInf && atoi(inputString)<limiteSup ))
		{
			return 1;
		}
		else
		{
			puts("\n**INPUT ERRATO,riprovare\n");
			return 0;
		}
	}

	/*
	 * funzione che permette inserim di num dec
	 */
	short inserisciNumeroDec(char* inputString, float limiteInf, float limiteSup)
	{
		scanf("%s", inputString);
		if( isNumeroDec(inputString) != 0){
		//funzione atof converte stringa in double
		if( atof(inputString) > limiteInf && atof(inputString) < limiteSup )
		{
			return 1;
		}else
		{
			puts("\n**INPUT ERRATO,riprovare\n");
			return 0;
		}
		}else
		{
			puts("\n**INPUT ERRATO,riprovare\n");
			return 0;
		}
	}

