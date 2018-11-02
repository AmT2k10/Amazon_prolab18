/**
 * @file gestoreDate.h
 *
 * Libreria che definsce il tipo di dato data
 *
 *
 *
 * @version 1.0
 * @date 30/09/2018
 * @authors Montemurro Andrea, Mininni Claudio
 * @copyright AJCM
 *
 */

#ifndef GESTOREDATE_H_
#define GESTOREDATE_H_

/**
 * Tipo di dato che descrive una data nel formato GG/MMM/AAAA
 */
typedef struct
{
	int giorno; /** < Giorno, valore numerico */
	char mese [3]; /** < Mese, stringa di 3 caratteri */
	int anno; /** < Anno, valore numerico*/
}data;



#endif /* GESTOREDATE_H_ */
