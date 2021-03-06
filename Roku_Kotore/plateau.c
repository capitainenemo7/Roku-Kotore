/*******************************************************/
/*                                                     */
/*  plateau.c  Projet : RokuKotore                     */
/*  edité par :  QUERUEL David                         */
/*               CAILLOT Antoine                       */
/*                                                     */
/*   note : login.c                                    */
/*          Ici est la racine du note programme        */
/*                                                     */
/*   Plus d'information sur la compilation             */
/*   rendez-vous dans main.c                           */
/*                                                     */
/*                                                     */
/*******************************************************/

#include "game_include.h"
#include "include.h"

static Paquet paq;
static int envoie_ok=0;
static running=1;
static print=1;
static pthread_mutex_t mutex=(pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;


void one_deck(SDL_Renderer *ren, int s, int y, int lang){  //iniature ligne rammassée
	TTF_Font *f;
	char tetes[10] = {0};
	Setting setting;
	if(lang == 2)
		f = loadFont("galacticmini.ttf", 20);
	else
		f = loadFont("minecraft.ttf", 20);
	color(ren, 0, 102, 47);
	rect(ren, 0, y, 100, 50, 1);
	image(ren, "cow.bmp", 5, y+5, 40, 40, 0, 0, 255);
	sprintf(tetes, "%d ", s);
	text(ren, f, tetes, 45, y+15, -1, -1, 255, 255, 255, 255);
	closeFont(f);
}

void show_deck(SDL_Renderer *ren, int deck[][5], int lang){  // calcule le nombre de tete pour la ligne ramassée et affiche toute les (miniature) lignes ramassé
	int i, j, s = 0;
	for(i = 0; i < 10 ; i++){
		if(deck[i][0] != 0){
			s = 0;
			for (j = 0; j < 5; j++)
			{
				if(deck[i][j] > 0)
					s += tete(deck[i][j]);
			}
			one_deck(ren, s, 100 + i*60, lang);
		}
	}
}

void show_one_deck(SDL_Renderer *ren, int hand[5], int lang){ // montre toute les carte rammassé de la ligne (passage de la sourie)
	int i;
	for(i = 0; i < 5; i++){
		if(hand[i] != 0){
				carte(ren, hand[i], 120, 50 + i*105, 100, 0, lang);
				delay(5);
		}
	}
}

void show_hand(SDL_Renderer *ren, int hand[], int selected, int lang){ //montre la main du joueur (les dix cartes)
	int i;
	for(i = 0; i < 5; i++){  //deux colones
		if(hand[i] != 0){ 
				if(selected == i){
					carte(ren, hand[i], 850, 50 + i*105, 100, 1, lang);
				}
				else{
					carte(ren, hand[i], 850, 50 + i*105, 100, 0, lang);
				}
				delay(5);
		}
	}
	for(i = 5; i < 10; i++){
		if(hand[i] != 0){
				if(selected == i){
					carte(ren, hand[i], 950, 50 + (i-5)*105, 100, 1, lang);
				}
				else{
					carte(ren, hand[i], 950, 50 + (i-5)*105, 100, 0, lang);
				}
				delay(5);
		}
	}
}

void show_grid(SDL_Renderer *ren, int grille[4][5], int lang){  // montre la grille, cad l'ensemble des carte sur la table
	int i, j;
	for(i = 0; i < 4; i++){
		for(j = 0; j < 5; j++){
			if(grille[i][j] != 0){
				carte(ren, grille[i][j], 250 + j*100, 50 + i*155, 150, 0, lang);
				delay(5);
			}
		}
	}
}

void carte(SDL_Renderer *ren, int numero, int x, int y, int h, int selected, int lang){ //dessin d'une carte

	/*
		On dessine la carte à l'aide de plusieurs rectangles de tailles differentes, puis on colle des tête (image BMP)
		et affiche le nombre de la carte
	*/
	char num[5];
	TTF_Font *f;
	SDL_Rect textPos;
	//int tete = 1;

	sprintf(num, "%d", numero);
	if(lang == 2) // gestion de la langue
		f = loadFont("galacticmini.ttf", 20); 
	else
		f = loadFont("minecraft.ttf", 20);
		

	textPos = text(ren, f, num, x + 20, y + 20, -1, -1, 0, 0, 0, 0);


	if(selected){
		color(ren, 0, 200, 50);
	}
	else{
		color(ren, 0, 0, 100);
	}
	
	rect(ren, x, y+10, 90, h-20, 1);
	rect(ren, x+5, y+5, 80, h-10, 1);
	rect(ren, x+10, y, 70, h, 1);

	

	switch(tete(numero)){
		case 1:
			color(ren, 255, 255, 230);
			rect(ren, x+5, y+15, 80, h-30, 1);
			rect(ren, x+10, y+10, 70, h-20, 1);
			rect(ren, x+15, y+5, 60, h-10, 1);
			image(ren, "cow.bmp", x + (90/2)-(30/2), y + 20, 30, 30, 0, 0, 255);
			break;

		case 2:
			color(ren, 255, 255, 170);
			rect(ren, x+5, y+15, 80, h-30, 1);
			rect(ren, x+10, y+10, 70, h-20, 1);
			rect(ren, x+15, y+5, 60, h-10, 1);
			image(ren, "cow.bmp", x + (90/2)-22, y + 20, 20, 20, 0, 0, 255);
			image(ren, "cow.bmp", x + (90/2)+(22-20), y + 20, 20, 20, 0, 0, 255);
			break;

		case 3:
			color(ren, 255, 255, 0);
			rect(ren, x+5, y+15, 80, h-30, 1);
			rect(ren, x+10, y+10, 70, h-20, 1);
			rect(ren, x+15, y+5, 60, h-10, 1);
			image(ren, "cow.bmp", x + (90/2)-(20/2), y + 20, 20, 20, 0, 0, 255);
			image(ren, "cow.bmp", x + (90/2)-35, y + 20, 20, 20, 0, 0, 255);
			image(ren, "cow.bmp", x + (90/2)+(35-20), y + 20, 20, 20, 0, 0, 255);
			break;

		case 5:
			color(ren, 255, 150, 0);
			rect(ren, x+5, y+15, 80, h-30, 1);
			rect(ren, x+10, y+10, 70, h-20, 1);
			rect(ren, x+15, y+5, 60, h-10, 1);
			image(ren, "cow.bmp", x + (90/2)-(20/2), y + 12, 20, 20, 0, 0, 255);
			image(ren, "cow.bmp", x + (90/2)-35, y + 12, 20, 20, 0, 0, 255);
			image(ren, "cow.bmp", x + (90/2)+(35-20), y + 12, 20, 20, 0, 0, 255);
			image(ren, "cow.bmp", x + (90/2)-22, y + 35, 20, 20, 0, 0, 255);
			image(ren, "cow.bmp", x + (90/2)+(22-20), y + 35, 20, 20, 0, 0, 255);
			break;

		case 7:
			color(ren, 255, 0, 0);
			rect(ren, x+5, y+15, 80, h-30, 1);
			rect(ren, x+10, y+10, 70, h-20, 1);
			rect(ren, x+15, y+5, 60, h-10, 1);
			image(ren, "cow.bmp", x + (90/2)-18, y + 12, 15, 15, 0, 0, 255);
			image(ren, "cow.bmp", x + (90/2)+(18-15), y + 12, 15, 15, 0, 0, 255);
			image(ren, "cow.bmp", x + (90/2)-38, y + 12, 15, 15, 0, 0, 255);
			image(ren, "cow.bmp", x + (90/2)+(38-15), y + 12, 15, 15, 0, 0, 255);
			image(ren, "cow.bmp", x + (90/2)-(15/2), y + 35, 15, 15, 0, 0, 255);
			image(ren, "cow.bmp", x + (90/2)-28, y + 35, 15, 15, 0, 0, 255);
			image(ren, "cow.bmp", x + (90/2)+(28-15), y + 35, 15, 15, 0, 0, 255);
			break;

		default:
			break;
	}
	
	text(ren, f, num, x+ (90/2)-(textPos.w/2), y+ (130/2)-(textPos.h/2)+20, -1, -1, 0, 0, 0, 0);

	delay(5);
	closeFont(f);
}

void retardement(Paquet *tampon)
{
	
	int i,j,h=0,k,l;

	for(i=0 ; i< tampon->nb_client ; i++)
	{	
		for(j=0; j< tampon->nb_client; j++)
		{

			if(tampon->carte_jouee[j][3] == h && tampon->carte_jouee[j][0] >0)
			{	
			//si on a rammassé une rangée ... on efface les anciennes
				if(tampon->carte_jouee[j][2] ==0 )
				{	
					pthread_mutex_lock(&mutex);
					for(l=0;l<5;l++)
					{

						paq.grille[tampon->carte_jouee[j][1]][4-l]=0;
						sleep(0.5);
					}

					paq.grille[tampon->carte_jouee[j][1]][0]= tampon->carte_jouee[j][0];
					pthread_mutex_unlock(&mutex);
					tampon->carte_jouee[j][0]=0;
					tampon->carte_jouee[j][2]=-1;
					tampon->carte_jouee[j][3]=-1;


				}
				else
				{
					pthread_mutex_lock(&mutex);
					paq.grille[tampon->carte_jouee[j][1]][tampon->carte_jouee[j][2]]=tampon->carte_jouee[j][0];
					pthread_mutex_unlock(&mutex);
					tampon->carte_jouee[j][0]=0;
					tampon->carte_jouee[j][2]=-1;
					tampon->carte_jouee[j][3]=-1;
				}
				h++;
				j=10;
				sleep(1);
			}

		}


	}
	pthread_mutex_lock(&mutex);
	copier_grille(&paq,*tampon);
	pthread_mutex_unlock(&mutex);


}

void *client(void * arg)
{
	FILE *server_settings = NULL;

    ServSetting serv;

   #if defined (WIN32)
	WSADATA WSAData;
	int erreur = WSAStartup(MAKEWORD(2,2), &WSAData);
    #else
	int erreur = 0;
    #endif
	int i,k,j,tour=0;
	Obj_sock client;

    //int port=23;
	Paquet tampon;
	if(!erreur)
	{
		client = create_sock_obj();

		strcpy(serv.ip, "127.0.0.1");//127.0.0.1 est le serveur local pour tous les ordi!
	    serv.port = 23;

	    server_settings = fopen("server_settings.conf", "r");
	    if(server_settings != NULL){
	    	printf("reading\n");
	    	fread(&serv, sizeof(serv), 1, server_settings);
	    	printf("try to connect to IP : %s PORT : %d\n", serv.ip, serv.port);
	    	fclose(server_settings);
	    }
	    else{
	    	perror("Open server_settings.conf");
	    }
     	
		client=client_config(client,serv.ip,serv.port);

		do{

  		pthread_mutex_lock(&mutex);
			reception_pqt(client,&tampon);
			printf("\ngrille ==\n");
			affichage_grille(tampon);

			paq = copier_Paquet(paq,tampon,tour);
			print=1;
        	pthread_mutex_unlock(&mutex);
			retardement(&tampon);
			printf("carte jouee \n");
			for(i=0;i<paq.nb_client;i++)
			{
				for(j=0;j<4;j++)
				{

					printf("%d\t", paq.carte_jouee[i][j]);
				}
				printf("\n");

			}



			printf("deck:%d\n",paq.nb_client );

			printf("Nombre de tete de boeuf :%d\nN_dec =%d\n",paq.moi.tete_partie,paq.moi.n_deck);
			affichage_grille(paq);
			afficher_carte_main(paq);  


			if(paq.etat==1)
			{
				printf("\nNouvelle manche!\n");
				pthread_mutex_lock(&mutex);
				reception_pqt(client,&paq);
				pthread_mutex_unlock(&mutex);
				printf("Etat du jeu :%d\n",paq.etat);
			}
			if(paq.etat<2)
			{


				do{

				}while(envoie_ok == 0 && running);
    //pthread_mutex_lock(&mutex); 
				envoie_ok=0;
    //on supprime la carte choisie
				paq=supprimer_carte(paq);
    //pthread_mutex_unlock(&mutex);
    //Envoie le paquet modifié
				envoie_pqt(client,paq);

			}
			tour++;             
		}while(paq.etat!=2);

		printf("Fin du jeu\n");

		reception_pqt(client,&paq);


		affichage_grille(paq);


        /* On ferme la socket précédemment ouverte */
		closesocket(client.sock);


        #if defined (WIN32)
		WSACleanup();
        #endif
	}

	pthread_exit(NULL);
}


void plateau(SDL_Window *win, SDL_Renderer *ren, char filename[45]){
	//printf("ON LANCE LA GUI LES MEC!!!!!\n"); //souvenir d'un bug de qualité

	//Initialisation et declaration des variable graphique
	SDL_Surface *img_srf;
    SDL_Texture *img_txtu;
    SDL_Rect tapisPos;
    SDL_Event event;

    Mix_Music *musique;
  	
  	TTF_Font *f;
    TTF_Font *fBig;
    TTF_Font *fG;
    TTF_Font *fBigG;


    //chargement des reglages
    Setting setting;
    FILE *settingFile = NULL;
    settingFile = fopen("properties.conf", "r");
	if(settingFile != NULL){
		fread(&setting, sizeof(setting), 1, settingFile);
		fclose;
	}
	else{
		setting.lang = 0;
		setting.music = 1;
	}


	// variable utiles
	int loop = 1;
	int i, j;

    char tete_manche[20];
    f = loadFont("minecraft.ttf", 15); 
    fBig = loadFont("minecraft.ttf", 20);
    fG = loadFont("galacticmini.ttf", 15); 
    fBigG = loadFont("galacticmini.ttf", 20);

    int card_to_send = -1;

    // arriere plan (ici on n'utilise pas de fonction pour optimiser les performance)
	img_srf = SDL_LoadBMP("tapis.bmp");
	img_txtu = SDL_CreateTextureFromSurface(ren, img_srf);
    SDL_FreeSurface(img_srf);


    // musique
	musique = Mix_LoadMUS("music/track_Roku_Torimasu.mp3");
	if(setting.music){
		Mix_PlayMusic(musique, -1);
	}

	//pause (David)
    do{
    	//NOP
    }while(print == 0);


    //boucle principale
	while(loop){

		for(i = 0; i <= 14; i++){
			for(j = 0; j <= 9; j++){
				//image(ren, "tapis.bmp", i*80, j*80, 80, 80, 0, 0, 0);
				tapisPos.x = i*80;
    			tapisPos.y = j*80;
    			tapisPos.w = 80;
        		tapisPos.h = 80;
				SDL_RenderCopy(ren, img_txtu, NULL, &tapisPos);
			}
		}
		


		image(ren, "cow.bmp", 50, 585, 65, 65, 0, 0, 255);

		// affichage des tete de la partie
		switch(setting.lang){ // langue
			case 0:
				sprintf(tete_manche, "%d Tetes", paq.moi.tete_partie);
			break;

			case 1:
				sprintf(tete_manche, "%d Heads", paq.moi.tete_partie);
			break;

			case 2:
				sprintf(tete_manche, "%d HEADS", paq.moi.tete_partie);
			break;

			default:
				sprintf(tete_manche, "%d Tetes", paq.moi.tete_partie);
			break;
		}
		if(setting.lang == 2){
			text(ren, fBigG, tete_manche, 50, 655, -1, -1, 255, 255, 255, 255);
		}
		else{
			text(ren, fBig, tete_manche, 50, 650, -1, -1, 255, 255, 255, 255);
		}
		

		//on affiche les differents elements
		show_grid(ren, paq.grille, setting.lang);
		show_hand(ren, paq.moi.paquet_carte, card_to_send, setting.lang);
		show_deck(ren, paq.moi.deck, setting.lang);

		for(i = 0; i < 10; i++){
			if(mouseX() <= 100 && mouseY() >= 100 + i*60 && mouseY() <= 160 + i*60){ //si on est sur une miniature, on affiche les cartes de la ligne
				show_one_deck(ren, paq.moi.deck[i], setting.lang);
			}
		}

		if(paq.etat == 2){
			loop = 0;
		}
		
		//carte(ren, 55, 200, 200);
		//background(ren, 0, 150, 50);

		while(SDL_PollEvent(&event)){
			switch(event.type){ // quitter
				case SDL_QUIT:
					loop = 0;
					running =0;
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_BACKSPACE:
							break;
						case SDLK_RETURN:
							break;
							
						case SDLK_ESCAPE: //quitter
							loop = 0;
							running =0;
							break;
					}
					break;
				case SDL_TEXTINPUT:
				    break;
				
				case SDL_MOUSEBUTTONDOWN: // cliquer sur une carte
					for(i = 0; i < 5; i++){
						if(paq.moi.paquet_carte[i] != 0){
								if(mouseX() >= 850 && mouseX() < 950 && mouseY() >= 50 + i*105 && mouseY() <= 150 + i*105){
									card_to_send = i;
									pthread_mutex_lock(&mutex);
									paq.moi.num_carte = paq.moi.paquet_carte[i];
									pthread_mutex_unlock(&mutex);
									envoie_ok=1;
								}
						}
					}
					for(i = 5; i < 10; i++){
						if(paq.moi.paquet_carte[i] != 0){
								if(mouseX() >= 950 && mouseX() < 1050 && mouseY() >= 50 + (i-5)*105 && mouseY() <= 150 + (i-5)*105){
									card_to_send = i;
									pthread_mutex_lock(&mutex);
									paq.moi.num_carte = paq.moi.paquet_carte[i];
									pthread_mutex_unlock(&mutex);
									envoie_ok=1;
								}
						}
					}
					break;
			}
		}
		//delay(5);
		drawScene(ren);
	}
	Mix_FreeMusic(musique);
	closeFont(f);
    closeFont(fBig);
    closeFont(fG);
    closeFont(fBigG);
    SDL_DestroyTexture(img_txtu);
    archivage(paq, filename);
    end_screen(win, ren, paq.moi.tete_partie, setting.lang, filename); //on affiche l'écran de fin
}

int tete(int carte){ //calcule tête pour chaque carte
	int t = 0;
	if(carte%11 == 0)
		t+=5;
	if(carte%10 == 0)
		t+=3;
	if(carte%5 == 0 && carte%10 != 0)
		t+=2;
	if(carte%11 != 0 && carte%10 != 0 && carte%5 != 0)
		t=1;
	return t;
}

void end_screen(SDL_Window *win, SDL_Renderer *ren, int ntete, int lang, char *filename){ //ecran de fin & enregistrement dans le fichier d'archive
	SDL_Surface *img_srf;
    SDL_Texture *img_txtu;
    SDL_Rect tapisPos;
    SDL_Rect but, butClick, txt;

	int loop = 1;
	int i, j;
	int state = -1;

	TTF_Font *f;
	TTF_Font *fG;
	TTF_Font *fBig;
	SDL_Event event;

	f = loadFont("minecraft.ttf", 18);
	fBig = loadFont("minecraft.ttf", 25);  
	fG = loadFont("galacticmini.ttf", 18); 

	img_srf = SDL_LoadBMP("grey_wool.bmp");
	img_txtu = SDL_CreateTextureFromSurface(ren, img_srf);
    SDL_FreeSurface(img_srf);

    switch(lang){ // on recupère les tailles du texte
			case 0:
				if(ntete >= 66){
					txt = text(ren, f, "Vous avez perdu", (1100/2)-(txt.w/2) - 10, 75, -1, -1, 255, 255, 255, 255);
				}
				else{
					txt = text(ren, f, "Vous avez gagne", (1100/2)-(txt.w/2) - 10, 75, -1, -1, 255, 255, 255, 255);
				}
				
			break;

			case 1:
				if(ntete >= 66){
					txt = text(ren, f, "You loose", (1100/2)-(txt.w/2) - 10, 75, -1, -1, 255, 255, 255, 255);
				}
				else{
					txt = text(ren, f, "You win", (1100/2)-(txt.w/2) - 10, 75, -1, -1, 255, 255, 255, 255);
				}
				
			break;

			case 2:
				if(ntete >= 66){
					txt = text(ren, fG, "YOU LOOSE", (1100/2)-(txt.w/2) - 10, 75, -1, -1, 255, 255, 255, 255);
				}
				else{
					txt = text(ren, fG, "YOU WIN", (1100/2)-(txt.w/2) - 10, 75, -1, -1, 255, 255, 255, 255);
				}
				
			break;

			default:
				if(ntete >= 66){
					txt = text(ren, f, "Vous avez perdu", (1100/2)-(txt.w/2) - 10, 75, -1, -1, 255, 255, 255, 255);
				}
				else{
					txt = text(ren, f, "Vous avez gagne", (1100/2)-(txt.w/2) - 10, 75, -1, -1, 255, 255, 255, 255);
				}
				
			break;
		}



	while(loop){
	    for(i = 0; i <= 14; i++){ // fond d'écran
				for(j = 0; j <= 9; j++){
					tapisPos.x = i*80;
	    			tapisPos.y = j*80;
	    			tapisPos.w = 80;
	        		tapisPos.h = 80;
					SDL_RenderCopy(ren, img_txtu, NULL, &tapisPos);
				}
			}
		
		//text(ren, fBig, "Roku Kotore", 465, 75, -1, -1, 255, 255, 255, 255);

		color(ren, 50, 50, 50);

		switch(lang){ // langue et bouton
			case 0:
				if(ntete >= 66){
					text(ren, f, "Vous avez perdu", (1100/2)-(txt.w/2), 300, -1, -1, 255, 255, 255, 255);
				}
				else{
					text(ren, f, "Vous avez gagne", (1100/2)-(txt.w/2), 300, -1, -1, 255, 255, 255, 255);
				}
				but = text(ren, f, "Continuer", 490, 600, -1, -1, 255, 255, 255, 255);
				butClick = rect(ren, but.x - 100, but.y - 10, but.w + 200, but.h + 20, 1);
				text(ren, f, "Continuer", 490, 600, -1, -1, 255, 255, 255, 255);
			break;

			case 1:
				if(ntete >= 66){
					text(ren, f, "You loose", (1100/2)-(txt.w/2), 300, -1, -1, 255, 255, 255, 255);
				}
				else{
					text(ren, f, "You win", (1100/2)-(txt.w/2), 300, -1, -1, 255, 255, 255, 255);
				}
				but = text(ren, f, "Continue", 490, 600, -1, -1, 255, 255, 255, 255);
				butClick = rect(ren, but.x - 100, but.y - 10, but.w + 200, but.h + 20, 1);
				text(ren, f, "Continue", 490, 600, -1, -1, 255, 255, 255, 255);
			break;

			case 2:
				if(ntete >= 66){
					text(ren, fG, "YOU LOOSE", (1100/2)-(txt.w/2), 300, -1, -1, 255, 255, 255, 255);
				}
				else{
					text(ren, fG, "YOU WIN", (1100/2)-(txt.w/2), 300, -1, -1, 255, 255, 255, 255);
				}
				but = text(ren, fG, "CONTINUE", 490, 600, -1, -1, 255, 255, 255, 255);
				butClick = rect(ren, but.x - 100, but.y - 10, but.w + 200, but.h + 20, 1);
				text(ren, fG, "CONTINUE", 490, 600, -1, -1, 255, 255, 255, 255);
			break;

			default:
				if(ntete >= 66){
					text(ren, f, "Vous avez perdu", (1100/2)-(txt.w/2), 300, -1, -1, 255, 255, 255, 255);
				}
				else{
					text(ren, f, "Vous avez gagne", (1100/2)-(txt.w/2), 300, -1, -1, 255, 255, 255, 255);
				}
				but = text(ren, f, "Continuer", 490, 600, -1, -1, 255, 255, 255, 255);
				butClick = rect(ren, but.x - 100, but.y - 10, but.w + 200, but.h + 20, 1);
				text(ren, f, "Continuer", 490, 600, -1, -1, 255, 255, 255, 255);
			break;
		}

		if(state != -1){
			loop = 0;
		}


		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					state = 4;
					loop = 0;
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_BACKSPACE:
							break;
						case SDLK_RETURN:
							break;
							
						case SDLK_ESCAPE:
							state = 4;
							loop = 0;
							break;
					}
					break;
				
				case SDL_MOUSEBUTTONUP:
					switch(event.button.button){ 
						case SDL_BUTTON_LEFT:
								if(mouseX() >= butClick.x && mouseX() <= butClick.x + butClick.w && mouseY() >= butClick.y && mouseY() <= butClick.y + butClick.h ){
	
									loop = 0;
									//printf("click %d\n", i);
								}
						break;
					}
					break;
			}
		}		
		drawScene(ren);
	}
	closeFont(f);
	closeFont(fBig);
	closeFont(fG);
	SDL_DestroyTexture(img_txtu);
}


void archivage(Paquet paquet, char filename[45]){
	Archive arch, old;
	FILE *ficArch = NULL;

	old.point = 0;
	old.reussite = 0;
	old.defaite = 0;

	ficArch = fopen(filename, "r");
	if(ficArch != NULL){
		fread(&old, sizeof(Archive), 1, ficArch);
		close(ficArch);
	}
	else{
		printf("erreur d'ouverture'\n");
	}

	ficArch = NULL;

	if(paquet.moi.tete_partie >= 66){
		arch.point = 0 + old.point;
		arch.reussite = 0 + old.reussite;
		arch.defaite = 1 + old.defaite;
	}
	else{
		arch.point = paquet.nb_client + old.point;
		arch.reussite = 1 + old.reussite;
		arch.defaite = 0 + old.defaite;
	}


	ficArch = fopen(filename, "w");
	if(ficArch != NULL){
		fwrite(&arch, sizeof(Archive), 1, ficArch);
		close(ficArch);
	}
	else{
		printf("erreur d'enregistrement\n");
	}
}

