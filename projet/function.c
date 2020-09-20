#include <stdio.h>
#include <stdlib.h>
#include "function.h"


T_Noeud* creer_noeud(int Id_entreprise,T_inter intervalle)
{
    T_Noeud *new_node = malloc(sizeof(T_Noeud));
    new_node->Id_entreprise=Id_entreprise;
    new_node->intervalle=intervalle;
    new_node->gauche=NULL;
    new_node->droit=NULL;
    return new_node;
}

void ajouter_noeud( T_Arbre* abr,T_Noeud* noeud)
{

    T_Noeud* current_node= *abr;


    if(current_node==NULL)
        *abr=noeud;
    else if( chevaucher(current_node,noeud->intervalle)==1)
    {
        printf("c est pas possible pour ajouter\n");
        return;
    }
    else
    {
        if(current_node->intervalle.g > noeud->intervalle.g)
        {
            ajouter_noeud(&current_node->gauche,noeud);
        }
        else if(current_node->intervalle.g < noeud->intervalle.g)
        {
            ajouter_noeud(&current_node->droit,noeud);
        }
    }
}

int chevaucher(T_Arbre abr,T_inter intervalle)
{
    int check=0;
    if(intervalle.g <= abr->intervalle.g &&
            intervalle.d >= abr->intervalle.g )
        check=1;
    if(intervalle.g >= abr->intervalle.g &&
            intervalle.g <= abr->intervalle.d )
        check=1;

    return check;
}
int chevaucher_parcours(T_Arbre abr, T_inter intervalle)
{
    int q=0;
    if(abr != NULL)
    {
        chevaucher_parcours(abr->gauche,intervalle);
        if (chevaucher(abr,intervalle))
            return 1;
        chevaucher_parcours(abr->droit,intervalle);
    }
    return q;
}


T_Noeud* recherche(T_Arbre abr, T_inter intervalle,int Id_entreprise)
{
    if (abr==NULL)
        return NULL;
    if(abr->intervalle.g == intervalle.g && abr->intervalle.d== intervalle.d  && abr->Id_entreprise==Id_entreprise)
        return abr;
    if (abr->intervalle.g < intervalle.g)
        return recherche(abr->droit,intervalle,Id_entreprise);
    if (abr->intervalle.g > intervalle.g)
        return recherche(abr->gauche,intervalle,Id_entreprise);
    return NULL;
}



void Supp_noeud(T_Arbre* abr,T_inter intervalle,int Id_entreprise)
{
    if ((*abr)==NULL)
    {
        return;
    }
    if ((*abr)->intervalle.g > intervalle.g)
    {
        Supp_noeud(&((*abr)->gauche), intervalle, Id_entreprise);
    }
    else if ((*abr)->intervalle.g < intervalle.g)
    {
        Supp_noeud(&((*abr)->droit), intervalle, Id_entreprise);
    }
    else if (((*abr)->intervalle.d == intervalle.d) && ((*abr)->Id_entreprise == Id_entreprise))
    {
        // 1 child or 0 child
        T_Noeud *temp = *abr;
        if ((*abr)->gauche==NULL)
        {
            (*abr) = (*abr)->droit;
        }
        else if ((*abr)->droit == NULL)
        {
            (*abr) = (*abr)->gauche;
        }
        else     // 2 child
        {
            echanger_noeuds(&((*abr)->droit), &temp);
        }
        free(temp);
        temp=NULL;
    }
}

void echanger_noeuds(T_Arbre *abr, T_Arbre* pabr)
{
    if ((*abr)->gauche != NULL)
        echanger_noeuds(&((*abr)->gauche), pabr);
    else
    {
        (*pabr)->Id_entreprise = (*abr)->Id_entreprise;
        (*pabr)->intervalle = (*abr)->intervalle;
        (*pabr) = (*abr);
        (*abr) = (*abr)->droit;
    }

}

void modif_noeud(T_Arbre abr, T_inter intervalle,int Id_entreprise,T_inter Nouvelntervalle)
{
    if (chevaucher_parcours(abr,Nouvelntervalle)==0 )
    {
        Supp_noeud(&abr,intervalle,Id_entreprise);
        ajouter_noeud(&abr,creer_noeud(Id_entreprise,Nouvelntervalle));
    }
    else
    {
        printf("cette reservation existe deja ou chevauche un autre.");
    }
}




void affiche_abr(T_Arbre abr)
{
    if(abr != NULL)
    {
        affiche_abr(abr->gauche);
        printf(" --> ID_Entr:%d -- [%d,%d]\n", abr->Id_entreprise, abr->intervalle.g,abr->intervalle.d);
        affiche_abr(abr->droit);
    }
}



void affiche_entr(T_Arbre abr,int Id_entreprise)
{
    if(abr != NULL)
    {
        affiche_entr(abr->gauche,Id_entreprise);
        if(abr->Id_entreprise==Id_entreprise)
            printf("--> ID_Entr:%d -- [%d,%d]\n", abr->Id_entreprise,abr->intervalle.g,abr->intervalle.d);
        affiche_entr(abr->droit,Id_entreprise);
    }
}




void detruire_arbre(T_Arbre* abr)
{
    free(*abr);
    *abr=NULL;
}




T_inter creer_inter()
{
    T_inter intervalle;
    int check=0;
    printf("Saisir  une reservation\n");
    do
    {
        printf(" date debut:");
        scanf("%d",&intervalle.g);
        printf(" date fin:");
        scanf("%d",&intervalle.d);
        if(intervalle.g <=0 || intervalle.d<=0 || intervalle.g>=intervalle.d)
            check=1;
        else
            check=0;
        if(check==1)
            printf("Ce n'est pas possible, veuillez reessayer. \n");
    }
    while (check==1);
    return intervalle;
}



int creer_ID()
{
    int Id_entreprise;
    do
    {
        printf(" Saisir ID entreprise :");
        scanf("%d",&Id_entreprise);
        if(Id_entreprise <= 0)
            printf("Ce n'est pas possible, veuillez reessayer. ");
    }
    while (Id_entreprise<=0);
    return Id_entreprise;
}




//rechercher le père
//T_Noeud *current_node=*abr
//T_Noeud *current_node2=abr
//current_node = recherche(abr, intervalle, Id_entreprise);
//if (current_node == NULL) printf("Cette reservation n'existe pas");
//else {
//  if (current_node->gauche == NULL && current_node->droit ==NULL) free(current_node);
//else if (current_node->gauche == NULL{//à modifier
//  current_node2=current_node;
//current_node=current_node->gauche;
//free(current_node2);

//}
//else if (current_node->droit ==NULL){

