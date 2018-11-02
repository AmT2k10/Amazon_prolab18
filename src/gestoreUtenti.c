/**
 * @file gestoreUtenti.c
 *
 * Libreria che include le funzioni/procedure per gestire gli utenti
 *
 * Contiene un menu, richiamato nel main che a sua volta può richiamare le varie operazioni da fare sul tipo di dato utente
 *
 * @version 1.0
 * @date 30/09/2018
 * @authors Montemurro Andrea, Mininni Claudio
 * @copyright AJCM
 *
 */

#include "gestoreUtenti.h"
#include "gestoreDate.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @var mesiStringhe[12] array di puntatori a char contenente i nomi dei mesi in stringhe di 3 caratteri
 */
char* mesiStringhe [12]= {"GEN", "FEB", "MAR", "APR", "MAG", "GIU",
		"LUG", "AGO", "SET", "OTT", "NOV", "DIC"};

/**
 * @var giornoMesi[12] array di inter contenente il numero dei giorni del mese relativo al suo indice
 */
int giornoMesi[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/* MENU GESTIONE UTENTI
 * permette di gestire le operazioni relative agli utenti di amazon
 */
short gestoreUtenti ()
{
	system("cls");
	short controlloInput;
	char stringa_input [50];
	short uscita = 0;
	//MENU PRINCIPALE DEL GESTORE UTENTI
	do{
		puts("AMAZON MENU UTENTI\n\n");
		puts("[1]\tISCRIVI utente\n");
		puts("[2]\tVISUALIZZA elenco utenti\n");
		puts("[3]\tMODIFICA DATI utente\n");
		puts("[4]\tVISUALIZZA DATI \n");
		puts("[5]\tCANCELLA utente\n");
		puts("[6]\tUscita\n");
		do
		{
			controlloInput=inserisciNumero(stringa_input, 0, 7);
		}while(controlloInput==0);
		/*Switch */
		switch (atoi(stringa_input)) {
			case 1:
				iscriviUtente();
			break;
			case 2:
				visualizzaElencoUtenti();
			break;
			case 3:
				modificaUtente();
			break;
			case 4:
				visualizzaUtente();
			break;
			case 5:
				cancellaUtente();
			break;
			case 6:
				uscita =1;
				break;
		}
	}while (uscita == 0);
	system("cls");
	return uscita;
}


/**
 * Iscrizione di un utente
 *
 * @pre esistenza del file listaUtenti
 * @post nuovo utente nel file
 */

short iscriviUtente ()
{
	system("cls");
	FILE* listaUtenti; //puntatore al file contenente la lista degli utenti registrati
	utente nuovoUtente; //dichiaro un nuovoUtente
	char strInputGiorno[20];
	char strInputMese[20];
	char strInputAnno[20];
	/*inizializzo il nuovoUtente ai dati di default*/
	nuovoUtente.utenteID = 0;
	//ID (numero incrementale)

	/* Leggo da file per vedere quanti utenti si sono già registrati,
	 * operazione che mi serve per assegnare un codice incrementale all'utente come id
	 * e per vedere se ho raggiunto eventualmente il numero massimo di iscritti
	 */
	int numUtenti = 0; /* contatore di utenze */
	short controlloInput = 0; /*variabile di controllo per input, 0 indica falso, 1 vero*/
	/* Apro il file in modalità di lettura binaria */
	if ((listaUtenti = fopen("listaUtenti.txt","rb+")) == NULL)
	{
		/* ERRORE DI APERTURA DEL FILE */
		printf("\nERRORE DI APERTURA DEL FILE!");
		return 0;
	}

	/*Il file è aperto correttamente, posso eseguire le operazioni su di esso*/
	else
	{
		while (!feof(listaUtenti))
		{
			fread(&nuovoUtente, sizeof(utente), 1, listaUtenti);
			if(!feof(listaUtenti))
				numUtenti++; 		/*incremento del contatore di utenze*/
		}
		/*Controllo che ci sia spazio per l'inserimento di nuovi utenti nel sistema */
		if(numUtenti >= MAX_UTENTI)
		{
			/*Numero massimo di utenze raggiunte*/
			printf("\nNUMERO MASSIMO DI UTENTI RAGGIUNTO DAL SISTEMA, IMPOSSIBILE ISCRIVERSI!\n");
			return 0;
		}
		/*Nessun problema, posso leggere i dati per il nuovo utente da inserire*/
		else
		{
			printf("\n\t\tINSERIMENTO DATI\n");
			/*Inserisco nome*/
			printf("Inserisci nome dell'utente: \n");
			do
			{
				controlloInput=inserisciStringaSpaziNome(nuovoUtente.nome, DIM_NOME);
			}while (controlloInput==0);
			controlloInput = 0;


			/* Inserisco cognome */
			printf("\nInserisci cognome dell'utente: \n");
			do
			{
				controlloInput=inserisciStringaSpaziNome(nuovoUtente.cognome, DIM_COGNOME);
			}while(controlloInput==0);
			controlloInput = 0;

			/*Inserimento data di nascita dell'utente*/
			puts("\nDigita il giorno di nascita: \n");
			do
			{
				controlloInput=inserisciNumero(strInputGiorno, 0, 32);
			}while (controlloInput==0);
			controlloInput=0;

			puts("\nDigita il mese di nascita: \n");
			do
			{
				controlloInput=inserisciNumero(strInputMese,0,13);
			}while (controlloInput==0);
			controlloInput=0;


			puts("\nDigita anno di nascita: \n");
			do
			{
				controlloInput=inserisciNumero(strInputAnno,1900,2005);
			}while (controlloInput==0);
			controlloInput=0;

			/*Converto il mese da formato numerico a lettere */
			nuovoUtente.dataNascita.giorno = atoi (strInputGiorno);
			//strcpy(nuovoUtente.dataNascita.mese, getMese(atoi(strInputMese)));
			strcpy(nuovoUtente.dataNascita.mese, mesiStringhe[atoi(strInputMese)-1]);
			nuovoUtente.dataNascita.anno = atoi(strInputAnno);
		    /*leggo dal sistema la data attuale e la memorizzo come data di iscrizione*/
			time_t orologio;
			struct tm *dataInfo = NULL;
			time (&orologio);
			dataInfo = localtime(&orologio);
			nuovoUtente.dataIscrizione.giorno = dataInfo->tm_mday;
			nuovoUtente.dataIscrizione.anno = (dataInfo->tm_year)+1900;
			strcpy(nuovoUtente.dataIscrizione.mese, mesiStringhe[(dataInfo->tm_mon)]);

			/* Dati inseriti sono corretti, si può allora inserire l'utente nel FILE delle utenze*/
			/* Aggiorno l'id dell'utente da inserire */
			numUtenti++;
			nuovoUtente.utenteID = numUtenti;
			/*Posiziono il puntatore del file dopo l'ultimo utente iscritto*/
			fseek(listaUtenti, (nuovoUtente.utenteID -1) * sizeof(utente), SEEK_SET);
			/*SCRITTURA SU FILE*/
			fwrite(&nuovoUtente, sizeof(utente), 1, listaUtenti);
		}
	}
	printf("%s %s %d-%s-%d", nuovoUtente.nome, nuovoUtente.cognome, nuovoUtente.dataNascita.giorno,nuovoUtente.dataNascita.mese, nuovoUtente.dataNascita.anno);
	printf("\nData iscrizione: ");
	printf("%d-%s-%d", nuovoUtente.dataIscrizione.giorno, nuovoUtente.dataIscrizione.mese, nuovoUtente.dataIscrizione.anno );
	printf("\n\n\n\n");
	fclose(listaUtenti);
	return 1;
}



/**
 * Visualizza elenco utenti
 *
 * @pre esistenza del file listaUtenti
 */

void visualizzaElencoUtenti ()
{
	system("cls");
	FILE* listaUtenti;
	utente utenteFile;
	int numUtenti = 0;

	if ((listaUtenti = fopen("listaUtenti.txt", "rb+")) == NULL)
	{
		printf("\nERRORE NELL'APERTURA DEL FILE!");
	}
	else
	{
		/*Stampo intestazione tabella*/
		printf("%-6s%-13s%-11s%18s%18s\n\n", "ID", "NOME", "COGNOME",
				"DATA NASCITA","DATA ISCRIZIONE");
		while (!feof(listaUtenti))
		{
			fread(&utenteFile, sizeof(utenteFile), 1, listaUtenti);
			/*Evito di stampare due volte l'ultimo record*/
			if(feof(listaUtenti))
				break;
			if (utenteFile.utenteID != 0)
			{
				printf("%-6d%-13s%-11s\t%2d-%3s-%4d\t\t%2d-%3s-%4d\n", utenteFile.utenteID,
				utenteFile.nome,utenteFile.cognome,
				utenteFile.dataNascita.giorno, utenteFile.dataNascita.mese, utenteFile.dataNascita.anno,
				utenteFile.dataIscrizione.giorno, utenteFile.dataIscrizione.mese, utenteFile.dataIscrizione.anno);
			}
			numUtenti++;
		}
	}

	fclose(listaUtenti);
}


/**
 * Modifica di un utente
 *
 * @pre esistenza del file listaUtenti
 * @pre esistenza dell'utente da modificare
 * @post utente con dati modificati
 */

short modificaUtente()
{
	system("cls");
	visualizzaElencoUtenti();
	FILE* listaUtenti;
	utente utenteApp; /*Dati utene modificati*/
	utente utenteFile; /*Dati utente letti da file*/
	short controlloInput = 0; /*variabile di controllo per input, 0 indica falso, 1 vero*/
	char strInput[20]; //per lettura dati da tastiera
	char strInputGiorno[20];
	char strInputMese[20];
	char strInputAnno[20];
	int chiaveID; //id dell'utente da modificare
	int numUtenti= 0;
	/*Apertura file*/
	if ((listaUtenti = fopen("listaUtenti.txt", "rb+")) == NULL)
		{
			printf("\nERRORE NELL'APERTURA DEL FILE!");
		}
	else
	{
		/*Controllo il numero di utenti nel file*/
		while (!feof(listaUtenti))
		{
			fread(&utenteFile, sizeof(utente), 1, listaUtenti);
			if(!feof(listaUtenti))
				numUtenti++; 		/*incremento del contatore di utenze*/
		}
		/* Chiedo l'id dell'utente da cercare */
		printf("\n\nInserisci l' ID dell'utente che vuoi modificare: ");
		do
		{
			controlloInput=inserisciNumero(strInput,0,(numUtenti+1));
		}while(controlloInput==0);
		chiaveID = atoi(strInput);
		controlloInput = 0;


		/*Posizionamento sul record da modificare*/
		fseek(listaUtenti, (chiaveID-1)* sizeof(utente),SEEK_SET );

		/*Leggo il record*/
		fread(&utenteFile, sizeof(utente), 1, listaUtenti);
		//Lo stampo a video
		printf("%-6s%-13s%-11s%18s%18s\n\n", "ID", "NOME", "COGNOME",
						"DATA NASCITA","DATA ISCRIZIONE");
		printf("%-6d%-13s%-11s\t%2d-%3s-%4d\t\t%2d-%3s-%4d\n", utenteFile.utenteID,
		utenteFile.nome,utenteFile.cognome,
		utenteFile.dataNascita.giorno, utenteFile.dataNascita.mese, utenteFile.dataNascita.anno,
		utenteFile.dataIscrizione.giorno, utenteFile.dataIscrizione.mese, utenteFile.dataIscrizione.anno);
		/*Controllo che non si tratta di un utente cancellato (ID uguale a 0)
		 */

		if (utenteFile.utenteID != 0)
		{
			printf("\n Aggiorna il nome: \n");
			do
			{
				controlloInput = inserisciStringaSpaziNome(utenteApp.nome, DIM_NOME);
			}while (controlloInput==0);

			/* Inserisco cognome */
			printf("\n Aggiorna il cognome: \n");
			do
			{
				controlloInput = inserisciStringaSpaziNome(utenteApp.cognome, DIM_COGNOME);
			}while (controlloInput==0);


			/*MODIFICA DATA DI NASCITA*/
			puts("Modifica il giorno: ");
			do
			{
				controlloInput = inserisciNumero(strInputGiorno, 0, 32);
			}while(controlloInput==0);
			utenteApp.dataNascita.giorno = atoi(strInputGiorno);

			puts("Modifica il mese: ");
			do
			{
				controlloInput=inserisciNumero(strInputMese, 0, 13);
			}while(controlloInput==0);
			strcpy(utenteApp.dataNascita.mese, mesiStringhe[atoi(strInputMese)-1]);

			puts("Modifica l' anno: ");
			do
			{
				controlloInput=inserisciNumero(strInputAnno, 1900, 2005);
			}while(controlloInput==0);
			utenteApp.dataNascita.anno = atoi(strInputAnno);


			printf("\nMantenere le modifiche?\n\t[1] SI\n\t[2] NO\n");
			do
			{
				controlloInput = inserisciNumero(strInput,0,3);
			}while(controlloInput==0);
			if (atoi(strInput)==1)
			{
				/*scrivo sul file i dati aggiornati*/
				/*Posizionamento sul record da modificare*/
				fseek(listaUtenti, (chiaveID-1)* sizeof(utente),SEEK_SET );
				strcpy(utenteFile.nome, utenteApp.nome);
				strcpy(utenteFile.cognome, utenteApp.cognome);
				utenteFile.dataNascita.giorno = utenteApp.dataNascita.giorno;
				strcpy(utenteFile.dataNascita.mese, utenteApp.dataNascita.mese);
				utenteFile.dataNascita.anno = utenteApp.dataNascita.anno;
				fwrite(&utenteFile, sizeof(utenteFile), 1, listaUtenti);
			}
			else
				return 0;
		}
		else
		{
			/*Utente è stato cancellato!*/
			printf("/nQuesto utente è stato cancellato\n");
			return 0;
		}
	}
	fclose(listaUtenti);
	return 1;
}

/**
 * Visualizzazione di un utente
 *
 * @pre esistenza del file listaUtenti
 * @pre esistenza dell'utente da visualizzare
 */

void visualizzaUtente ()
{
	system("cls");
	FILE* listaUtenti;
	utente utenteFile; /*Dati utente letti da file*/
	short controlloInput = 0; /*variabile di controllo per input, 0 indica falso, 1 vero*/
	char strInput[20]; //per lettura dati da tastiera
	int chiaveID; //id dell'utente da modificare
	int numUtenti= 0;
	/*Apertura file*/
	if ((listaUtenti = fopen("listaUtenti.txt", "rb+")) == NULL)
		{
			printf("\nERRORE NELL'APERTURA DEL FILE!");
		}
	else
	{
		/*Controllo il numero di utenti nel file*/
		while (!feof(listaUtenti))
		{
			fread(&utenteFile, sizeof(utente), 1, listaUtenti);
			if(!feof(listaUtenti))
				numUtenti++; 		/*incremento del contatore di utenze*/
		}
		/* Chiedo l'id dell'utente da cercare */
		printf("\n\nInserisci l' ID dell'utente che vuoi visualizzare: ");
		do
		{
			controlloInput=inserisciNumero(strInput, 0, (numUtenti+1));
		}while(controlloInput==0);
		chiaveID = atoi(strInput);
		controlloInput = 0;
		/*Posizionamento sul record da visualizzare*/
		fseek(listaUtenti, (chiaveID-1)* sizeof(utente),SEEK_SET );

		/*Leggo il record*/
		fread(&utenteFile, sizeof(utente), 1, listaUtenti);
		if (utenteFile.utenteID == 0)
		{
			/* UTENTE CANCELLATO*/
			printf("\nQuesto utente è stato cancellato!\n");
		}
		else
		{
			//Lo stampo a video
			printf("%-6s%-13s%-11s%18s%18s\n\n", "ID", "NOME", "COGNOME",
							"DATA NASCITA","DATA ISCRIZIONE");
			printf("%-6d%-13s%-11s\t%2d-%3s-%4d\t\t%2d-%3s-%4d\n", utenteFile.utenteID,
			utenteFile.nome,utenteFile.cognome,
			utenteFile.dataNascita.giorno, utenteFile.dataNascita.mese, utenteFile.dataNascita.anno,
			utenteFile.dataIscrizione.giorno, utenteFile.dataIscrizione.mese, utenteFile.dataIscrizione.anno);
		}
	}
	fclose(listaUtenti);
}

/**
 * Cancellazione di un utente
 *
 * @pre esistenza del file listaUtenti
 * @pre esistenza dell'utente da cancellare
 * @post utente settato con id a 0
 */

short cancellaUtente()
{
	system("cls");
	visualizzaElencoUtenti();
	FILE* listaUtenti;
	utente utenteApp; /*Dati utente cancellato*/
	utente utenteFile; /*Dati utente letti da file*/
	short controlloInput = 0; /*variabile di controllo per input, 0 indica falso, 1 vero*/
	char strInput[20]; //per lettura dati da tastiera
	int chiaveID; //id dell'utente da modificare
	int numUtenti= 0;
	/*Apertura file*/
	if ((listaUtenti = fopen("listaUtenti.txt", "rb+")) == NULL)
	{
		printf("\nERRORE NELL'APERTURA DEL FILE!");
		return 0;
	}
	else
	{
	/*Controllo il numero di utenti nel file*/
		while (!feof(listaUtenti))
		{
			fread(&utenteFile, sizeof(utente), 1, listaUtenti);
			if(!feof(listaUtenti))
				numUtenti++; 		/*incremento del contatore di utenze*/
		}
		/* Chiedo l'id dell'utente da cercare */
		printf("\n\nInserisci l' ID dell'utente che vuoi modificare: ");
		do
		{
			controlloInput=inserisciNumero(strInput, 0, (numUtenti+1));
		}while(controlloInput==0);
		chiaveID = atoi(strInput);
		controlloInput = 0;
		/*Posizionamento sul record da modificare*/
		fseek(listaUtenti, (chiaveID-1)* sizeof(utente),SEEK_SET );

		/*Leggo il record*/
		fread(&utenteFile, sizeof(utente), 1, listaUtenti);
		if (utenteFile.utenteID == 0)
		{
			/* SI TRATTA DI UN UTENTE GIA' CANCELLATO*/
			printf("\nQuesto utente risulta già cancellato!\n");
			return 0;
		}
		else
		{
			utenteApp.utenteID = 0;
			strcpy(utenteApp.nome, utenteFile.nome);
			strcpy(utenteApp.cognome, utenteFile.cognome);
			utenteApp.dataNascita = utenteFile.dataNascita;
			utenteApp.dataIscrizione = utenteFile.dataIscrizione;
			/*Posizionamento sul record da modificare*/
			fseek(listaUtenti, (chiaveID-1)* sizeof(utente),SEEK_SET );

			/*Scrivo il record*/
			fwrite(&utenteApp,sizeof(utenteApp), 1, listaUtenti);
			printf("\n%s %s cancellato.\n", utenteApp.nome, utenteApp.cognome);

		}
		fclose(listaUtenti);
		return 1;
	}
}
