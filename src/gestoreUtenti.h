/**
 * @file gestoreUtenti.h
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

#ifndef GESTOREUTENTI_H_
#define GESTOREUTENTI_H_


#include "gestoreDate.h"
#include "gestoreStringhe.h"


/**
 * Dimensione massima per la stringa nome
 */
#define DIM_NOME 20


/**
 * Dimensione massima per la stringa cognome
 */
#define DIM_COGNOME 20

/**
 * Numero massimo di utenti memorizzabili nel file
 */
#define MAX_UTENTI 10000


/**
 * Tipo di dato che descrive un utente all'interno del file "listaUtenti"
 */
typedef struct {
	int utenteID; /**< ID dell'utente, valore numerico*/
	char nome [DIM_NOME]; /**< Nome dell'utente */
	char cognome[DIM_COGNOME]; /**< Cognome dell'utente */
	/**
	 * @struct data
	 * @brief struttura per descrivere date
	 *
	 * @??? dataNascita contiene la data di nascita dell'utente
	 * @??? dataIscrizione contiene la data di iscrizione dell'utente
	 */
	data dataNascita;
	data dataIscrizione;
} utente ;


/**
 * Menu per la gestione degli utenti
 *
 * Permette di richiamare attraverso un menù le operazioni relative agli utenti
 *
 * @return 1 in caso di funzione terminata con successo
 * @return 0 in caso di funzione terminata con errore
 */
short gestoreUtenti ();


/**
 * Iscrizione di un utente
 *
 * Permette di iscrivere un utente.Fa inserire da tastiera le informazioni relative all'utente e legge da sistema
 * la data per memorizzare in un file denominato "listaUtenti.txt".
 *
 * @return 1 in caso di funzione terminata con successo
 * @return 0 in caso di funzione terminata con errore
 */
short iscriviUtente();


/**
 * Visualizza un utente
 *
 * Inserito un id utente, la procedura legge da file e stampa a video i suoi dati
 */
void visualizzaUtente();


/**
 * Visualizza elenco utenti
 *
 * Stampa a video tutto l'elenco degli utenti leggendo da file
 */
void visualizzaElencoUtenti();


/**
 * Modifica utente
 *
 * Funzione che permette di modificare i dati relativi a un utente, leggendo da tastiera il suo id
 *
 * @return 1 in caso di modifica effettuata con successo
 * @return 0 in caso di modifica terminata con errore, ad esempio quando si tenta di modificare un utente eliminato
 */
short modificaUtente();


/**
 * Cancella utente
 *
 * Inserito un id utente, la funzione cancella questo utente.
 * NB: la cancellazione non è fisica, ma avviene settando l'id dell'utente a 0
 *
 * @return 1 in caso di cancellazione terminata con successo
 * @return 0 in caso di cancellazione terminata con errore
 */
short cancellaUtente();


#endif  /*GESTOREUTENTI_H_*/
