#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct livre
{
int code;
char titre[30];
char genre[30];
char auteur[30];
}livre;

typedef struct listlivre
{
  struct listlivre *suiv;
  livre a;
  int NExemplaires;
}listlivre;

typedef struct filetudiant
{
  struct filetudiant *suiv;
  int codelivre;
  char nometudiant[30];
}filetudiant;


filetudiant *f;
listlivre *liste;

void printSpaces()
{
  printf("\n\n\n\n");
}

void suprfile(int code)
{
  filetudiant *p;
  p=f;
  while(p->suiv->codelivre!=code)
    p=p->suiv;
  if(p->suiv->suiv==NULL)
    p->suiv=NULL;
  else
    p=p->suiv->suiv;  
}

void suprliste(int code)
{
  listlivre *p;
  p=liste;
  while(p->suiv->a.code!=code)
    p=p->suiv;
  if(p->suiv!=NULL)
    p->suiv=p->suiv->suiv;
  else
    p=NULL;
}

void ajoutlivre(livre L, filetudiant *F)
{
  //Le cas de la non existance du livre dans la file des étudiants
  if(F==NULL)
    {
      listlivre *pl1,*pl2;
      pl1=liste;
      pl2=liste;
      
      listlivre *p=(listlivre*)malloc(sizeof(listlivre));
      p->a.code=L.code;
      p->suiv=NULL;
      strcpy(p->a.auteur,L.auteur);
      strcpy(p->a.genre,L.genre);
      strcpy(p->a.titre,L.titre);
      p->NExemplaires=1;
      if(liste==NULL){
	liste=p;
      }
      
      else
        {
	  while((pl1!=NULL)&(L.code!=pl2->a.code))
	    {
	      pl2=pl1;
	      pl1=pl1->suiv; 
	    }
	  
	  if(pl1==NULL)
	    {
	      pl2->suiv=p;
	    }
	  else
	    pl1->NExemplaires++;
        }
      
      return;
    }
  
  //Le cas de l'existance dans la file
  if(F->codelivre==L.code)
    {
      printf("Le livre a ete delivree avec succes au étudiant %s",F->nometudiant);
      return;
    }
  return ajoutlivre(L,F->suiv);
}

void afficherlist(listlivre *L)
{
  while(L)
    {
      if(L->NExemplaires == 1)
	printf("1 seule exemplaire de %s\n",L->a.titre);
      else
	printf("%d exemplaires de %s\n",L->NExemplaires,L->a.titre);
      
      L=L->suiv;
    }
}

void ajoutfile(char nomE[],int code)
{
  filetudiant *p=(filetudiant*)malloc(sizeof(filetudiant));
  p->codelivre=code;
  strcpy(p->nometudiant,nomE);
  p->suiv=NULL;
  if(f==NULL)
    {
      f=p;
    }
  else
    {
      p->suiv=f;
      f=p;
    }
  
  return;
}

void servirlivre(char nomE[],int code,listlivre *L)
{
  if(L==NULL)
    {
      printf("le livre n'est pas disponible, on a ajouté l'étudiant %s a file d'attente",nomE);
      ajoutfile(nomE,code);
      return;
    }
  
  if(L->a.code==code)
    {
      if(L->NExemplaires==0)
        {
	  ajoutfile(nomE,code);
	  printf("le livre n'est pas disponible, on a ajouté l'étudiant %s a file d'attente",nomE);
	  return;
        }
      else{
        printf("Le livre a ete delivree avec succes a l'etudiant %s\n",nomE);
        L->NExemplaires--;
        return;
      }
    }
  return servirlivre(nomE,code,L->suiv);
}

void afficherfile(filetudiant *F)
{
  while(F)
    {
      printf("%s\n",F->nometudiant);
      F=F->suiv;
    }
}

FILE* fs;
void sauvegarde(listlivre *L)
{
  if(L!=NULL)
    {
      fs=fopen("sauvegarde.txt","a");
      while(L)
	{
	  fwrite(L,sizeof(listlivre),1,fs);
	  L=L->suiv;  
	}
    }
}

int menu()
{
    int choix;
    printf("1- Ajouter un livre\n");
    printf("2- Servir un etudiant\n");
    printf("3- Afficher liste des livres\n");
    printf("4- Ajouter a la file\n");
    printf("5- Afficher la file\n");
    printf("6- Quitter\n");
    printf("\n\n");
    printf("Entrer votre choix : ");
    
    scanf("%d",&choix);
    
   
    switch(choix){
    case 1:
      {
	listlivre *pl1,*pl2;
   	pl1=liste;
	pl2=liste;
	livre liv;
	printf("Entrer le code : ");
	scanf("%d",&liv.code);
	getchar();
	
	int livre_trouve = 0;
	while((pl1!=NULL))
	  {
	    if(liv.code==(pl1->a).code)
	      {
		printf("\nCe livre figure déjà dans la liste des livres , on a augmenté le nombre d'exemplaire de 1\n");
		pl2->NExemplaires++;
		livre_trouve = 1;
		break;
	      }
	    pl1=pl1->suiv;
	  }
	
	
	// cas ou le livre n'est pas trouvé dans la biblio
	if(livre_trouve == 0)
	  {
	    printf("Entrer l'auteur : ");
	    fgets(liv.auteur, sizeof(liv.auteur), stdin);
	    printf("Entrer le genre : ");
	    fgets(liv.genre, sizeof(liv.genre), stdin);
	    printf("Entrer le titre : ");
	    fgets(liv.titre, sizeof(liv.titre), stdin);
	    ajoutlivre(liv,f);
	    printf("livre ajouté avec succès à la bibliothèque");
	    printSpaces();
	  }
	
	
	break;
      }
    case 2:
      {
	int n;
        char nometudiant[30];
	printSpaces();
        printf("entrer le nom de l'etudiant : ");
        scanf("%s",(char *)&nometudiant);
        printf("\n entrer le code du livre : ");
        scanf("%d",&n);
        servirlivre(nometudiant,n,liste);
	break;
      }
    case 3:
      {
	printSpaces();
	afficherlist(liste);
	break;
      }
    case 4:
      {
	int code;
	char NomE[30];
	printSpaces();
	printf("Entrer le code : ");
	scanf("%d",&code);
	getchar();
	printf("Entrer le nom de l'etudiant : ");
	fgets(NomE, sizeof(NomE), stdin);
	servirlivre(NomE,code,liste);
	break;
      }
    case 5:
      {
	printSpaces();
	afficherfile(f);
	break;
      }
    case 6:
      sauvegarde(liste);
      break;
    }
    return choix;
}

int  main()
{
  liste=NULL;
 
  f=NULL;
  int ch;
  do
    {
      ch=menu();
      printSpaces();
    }while(ch!=6);
}
