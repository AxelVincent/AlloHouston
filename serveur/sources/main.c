#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "../headers/main.h"
#include "../headers/service.h"

int main(int argc, char *argv[])
{
	if(argc == 2)
	{
		// On a bien 1 argument qui doit etre le numero de PORT

		ecouteServeur(creationServeur(atoi(argv[1])));
	}else
	{
		printf("Il doit y avoir 1 argument : PORT\n");
	}
	return 0;

}

int creationServeur(int numeroPort)
{
	//Creation du serveur
	// TODO Verifier si c'est bien le socket d'ecoute

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
				printf("Erreur lors du listen\n");
			}

		}
		else
		{
			//Bind don't works
			printf("Erreur lors du bind\n");
			printf("Peut etre que le port %d est deja utilise?\n", numeroPort);
		}
	}
	else
	{
		printf("Erreur lors de la creation de la socket\n");
	}
	return -1;
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
				printf("Erreur dans la création d'un fils");

				case 0:
				// FILS
				printf("Création du fils ayant pour numero de PID : %d\n",getpid());
				nouveauService(descripteurSocketService);

				default:
				// PERE
				printf("Pere se remet en écoute : %d\n",getpid() );

			}
		}
		else
		{
			printf("Erreur lors de accept\n");
		}



	}
}
