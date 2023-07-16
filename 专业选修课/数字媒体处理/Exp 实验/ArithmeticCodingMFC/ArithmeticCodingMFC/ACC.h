#define Code_value_bits 16             /* Number of bits in a code value   */
typedef long code_value;                /* Type of an arithmetic code value */

#define Top_value (((long)1<<Code_value_bits)-1)      /* Largest code value */


#define First_qtr (Top_value/4+1)       /* Point after first quarter        */
#define Half      (2*First_qtr)         /* Point after first half           */
#define Third_qtr (3*First_qtr)         /* Point after third quarter        */

#define No_of_chars 16                  /* Number of character symbols      */
#define EOF_symbol (No_of_chars+1)      /* Index of EOF symbol              */

#define No_of_symbols (No_of_chars+1)   /* Total number of symbols          */

/* TRANSLATION TABLES BETWEEN CHARACTERS AND SYMBOL INDEXES. */


/* CUMULATIVE FREQUENCY TABLE. */

#define Max_frequency 16383             /* Maximum allowed frequency count */
#define Max_code_length 10000000
extern void encode(BYTE * source, int size);
extern void decode();
extern char code[Max_code_length];
extern BYTE DecodeRS[Max_code_length];
extern  long code_index;
extern  int decode_index;
extern  int decode_length;
extern  int freq[No_of_symbols + 1];
extern  void start_model();