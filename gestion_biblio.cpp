#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct livre{
int code;
char titre[30];
char genre[30];
char auteur[30];
}livre;

typedef struct listlivre{
    struct listlivre *suiv;
    livre a;
    int NExemplaires;
}listlivre;

typedef struct filetudiant{
    struct filetudiant *suiv;
    int codelivre;
    char nometudiant[30];
}filetudiant;


filetudiant *f;
listlivre *liste;

void suprfile(int code)
{filetudiant *p;
p=f;
    while(p->suiv->codelivre!=code)
        p=p->suiv;
 if(p->suiv->suiv==NULL)
                  p->suiv=NULL;
 else
     p=p->suiv->suiv;

}

void suprliste(int code)
{listlivre *p;
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
    {listlivre *pl1,*pl2;
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
        printf("%d*%s\n",L->NExemplaires,L->a.titre);
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
    {   if(L->NExemplaires==0)
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
{if(L!=NULL)
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
    printf("1-ajouter un livre\n");
    printf("2-Servir un etudiant\n");
    printf("3-afficher liste des livres\n");
    printf("4-Ajouter a la file\n");
    printf("5-Afficher la file\n");
    printf("6-Quitter\n");
    printf("entrer votre choix \t");
    scanf("%d",&choix);
    switch(choix){
        case 1:
        {
            listlivre *pl1,*pl2;
            pl1=liste;
            livre liv;
            printf("Entrer le code : ");
            scanf("%d",&liv.code);
            getchar();
            while((pl1!=NULL)&&(liv.code!=pl2->a.code))
            {
                pl2=pl1;
                pl1=pl1->suiv;

            }
            if(liv.code==pl2->a.code)
            {
                printf("\nce livre figure déja dans la liste des livres , on a augmenté le nombre d'exemplaire de 1\n");
			       	pl2->NExemplaires++;
            }

            else{


            printf("Entrer l'auteur : ");
            gets(liv.auteur);
            printf("Entrer le genre : ");
            gets(liv.genre);
            printf("Entrer le titre : ");
            gets(liv.titre);
            ajoutlivre(liv,f);	}
            break;
        }
        case 2:
        {int n;
        char nometudiant[30];
        printf("entrer le nom de l'etudiant\t");
        scanf("%s",&nometudiant);
        printf("\n entrer le code du livre\t ");
        scanf("%d",&n);
        servirlivre(nometudiant,n,liste);
            break;
        }
        case 3:
        {
            afficherlist(liste);
            break;
        }
        case 4:
        {
            int code;
            char NomE[30];
            printf("Entrer le code : ");
            scanf("%d",&code);
            getchar();
            printf("Entrer le nom de l'etudiant : ");
            gets(NomE);
            servirlivre(NomE,code,liste);
            break;
        }
        case 5:
        {
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

    }while(ch!=6);

}
