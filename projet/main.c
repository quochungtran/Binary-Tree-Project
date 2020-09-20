#include <stdio.h>
#include <stdlib.h>
#include "function.h"


int main()
{

    int choix = 0;
    T_inter intervalle;
    T_inter Nouvelintervalle;
    int Id_entreprise=0;


    do
    {
        printf("MENU  Taper:\n");
        printf("\n");
        printf("1 Creer un ABR\n");
        printf("2 Afficher tous les reservations\n");
        printf("3 Ajouter une reservation\n");
        printf("4 Modifier une reservation\n");
        printf("5 Supprimer une reservation\n");
        printf("6 Afficher les reservations d une entreprise\n");
        printf("7 Supprimer l arbre\n");
        printf("8 Quitter \n");
        scanf("%ld",&choix);
        printf("\n");

        switch(choix)
        {
        case 1:
            printf("---Creer un ABR--- \n\n  ");
            T_Arbre abrr=NULL;
            int n=0;
            do
            {
                printf("commbien reservation voulez vous ajouter? ");
                scanf("%d",&n);
                if(n<=0)
                    printf("c'est pas posiple, veuillez essayez");
            }
            while(n<=0);

            while(n!=0)
            {
                Id_entreprise=creer_ID();
                intervalle=creer_inter();
                T_Noeud* noeud=creer_noeud( Id_entreprise, intervalle);
                ajouter_noeud(&abrr, noeud);
                printf("\n");
                n--;
            }
            break;

        case 2:
            printf("---Afficher toutes les reservations--- \n");

            if(abrr==NULL)
                printf("il y a aucun noeud");
            else
                affiche_abr(abrr);
            break;

        case 3:
            printf("---Ajouter une reservation--- \n\n  ");

            Id_entreprise=creer_ID();
            intervalle=creer_inter();
            T_Noeud* noeud=creer_noeud( Id_entreprise, intervalle);
            ajouter_noeud(&abrr, noeud);

            break;
        case 4:
            printf("---Modifier une reservation---\n\n");
            int flag=0;
            do
            {
                printf("Entrez la modification a changer?\n");
                Id_entreprise=creer_ID();
                intervalle=creer_inter();
                if(recherche(abrr,intervalle,Id_entreprise)==NULL)
                {
                    printf("la reservation n'existe pas.\n");
                    int flag = 0;
                }
                else
                    flag = 1;
            }
            while(recherche(abrr,intervalle,Id_entreprise)==NULL);
            if (flag == 1)
                ;
            {
                printf("\n Entrez sa modification\n");
                Nouvelintervalle=creer_inter();
                modif_noeud(abrr, intervalle,Id_entreprise, Nouvelintervalle);
            }
            break;
        case 5:

            printf("---Supprimer une reservation---\n\n");

            do
            {
                printf("la reservation que tu veux supprimer?\n");
                Id_entreprise=creer_ID();
                intervalle=creer_inter();

                if(recherche(abrr,intervalle,Id_entreprise)==NULL)
                    printf("la reservation n'a pas existe \n");
            }
            while(recherche(abrr,intervalle,Id_entreprise)==NULL);

            Supp_noeud(&abrr, intervalle,Id_entreprise);
            break;
        case 6:
            printf("---Afficher les reeservations d une entreprise---\n\n");

            Id_entreprise=creer_ID();
            affiche_entr(abrr,Id_entreprise);
            break;
        case 7:
            printf("---Supprimer l arbre---\n\n");

            if(abrr==NULL)
                printf("il y a aucun node pour supprimer");
            else
                detruire_arbre(&abrr);
            break;
        case 8:
            printf("Quitter\n");

            break;
        default:
            printf("taper un nombre compris entre 1 et 8\n");

        }
        printf("\n");
    }
    while(choix != 8);
    return 0;
}

