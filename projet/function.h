#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED

typedef struct  T_inter{
    int d;
    int g;
}T_inter;

typedef struct T_Noeud {
    int  Id_entreprise;
    T_inter intervalle;
   struct T_Noeud *gauche;
   struct T_Noeud *droit;
}T_Noeud ;

typedef T_Noeud* T_Arbre;

T_Noeud* creer_noeud(int Id_entreprise,T_inter intervalle);
 void ajouter_noeud( T_Arbre* abr,T_Noeud* noeud);
T_Noeud* recherche(T_Arbre abr, T_inter intervalle,int Id_entreprise);
void Supp_noeud(T_Arbre* abr, T_inter intervalle,int Id_entreprise);
void modif_noeud(T_Arbre abr, T_inter intervalle,int Id_entreprise,T_inter Nouvelntervalle);
void affiche_abr(T_Arbre abr);
void affiche_entr(T_Arbre abr,int Id_entreprise);
void detruire_arbre(T_Arbre *abr);
////SUPPLEMANTAIRE FONCTION
void echanger_noeuds(T_Arbre *abr,T_Arbre* noeud );
int chevaucher(T_Arbre abr,T_inter intervalle);
int chevaucher_parcours(T_Arbre abr,T_inter intervalle);
T_inter creer_inter();
int creer_ID();
#endif // FUNCTION_H_INCLUDED
