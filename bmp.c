#include "bmp.h"

/* BMP_read_header
 * lit l'entête d'un fichier BMP
 * 
 * Paramètres
 * - bmp_file est le fichier à lire (mode binaire)
 * - header est un pointeur vers la structure à compléter
 * 
 * Retour
 * - TRUE si succès
 * - FALSE si échec
 */
int BMP_read_file_header(FILE *bmp_file, BMP_FILE_HEADER *header) {
    unsigned char c[4];
    unsigned int i,j;
    unsigned int w;
    /* place le curseur au début du fichier */
    fseek(bmp_file,0,SEEK_SET);
    /* lit les deux premiers caratères et vérifie s'ils valent 0x42 0x4D (BM) */
    if(fread(c, 1, 1, bmp_file) != 1) return(FALSE);
    if(c[0]==0x42) (*header).ID1 = c[0]; else return(FALSE);
    if(fread(c, 1, 1, bmp_file) != 1) return(FALSE);
    if(c[0]==0x4D) (*header).ID2 = c[0]; else return(FALSE);
    /* lit la taille du fichier */
    if(fread(c, 1, 4, bmp_file) != 4) return(FALSE);
    for(i=0,j=3,w=0; i<4; i++,j--) {
        w <<= 8;
        w |= (unsigned int)c[j];
    }
    (*header).file_size = w;
    /* lit mot réservé et vérifie qu'il vaut bien 0 */
    if(fread(c, 1, 4, bmp_file) != 4) return(FALSE);
    for(i=0,j=3,w=0; i<4; i++,j--) {
        w <<= 8;
        w |= (unsigned int)c[j];
    }
    if(w==0) (*header).reserved = w; else return(FALSE);
    
    /* lit l'offset de début d'image */
    if(fread(c, 1, 4, bmp_file) != 4) return(FALSE);
    for(i=0,j=3,w=0; i<4; i++,j--) {
        w <<= 8;
        w |= (unsigned int)c[j];
    }
    (*header).image_offset = w;
    /* quitte OK */
    return(TRUE);
}

int BMP_read_image_header(FILE *bmp_file, BMP_IMAGE_HEADER_V4 *header) {
    unsigned char c[4];
    unsigned int i,j,k;
    unsigned int rest;
    unsigned int w;
    unsigned int *wp;
    /* place le curseur au 14ème octet */
    fseek(bmp_file,14,SEEK_SET);
    /* lit la taille de l'entête */
    if(fread(c, 1, 4, bmp_file) != 4) return(FALSE);
    for(i=0,j=3,w=0; i<4; i++,j--) {
        w <<= 8;
        w |= (unsigned int)c[j];
    }
    switch(w) {
        /* formats reconnus */
        case V1_SIZE:
        case V2_SIZE:
        case V3_SIZE:
        case V4_SIZE:
            (*header).header_size = w;
            break;
        /* sinon retour avec code erreur */
        default:
            return(FALSE);
    }
    /* lit la taille de l'image */
    if(fread(c, 1, 4, bmp_file) != 4) return(FALSE);
    for(i=0,j=3,w=0; i<4; i++,j--) {
        w <<= 8;
        w |= (unsigned int)c[j];
    }
    (*header).image_width = w;
    if(fread(c, 1, 4, bmp_file) != 4) return(FALSE);
    for(i=0,j=3,w=0; i<4; i++,j--) {
        w <<= 8;
        w |= (unsigned int)c[j];
    }
    (*header).image_height = w;
    /* lit nombre de plans et vérifie si égal à 1 */
    if(fread(c, 1, 2, bmp_file) != 2) return(FALSE);
    for(i=0,j=1,w=0; i<2; i++,j--) {
        w <<= 8;
        w |= (unsigned int)c[j];
    }
    if(w==1) (*header).planes = (unsigned short int)w; else return(FALSE);
    /* lit bit/pixel et vérifie si conforme */
    if(fread(c, 1, 2, bmp_file) != 2) return(FALSE);
    for(i=0,j=1,w=0; i<2; i++,j--) {
        w <<= 8;
        w |= (unsigned int)c[j];
    }
    switch(w) {
        case 24:
        case 32:
            (*header).bit_count = (unsigned short int)w;
            break;
        default:
            return(FALSE);
    }
    /* lit tous les mots 32 bits suivants */
    rest = ((*header).header_size-16)>>2; /* nbre de mots restants à lire */
    wp = &((*header).compression); /* pointeur vers premier élément suivant bit_count */
    for(i=4; i<rest; i++) {
        /* lit un mot */
        if(fread(c, 1, 4, bmp_file) != 4) return(FALSE);
        for(k=0,j=3,w=0; k<4; k++,j--) {
            w <<= 8;
            w |= (unsigned int)c[j];
        }
        /* l'insère dans la structure */
        *wp = w;
        /* incrémente le pointeur vers le mot suivant */
        wp++;
    }
    /* complète avec des zéros */
    rest = (V4_SIZE-(*header).header_size)>>2; /* nbre de mots ignorés */
    for(i=4; i<rest; i++) *wp++ = 0;

    /* quitte OK */
    return(TRUE);
}


int BMP_write_file_header(FILE *bmp_file, BMP_FILE_HEADER file_header, BMP_IMAGE_HEADER_V4 image_header) {
    unsigned char c[4];
    unsigned int i;
    unsigned int w;
    unsigned int li;
    /* écrit les deux premiers caratères 0x42 0x4D (BM) */
    c[0] = 0x42;
    c[1] = 0x4D;
    if(fwrite(c, 1, 1, bmp_file) != 1) return(FALSE);
    if(fwrite(c+1, 1, 1, bmp_file) != 1) return(FALSE);
    /* écrit la taille du fichier */
    w=file_header.file_size;
    
    w =  14+V4_SIZE;
    li = 3*image_header.image_width;
    if(li&0x3) {
        li>>=2;
        li++;
        li<<=2;
    }
    w += li*image_header.image_height;
    
    for(i=0; i<4; i++) {
        c[i]=(unsigned char)(w&0x000000FF);
        w >>= 8;
    }
    if(fwrite(c, 1, 4, bmp_file) != 4) return(FALSE);
    /* écrit le mot réservé  0 */
    w=0;
    if(fwrite(&w, 4, 1, bmp_file) != 1) return(FALSE);
    /* écrit l'offset de début d'image */
    w=file_header.image_offset;
    for(i=0; i<4; i++) {
        c[i]=(unsigned char)(w&0x000000FF);
        w >>= 8;
    }
    if(fwrite(c, 1, 4, bmp_file) != 4) return(FALSE);
    /* quitte OK */
    return(TRUE);
}


int BMP_write_image_header(FILE *bmp_file, BMP_IMAGE_HEADER_V4 header) {
    unsigned char c[4];
    unsigned int i,j;
    unsigned int rest;
    unsigned int w;
    unsigned int *wp;
    /* écrit la taille de l'entête */
    w=V4_SIZE;
    for(i=0; i<4; i++) {
        c[i]=(unsigned char)(w&0x000000FF);
        w >>= 8;
    }
    if(fwrite(c, 1, 4, bmp_file) != 4) return(FALSE);
    /* écrit la taille de l'image */
    w=header.image_width;
    for(i=0; i<4; i++) {
        c[i]=(unsigned char)(w&0x000000FF);
        w >>= 8;
    }
    if(fwrite(c, 1, 4, bmp_file) != 4) return(FALSE);
    w=header.image_height;
    for(i=0; i<4; i++) {
        c[i]=(unsigned char)(w&0x000000FF);
        w >>= 8;
    }
    if(fwrite(c, 1, 4, bmp_file) != 4) return(FALSE);
    /* écrit nombre de plans égal à 1 */
    w=header.planes;
    for(i=0; i<2; i++) {
        c[i]=(unsigned char)(w&0x000000FF);
        w >>= 8;
    }
    if(fwrite(c, 1, 2, bmp_file) != 2) return(FALSE);
    /* écrit bit/pixel et vérifie si conforme */
    w=header.bit_count;
    for(i=0; i<2; i++) {
        c[i]=(unsigned char)(w&0x000000FF);
        w >>= 8;
    }
    if(fwrite(c, 1, 2, bmp_file) != 2) return(FALSE);
    /* écrit tous les mots 32 bits suivants */
    rest = (V4_SIZE-16)>>2; /* nbre de mots restants à écrire */
    wp = &(header.compression); /* pointeur vers premier élément suivant bit_count */
    for(i=0; i<rest; i++) {
        /* écrit un mot */
        for(j=0; j<4; j++) {
            c[j]=(unsigned char)((*wp)&0x000000FF);
            (*wp) >>= 8;
        }
        if(fwrite(c, 1, 4, bmp_file) != 4) return(FALSE);
        /* incrémente le pointeur vers le mot suivant */
        wp++;
    }

    /* quitte OK */
    return(TRUE);
}
