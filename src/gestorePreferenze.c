/**
 * @file gestorePreferenze.c
 *
 * Libreria che include le funzioni/procedure per gestire le preferenze
 *
 * @version 1.0
 * @date 30/09/2018
 * @authors Montemurro Andrea, Mininni Claudio
 * @copyright AJCM
 *
 */
#include "gestorePreferenze.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @var mesiStringhe[12] array di puntatori a char contenente i nomi dei mesi in stringhe di 3 caratteri
 */
char* mesiStringhes [12]= {"GEN", "FEB", "MAR", "APR", "MAG", "GIU",
		"LUG", "AGO", "SET", "OTT", "NOV", "DIC"};

/* MENU GESTIONE PREFERENZE
 * permette di gestire le operazioni relative alle preferenze degli utenti di amazon
 */
short gestorePreferenze ()
{
	system("cls");
	short controlloInput = 0; //variabile per controllare l'input
	char stringa_input [50];
	short uscita = 0;
	//MENU PRINCIPALE DEL GESTORE PREFERENZE
	do{
		puts("AMAZON MENU PRODOTTI\n\n");
		puts("[1]\tINSERISCI preferenza\n");
		puts("[2]\tVISUALIZZA elenco preferenze\n");
		puts("[3]\tMODIFICA preferenza\n");
		puts("[4]\tVISUALIZZA DATI preferenza\n");
		puts("[5]\tCANCELLA preferenza\n");
		puts("[6]\tFUNZIONALITA' di visualizzazione profilo e relative preferenze\n");
		puts("[7]\tVISUALIZZA Prodottti top 10 venduti\n");
		puts("[8]\tUscita\n");
		do
		{
			controlloInput=inserisciNumero(stringa_input,0,9);
		}while(controlloInput==0);

		switch (atoi(stringa_input)) {
			case 1:
				inserisciPreferenza();
			break;
			case 2:
				visualizzaElencoPreferenze();
			break;
			case 3:
				modificaPreferenza();
			break;
			case 4:
				visualizzaPreferenza();
			break;
			case 5:
				cancellaPreferenza();
				break;
			case 6:
				visualizzazioneProfiloPreferenze();
				break;
			case 7:
				topDieciVenduti();
				break;
			case 8:
				uscita =1;
				break;
			default:
				puts("Valore inserito non valido! Ripetere l'inserimento:\n");
				scanf("%s", stringa_input);
		}
	}while (uscita == 0);
	system("cls");
	return uscita;
}


/**
 * Inserimento di una preferenza
 *
 * @pre esistenza del file ListaPreferenze
 * @post nuova preferenza nel file
 */
short inserisciPreferenza()
{
	system("cls");
	/*Puntatori ai file*/
	FILE* listaProdotti;
	FILE* listaUtenti;
	FILE* listaPreferenze;

	/*Tipi di dato per le letture/scritture */
	prodotto prodottoFile;
	utente utenteFile;
	preferenza preferenzaFile;
	preferenza nuovaPreferenza;

	nuovaPreferenza.preferenzaID = 0;
	int numPreferenze = 0;/* contatore di preferenze */
	int numUtenti = 0;
	int numProdotti = 0;

	char strInput[20];
	char strInputUtenteID[20];
	char strInputProdottoID[20];
	short controlloInput = 0; /*variabile di controllo per input, 0 indica falso, 1 vero*/
	/* Apro i file in modalità di lettura binaria */
	if ( ((listaUtenti = fopen("listaUtenti.txt","rb+"))==NULL) ||
			((listaProdotti = fopen("listaProdotti.txt","rb+"))== NULL) ||
			((listaPreferenze = fopen("listaPreferenze.txt","rb+")) == NULL))
	{
		/*Errore di apertura*/
		printf("\nErrore di apertura file!\n");
		return 0;
	}
	else
	{
		/*Apertura corretta*/
		/*Scorro il file delle preferenze e le conto*/
		while(!feof(listaPreferenze))
		{
			fread(&preferenzaFile, sizeof(preferenza), 1, listaPreferenze);
			if(!feof(listaPreferenze))
				numPreferenze++;
		}
		/*Scorro il file degli utenti e li conto*/
		while(!feof(listaUtenti))
		{
			fread(&utenteFile, sizeof(utente), 1, listaUtenti);
			if(!feof(listaUtenti))
				numUtenti++;
		}
		/*Scorro il file dei prodotti e li conto*/
		while(!feof(listaProdotti))
		{
			fread(&prodottoFile, sizeof(prodotto), 1, listaProdotti);
			if(!feof(listaProdotti))
				numProdotti++;
		}
		/*Controllo che ci sia spazio per l'inserimento di nuove preferenze nel file*/
		if (numPreferenze >= MAX_PREFERENZE)
		{
			printf("\nNUmero massimo di preferenze raggiunto!\n");
			return 0;
		}
		else
			/*Nessun problema, posso inserire nuove preferenze*/
		{
			printf("\t\tINSERIMENTO DELL'AZIONE PRODOTTO\nScelta utente: stampare elenco utenti?\n");
			printf("[1]\tSI\n");
			printf("[2]\tNO\n");
			do
			{
				controlloInput=inserisciNumero(strInput,0,3);
			}while(controlloInput==0);

			/*Se l'utente ha scelto SI stampo l'elenco degli utent*/
			if(atoi(strInput)==1)
				visualizzaElencoUtenti();
			/*Inserisco l'utente tramite l'input di un ID*/
			printf("\n\nInserisci l'ID dell'utente con cui vuoi esprimere la preferenza: ");
			do
			{
				controlloInput=inserisciNumero(strInputUtenteID, 0, numUtenti+1);
			}while(controlloInput==0);

			printf("\t\tINSERIMENTO DELL' AZIONE PRODOTTO\nScelta prodotto: stampare elenco prodotti?\n");
			printf("[1]\tSI\n");
			printf("[2]\tNO\n");
			do
			{
				controlloInput=inserisciNumero(strInput,0,3);
			}while(controlloInput==0);

			/*Se l'utente ha scelto SI stampo l'elenco dei prodotti*/
			if(atoi(strInput)==1)
				visualizzaElencoProdotti();
			/*Inserisco l'utente tramite l'input di un ID*/
			printf("\n\nInserisci l'ID del prodotto con cui vuoi operare: ");
			do
			{
				controlloInput=inserisciNumero(strInputProdottoID,0,numProdotti+1);
			}while(controlloInput==0);
			/*Chiedo cosa intende fare con questo prodotto, se lasciare un like, visualizzarlo, oppure Acquistarlo*/
			printf("\nInserisci l'azione dell'utente n° %s relativa al prodotto n° %s: \n", strInputUtenteID, strInputProdottoID);
			printf("[1]\t Prodotto Visualizzato\n");
			printf("[2]\t Prodotto Piaciuto\n");
			printf("[3]\t Prodotto Acquistato\n");
			do
			{
					controlloInput=inserisciNumero(strInput,0,4);
			}while(controlloInput==0);
			/*Memorizzo la data della preferenza prendendola dal sistema*/
			/*leggo dal sistema la data attuale e la memorizzo come data di iscrizione*/
			time_t orologio;
			struct tm *dataInfo = NULL;
			time (&orologio);
			dataInfo = localtime(&orologio);
			nuovaPreferenza.dataPreferenza.giorno = dataInfo->tm_mday;
			nuovaPreferenza.dataPreferenza.anno = (dataInfo->tm_year)+1900;
			strcpy(nuovaPreferenza.dataPreferenza.mese, mesiStringhes[(dataInfo->tm_mon)]);
			nuovaPreferenza.preferenzaID = (numPreferenze + 1);
			nuovaPreferenza.prodottoID = atoi(strInputProdottoID);
			nuovaPreferenza.utenteID = atoi(strInputUtenteID);
			nuovaPreferenza.tipoPreferenza = atoi(strInput);
			fwrite(&nuovaPreferenza, sizeof(preferenza), 1, listaPreferenze);
			/*Scrivo su file la preferenza*/
			/*Mi posiziono sui file prodotti e utente per leggere e stampare i dati*/
			fseek(listaProdotti, (atoi(strInputProdottoID)-1)*sizeof(prodotto) , SEEK_SET);
			fseek(listaUtenti, (atoi(strInputUtenteID)-1) * sizeof(utente), SEEK_SET);
			fread(&prodottoFile, sizeof(prodotto), 1, listaProdotti);
			fread(&utenteFile, sizeof(utente), 1, listaUtenti);
			switch (nuovaPreferenza.tipoPreferenza)
			{
			case 1:
				printf("\nL'utente %s %s con ID %d ha VISUALIZZATO il prodotto %s di %s con ID %d e prezzo %.2f",
						utenteFile.nome, utenteFile.cognome, utenteFile.utenteID,
						prodottoFile.nome, prodottoFile.azienda, prodottoFile.prodottoID, prodottoFile.prezzo);
				break;
			case 2:
				printf("\nAll'utente %s %s con ID %d è PIACIUTO il prodotto %s di %s con ID %d e prezzo %.2f",
										utenteFile.nome, utenteFile.cognome, utenteFile.utenteID,
										prodottoFile.nome, prodottoFile.azienda, prodottoFile.prodottoID, prodottoFile.prezzo);
				break;
			case 3:
				printf("\nL'utente %s %s con ID %d ha ACQUISTATO il prodotto %s di %s con ID %d e prezzo %.2f",
										utenteFile.nome, utenteFile.cognome, utenteFile.utenteID,
										prodottoFile.nome, prodottoFile.azienda, prodottoFile.prodottoID, prodottoFile.prezzo);
			}

		}
	}
	/*Operazioni finite*/
	fclose(listaUtenti);
	fclose(listaProdotti);
	fclose(listaPreferenze);
	return nuovaPreferenza.tipoPreferenza;
}


/**
 * Visualizza elenco preferenze
 *
 * @pre esistenza del file listaPreferenze
 */
void visualizzaElencoPreferenze()
{
	/*Puntatori a file*/
	FILE* listaUtenti;
	FILE* listaProdotti;
	FILE* listaPreferenze;

	/*Strutture per letture da file*/
	utente utenteFile;
	prodotto prodottoFile;
	preferenza preferenzaFile;

	char preferenzaStr[20];
	/*Apertura file*/
	if ( ((listaUtenti = fopen("listaUtenti.txt","rb+"))==NULL) ||
			((listaProdotti = fopen("listaProdotti.txt","rb+"))== NULL) ||
			((listaPreferenze = fopen("listaPreferenze.txt","rb+")) == NULL) )
	{
		/*Errore di apertura file*/
		printf("\nErrore di apertura file\n");
	}
	else
	{
		/*File aperti con successo*/
		/*Stampo intestazione tabella*/
		printf("%7s%7s%7s%40s%20s%8s%10s\n\n", "ID PREF", "ID PROD", "ID UTE",
						"NOME UTENTE","NOME PR.", "PREZZO", "PREFERENZA");
		/*Lettura da file*/
		while (!feof(listaPreferenze))
		{
			fread(&preferenzaFile, sizeof(preferenza), 1, listaPreferenze);
			if(!feof(listaPreferenze))
			{
				/*Leggo anche dati utente e prodotto*/
				fseek(listaUtenti, (preferenzaFile.utenteID-1)*sizeof(utente), SEEK_SET);
				fread(&utenteFile, sizeof(utente), 1, listaUtenti);
				fseek(listaProdotti, (preferenzaFile.prodottoID-1)*sizeof(prodotto), SEEK_SET);
				fread(&prodottoFile, sizeof(prodotto), 1, listaProdotti);
				strcpy(preferenzaStr, preferenzaStringa[preferenzaFile.tipoPreferenza-1]);
				if(preferenzaFile.preferenzaID != 0 )
				{
					/*Stampo se la preferenza non è stata cancellata!*/
					printf("%6d %6d %6d%20s%20s%20s%8.2f %10s\n\n", preferenzaFile.preferenzaID, preferenzaFile.prodottoID, preferenzaFile.utenteID,
					utenteFile.nome,utenteFile.cognome,prodottoFile.nome, prodottoFile.prezzo, preferenzaStr);
				}
			}

		}
	}
	/*Operazioni finite*/
	fclose(listaUtenti);
	fclose(listaProdotti);
	fclose(listaPreferenze);
}



/**
 * Modifica preferenza
 *
 * @pre esistenza del file listaPreferenza
 * @post modifica dei dati relativi a una preferenza
 */
short modificaPreferenza()
{
	system("cls");
	visualizzaElencoPreferenze();
	/*Puntatori a file*/
	FILE* listaUtenti;
	FILE* listaProdotti;
	FILE* listaPreferenze;

	/*Strutture per letture da file*/
	preferenza preferenzaFile;

	/*Contatore preferenze*/
	int numPreferenze = 0;

	/*Variabile per salvare offset relativo del record da modificare (sovrascrivere)*/
	int offsetRelativo;

	/*Stringa input*/
	char strInput[20];
	char preferenzaStr[20];
	short controlloInput = 0; /*variabile di controllo per input, 0 indica falso, 1 vero*/

	/*Apertura file*/
		if ( ((listaUtenti = fopen("listaUtenti.txt","rb+"))==NULL) ||
				((listaProdotti = fopen("listaProdotti.txt","rb+"))== NULL) ||
				((listaPreferenze = fopen("listaPreferenze.txt","rb+")) == NULL) )
		{
			/*Errore di apertura file*/
			printf("\nErrore di apertura file\n");
			return 0;
		}
		else
		{
			/*CONTO LE PREFERENZE*/
			while (!feof(listaPreferenze))
			{
				fread(&preferenzaFile, sizeof(preferenza), 1, listaPreferenze);
				if(!feof(listaPreferenze))
					numPreferenze++;
			}
			printf("\nInserisci l'ID della preferenza che vuoi modificare: \n");
			do
			{
				controlloInput=inserisciNumero(strInput,0, numPreferenze+1);
			}while(controlloInput==0);

			offsetRelativo = atoi(strInput);
			controlloInput = 0;
			/*Leggo la preferenza*/
			fseek(listaPreferenze, (offsetRelativo-1)*sizeof(preferenza), SEEK_SET);
			fread(&preferenzaFile, sizeof(preferenza), 1, listaPreferenze);
			strcpy(preferenzaStr, preferenzaStringa[preferenzaFile.tipoPreferenza-1]);
			if (preferenzaFile.preferenzaID != 0)
			{
				/*Se non si tratta di una preferenza cancellata*/
				printf("\nPreferenza: \n");
				printf("%6s%6s%12s", "ID PROD", "ID UTE", "PREFERENZA");
				printf("\n");
				printf("%6d%6d%12s",preferenzaFile.prodottoID,preferenzaFile.utenteID, preferenzaStr);
				/*Chiedo cosa intende fare con questo prodotto, se lasciare un like, visualizzarlo, oppure Acquistarlo*/
				printf("\nInserisci la nuova preferenza: \n");
				printf("[1]\t Prodotto Visualizzato\n");
				printf("[2]\t Prodotto Piaciuto\n");
				printf("[3]\t Prodotto Acquistato\n");
				do
				{
					controlloInput=inserisciNumero(strInput,0,4);
				}while(controlloInput==0);

				preferenzaFile.tipoPreferenza = atoi(strInput);
				fseek(listaPreferenze, (offsetRelativo-1)*sizeof(preferenza), SEEK_SET);
				fwrite(&preferenzaFile, sizeof(preferenza), 1, listaPreferenze);
			}
			else
			{
				printf("\nPreferenza cancellata!\n");
				return 0;
			}
		}
		/*Operazioni finite*/
		fclose(listaUtenti);
		fclose(listaProdotti);
		fclose(listaPreferenze);
		return preferenzaFile.tipoPreferenza;
}


/**
 * Visualizzazione di una preferenza
 *
 * @pre esistenza del file listaPreferenze
 * @pre esistenza della preferenza da visualizzare
 */
short visualizzaPreferenza()
{
	system("cls");
	/*Puntatori a file*/
	FILE* listaUtenti;
	FILE* listaProdotti;
	FILE* listaPreferenze;

	/*Strutture per letture da file*/
	utente utenteFile;
	prodotto prodottoFile;
	preferenza preferenzaFile;

	/*Contatore preferenze*/
	int numPreferenze = 0;

	/*Stringa input*/
	char strInput[20];
	char preferenzaStr[20];
	short controlloInput = 0; /*variabile di controllo per input, 0 indica falso, 1 vero*/

	/*Apertura file*/
	if ( ((listaUtenti = fopen("listaUtenti.txt","rb+"))==NULL) ||
			((listaProdotti = fopen("listaProdotti.txt","rb+"))== NULL) ||
			((listaPreferenze = fopen("listaPreferenze.txt","rb+")) == NULL) )
	{
		/*errore apertura file*/
		printf("\nErrore di apertura file\n");
		return 0;
	}
	else
	{
		/*File aperti con successo*/
		/*CONTO LE PREFERENZE*/
		while (!feof(listaPreferenze))
		{
			fread(&preferenzaFile, sizeof(preferenza), 1, listaPreferenze);
			if(!feof(listaPreferenze))
				numPreferenze++;
		}
		printf("\nInserisci l'ID della preferenza che vuoi visualizzare: \n");
		do
		{
			controlloInput=inserisciNumero(strInput,0,numPreferenze+1);
		}while(controlloInput==0);

		/*Leggo la preferenza*/
		fseek(listaPreferenze, (atoi(strInput)-1)*sizeof(preferenza), SEEK_SET);
		fread(&preferenzaFile, sizeof(preferenza), 1, listaPreferenze);
		fseek(listaUtenti, (preferenzaFile.utenteID-1)*sizeof(utente), SEEK_SET);
		fread(&utenteFile, sizeof(utente), 1, listaUtenti);
		fseek(listaProdotti, (preferenzaFile.prodottoID-1)*sizeof(prodotto), SEEK_SET);
		fread(&prodottoFile, sizeof(prodotto), 1, listaProdotti);
		strcpy(preferenzaStr, preferenzaStringa[preferenzaFile.tipoPreferenza-1]);
		if (preferenzaFile.preferenzaID != 0)
		{

			/*Stampo dati della preferenza*/
			printf("\n\t\tDATI PREFERENZA\n");
			printf("ID PREFERENZA:\t%d\n", preferenzaFile.preferenzaID);
			printf("TIPO PREFERENZA:\t%s\n", preferenzaStr);
			printf("DATA PREFERENZA:\t%d-%s-%d\n", preferenzaFile.dataPreferenza.anno, preferenzaFile.dataPreferenza.mese, preferenzaFile.dataPreferenza.anno);
			printf("\nDATI UTENTE\n");
			printf("ID UTENTE:\t%d\n", utenteFile.utenteID);
			printf("NOME UTENTE:\t%s %s\n", utenteFile.nome, utenteFile.cognome);
			printf("DATA NASCITA UTENTE:\t%d-%s-%d\n", utenteFile.dataNascita.giorno, utenteFile.dataNascita.mese, utenteFile.dataNascita.anno);
			printf("DATA ISCRIZIONE UTENTE:\t%d-%s-%d\n", utenteFile.dataIscrizione.giorno, utenteFile.dataIscrizione.mese, utenteFile.dataIscrizione.anno);
			printf("\nDATI PRODOTTO\n");
			printf("ID PRODOTTO:\t%d\n", prodottoFile.prodottoID);
			printf("NOME PRODOTTO:\t%s \n", prodottoFile.nome);
			printf("AZIENDA PRODOTTO:\t%s \n", prodottoFile.azienda);
			printf("CATEGORIA PRODOTTO:\t%s\n", prodottoFile.categoria);
			printf("PREZZO PRODOTTO:\t%.2f\n", prodottoFile.prezzo);
		}
		else
		{
			/*Preferenza cancellata*/
			printf("\nPreferenza Cancellata!\n");
		}

	}

	/*Chiusura file e ritorno valore*/
	fclose(listaPreferenze);
	fclose(listaProdotti);
	fclose(listaUtenti);
	return preferenzaFile.preferenzaID;
}


/**
 * Cancellazione di una preferenza
 *
 * @pre esistenza del file listaPreferenza
 * @pre esistenza della preferenza da cancellare
 * @post preferenza settato con id a 0
 */short cancellaPreferenza()
{
	system("cls");
	visualizzaElencoPreferenze();
	/*Puntatore a file*/
	FILE* listaPreferenze;

	/*Struttura dati per lettura da file*/
	preferenza preferenzaFile;

	int numPreferenze = 0;
	char strInput[20];
	short controlloInput = 0;
	/*Apertura file*/
	if ((listaPreferenze = fopen("listaPreferenze.txt", "rb+")) == NULL)
	{
		/*Errore apertura file*/
		printf("\nErrore di apertura file!\n");
		return 0;
	}
	else
	{
		/*FIle aperto con successo*/
		/*Conto le preferenze*/
		while(!feof(listaPreferenze))
		{
			fread(&preferenzaFile,sizeof(preferenza),1,listaPreferenze);
			if(!feof(listaPreferenze))
				numPreferenze++;
		}
		printf("\nInserisci l'ID della preferenza che vuoi eliminare:\n");
		do
		{
			controlloInput=inserisciNumero(strInput,0,numPreferenze+1);
		}while(controlloInput==0);
		fread(&preferenzaFile, sizeof(preferenza), 1, listaPreferenze);
		/*Setto a 0 l'id della preferenza*/
		preferenzaFile.preferenzaID = 0;
		/*Mi riposiziono nella giusta posizione e riscrivo la preferenza con l'id settato a 0*/
		fseek(listaPreferenze, (atoi(strInput)-1)*sizeof(preferenza),SEEK_SET);
		fwrite(&preferenzaFile, sizeof(preferenza),1, listaPreferenze);
	}
	/*Cancellazione avvenuta con successo, ritorno codice 1 e chiudo stream*/
	fclose(listaPreferenze);
	return 1;
}


 /**
  * Visualizzazione di un profilo con preferenze espresse
  *
  * @pre esistenza del file listaPreferenze
  */
int visualizzazioneProfiloPreferenze()
{
	system("cls");
	visualizzaElencoUtenti();
	/*Puntatori a file*/
	FILE* listaUtenti;
	FILE* listaProdotti;
	FILE* listaPreferenze;
	/*Strutture per letture da file*/
	utente utenteFile;
	prodotto prodottoFile;
	preferenza preferenzaFile;

	/*Contatore preferenze*/
	int numPreferenze = 0;
	/*Contarore utenti*/
	int numUtenti = 0;
	/*Preferenza in stringa*/
	char preferenzaStr[20];
	/*Variabile accumulatore che tiene in memoria la spesa totale di un utente*/
	float totSpese = 0.00;
	/*Stringa input*/
	char strInput[20];
	short controlloInput = 0; /*variabile di controllo per input, 0 indica falso, 1 vero*/


	/*Apertura file*/
	if ( ((listaUtenti = fopen("listaUtenti.txt","rb+"))==NULL) ||
			((listaProdotti = fopen("listaProdotti.txt","rb+"))== NULL) ||
			((listaPreferenze = fopen("listaPreferenze.txt","rb+")) == NULL) )
	{
		/*errore apertura file*/
		printf("\nErrore di apertura file\n");
		return 0;
	}
	else
	{
		/*Conto gli utenti presenti nel file*/
		while(!feof(listaUtenti))
		{
			fread(&utenteFile, sizeof(utente),1,listaUtenti);
			if(!feof(listaUtenti))
				numUtenti++;
		}
		/*Ora chiedo all'utente quale profile utente vuole visualizzare e leggo l' ID*/
		printf("\nInserisci l'ID dell'utente di cui visualizzare le azioni: \n");
		do
		{
			controlloInput=inserisciNumero(strInput,0, numUtenti+1);
		}while(controlloInput==0);

		/*leggo i dati dell'utente selezionato*/
		fseek(listaUtenti, (atoi(strInput)-1)*sizeof(utente), SEEK_SET);
		fread(&utenteFile, sizeof(utente),1,listaUtenti);
		/*Inizio a leggere le preferenze e stampo solo quelle che soddisfano i requisiti*/
		while (!feof(listaPreferenze))
		{
			fread(&preferenzaFile, sizeof(preferenza),1, listaPreferenze);
			if (!feof(listaPreferenze))
			{
				if((preferenzaFile.utenteID == atoi(strInput)) && preferenzaFile.preferenzaID!=0)
				{
					numPreferenze++;
					if(numPreferenze==1)
					{
						/*Stampo intestazione tabella solo prima della stampa della prima preferenza*/
						printf("%6s%6s%40s%20s%20s%8s%10s\n\n", "ID PREF", "ID PROD",
												"NOME UT.","NOME PR.","AZIENDA", "PREZZO", "AZIONE");
					}
					/*Leggo dati relativi al prodotto*/
					fseek(listaProdotti, (preferenzaFile.prodottoID-1)*sizeof(prodotto), SEEK_SET);
					fread(&prodottoFile, sizeof(prodotto),1,listaProdotti);
					strcpy(preferenzaStr, preferenzaStringa[preferenzaFile.tipoPreferenza-1]);
					/*Se la preferenza è un acquisto incremento l'accumulatore della spesa totale dell'utente*/
					if (preferenzaFile.tipoPreferenza == 3)
					{
						totSpese = totSpese + prodottoFile.prezzo;
					}
					printf("%6d%6d%20s%20s%20s%20s%8.2f%10s\n\n", preferenzaFile.preferenzaID, prodottoFile.prodottoID,
							utenteFile.nome,utenteFile.cognome,prodottoFile.nome, prodottoFile.azienda, prodottoFile.prezzo, preferenzaStr);
				}
			}
		}
		printf("\nL'utente %s %s ha speso in totale %.2f euro in acquisti su Amazon.\n",
							utenteFile.nome, utenteFile.cognome, totSpese);
	}
	/*Fine operazioni*/
	fclose(listaUtenti);
	fclose(listaProdotti);
	fclose(listaPreferenze);
	return numPreferenze;
}

/**
  * Visualizzazione dei top 10 prodotti venduti
  *
  * @pre esistenza del file listaPreferenze
  */
void topDieciVenduti()
{
	system("cls");
	FILE* listaPreferenze;
	FILE* listaProdotti;

	/*Tipi di dato per letture da file*/
	preferenza preferenzaFile;
	prodotto prodottoFile;

	int i, j;

	/*Definisco struct con prodotto e campo che indica le vendite, che verrà inizializzato leggendo
	 * da file i prodotti e le vendite di essi dal file contenente le preferenze, per poi essere ordinato
	 * sul campo delle vendite per visualizzare in ordine i prodotti più venduti.
	 */
	typedef struct
	{
		prodotto prodottoVenduto;
		int vendita;
	}prodottoVendite;
	prodottoVendite tmp;
	prodottoVendite prodotti [MAX_PRODOTTI];
	int numProdotti = 0;
	int numProdottiValidi = 0;

	char spedizione[DIM_NOME];
	/*Apro i file*/
	if  (((listaProdotti = fopen("listaProdotti.txt","rb+"))== NULL) ||
		((listaPreferenze = fopen("listaPreferenze.txt","rb+")) == NULL) )
	{
		printf("\Errore apertura file!\n");
	}
	else
	{
		/*Inizializzo il vettore*/
		/*Leggo i prodotti validi da file e li metto nella struct*/
		while(!feof(listaProdotti))
		{
			fread(&prodottoFile, sizeof(prodotto),1, listaProdotti);
			if (!feof(listaProdotti))
			{
				prodotti[numProdotti].prodottoVenduto = prodottoFile;
				prodotti[numProdotti].vendita = 0;
				numProdotti++;
				/*Verifico se si tratta di un prodotto valido*/
				if(prodottoFile.prodottoID!=0)
				{
					numProdottiValidi++;
				}
			}
		}
		/*Leggo le preferenze e se sono valide, se sono relative a delle vendite,
		 * incremento il contatore di vendite del prodotto a cui si riferisce
		 */
		while(!feof(listaPreferenze))
		{
			fread(&preferenzaFile, sizeof(preferenza), 1, listaPreferenze);
			if(!feof(listaPreferenze))
			{
				if(preferenzaFile.preferenzaID!=0)
				{
					/*Se si tratta di una preferenza*/
					if(preferenzaFile.tipoPreferenza==3)
					{
						prodotti[preferenzaFile.prodottoID-1].vendita++;
					}
				}
			}
		}
		/*Ordino in base alle vendite*/
		for(i = numProdotti-1; i > 0; i--)
		{
			for(j = 0; j < i; j++)
			{
				if(prodotti[j].vendita < prodotti[j+1].vendita)
				{
					tmp = prodotti[j];
			 		prodotti[j] = prodotti[j+1];
			 		prodotti[j+1] = tmp;
			 	}
			 }
		}
		/*ora stampo i primi dieci elementi del vettore che non hanno id pari a 0, cioè prodotti che non sono
		 * cancellati
		 */
		if(numProdottiValidi>=10)
		{
			i=0;
			/*stampo intestazione tabella*/
			printf("%6s%20s%20s%20s%8s%9s\n\n", "ID PROD", "NOME",
							"AZIENDA","CATEGORIA", "PREZZO", "QUANTITA");
			do
			{
				if(prodotti[i].prodottoVenduto.prodottoID != 0)//se è un prodotto ancora valido e non cancellato
				{
					if(prodotti[i].prodottoVenduto.spedizioneRapida == 1)
					 	strcpy(spedizione, "SI");
					 else
						 strcpy(spedizione, "NO");
					 printf("%6d%20s%20s%20s%   .2f%9d\n", prodotti[i].prodottoVenduto.prodottoID,
					 prodotti[i].prodottoVenduto.nome,prodotti[i].prodottoVenduto.azienda,prodotti[i].prodottoVenduto.categoria,prodotti[i].prodottoVenduto.prezzo, prodotti[i].vendita);
					 i++;
				}
			}while(i<10);
		}
		else
		{
			printf("\nBisogna avere almeno 10 prodotti!\n");
		}

	}
	fclose(listaPreferenze);
	fclose(listaProdotti);

}
