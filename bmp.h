#include <stdlib.h>
#include <stdio.h>

/* FALSE et TRUE */
#define FALSE 0
#define TRUE 1

/* messages d'erreur */
#define MSG_ERR_OPEN "ERR : Error opening <%s>\n"
#define MSG_ERR_READ "ERR : Error reading <%s>\n"
#define MSG_ERR_NOT_VALID_BMP "ERR : <%s> is not a valid BMP file\n"
#define MSG_ERR_PREFIXE "ERR "


/* tailles entête image */
#define V1_SIZE 40
#define V2_SIZE 52
#define V3_SIZE 56
#define V4_SIZE 108

/* strucutres */
/* BMP file header */
typedef struct {
    unsigned char ID1;          /* 1 octet 0x42 */
    unsigned char ID2;          /* 1 octet 0x4D */
    unsigned int file_size;     /* 4 octets : taille du fichier en octets */
    unsigned int reserved;      /* 4 octets : réservé, généralement 0 */
    unsigned int image_offset;  /* 4 octets : position de l'image par rapport au début du fichier (offset) */
}BMP_FILE_HEADER;

/* BMP image header */
typedef struct {
    /* V1 to V4 */
    unsigned int header_size;       /* 4 octets : taille entête; permet de déterminer le type : 40=V1, 108=V4 */
    unsigned int image_width;       /* 4 octets : largeur de l'image en pixels */
    unsigned int image_height;      /* 4 octets : hauteur de l'image en pixels */
    unsigned short int planes;      /* 2 octets : nombre de plans; doit être égal à 1 */
    unsigned short int bit_count;   /* 2 octets : 1, 4, 8, 16, 24 ou 32; nombre de bit par pixels */
    unsigned int compression;       /* 4 octets : type de compression 0=aucune, 1=RLE8, 2=RLE4, bitfields */
    unsigned int image_size;        /* 4 octets : taille en octets de l'image (pas du fichier); peut valoir 0 si non compressé */
    unsigned int x_res;             /* 4 octets : résolution en pixels/mètre */
    unsigned int y_res;             /* 4 octets : résolution en pixels/mètre */
    unsigned int col_used;          /* 4 octets : nombre de couleurs utilisées */
    unsigned int col_important;     /* 4 octets : nombre de couleurs couleurs importantes; 0 = toutes importantes */
    /* end of V1 */
    unsigned int red_mask;          /* 4 octets : masque rouge (compression bitfields) */
    unsigned int gre_mask;          /* 4 octets : masque vert (compression bitfields) */
    unsigned int blu_mask;          /* 4 octets : masque bleu (compression bitfields) */
    /* end of V2 */
    unsigned int alp_mask;          /* 4 octets : masque alpha (compression bitfields) */
    /* end of V3 */
    unsigned int color_space;       /* 4 octets : color space */
    unsigned int CIEXYZREDX;        /* 4 octets : CIEXYZ */
    unsigned int CIEXYZREDY;        /* 4 octets : CIEXYZ */
    unsigned int CIEXYZREDZ;        /* 4 octets : CIEXYZ */    
    unsigned int CIEXYZGREX;        /* 4 octets : CIEXYZ */
    unsigned int CIEXYZGREY;        /* 4 octets : CIEXYZ */
    unsigned int CIEXYZGREZ;        /* 4 octets : CIEXYZ */
    unsigned int CIEXYZBLUX;        /* 4 octets : CIEXYZ */
    unsigned int CIEXYZBLUY;        /* 4 octets : CIEXYZ */
    unsigned int CIEXYZBLUZ;        /* 4 octets : CIEXYZ */
    unsigned int gamma_red;         /* 4 octets : correction gamma */
    unsigned int gamma_gre;         /* 4 octets : correction gamma */
    unsigned int gamma_blu;         /* 4 octets : correction gamma */
    /* end of V4 */
}BMP_IMAGE_HEADER_V4;

/* BMP_RGB */
typedef struct {
    unsigned char *R;
    unsigned char *G;
    unsigned char *B;
}BMP_RGB;

/* fonctions */
int BMP_read_file_header(FILE *, BMP_FILE_HEADER *);
int BMP_read_image_header(FILE *, BMP_IMAGE_HEADER_V4 *);

int BMP_write_file_header(FILE *, BMP_FILE_HEADER, BMP_IMAGE_HEADER_V4);
int BMP_write_image_header(FILE *, BMP_IMAGE_HEADER_V4);
