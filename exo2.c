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

	FILE *fp2;
	
	long taille_fichier;
	unsigned char *buf;
	/*printf(MSG_INFO_USAGE,argv[1]);*/
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
	printf("color_space : %d\n",entete_image_bmp.color_space);
	printf("col_used : %d\n",entete_image_bmp.col_used);
	printf("image_size : %d\n",entete_image_bmp.image_size);
	
	pixel_manquant = (entete_image_bmp.image_width)%4;
	printf("pixel_manquant c'est %d\n",pixel_manquant);


	/*trouver la taille de fichier entree:*/

  	fseek (fp , 0 , SEEK_END);
  	taille_fichier = ftell (fp);
  	rewind (fp);
       /*mettre position à point début de stream fp*/
	
	buf = (char *) malloc ((taille_fichier)*sizeof(char));/*creer un memoire pour enregistre tout le fichier*/
	
	result = fread (buf,1,taille_fichier,fp);/*mettre le fichier dans la memoire*/


	if (buf == NULL) {
		perror("Erreur c'est ");
		return(-1);
	}
	
	
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
	for(i=entete_bmp.image_offset;i<(taille_fichier-668);i=i+3){
		B[compteur_h][compteur_l]=buf[i];
		V[compteur_h][compteur_l]=buf[i+1];
		R[compteur_h][compteur_l]=buf[i+2];
		compteur_l++;

		if(compteur_l == entete_image_bmp.image_width){
			/*if(pixel_manquant!=0){
				for(j=0;j<pixel_manquant;j++){
					B[compteur_h][compteur_l+j]=0;
					V[compteur_h][compteur_l+j]=0;
					R[compteur_h][compteur_l+j]=0;
				}
			}*/
					B[compteur_h][501]= 0;
					V[compteur_h][501]=0;
					R[compteur_h][501]= 0;
		compteur_l=0;
		compteur_h++;
		}	
	
	}
	
	/*printf("Memoire allocate pour bleu : %d octets \n", (unsigned char) sizeof(B[0]));*/
	
	fp2 = fopen ("negatif.bmp","w+");
	entete_image_bmp.image_width+=pixel_manquant;
	
	BMP_write_file_header(fp2,entete_bmp,entete_image_bmp);
	BMP_write_image_header(fp2, entete_image_bmp);
	
	printf("%d",entete_image_bmp.image_width);
	
	for(j=0;j<entete_image_bmp.image_height;j++){
		
		for(i=0;i<entete_image_bmp.image_width;i++){
			if(B[j][i]!=0){B[j][i]=255-B[j][i];}
			fwrite(&B[j][i] , 1 , sizeof(B[0][0]) , fp2 );
			if(V[j][i]!=0){V[j][i]=255-V[j][i];}
			fwrite(&V[j][i] , 1 , sizeof(V[0][0]) , fp2 );
			if(R[j][i]!=0){R[j][i]=255-R[j][i];}
			fwrite(&R[j][i] , 1 , sizeof(R[0][0]) , fp2 );
		}		
		
	}


	fclose(fp2);
	fclose(fp);
	free(buf);

return (EXIT_SUCCESS);

}
/*
zone de réponse
*/
