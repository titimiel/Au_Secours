#include "dijkstra.h"
#include <stdlib.h>

/**
 * construire_chemin_vers - Construit le chemin depuis le noeud de départ donné vers le
 * noeud donné. On passe un chemin en entrée-sortie de la fonction, qui est mis à jour
 * par celle-ci.
 *
 * Le noeud de départ est caractérisé par un prédécesseur qui vaut `NO_ID`.
 *
 * Ce sous-programme fonctionne récursivement :
 *  1. Si le noeud a pour précédent `NO_ID`, on a fini (c'est le noeud de départ, le chemin de
 *     départ à départ se compose du simple noeud départ)
 *  2. Sinon, on construit le chemin du départ au noeud précédent (appel récursif)
 *  3. Dans tous les cas, on ajoute le noeud au chemin, avec les caractéristiques associées dans visites
 *
 * @param chemin [in/out] chemin dans lequel enregistrer les étapes depuis le départ vers noeud
 * @param visites [in] liste des noeuds visités créée par l'algorithme de Dijkstra
 * @param noeud noeud vers lequel on veut construire le chemin depuis le départ
 */
static void construire_chemin_vers(liste_noeud_t* chemin,
                                   liste_noeud_t* visites,
                                   noeud_id_t noeud) {
    noeud_id_t precedent = precedent_noeud_liste(visites, noeud);
    if (precedent != NO_ID) {
        construire_chemin_vers(chemin, visites, precedent);
        float dist_precedent = distance_noeud_liste(visites, precedent);
        noeud_id_t precedent_du_precednt = precedent_noeud_liste(visites, precedent);
        inserer_noeud_liste(chemin, precedent, precedent_du_precednt, dist_precedent);
    }
}


float dijkstra(
    const struct graphe_t* graphe, 
    noeud_id_t source, noeud_id_t destination, 
    liste_noeud_t** chemin) {

    // Initialisation de la liste de noeuds
    liste_noeud_t* A_Visiter = creer_liste();
    liste_noeud_t* Visites = creer_liste();
    inserer_noeud_liste(A_Visiter, source, NO_ID, 0.0);

    while (!(est_vide_liste(A_Visiter))){

        //Chercher un noeud nc ∈ A_Visiter dont la distance associée est minimale
        noeud_id_t nc = min_noeud_liste(A_Visiter);

        //Ajouter nc dans Visités
        changer_noeud_liste(Visites,nc,precedent_noeud_liste(A_Visiter,nc),distance_noeud_liste(A_Visiter,nc));

        //Supprimer nc de A_Visiter
        supprimer_noeud_liste(A_Visiter,nc);

        noeud_id_t* voisins = NULL;
        noeuds_voisins(graphe,nc,voisins);
        int taille = nombre_voisins(graphe,nc);
        for (int i = 0; i < taille; i++) {
            noeud_id_t nv = voisins[i];
            //Calculer la distance totale du noeud de départ nd à nv
            float delta_prim = noeud_distance(graphe,nc,nv) + distance_noeud_liste(Visites,nc);
            //la distance actuelle de nd à nv
            float delta = distance_noeud_liste(A_Visiter,nc);
            if (delta_prim<delta) {
                changer_noeud_liste(A_Visiter,nc,nv,noeud_distance(graphe,nc,nv));
            }
        }
        free(voisins);
    }
    if (chemin != NULL) {
        *chemin = creer_liste();
        construire_chemin_vers(*chemin, Visites, destination);
        float dist_destination = distance_noeud_liste(Visites, destination);
        noeud_id_t prec_destination = precedent_noeud_liste(Visites, destination);
        inserer_noeud_liste(*chemin, destination, prec_destination, dist_destination);
    }

    float distance = distance_noeud_liste(Visites, destination);
    detruire_liste(&A_Visiter);
    detruire_liste(&Visites);

    return distance;
}



