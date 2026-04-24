#ifndef KIOLIB_H
#define KIOLIB_H

/* =========================================================
 * INCLUSIONI
 * ========================================================= */
/* nessun header standard: siamo in kernel space */

/* =========================================================
 * COSTANTI E MACRO — colori VGA (attributo byte)
 *
 * Formato attributo: 0xBF
 *   B = colore sfondo (4 bit)
 *   F = colore testo  (4 bit)
 * ========================================================= */

#define VGA_WIDTH       80U
#define VGA_HEIGHT      25U
#define VGA_MEM         ((char *) 0xB8000)

/* Colori testo (foreground) su sfondo nero */
#define BLACK_TXT       0x00
#define BLUE_TXT        0x01
#define GREEN_TXT       0x02
#define CYAN_TXT        0x03
#define RED_TXT         0x04
#define MAGENTA_TXT     0x05
#define BROWN_TXT       0x06
#define WHITE_TXT       0x07    /* grigio chiaro — default */
#define GREY_TXT        0x08    /* grigio scuro (bright black) */
#define LIGHT_BLUE_TXT  0x09
#define LIGHT_GREEN_TXT 0x0A
#define LIGHT_CYAN_TXT  0x0B
#define LIGHT_RED_TXT   0x0C
#define PINK_TXT        0x0D
#define YELLOW_TXT      0x0E
#define BRIGHT_WHITE_TXT 0x0F

/* =========================================================
 * TIPI ED ENUMERAZIONI
 * ========================================================= */

/** Codici di ritorno delle funzioni kiolib */
typedef enum {
    KIO_OK      =  0,   /**< Operazione riuscita       */
    KIO_ERR     = -1,   /**< Errore generico           */
    KIO_EINVAL  = -2    /**< Parametro non valido      */
} KioStatus;

/* =========================================================
 * DICHIARAZIONI DELLE FUNZIONI
 * ========================================================= */

/**
 * @brief  Pulisce l'intero schermo VGA (80x25) con sfondo nero.
 *
 * Riempie la memoria video di spazi bianchi con attributo WHITE_TXT.
 */
void k_clear_screen(void);

/**
 * @brief  Stampa una stringa a partire dalla riga specificata.
 *
 * Supporta il carattere di escape '\n' per andare a capo.
 * Non gestisce lo scrolling: se si supera la riga 24 il
 * comportamento non è definito.
 *
 * @param[in]  message  Stringa terminata da '\0' da stampare.
 * @param[in]  line     Riga di partenza (0 – VGA_HEIGHT-1).
 * @param[in]  colour   Attributo colore VGA (es. WHITE_TXT).
 * @return     Riga successiva all'ultima scritta.
 */
unsigned int k_printf(const char *message, unsigned int line, char colour);

#endif /* KIOLIB_H */