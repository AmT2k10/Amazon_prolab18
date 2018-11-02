/**
 * @file gestoreProdotti.h
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
#ifndef GESTOREPRODOTTI_H_
#define GESTOREPRODOTTI_H_

/**
 * Numero massimo di prodotti da inserire su file
 */
#define MAX_PRODOTTI 10000

/**
 * Numero delle categorie del prodotto
 */
#define NUM_CATEGORIE 6

/**
 * Dimensione massima per le stringhe dei nomi
 */
#define DIM_NOME 20

/**
 * Valore massimo del prezzo di un prodotto
 */
#define MAX_PREZZO 100000


/**
 * Tipo di dato che descrive un prodotto all'interno del file "listaProdotti"
 */
typedef struct
{
	int prodottoID; /** <Id del prodotto, valore numerico incrementale*/
	char nome [DIM_NOME]; /**< Stringa che contiene il nome del prodotto*/
	char categoria[DIM_NOME]; /** < Stringa che contiene il nome della categoria del prodotto*/
	char azienda[DIM_NOME]; /** < Stringa che contiene il nome dell' azienda del prodotto*/
	double prezzo; /** < Valore del prezzo del prodotto*/
	short spedizioneRapida; /** <Indica con 1/0 se il prodotto ha oppure no la spedizione rapida*/
}prodotto;



/* FUNZIONI */

/**
 * Menu per la gestione dei prodotti
 *
 * Permette di richiamare attraverso un menù le operazioni relative agi prodotti
 *
 * @return 1 in caso di funzione terminata con successo
 * @return 0 in caso di funzione terminata con errore
 */
short gestoreProdotti ();


/**
 * Menu per la gestione della ricerca dei prodotti
 *
 * Permette di richiamare attraverso un menù le operazioni relative ai vari metodi di ricerca sui prodotti
 *
 * @return 1 in caso di funzione terminata con successo
 * @return 0 in caso di funzione terminata con errore
 */
short menuRicercaProdotti();


/**
 * Menu per l'ordinamento dei prodotti
 *
 * Permette di richiamare attraverso un menù le operazioni relative agli ordinamenti sui prodotti
 *
 * @return 1 in caso di funzione terminata con successo
 * @return 0 in caso di funzione terminata con errore
 */
short menuOrdinaProdotto();


/**
 * Inserimento prodotto
 *
 * Permette di inserire un prodotto. Fa inserire da tastiera le informazioni relative al prodotto  per
 * memorizzare in un file denominato "listaProdotti.txt".
 *
 * @return 1 in caso di funzione terminata con successo
 * @return 0 in caso di funzione terminata con errore
 */
short inserisciProdotto();


/**
 * Visualizza prodotto
 *
 *Permette di visualizzare un prodotto dopo aver inserito da tastiera il suo id
 *
 */
void visualizzaProdottoID();


/**
 * Visualizza prodotti dal prezzo minore
 *
 * Inserito un prezzo da tastiera, visualizza i prodotti che hanno prezzo minore o uguale a quello inserito.
 *
 * @return numProdotti Il numero di prodotti corrispondenti
 * @return 0 in caso di funzione terminata con errore
 */
int visualizzaProdottoPrezzoMin();


/**
 * Visualizza prodotti dal prezzo maggiore
 *
 * Inserito un prezzo da tastiera, visualizza i prodotti che hanno prezzo maggiore o uguale a quello inserito.
 *
 * @return numProdotti Il numero di prodotti corrispondenti
 * @return 0 in caso di funzione terminata con errore
 */
int visualizzaProdottoPrezzoMagg();


/**
 * Visualizza prodotti dal nome uguale
 *
 * Inserito un nome da tastiera, visualizza i prodotti che hanno nome uguale a quello inserito.
 *
 * @return  numProdotti Il numero di prodotti corrispondenti
 * @return 0 in caso di funzione terminata con errore
 */
int visualizzaProdottoNome();


/**
 * Visualizza prodotti dal nome azienda uguale
 *
 * Inserito un nome azienda da tastiera, visualizza i prodotti che hanno azienda uguale a quella inserita.
 *
 * @return numProdotti Il numero di prodotti corrispondenti
 * @return 0 in caso di funzione terminata con errore
 */
int visualizzaProdottoAzienda();


/**
 * Visualizza prodotti dalla categoria uguale
 *
 * Inserito una categoria da tastiera, visualizza i prodotti che hanno categoria uguale a quella inserito.
 *
 * @return numProdotti Il numero di prodotti corrispondenti
 * @return 0 in caso di funzione terminata con errore
 */
int visualizzaProdottoCategoria();


/**
 * ELenco prodotti
 *
 * Stampa a video tutti i prodotti leggendo da file
 */
void visualizzaElencoProdotti();


/**
 *  Modifica prodotto
 *
 * Inserito un id prodotto, modifica i dati relativi a quel prodotto.
 *
 * @return 1 in caso di modifica terminata con successo
 * @return 0 in caso di modifica terminata con errore
 */
short modificaProdotto();


/**
 * Cancella prodotto
 *
 * Inserito un id prodotto, la funzione cancella questo prodotto.
 * NB: la cancellazione non è fisica, ma avviene settando l'id del prodotto a 0
 *
 * @return 1 in caso di cancellazione terminata con successo
 * @return 0 in caso di cancellazione terminata con errore
 */
short cancellaProdotto();


/**
 * Ultimi dieci arrivi
 *
 * Stampa a video gli ultimi dieci prodotti, leggendo il file in ordine invertito essendo questo già ordinato
 */
void ultimiDieciArrivi();


/**
 * Top 10 costosi
 *
 * Ordina i prodotti in base al prezzo e stampa i primi 10.
 */
void topDieciCostosi();

#endif  /*GESTOREPRODOTTI_H_*/
