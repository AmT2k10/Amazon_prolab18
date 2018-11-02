/**
 * @file gestoreProdotti.c
 *
 * Libreria che include le funzioni/procedure per gestire i prodotti
 *
  * Contiene un menu, richiamato nel main che a sua volta può richiamare le varie operazioni da fare sul tipo di dato prodotto
 * Contiene anche un ulteriore menu per richiamare le funzioni di ordinamento sui prodotti
 *
 * @version 1.0
 * @date 30/09/2018
 * @authors Montemurro Andrea, Mininni Claudio
 * @copyright AJCM
 *
 */

#include "gestoreProdotti.h"
#include "gestoreStringhe.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @var nomicategoria array di char contenente i nomi delle categorie dei prodotti
 */
char* nomiCategorie[NUM_CATEGORIE] = {"Elettronica", "Cucina", "Sport", "Hobby", "Giardinaggio", "Libri"};


/* MENU GESTIONE PRODOTTI
 * permette di gestire le operazioni relative ai prodotti di amazon
 */
short gestoreProdotti ()
{
	system("cls");
	char stringa_input [50];
	short isValida=0; //variabile booleana che stabilisce se la stringa_input è valida per il menu
	short uscita = 0;
	//MENU PRINCIPALE DEL GESTORE UTENTI
	do{
	while(!isValida)
	{
		puts("AMAZON MENU PRODOTTI\n\n");
		puts("[1]\tINSERISCI prodotto\n");
		puts("[2]\tVISUALIZZA elenco prodotti\n");
		puts("[3]\tMODIFICA DATI prodotto\n");
		puts("[4]\tRICERCA DATI prodotto\n");
		puts("[5]\tCANCELLA prodotto\n");
		puts("[6]\tFUNZIONALITA' ORDINAMENTO prodotto\n");
		puts("[7]\tUscita\n");
		scanf("%s", stringa_input);
		if (isNumero(stringa_input) && (atoi(stringa_input)>0 && atoi(stringa_input)<8 ))
		{
			isValida=1;
		}
		else
		{
			puts("**INPUT ERRATO,riprovare\n");
			scanf("%s",stringa_input);
		}
	}
		switch (atoi(stringa_input)) {
			case 1:
				inserisciProdotto();
			break;
			case 2:
				visualizzaElencoProdotti();
			break;
			case 3:
				modificaProdotto();
			break;
			case 4:
				menuRicercaProdotti();
			break;
			case 5:
				cancellaProdotto();
			break;
			case 6:
				menuOrdinaProdotto();
				break;
			case 7:
				uscita =1;
				break;
			default:
				puts("Valore inserito non valido! Ripetere l'inserimento:\n");
				scanf("%s", stringa_input);
		}
		isValida=0;
	}while (uscita == 0);
	system("cls");
	return uscita;
}

/*Menu per gestire i tipi di ricerca del prodotto*/
short menuRicercaProdotti()
{
	system("cls");
	short controlloInput=0;
	char stringa_input [50];
	short uscita = 0;
	//MENU PRINCIPALE per la ricerca del prodotto
	do{
		puts("Secondo quale criterio vuoi visualizzare i prodotti?\n\n");
		puts("[1]\tVisualizza un prodotto da ID\n");
		puts("[2]\tVisualizza un elenco prodotti dato un prezzo limite\n");
		puts("[3]\tVisualizza un elenco prodotti dato un prezzo base\n");
		puts("[4]\tVisualizza un elenco prodotti inserendo un nome\n");
		puts("[5]\tVisualizza un elenco prodotti inserendo un'azienda\n");
		puts("[6]\tVisualizza un elenco prodotti inserendo una categoria\n");
		puts("[7]\tUscita\n");
		do
		{
			controlloInput= inserisciNumero(stringa_input, 0, 8);
		}while(controlloInput==0);
			switch (atoi(stringa_input)) {
				case 1:
					visualizzaProdottoID();
				break;
				case 2:
					visualizzaProdottoPrezzoMin();
				break;
				case 3:
					visualizzaProdottoPrezzoMagg();
				break;
				case 4:
					visualizzaProdottoNome();
				break;
				case 5:
					visualizzaProdottoAzienda();
				break;
				case 6:
					visualizzaProdottoCategoria();
					break;
				case 7:
					uscita =1;
					break;
				default:
					puts("Valore inserito non valido! Ripetere l'inserimento:\n");
					scanf("%s", stringa_input);
			}
		}while (uscita == 0);
	return uscita;
}

/*Menu per gestire gli ordinamenti del prodotto*/
short menuOrdinaProdotto()
{
	system("cls");
	short controlloInput =0;
	char stringa_input [50];
	short uscita = 0;
	//MENU PRINCIPALE per gli ordinamenti dei prodotti
	do{
		puts("Quale elenco ordinato visualizzare?\n\n");
		puts("[1]\tUltimi 10 prodotti inseriti\n");
		puts("[2]\tTop 10 prodotti piu' costosi\n");
		puts("[3]\tUscita\n");
		do
		{
			controlloInput= inserisciNumero(stringa_input, 0, 4);
		}while(controlloInput==0);
			switch (atoi(stringa_input)) {
				case 1:
					ultimiDieciArrivi();
				break;
				case 2:
					topDieciCostosi();
				break;
				case 3:
					uscita =1;
					break;
				default:
					puts("Valore inserito non valido! Ripetere l'inserimento:\n");
					scanf("%s", stringa_input);
			}
		}while (uscita == 0);
		return uscita;
}


/**
 * Iscrizione di un prodotto
 *
 * @pre esistenza del file listaprodotti
 * @post nuovo prodotto nel file
 */
short inserisciProdotto()
{
	system("cls");
	FILE* listaProdotti;
	prodotto nuovoProdotto;
	char strInputNome[DIM_NOME];
	char strInputAzienda [DIM_NOME];
	char strInputCategoria [DIM_NOME];
	char strInputPrezzo [DIM_NOME];
	char strInputSpedizione [DIM_NOME];
	nuovoProdotto.prodottoID = 0;

	int numProdotti = 0; /* contatore di prodotti */
	short controlloInput = 0; /*variabile di controllo per input, 0 indica falso, 1 vero*/
	/* Apro il file in modalità di lettura binaria */
	if ((listaProdotti = fopen("listaProdotti.txt","rb+")) == NULL)
	{
		/* ERRORE DI APERTURA DEL FILE */
		printf("\nERRORE DI APERTURA DEL FILE!");
		return 0;
	}

	/*Il file è aperto correttamente, posso eseguire le operazioni su di esso*/
	else
	{
		while (!feof(listaProdotti))
			{
				fread(&nuovoProdotto, sizeof(prodotto), 1, listaProdotti);
				if(!feof(listaProdotti))
					numProdotti++; 		/*incremento del contatore di prodotti*/
			}
			/*Controllo che ci sia spazio per l'inserimento di nuovi Prodotti nel sistema */
			if(numProdotti >= MAX_PRODOTTI)
			{
				/*Numero massimo di utenze raggiunte*/
				printf("\nNUMERO MASSIMO DI PRODOTTI RAGGIUNTO DAL SISTEMA, IMPOSSIBILE AGGIUNGERE!\n");
				return 0;
			}
			/*Nessun problema, posso leggere i dati per il nuovo utente da inserire*/
			else
			{
				printf("\n\t\tINSERIMENTO DATI\n");
				/*Inserisco Nome*/
				printf("Inserisci nome del Prodotto: \n");
				do
				{
					controlloInput=inserisciStringaSpazi(strInputNome, DIM_NOME);
				}while(controlloInput==0);
				strcpy(nuovoProdotto.nome,strInputNome);
				fflush(stdin);
				/* Inserisco nome azienda */
				printf("\nInserisci l'azienda produttrice del prodotto: \n");
				do
				{
					controlloInput=inserisciStringaSpazi(strInputAzienda, DIM_NOME);
				}while(controlloInput==0);
				strcpy(nuovoProdotto.azienda, strInputAzienda);

				/* SCELTA CATEGORIA DEL PRODOTTO*/
				printf("\n SELEZIONA LA CATEGORIA DEL PRODOTTO:\n");
				printf("[1]\t Elettronica\n");
				printf("[2]\t Cucina\n");
				printf("[3]\t Sport\n");
				printf("[4]\t Hobby\n");
				printf("[5]\t Giardinaggio\n");
				printf("[6]\t Libri\n");
				do
				{
					controlloInput=inserisciNumero(strInputCategoria,0,NUM_CATEGORIE+1);
				}while(controlloInput==0);
				strcpy(nuovoProdotto.categoria, nomiCategorie[atoi(strInputCategoria)-1]);

				/*TIPO DI SPEDIZIONE*/
				fflush(stdin);
				printf("\nIl prodotto ha la spedizione rapida?\n\t[1] SI\n\t[2] NO\n");
				do
				{
					controlloInput = inserisciNumero(strInputSpedizione,0,3);
				}while(controlloInput==0);
				if(atoi(strInputSpedizione)==1)
					nuovoProdotto.spedizioneRapida= 1;
				else
					nuovoProdotto.spedizioneRapida=0;

				/*INSERISCO PREZZO*/
				printf("\nInserisci il prezzo in formato decimale (Es. 0.97) : ");
				do
				{
					controlloInput= inserisciNumeroDec(strInputPrezzo, 0.00, MAX_PREZZO);
				}while(controlloInput==0);
				nuovoProdotto.prezzo = atof(strInputPrezzo);

				/* Dati inseriti sono corretti, si può allora inserire  nel FILE dei prodotti*/
				/* Aggiorno l'id prodotto da inserire */
				numProdotti++;
				nuovoProdotto.prodottoID = numProdotti;
				/*Posiziono il puntatore del file dopo l'ultimo prodotto inserito*/
				fseek(listaProdotti, (nuovoProdotto.prodottoID -1) * sizeof(prodotto), SEEK_SET);
				/*SCRITTURA SU FILE*/
				fwrite(&nuovoProdotto, sizeof(nuovoProdotto), 1, listaProdotti);
			}
	}
	printf("%6d%13s%11s%18s%22s %.2f\n", nuovoProdotto.prodottoID,
					nuovoProdotto.nome,nuovoProdotto.azienda,nuovoProdotto.categoria, strInputSpedizione,nuovoProdotto.prezzo);
	fclose(listaProdotti);
	return 1;
}




/**
 * Visualizza elenco prodotti
 *
 * @pre esistenza del file listaprodotti
 */

void visualizzaElencoProdotti()
{
	system("cls");
	FILE* listaProdotti;
	prodotto prodottoFile;
	int numProdotti = 0;
	char spedizione [DIM_NOME];

	if ((listaProdotti = fopen("listaProdotti.txt", "rb+")) == NULL)
	{
		printf("\nERRORE NELL'APERTURA DEL FILE!");
	}
	else
	{
		/*Stampo intestazione tabella*/
		printf("%6s%20s%20s%20s%18s%8s\n\n", "ID", "NOME", "AZIENDA",
				"CATEGORIA","SPEDIZIONE GRAT.", "PREZZO");
		while (!feof(listaProdotti))
		{
			fread(&prodottoFile, sizeof(prodottoFile), 1, listaProdotti);
			/*Evito di stampare due volte l'ultimo record*/
			if(feof(listaProdotti))
				break;
			if (prodottoFile.prodottoID != 0)
			{
				if(prodottoFile.spedizioneRapida == 1)
					strcpy(spedizione, "SI");
				else
					strcpy(spedizione, "NO");
				printf("%6d%20s%20s%20s%18s %.2f\n", prodottoFile.prodottoID,
				prodottoFile.nome,prodottoFile.azienda,prodottoFile.categoria, spedizione,prodottoFile.prezzo);
			}
			if(!feof(listaProdotti))
				numProdotti++; 		/*incremento del contatore di prodotti*/
		}
	}
	fclose(listaProdotti);
}



/**
 * Modifica prodotto
 *
 * @pre esistenza del file listaprodotti
 * @post modifica dei dati relativi a un prodotto
 */

short modificaProdotto()
{
	system("cls");
	visualizzaElencoProdotti();
	FILE* listaProdotti;
	prodotto prodottoApp; /*Dati utene modificati*/
	prodotto prodottoFile; /*Dati utente letti da file*/
	short controlloInput = 0; /*variabile di controllo per input, 0 indica falso, 1 vero*/
	//per lettura dati da tastiera
	char strInputCategoria[DIM_NOME];
	char strInput[DIM_NOME];
	char strInputPrezzo[DIM_NOME];
	int chiaveID; //id del prodotto da modificare
	int numProdotti = 0; /*contatore del numero dei prodotti nel file*/
	char spedizione [DIM_NOME]; //stringa per stampare a video tipo di spedizione
	/*Apertura File*/
	if ((listaProdotti = fopen("listaProdotti.txt", "rb+")) == NULL)
	{
		printf("\nERRORE NELL'APERTURA DEL FILE!");
		return 0;
	}
	else
	{
		/*Controllo il numero di prodottti nel file*/
		while (!feof(listaProdotti))
		{
			fread(&prodottoFile, sizeof(prodotto), 1, listaProdotti);
			if(!feof(listaProdotti))
				numProdotti++; 		/*incremento del contatore di prodotti*/
		}
		/* Chiedo l'id dell'utente da cercare */
		printf("\n\nInserisci l' ID del prodotto che vuoi modificare: ");
		do
		{
			controlloInput=inserisciNumero(strInput, 0, numProdotti+1);
		}while(controlloInput==0);
		chiaveID = atoi(strInput);
		controlloInput = 0;
		/*Posizionamento sul record da modificare*/
		fseek(listaProdotti, (chiaveID-1)* sizeof(prodotto),SEEK_SET );

		/*Leggo il record*/
		fread(&prodottoFile, sizeof(prodotto), 1, listaProdotti);
		//Lo stampo a video
		if(prodottoFile.spedizioneRapida == 1)
			strcpy(spedizione, "SI");
		else
			strcpy(spedizione, "NO");
		/*Stampo intestazione tabella*/
		printf("%6s%13s%11s%18s%22s%8s\n\n", "ID", "NOME", "AZIENDA",
						"CATEGORIA","SPEDIZIONE GRATUITA", "PREZZO");
		printf("%6d%13s%11s%18s%22s %.2f\n", prodottoFile.prodottoID,
								prodottoFile.nome,prodottoFile.azienda,prodottoFile.categoria, spedizione,prodottoFile.prezzo);
		/*Controllo che non si tratta di un prodotto cancellato (ID uguale a 0) */
		if (prodottoFile.prodottoID != 0)
		{
			printf("\n Aggiorna il nome del prodotto: \n");
			do
			{
				controlloInput=inserisciStringaSpazi(prodottoApp.nome, DIM_NOME);
			}while(controlloInput==0);

			/* Modifico azienda */
			printf("\nModifica azienda del prodotto: \n");
			do
			{
				controlloInput=inserisciStringaSpazi(prodottoApp.azienda, DIM_NOME);
			}while(controlloInput==0);

			printf("\nModifica la categoria del prodotto\n");
			/* SCELTA CATEGORIA DEL PRODOTTO*/
			printf("\n SELEZIONA LA CATEGORIA DEL PRODOTTO:\n");
			printf("[1]\t Elettronica\n");
			printf("[2]\t Cucina\n");
			printf("[3]\t Sport\n");
			printf("[4]\t Hobby\n");
			printf("[5]\t Giardinaggio\n");
			printf("[6]\t Libri\n");
			do
			{
				controlloInput=inserisciNumero(strInputCategoria, 0, NUM_CATEGORIE+1);
			}while(controlloInput==0);
			strcpy(prodottoApp.categoria, nomiCategorie[atoi(strInputCategoria)-1]);

			/*MODIFICO IL PREZZO*/
			printf("\nModifica il prezzo in formato decimale (Es. 0.97) : ");
			do
			{
				controlloInput= inserisciNumeroDec(strInputPrezzo, 0.00, MAX_PREZZO);
			}while(controlloInput==0);
			prodottoApp.prezzo=atof(strInputPrezzo);

			printf("\nMantenere le modifiche?\n[1]\tSI\n[2]\tNO\n");
			do
			{
				controlloInput=inserisciNumero(strInput,0,3);
			}while(controlloInput==0);
			if (strcmp(strInput, "SI")==1)
			{
					/*Posso scrivere su file le modifiche*/
					/*Posizionamento sul record da modificare*/
					fseek(listaProdotti, (chiaveID-1)* sizeof(prodotto),SEEK_SET );
					strcpy(prodottoFile.nome, prodottoApp.nome);
					strcpy(prodottoFile.azienda, prodottoApp.azienda);
					strcpy(prodottoFile.categoria, prodottoApp.categoria);
					prodottoFile.prodottoID = chiaveID;
					prodottoFile.prezzo = prodottoApp.prezzo;
					prodottoFile.spedizioneRapida = prodottoApp.spedizioneRapida;
					fwrite(&prodottoFile, sizeof(prodotto), 1, listaProdotti);
			}
		}
		else
		{
			printf("\nQuesto prodotto è stato cancellato!\n");
			return 0;
		}
	}
	fclose(listaProdotti);
	return 1;
}

/**
 * Visualizzazione di un prodotto
 *
 * @pre esistenza del file listaProdotti
 * @pre esistenza del prodotto da visualizzare
 */
void visualizzaProdottoID ()
{
	system("cls");
	FILE* listaProdotti;
	prodotto prodottoFile; /*Dati prodotto letti da file*/
	char spedizione[DIM_NOME];
	short controlloInput = 0; /*variabile di controllo per input, 0 indica falso, 1 vero*/
	char strInput[20]; //per lettura dati da tastiera
	int chiaveID; //id del prodotto da modificare
	int numProdotti= 0; //contatore di prodotti nel file
	/*Apertura file*/
	if ((listaProdotti = fopen("listaProdotti.txt", "rb+")) == NULL)
		{
			printf("\nERRORE NELL'APERTURA DEL FILE!");
		}
	else
	{
		/*Controllo il numero di prodotti nel file*/
		while (!feof(listaProdotti))
		{
			fread(&prodottoFile, sizeof(prodotto), 1, listaProdotti);
			if(!feof(listaProdotti))
				numProdotti++; 		/*incremento del contatore di prodotti*/
		}
		/* Chiedo l'id del prodotto da cercare */
		printf("\n\nInserisci l' ID del prodotto che vuoi visualizzare: ");
		do
		{
			controlloInput=inserisciNumero(strInput, 0, numProdotti+1);
		}while(controlloInput==0);
		chiaveID = atoi(strInput);
		controlloInput = 0;
		/*Posizionamento sul record da visualizzare*/
		fseek(listaProdotti, (chiaveID-1)* sizeof(prodotto),SEEK_SET );

		/*Leggo il record*/
		fread(&prodottoFile, sizeof(prodotto), 1, listaProdotti);
		if (prodottoFile.prodottoID == 0)
		{
			/* UTENTE CANCELLATO*/
			printf("\nQuesto prodotto è stato cancellato!\n");
		}
		else
		{
			//Lo stampo a video
			/*Stampo intestazione tabella*/
			/*Stampo intestazione tabella*/
			printf("%6s%13s%11s%18s%22s%8s\n\n", "ID", "NOME", "AZIENDA",
							"CATEGORIA","SPEDIZIONE GRATUITA", "PREZZO");
			if(prodottoFile.spedizioneRapida == 1)
				strcpy(spedizione, "SI");
			else
				strcpy(spedizione, "NO");
			printf("%6d%13s%11s%18s%22s %.2f\n", prodottoFile.prodottoID,
							prodottoFile.nome,prodottoFile.azienda,prodottoFile.categoria, spedizione,prodottoFile.prezzo);
		}
	}
	fclose(listaProdotti);
}

/**
 * Visualizzazione il prodotto dal prezzo minore
 *
 * @pre esistenza del file listaUtenti
 * @pre file riempito
 * @post stampa a video del file dal prezzo minore
 */
int visualizzaProdottoPrezzoMin()
{
	system("cls");
	FILE* listaProdotti;
	prodotto prodottoFile; /*Dati prodotto letti da file*/
	char spedizione[DIM_NOME];
	short controlloInput = 0; /*variabile di controllo per input, 0 indica falso, 1 vero*/
	char strInput[20]; //per lettura dati da tastiera
	int numProdotti= 0; //contatore di prodotti che corrispondono alle specifiche

	printf("\tInserisci il prezzo LIMITE per visualizzare l'elenco dei prodotti: \n");
	do
	{
		controlloInput=inserisciNumero(strInput,0.00, MAX_PREZZO);
	}while(controlloInput==0);


	if ((listaProdotti = fopen("listaProdotti.txt", "rb+")) == NULL)
	{
		printf("\nERRORE NELL'APERTURA DEL FILE!");
		return 0;
	}
	else
	{
		while(!feof(listaProdotti))
		{
			fread(&prodottoFile, sizeof(prodotto), 1, listaProdotti);
			if(!feof(listaProdotti))
			{
				if((prodottoFile.prezzo<=atof(strInput))&& (prodottoFile.prodottoID!=0))
				{
					numProdotti++;
					if(numProdotti==1)
					{
						/*Stampo intestazione tabella*/
						printf("%6s%13s%11s%18s%22s%8s\n\n", "ID", "NOME", "AZIENDA",
						"CATEGORIA","SPEDIZIONE GRATUITA", "PREZZO");
					}
					printf("%6d%13s%11s%18s%22s %.2f\n", prodottoFile.prodottoID,
							prodottoFile.nome,prodottoFile.azienda,prodottoFile.categoria, spedizione,prodottoFile.prezzo);
				}
			}


		}

		}
	fclose(listaProdotti);
	if(numProdotti==0)
		printf("\nNessun prodotto con prezzo minore di quello inserito!\n");
	return numProdotti;
}

/**
 * Visualizzazione il prodotto dal prezzo maggiore
 *
 * @pre esistenza del file listaUtenti
 * @pre file riempito
 * @post stampa a video del file dal prezzo maggiore
 */
int visualizzaProdottoPrezzoMagg()
{
	system("cls");
	FILE* listaProdotti;
	prodotto prodottoFile; /*Dati prodotto letti da file*/
	char spedizione[DIM_NOME];
	short controlloInput = 0; /*variabile di controllo per input, 0 indica falso, 1 vero*/
	char strInput[20]; //per lettura dati da tastiera
	int numProdotti= 0; //contatore di prodotti che corrispondono alle specifiche

	printf("\nInserisci il prezzo BASE per visualizzare l'elenco dei prodotti: \n");
	do
	{
		controlloInput=inserisciNumero(strInput,0.00, MAX_PREZZO);
	}while(controlloInput==0);

	if ((listaProdotti = fopen("listaProdotti.txt", "rb+")) == NULL)
	{
		printf("\nERRORE NELL'APERTURA DEL FILE!");
		return 0;
	}
	else
	{
		while(!feof(listaProdotti))
		{
			fread(&prodottoFile, sizeof(prodotto), 1, listaProdotti);
			if(!feof(listaProdotti))
			{
				if((prodottoFile.prezzo>=atof(strInput))&& (prodottoFile.prodottoID!=0))
				{
					numProdotti++;
					if(numProdotti==1)
					{
						/*Stampo intestazione tabella*/
						printf("%6s%13s%11s%18s%22s%8s\n\n", "ID", "NOME", "AZIENDA",
						"CATEGORIA","SPEDIZIONE GRATUITA", "PREZZO");
					}
					printf("%6d%13s%11s%18s%22s %.2f\n", prodottoFile.prodottoID,
							prodottoFile.nome,prodottoFile.azienda,prodottoFile.categoria, spedizione,prodottoFile.prezzo);
				}
			}


		}

	}
	fclose(listaProdotti);
	if(numProdotti==0)
		printf("\nNessun prodotto con prezzo maggiore di quello inserito!\n");
	return numProdotti;
}

/**
 * Visualizzazione il prodotto dal nome corrispondente
 *
 * @pre una stringa che descrive il nome del prodotto
 * @pre esistenza del file listaUtenti
 * @pre file riempito
 * @post stampa a video del file dal nome corrispondente
 */
int visualizzaProdottoNome()
{
	system("cls");
	FILE* listaProdotti;

	prodotto prodottoFile; /*Dati prodotto letti da file*/

	char spedizione[DIM_NOME];
	short controlloInput = 0; /*variabile di controllo per input, 0 indica falso, 1 vero*/
	char strInput[20]; //per lettura dati da tastiera
	int numProdotti= 0; //contatore di prodotti che corrispondono alle specifiche
	/*Lettura nome da tastiera*/
	printf("\nInserisci il nome con cui effettuare la ricerca: \n");
	do
	{
		controlloInput=inserisciStringaSpazi(strInput, DIM_NOME);
	}while(controlloInput==0);

	/*Apro file*/
	if ((listaProdotti = fopen("listaProdotti.txt", "rb+")) == NULL)
	{
		printf("\nERRORE NELL'APERTURA DEL FILE!");
		return 0;
	}
	else
	{
		/*Leggo da file e prendo gli elementi che soddisfano il criterio di ricerca*/
		while(!feof(listaProdotti))
		{
			fread(&prodottoFile, sizeof(prodotto), 1, listaProdotti);
			if(!feof(listaProdotti))
			{
				if((strcmp(prodottoFile.nome, strInput)== 0)&& (prodottoFile.prodottoID!=0))
				{
					numProdotti++;
					if(numProdotti==1)
					{
						/*Stampo intestazione tabella*/
						printf("%6s%13s%11s%18s%22s%8s\n\n", "ID", "NOME", "AZIENDA",
						"CATEGORIA","SPEDIZIONE GRATUITA", "PREZZO");
					}
					printf("%6d%13s%11s%18s%22s %.2f\n", prodottoFile.prodottoID,
							prodottoFile.nome,prodottoFile.azienda,prodottoFile.categoria, spedizione,prodottoFile.prezzo);
				}
			}

		}

	}
	fclose(listaProdotti);
	if(numProdotti==0)
		printf("\nNessun prodotto con nome uguale quello inserito!\n");
	return numProdotti;
}


/**
 * Visualizzazione il prodotto dal nome azienda corrispondente
 *
 * @pre una stringa che descrive il nome azienda del prodotto
 * @pre esistenza del file listaUtenti
 * @pre file riempito
 * @post stampa a video del file dal nome  azienda corrispondente
 */
int visualizzaProdottoAzienda()
{
	system("cls");
	FILE* listaProdotti;

	prodotto prodottoFile; /*Dati prodotto letti da file*/

	char spedizione[DIM_NOME];
	short controlloInput = 0; /*variabile di controllo per input, 0 indica falso, 1 vero*/
	char strInput[20]; //per lettura dati da tastiera
	int numProdotti= 0; //contatore di prodotti che corrispondono alle specifiche

	/*Lettura nome da tastiera*/
	printf("\nInserisci il nome dell'azienda con cui effettuare la ricerca: \n");
	do
	{
		controlloInput=inserisciStringaSpazi(strInput,DIM_NOME);
	}while(controlloInput==0);

	/*Apro file*/
	if ((listaProdotti = fopen("listaProdotti.txt", "rb+")) == NULL)
	{
		printf("\nERRORE NELL'APERTURA DEL FILE!");
		return 0;
	}
	else
	{
		/*Leggo da file e prendo gli elementi che soddisfano il criterio di ricerca*/
		while(!feof(listaProdotti))
		{
			fread(&prodottoFile, sizeof(prodotto), 1, listaProdotti);
			if(!feof(listaProdotti))
			{
				if((strcmp(prodottoFile.azienda, strInput)== 0)&& (prodottoFile.prodottoID!=0))
				{
					numProdotti++;
					if(numProdotti==1)
					{
						/*Stampo intestazione tabella*/
						printf("%6s%13s%11s%18s%22s%8s\n\n", "ID", "NOME", "AZIENDA",
						"CATEGORIA","SPEDIZIONE GRATUITA", "PREZZO");
					}
					printf("%6d%13s%11s%18s%22s %.2f\n", prodottoFile.prodottoID,
							prodottoFile.nome,prodottoFile.azienda,prodottoFile.categoria, spedizione,prodottoFile.prezzo);
				}
			}

		}

	}
	fclose(listaProdotti);
	if(numProdotti==0)
		printf("\nNessun prodotto con nome azienda uguale quello inserito!\n");
	return numProdotti;
}


/**
 * Visualizzazione il prodotto dalla categoria corrispondente
 *
 * @pre una stringa che descrive il nome categoria del prodotto
 * @pre esistenza del file listaUtenti
 * @pre file riempito
 * @post stampa a video del file dalla categoria corrispondente
 */
int visualizzaProdottoCategoria()
{
	system("cls");
	FILE* listaProdotti;

	prodotto prodottoFile; /*Dati prodotto letti da file*/

	char spedizione[DIM_NOME];
	short controlloInput = 0; /*variabile di controllo per input, 0 indica falso, 1 vero*/
	char strInput[20]; //per lettura dati da tastiera
	int numProdotti= 0; //contatore di prodotti che corrispondono alle specifiche

	/* SCELTA CATEGORIA DEL PRODOTTO DA CERCARE*/
	printf("\n SELEZIONA LA CATEGORIA con cui effettuare la ricerca:\n");
	printf("[1]\t Elettronica\n");
	printf("[2]\t Cucina\n");
	printf("[3]\t Sport\n");
	printf("[4]\t Hobby\n");
	printf("[5]\t Giardinaggio\n");
	printf("[6]\t Libri\n");
	do
	{
		controlloInput=inserisciNumero(strInput, 0, 7);
	}while(controlloInput==0);


	/*Apro file*/
	if ((listaProdotti = fopen("listaProdotti.txt", "rb+")) == NULL)
	{
		printf("\nERRORE NELL'APERTURA DEL FILE!");
		return 0;
	}
	else
	{
		/*Leggo da file e prendo gli elementi che soddisfano il criterio di ricerca*/
		while(!feof(listaProdotti))
		{
			fread(&prodottoFile, sizeof(prodotto), 1, listaProdotti);
			if(!feof(listaProdotti))
			{
				if((strcmp(prodottoFile.categoria, nomiCategorie[atoi(strInput)-1])== 0)&& (prodottoFile.prodottoID!=0))
				{
					numProdotti++;
					if(numProdotti==1)
					{
						/*Stampo intestazione tabella*/
						printf("%6s%13s%11s%18s%22s%8s\n\n", "ID", "NOME", "AZIENDA",
						"CATEGORIA","SPEDIZIONE GRATUITA", "PREZZO");
					}
					printf("%6d%13s%11s%18s%22s %.2f\n", prodottoFile.prodottoID,
							prodottoFile.nome,prodottoFile.azienda,prodottoFile.categoria, spedizione,prodottoFile.prezzo);
				}
			}
		}

	}
	fclose(listaProdotti);
	if(numProdotti==0)
		printf("\nNessun prodotto con categoria uguale quello inserito!\n");
	return numProdotti;
}

/**
 * Cancellazione di un prodotto
 *
 * @pre esistenza del file listaProdotti
 * @pre esistenza del prodotto da cancellare
 * @post prodotto settato con id a 0
 */
short cancellaProdotto()
{
	system("cls");
	visualizzaElencoProdotti();
	FILE* listaProdotti;
	prodotto prodottoApp; /*Dati prodotto cancellato*/
	prodotto prodottoFile; /*Dati prodotto letti da file*/
	short controlloInput = 0; /*variabile di controllo per input, 0 indica falso, 1 vero*/
	char strInput[20]; //per lettura dati da tastiera
	int chiaveID; //id dell'utente da modificare
	int numProdotti= 0;
	/*Apertura file*/
	if ((listaProdotti = fopen("listaProdotti.txt", "rb+")) == NULL)
	{
		printf("\nERRORE NELL'APERTURA DEL FILE!");
		return 0;
	}
	else
	{
	/*Controllo il numero di prodotti nel file*/
		while (!feof(listaProdotti))
		{
			fread(&prodottoFile, sizeof(prodotto), 1, listaProdotti);
			if(!feof(listaProdotti))
				numProdotti++; 		/*incremento del contatore di prodotti*/
		}
		/* Chiedo l'id dell'utente da cercare */
		printf("\n\nInserisci l' ID del prodotto che vuoi cancellare: ");
		do
		{
			controlloInput=inserisciNumero(strInput, 0, numProdotti+1);
		}while(controlloInput==0);
		chiaveID = atoi(strInput);

		/*Posizionamento sul record da cancellare*/
		fseek(listaProdotti, (chiaveID-1)* sizeof(prodotto),SEEK_SET );

		/*Leggo il record*/
		fread(&prodottoFile, sizeof(prodotto), 1, listaProdotti);
		if (prodottoFile.prodottoID == 0)
		{
			/* SI TRATTA DI UN PRODOTTO GIA' CANCELLATO*/
			printf("\nQuesto prodotto risulta già cancellato!\n");
			return 0;
		}
		else
		{
			prodottoApp.prodottoID = 0;
			strcpy(prodottoApp.nome, prodottoFile.nome);
			strcpy(prodottoApp.azienda, prodottoFile.azienda);
			prodottoApp.spedizioneRapida=prodottoFile.spedizioneRapida;
			prodottoApp.prezzo=prodottoFile.prezzo;
			/*Posizionamento sul record da modificare*/
			fseek(listaProdotti, (chiaveID-1)* sizeof(prodotto),SEEK_SET );

			/*Scrivo il record*/
			fwrite(&prodottoApp,sizeof(prodottoApp), 1, listaProdotti);

		}
		fclose(listaProdotti);
		return 1;
	}
}


/**
 * Stampa ultimi 10 arrivi
 *
 * @pre esistenza del file listaProdotti
 * @pre file con almeno 10 elementi
 */
void ultimiDieciArrivi()
{
	system("cls");
	FILE* listaProdotti;

	prodotto prodottoFile; /*Dati prodotto letti da file*/
	char spedizione [DIM_NOME]; //stringa per mostrare se spedizione rapida SI o NO
	int numProdotti = 0;
	/*Bisogna contare anche i prodotti che oltre ad essere presenti nel file sono ancora validi,
	 * ossia quelli che non sono ancora stati cancellati che quindi non hanno ID settato a 0.*/
	int numProdottiValidi = 0;
	/*Variabile contatore che conterrà il numero di prodotti da stampare*/
	int contProdottiOutput;
	 /*Apro il file*/
	if ((listaProdotti = fopen("listaProdotti.txt", "rb+")) == NULL)
	{
		printf("\nERRORE NELL'APERTURA DEL FILE!");
	}
	else
	{
		while(!feof(listaProdotti))
		{
			fread(&prodottoFile, sizeof(listaProdotti), 1, listaProdotti);
			if(!feof(listaProdotti))
			{
				if(prodottoFile.prodottoID!=0)
				{
					/*Se è un prodotto non cancellato incremento anche il contatore dei prodotti
					 * effettivi presenti su sistema */
					numProdottiValidi++;
				}
				/*Incremento il numero di prodotti totali*/
				numProdotti++;
			}
		}
		/*Controllo che siano EFFETTIVAMENTE presenti in elenco almeno più di dieci prodotti
		 * validi, in modo da stampare gli ultimi dieci
		 */
		if(numProdottiValidi>=10)
		{
			/*Devo stampare a partire dall'ultimo record 10 */
			contProdottiOutput = 10;
			/*Stampo intestazione tabella*/
			printf("%6s%13s%11s%18s%22s%8s\n\n", "ID", "NOME", "AZIENDA",
									"CATEGORIA","SPEDIZIONE GRATUITA", "PREZZO");
			while (contProdottiOutput>0)
			{
				fseek(listaProdotti, (numProdotti-1)*sizeof(prodotto), SEEK_SET);
				fread(&prodottoFile, sizeof(prodotto),1,listaProdotti);
				if(prodottoFile.prodottoID != 0)
				{
					/*Si tratta di un prodotto valido, che devo mostrare*/

					/*setto la stringa relativa alla spedizione*/
					if(prodottoFile.spedizioneRapida == 1)
						strcpy(spedizione, "SI");
					else
						strcpy(spedizione, "NO");

					/*Stampa a video*/
					printf("%6d%13s%11s%18s%22s %.2f\n", prodottoFile.prodottoID,
							prodottoFile.nome,prodottoFile.azienda,prodottoFile.categoria, spedizione,prodottoFile.prezzo);

					/*Decremento il contatore dei prodotti da stampare che sono validi*/
					contProdottiOutput--;
				}
				/*Decremento anche l'indice nella lista dei prodotti*/
				numProdotti--;
			}
		}
		else
		{
			/*Caso con un numero di utenti minore  a 10, la lista degli utenti coincide*/
			printf("\nCi sono meno di 10 prodotti !\n");
		}
	}
	fclose(listaProdotti);
}

/**
 * Stampa 10 prodotti più costosi
 *
 * @pre esistenza del file listaProdotti
 * @pre file con almeno 10 elementi
 */
void topDieciCostosi()
{
	system("cls");
	 prodotto prodotti [MAX_PRODOTTI]; //Dichiaro array di prodotti

	 FILE* listaProdotti;
	 prodotto prodottoFile;
	 int numProdotti = 0;
	 int i,j;
	 prodotto tmp;
	 char spedizione [DIM_NOME];
	 /*Apro file*/
	 	if ((listaProdotti = fopen("listaProdotti.txt", "rb+")) == NULL)
	 	{
	 		printf("\nERRORE NELL'APERTURA DEL FILE!");
	 	}
	 	else
	 	{
	 		/*Leggo da file e prendo gli elementi che soddisfano il criterio di ricerca*/
	 		while(!feof(listaProdotti))
	 		{
	 			fread(&prodottoFile, sizeof(prodotto), 1, listaProdotti);
	 			if(!feof(listaProdotti))
	 			{
	 				if(prodottoFile.prodottoID!=0)
	 				{
	 					prodotti[numProdotti] = prodottoFile;
	 					numProdotti++;
	 				}
	 			}
	 		}
	 	/*Ora ordino il vettore in base al prezzo*/
	 		if(numProdotti>=10)
	 		{
	 			/*ordino il vettore*/
	 			//int i, j, tmp;
	 				for(i = numProdotti-1; i > 0; i--){
	 					for(j = 0; j < i; j++){
	 						if(prodotti[j].prezzo < prodotti[j+1].prezzo){
	 							tmp = prodotti[j];
	 							prodotti[j] = prodotti[j+1];
	 							prodotti[j+1] = tmp;
	 						}
	 					}
	 				}
	 			/*Stampo a video i primi dieci prodotti*/
	 				i=0;
	 				do
	 				{
	 					if(prodotti[i].prodottoID != 0)//se è un prodotto ancora valido e non cancellato
	 					{
	 						if(prodotti[i].spedizioneRapida == 1)
	 							strcpy(spedizione, "SI");
	 						else
	 							strcpy(spedizione, "NO");
	 						printf("%6d%13s%11s%18s%22s %.2f\n", prodotti[i].prodottoID,
	 								prodotti[i].nome,prodotti[i].azienda,prodotti[i].categoria, spedizione,prodotti[i].prezzo);
	 						i++;
	 					}
	 				}while(i<10);
	 		}
	 		else
	 		{
	 			printf("\nInserisci almeno 10 prodotti!\n");
	 		}

	 	}
	 	fclose(listaProdotti);
}
