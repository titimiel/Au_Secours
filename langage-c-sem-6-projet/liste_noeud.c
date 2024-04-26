#define _GNU_SOURCE
#include "liste_noeud.h"
#include <stdlib.h>
#include <math.h>


struct liste_noeud_t
{
    noeud_id_t noeud;
    float distance;
    noeud_id_t precedent;
    liste_noeud_t *suivant;
};

liste_noeud_t* creer_liste(){
    liste_noeud_t *liste = malloc(sizeof(*liste));

    liste->noeud = NO_ID;
    liste->distance=INFINITY;
    liste->precedent = NO_ID;
    liste->suivant = NULL;

    return liste;
}

void detruire_liste(liste_noeud_t** liste_ptr) {
    liste_noeud_t* courant = *liste_ptr;
    liste_noeud_t* suivant;
    while(courant!=NULL) {
        suivant = courant -> suivant;
        free(courant);
        courant=suivant;
    }
    *liste_ptr=NULL;
}

bool est_vide_liste(const liste_noeud_t* liste) {
    if ((liste->suivant == NULL)){
        return true;
    }
    return false;
}

bool contient_noeud_liste(const liste_noeud_t* liste, noeud_id_t noeud){
    if ((liste->suivant == NULL)){
        return false;
    }
    else if (liste->noeud == noeud){
        return true;
    }
    else {
        return contient_noeud_liste(liste->suivant,noeud);
    }
}

 bool contient_arrete_liste(const liste_noeud_t* liste, noeud_id_t source, noeud_id_t destination){
    if ((liste->suivant == NULL)){
        return false;
    }
    else if (liste->noeud == source){
        if ((liste->suivant == NULL)){
            return false;
        }
        else if (liste->suivant->noeud == destination){
            return true;
        }
        else {
            return contient_arrete_liste(liste->suivant,source,destination);
        }
    }
    else {
        return contient_arrete_liste(liste->suivant,source,destination);
    }
 }

float distance_noeud_liste(const liste_noeud_t* liste, noeud_id_t noeud){
    if ((liste->suivant == NULL)){
        return INFINITY;
    }
    else if (liste->noeud == noeud){
        return liste->distance;
    }
    else {
        return distance_noeud_liste(liste->suivant,noeud);
    }
}

noeud_id_t precedent_noeud_liste(const liste_noeud_t* liste, noeud_id_t noeud) {
    if ((liste->suivant == NULL)){
        return NO_ID;
    }
    else if (liste->noeud == noeud){
        return liste->precedent;
    }
    else {
        return precedent_noeud_liste(liste->suivant,noeud);
    }
}

noeud_id_t min_noeud_liste_rec(const liste_noeud_t* liste, noeud_id_t noeud_min) {
        if (noeud_min>liste->noeud) {
            noeud_min = liste->noeud;
        }
        if ((liste->suivant == NULL)){
            return noeud_min;
        }
        else {
            return min_noeud_liste_rec(liste->suivant,noeud_min);
        }
    }

noeud_id_t min_noeud_liste(const liste_noeud_t* liste){
    noeud_id_t min = NO_ID;
    return min_noeud_liste_rec(liste,min);
}

void inserer_noeud_liste(liste_noeud_t* liste, noeud_id_t noeud, noeud_id_t precedent, float distance) {
    if (liste->noeud == precedent) {
        liste_noeud_t *cellule = creer_liste();
        cellule->noeud = noeud;
        cellule->distance = distance;
        cellule->precedent = precedent;
        cellule->suivant = liste->suivant;
    }
    else if (liste->suivant == NULL) {
        NULL;
    }
    else {
        inserer_noeud_liste(liste->suivant,noeud,precedent,distance);
    }
}

void changer_noeud_liste(liste_noeud_t* liste, noeud_id_t noeud, noeud_id_t precedent, float distance) {
    if(liste->noeud == noeud) {
        liste->distance = distance;
        liste->precedent = precedent;
    }
    else if (liste->suivant == NULL) {
        inserer_noeud_liste(liste->suivant,noeud,NO_ID,distance);
    }
    else {
        changer_noeud_liste(liste->suivant,noeud,precedent,distance);
    }
}

void supprimer_noeud_liste(liste_noeud_t* liste, noeud_id_t noeud) {
    if(liste->noeud == noeud) {
        liste_noeud_t *aSupprimer = liste;
        liste = liste->suivant;
        free(aSupprimer);
    }
    else if (liste->suivant == NULL) {
        NULL;
    }
    else {
        supprimer_noeud_liste(liste->suivant,noeud);
    }
}
