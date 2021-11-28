#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"


int main(int argc,char *argv[]){

	
	BMP_RGB          bmp_rgb;

	BMP_FILE_HEADER  entete_bmp;
	BMP_IMAGE_HEADER_V4 entete_image_bmp;

	unsigned char **R;
	unsigned char **V;	
	unsigned char **B;

	
	int pixel_manquant;

	int i,j,result;
	FILE *fp ;
	long taille_fichier;
	unsigned char *buf;
	int seize;

	int compteur_h,compteur_l;
	
	fp = fopen(argv[1],"rb");
	if(fp==NULL){
	
		perror("Erreur c'est ");
		return(-1);
	}


	result = BMP_read_file_header(fp,&entete_bmp);
	if(result == NULL){
		
		perror("Erreur c'est ");
		return(-1);
	}

	result = BMP_read_image_header(fp,&entete_image_bmp);
	if(result == NULL){
		
		perror("Erreur c'est ");
		return(-1);
	}

	printf("Offset de image c'est %d\n",entete_bmp.image_offset);
	printf("Hauteur de image : %d\n",entete_image_bmp.image_height);	
	printf("Largeur de image : %d\n",entete_image_bmp.image_width);	
	pixel_manquant = (entete_image_bmp.image_width)%4;
	printf("pixel_manquant c'est %d\n",pixel_manquant);
	
	/*..........................allouer la taille d'entrée...........................*/

	rewind (fp);
  	fseek (fp , 0 , SEEK_END);
  	taille_fichier = ftell (fp);
  	rewind (fp);

	/*..........................positionner le début de fp.......................................*/	

	buf = (char *) malloc ((taille_fichier)*sizeof(char));

	/*.............................creation(location) de mémoire pour le sauvgarde........................................*/

	result = fread (buf,1,taille_fichier,fp);

	
	/*.............................creation(location) de mémoire pour le sauvgarde........................................*/



	if (buf == NULL) {
	
		return(-1);
	}
		/*.......................................sauvgarder dans la mémoire..........................................*/

	
	if (result != taille_fichier) {
		printf (MSG_ERR_READ,"buf"); 
		return(-1);
	}
	R = (unsigned char *) malloc ((entete_image_bmp.image_height)*sizeof(unsigned char *));
	for(i=0;i<(entete_image_bmp.image_height);i++){
	R[i]= (unsigned char *) malloc ((entete_image_bmp.image_width+pixel_manquant)*sizeof(unsigned char));
	}

	V = (unsigned char *) malloc ((entete_image_bmp.image_height)*sizeof(unsigned char *));
	for(i=0;i<(entete_image_bmp.image_height);i++){
	V[i]= (unsigned char *) malloc ((entete_image_bmp.image_width+pixel_manquant)*sizeof(unsigned char));
	}

	B = (unsigned char *) malloc ((entete_image_bmp.image_height)*sizeof(unsigned char *));
	for(i=0;i<(entete_image_bmp.image_height);i++){
	B[i]= (unsigned char *) malloc ((entete_image_bmp.image_width+pixel_manquant)*sizeof(unsigned char));
	}


	compteur_h=0;
	compteur_l=0;
	for(i=entete_bmp.image_offset;i<taille_fichier;i=i+3){
		B[compteur_h][compteur_l]=buf[i];
		V[compteur_h][compteur_l]=buf[i+1];
		R[compteur_h][compteur_l]=buf[i+2];
		compteur_l++;
		if(compteur_l == entete_image_bmp.image_width){
			compteur_l=0;
			compteur_h++;
			for(j=0;j<pixel_manquant;j++){
				B[compteur_h][compteur_l+j]=0;
				V[compteur_h][compteur_l+j]=0;
				R[compteur_h][compteur_l+j]=0;
			}
		}	
	
	}
	
	printf("Memoire allocate pour un couleur : %d octets \n", entete_image_bmp.image_height*(entete_image_bmp.image_width+pixel_manquant));
	



	fclose(fp);
	free(buf);

return (EXIT_SUCCESS);

}
/*
zone de réponse
*/

