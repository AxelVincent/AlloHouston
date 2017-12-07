#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "../headers/temps.h"
#include "../headers/train.h"
#include "../headers/main.h"
#include "../headers/service.h"
#include "../headers/color.h"
#include "../headers/requetes.h"

int main(int argc, char *argv[])
{
	if(argc == 2)
	{
		// On a bien 1 argument qui doit etre le numero de PORT

		ecouteServeur(creationServeur(atoi(argv[1])));
	}else
	{
		fprintf(stderr, RED "Il doit y avoir 1 argument : "MAG"PORT "RESET "\n");
		exit(-1);
	}
	return 0;

}

int creationServeur(int numeroPort)
{
	//Creation du serveur

	struct sockaddr_in socketEcoute;

	socketEcoute.sin_family = AF_INET;
	socketEcoute.sin_port = htons(numeroPort);
	(socketEcoute.sin_addr).s_addr = htonl(INADDR_ANY);

	//Creation de la socket d'ecoute (Primitive "socket")
	int descripteur;
	// int socket(int domaine, int type, int protocole);
	descripteur = socket(AF_INET,SOCK_STREAM,0);

	//Attachement de la socket (Primitive "bind")

	// int bind(int descripteur, const struct sockaddr *p, int len);
	if(descripteur>=3)
	{
		printf("socket fonctionne\n");
		if(bind(descripteur,(struct sockaddr *) &socketEcoute,sizeof(socketEcoute)) == 0)
		{
			// Bind works
			// int listen(int descripteur, int nb);
			printf("bind fonctionne\n");

			if(listen(descripteur, 100) == 0)
			{
				printf("listen fonctionne\n");
				return descripteur;

			}
			else
			{
				fprintf(stderr, RED "Erreur lors du listen" RESET "\n");
				exit(-1);
			}

		}
		else
		{
			//Bind don't works
			fprintf(stderr, RED "Erreur lors du listen" RESET "\n");
			fprintf(stderr, "Peut etre que le port "YEL "%d" RESET " est deja utilise?\n", numeroPort);
			exit(-1);
		}
	}
	else
	{
		fprintf(stderr, RED "Erreur lors de la creation de la socket" RESET "\n");
		exit(-1);
	}

}

void ecouteServeur(int descripteur)
{

	struct sockaddr_in socketService;
	// TODO Peut etre besoin de ça ?
	// socketService.sin_family = AF_INET;
	// socketService.sin_port = htons(numeroPort);
	// (socketService.sin_addr).s_addr = htonl(INADDR_ANY);

	while(1)
	{
		//int accept(int descripteur, struct sockaddr *p, int *len);
		//Attente d'acceptation client
		printf("En attente de connexion...\n");
		unsigned int tailleSocketService = sizeof(struct sockaddr_in);
		int descripteurSocketService = accept(descripteur, (struct sockaddr *) &socketService, &tailleSocketService);
		printf("%d\n",descripteurSocketService);
		if(descripteurSocketService >= 4)
		{
			printf("accept fonctionne\n");
			switch (fork()) {
				case -1:
				// Erreur dans la création d'un FILS
				fprintf(stderr, RED "Erreur dans la création d'un fils" RESET "\n");
				exit(-1);

				case 0:
				// FILS
				printf("Création du fils ayant pour numero de PID : %d\n",getpid());
				nouveauService(descripteurSocketService);
				break;
				default:
				// PERE
				printf("Pere se remet en écoute : %d\n",getpid() );
			}
		}
		else
		{
			fprintf(stderr, RED "Erreur lors du accept" RESET "\n");
			exit(-1);
		}

	}
}
