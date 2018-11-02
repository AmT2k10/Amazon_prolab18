/**
 * @file gestorePreferenze.h
 *
 * Libreria che include le funzioni/procedure per gestire le preferenze
 *
 * Contiene un menu, richiamato nel main che a sua volta può richiamare le varie operazioni da fare sul tipo di dato preferenza
 *
 * @version 1.0
 * @date 30/09/2018
 * @authors Montemurro Andrea, Mininni Claudio
 * @copyright AJCM
 *
 */

#ifndef GESTOREPREFERENZE_H_
#define GESTOREPREFERENZE_H_

/*Includo le mie librerie*/
#include "gestoreDate.h"
#include "gestoreStringhe.h"
#include "gestoreProdotti.h"
#include "gestoreUtenti.h"

/**
 * Definisce il numero massimo di preferenze salvabili su file
 */
#define MAX_PREFERENZE 10000


/**
 * Tipo di dato che descrive un utente all'interno del file "listaUtenti"
 */
typedef struct
{
	int preferenzaID; /** <Id della preferenza*/
	int utenteID; /** <Id dell'utente*/
	int prodottoID;/** <Id del prodotto*/
	/**
		 * @struct data
		 * @brief struttura per descrivere date
		 *
		 * @??? dataPreferenza contiene la data della preferenza
		 *
	*/
	data dataPreferenza;
	short tipoPreferenza;  /** <Tipo della preferenza 1 = visto , 2 = piaciuto, 3 = acquistato */
}preferenza;


/**
 * vettore di puntatori a stringhe che descrivono le preferenze
 * L'indice dell'array indica la categoria in numero
 */
char* preferenzaStringa[3] = {"VISUALIZZATO", "PIACIUTO", "ACQUISTATO"};

/**
 * Menu per la gestione delle preferenze
 *
 * Permette di richiamare attraverso un menù le operazioni relative alle preferenze
 *
 * @return 1 in caso di funzione terminata con successo
 * @return 0 in caso di funzione terminata con errore
 */
short gestorePreferenze();


/**
 * Inserimento preferenza
 *
 * Permette di inserire una preferenza. Fa inserire da tastiera le informazioni relative alla preferenza  per
 * memorizzare in un file denominato "listaPreferenza.txt".
 *
 * @return 1 in caso di funzione terminata con successo
 * @return 0 in caso di funzione terminata con errore
 */
short inserisciPreferenza();

/**
 *  Modifica prefeenza
 *
 * Inserito un id preferenza, modifica i dati relativi a quella preferenza.
 *
 * @return 1 in caso di cancellazione terminata con successo
 * @return 0 in caso di cancellazione terminata con errore
 */
short modificaPreferenza();



/**
 * Cancella preferenza
 *
 * Inserito un id preferenza, la funzione cancella questa.
 * NB: la cancellazione non è fisica, ma avviene settando l'id della preferenza a 0
 *
 * @return 1 in caso di cancellazione terminata con successo
 * @return 0 in caso di cancellazione terminata con errore
 */short cancellaPreferenza();


/**
 * Visualizza preferenza
 *
 * Inserito un id, visualizza quella preferenza
 *
 * @return 0 in caso di errore
 * @return id Preferenza in caso di funzione terminata con successo
 */
short visualizzaPreferenza();

/**
 * Visualizza elenco delle preferenze
 */
void visualizzaElencoPreferenze();



/**
 * Visualizza profilo preferenze
 *
 * Dato un id stampa tutte le preferenze dell'utente
 *
 * @return Numero delle preferenze espresse dall'utente
 * @return 0 in caso di errore
 */
int visualizzazioneProfiloPreferenze();

/**
 * Top 10 venduti
 *
 * Crea un array di prodotti con un campo di interi per il numero delle vendite.
 * Legge da file le preferenze per contare le vendite, poi ordina su questo campo e stampa i primi 10
 */
void topDieciVenduti();

#endif  /*GESTOREPREFERENZE_H_*/
