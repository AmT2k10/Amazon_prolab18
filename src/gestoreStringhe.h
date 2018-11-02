/**
 * @file gestoreStringhe.h
 *
 * Libreria che contiene funzioni per la gestione delle stringhe per gli input da tastiera
 *
 * @version 1.0
 * @date 30/09/2018
 * @authors Montemurro Andrea, Mininni Claudio
 * @copyright AJCM
 *
 */

#ifndef GESTORESTRINGHE_H_
#define GESTORESTRINGHE_H_


/**
 * Verifica se il parametro è un numero intero
 *
 * @param inputSring è un puntatore a char
 * @return 1 o 0 (vero o falso)
 */
short isNumero(char* inputString);


/**
 * Verifica se il parametro è un numero decimale
 *
 * @param inputSring è un puntatore a char
 * @return 1 o 0 (vero o falso)
 */
short isNumeroDec(char* inputString);


/**
 * Inserisce da tastiera una stringa con spazi
 *
 * @param inputSring è un puntatore a char
 * @param dim è un intero, dimensione massima della stringa
 * @return 1 in caso di successo, 0 in caso di errore
 */
short inserisciStringaSpazi (char* inputString, int dim);

/**
 * Inserisce da tastiera una stringa con spazi senza numeri, per nomi e cognomi di persone
 *
 * @param inputSring è un puntatore a char
 * @param dim è un intero, dimensione massima della stringa
 * @return 1 in caso di successo, 0 in caso di errore
 */
short inserisciStringaSpaziNome (char* inputString, int dim);


/**
 * Inserisce da tastiera una stringa senza spazi
 *
 * @param inputSring è un puntatore a char
 * @param dim è un intero, dimensione massima della stringa
 * @return 1 in caso di successo, 0 in caso di errore
 */
short inserisciStringa (char* inputString, int dim);


/**
 * Inserisce da tastiera una stringa contente un numero intero compreso tra due limiti
 *
 * @param inputSring è un puntatore a char
 * @param limiteInf è un intero, limite inferiore
 * @param limiteSup è un intero, limite superiore
 * @return 1 in caso di successo, 0 in caso di errore
 */
short inserisciNumero (char* inputString, int limiteInf, int limiteSup);


/**
 * Inserisce da tastiera una stringa contente un numero decimale compreso tra due limiti
 *
 * @param inputSring è un puntatore a char
 * @param limiteInf è un float, limite inferiore
 * @param limiteSup è un float, limite superiore
 * @return 1 in caso di successo, 0 in caso di errore
 */
short inserisciNumeroDec(char* inputString, float limiteInf, float limiteSup);

#endif /*GESTORESTRINGHE_H_*/
