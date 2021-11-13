/**
 * Devoir Maison Algorithlique: Partie 2
 * Manitas Bahri, LDD2 IM2
 */

#include "entete.c"
#include <assert.h>

// Exercice 1
/** 
 * @brief Fonction zeroEnDeuxiemePosition.
 * 
 * @param l Une liste.
 * @return Renvoie vrai ssi la liste possède un 0 en deuxième position. 
 * Sinon renvoie faux.
 */
bool zeroEnDeuxiemePosition(Liste l)
{
    return !estVide(l) && !estVide(suite(l)) && premier(suite(l)) == 0;
}

// Exercice 2
/** 
 * @brief Fonction queDesZeros.
 * 
 * @param l Une liste.
 * @return Renvoie vrai ssi tout les éléments dans cette liste valent 0. 
 * Sinon renvoie faux.
 */
bool queDesZeros(Liste l)
{
    if (estVide(l))
        return TRUE;
    else
        return premier(l) == 0 && queDesZeros(suite(l));
}

// Exercice 3.1
/** 
 * @brief Fonction Compte0Initiaux version récursive
 * 
 * @param l Une liste.
 * @return Renvoie le nombre de 0 qui se trouvent en début de liste
 */
int compte0InitiauxRec(Liste l)
{
    if (estVide(l) || premier(l) != 0)
        return 0;

    else
        return 1 + compte0InitiauxRec(suite(l));
}

// Exercice 3.2
/** 
 * @brief Fonction Compte0Initiaux en version itérative.
 * 
 * @param l Une liste.
 * @return Renvoie le nombre de 0 qui se trouvent en début de liste.
 */
int compte0InitiauxIter(Liste l)
{
    int n = 0;
    Liste l_iter = l;

    while (!estVide(l_iter) && premier(l_iter) == 0)
    {
        n++;
        l_iter = suite(l_iter);
    }

    return n;
}

// Exercice 3.3
/** 
 * @brief La sous-fonction de la fonction récursive Compte0InitiauxIn.
 * 
 * @param l Une liste.
 * @param acc Un accumultateur.
 * @return Renvoie le nombre de 0 qui se trouvent en début de liste.
 */
int compte0InitiauxRecInSub(Liste l, int acc)
{
    if (estVide(l) || premier(l) != 0)
        return acc;

    else
        return compte0InitiauxRecInSub(suite(l), acc + 1);
}

/** 
 * @brief Fonction Compte0InitiauxIn en version récursive avec un paramètre in.
 * 
 * @param l Une liste.
 * @return Renvoie le nombre de 0 qui se trouvent en début de liste.
 */
int compte0InitiauxRecIn(Liste l)
{
    return compte0InitiauxRecInSub(l, 0);
}

// Exercice 3.4
/** 
 * @brief La sous-fonction de la fonction récursive Compte0InitiauxInout.
 * 
 * @param l Une liste.
 * @param acc Un pointeur de l'accumultateur.
 * @return Renvoie le nombre de 0 qui se trouvent en début de liste.
 */
void compte0InitiauxRecInoutSub(Liste l, int *acc)
{
    if (!estVide(l) && premier(l) == 0)
    {
        *acc += 1;
        compte0InitiauxRecInoutSub(suite(l), acc);
    }
}

/** 
 * @brief Fonction compte0InitiauxRecInout en version récursive avec un paramètre inout.
 * 
 * @param l Une liste.
 * @return Renvoie le nombre de 0 qui se trouvent en début de liste.
 */
int compte0InitiauxRecInout(Liste l)
{
    int n = 0;
    compte0InitiauxRecInoutSub(l, &n);
    return n;
}

// Exercice 4
/**
 * @brief Fonction intersectionTriee en version récursive.
 * 
 * @param l1 Une liste triée.
 * @param l1 Une liste triée.
 * @return Renvoie la liste triée des éléments communs aux deux listes.
 */
Liste intersectionTriee(Liste l1, Liste l2)
{
    if (estVide(l1))
        return l1;
    else if (estVide(l2))
        return l2;

    else
    {
        if (premier(l1) == premier(l2))
            return ajoute(premier(l1), intersectionTriee(suite(l1), suite(l2)));

        else if (premier(l1) < premier(l2))
            return intersectionTriee(suite(l1), l2);

        else
            return intersectionTriee(l1, suite(l2));
    }
}

// Exercice 5
/**
 * @brief Fonction elimineKpremiersX.
 * 
 * @param l1 Une liste triée.
 * @param l1 Une liste triée.
 * @return Renvoie la liste triée des éléments communs aux deux listes.
 */
void elimineKpremiersX(Liste *l, int k, int x)
{
    if (!estVide(*l) AND k > 0)
    {
        if (x == premier(*l))
        {
            depile(l);
            elimineKpremiersX(l, k - 1, x);
        }

        else
            elimineKpremiersX(&((*l)->suivant), k, x);
    }
}

// Exercice 5
/**
 * @brief Fonction elimineKpremiersX.
 * 
 * @param l1 Une liste triée.
 * @param l1 Une liste triée.
 * @return Renvoie la liste triée des éléments communs aux deux listes.
 */
void elimineKdernierXBis(Liste *l, int *cpt, int x, bool *vu)
{
    if (estVide(*l))
        *vu = FALSE;

    else
    {
        elimineKdernierXBis(&((*l)->suivant), cpt, x, vu);

        *vu = (*cpt <= 0);
        if (premier(*l) == x AND !(*vu))
        {
            depile(l);
            *cpt = *cpt - 1;
        }
    }
}

void elimineKdernierX(Liste *l, int k, int x)
{
    bool vu;
    int cpt = k;
    elimineKdernierXBis(l, &cpt, x, &vu);
}

// Exercice 7
/* Déclaration de la structure liste de liste d'entier. */
typedef struct LDLStruct LDLStruct;
struct LDLStruct
{
    Liste element;
    struct LDLStruct *suivant;
};
typedef LDLStruct *LDL;

int nombreMalloc = 0;

/**
 * @brief Teste si une liste de liste est vide.
 * 
 * @param ldl Une liste de liste.
 * @return Renvoie TRUE si la liste de liste est vide. Sinon FALSE.
 */
bool estVideLDL(LDL ldl)
{
    return ldl == NULL;
}

/**
 * @brief Initialise une liste de liste vide.
 * 
 * @param ldl Une liste de liste.
 */
void initVideLDL(LDL *ldl)
{
    *ldl = NULL;
}

/** 
 * @brief Ajoute une liste dans une liste de liste.
 * 
 * @param l Une liste.
 * @param ldl Une liste de liste.
 * @return Renvoie la liste de liste ldl avec la liste l en haut de la pile.
*/
LDL ajouteLDL(Liste l, LDL ldl)
{
    LDL tmp = (LDL)malloc(sizeof(LDLStruct));
    tmp->element = l;
    tmp->suivant = ldl;
    nombreMalloc += 1;

    return tmp;
}

/**
 * @brief Première liste de la liste de liste ldl.
 * 
 * @param ldl Une liste de liste
 * @return Le premier élément de la liste de liste. 
 */
Liste premierLDL(LDL ldl)
{
    return ldl->element;
}

/**
 * @brief Suite d'une liste de liste.
 * 
 * @param ldl Liste d'une liste.
 * @return Renvoie la liste de liste sans son premier élément.
 */
LDL suiteLDL(LDL ldl)
{
    return ldl->suivant;
}

/**
 * @brief Concatène deux listes de liste.
 * 
 * @param ldl1 Une liste de liste.
 * @param ldl2 Une liste de liste.
 * @return Renvoie la liste de liste de la concaténation de ldl1 et ldl2
 */
LDL concatLDL(LDL ldl1, LDL ldl2)
{
    if (estVideLDL(ldl1))
        return ldl2;

    else
        return ajouteLDL(premierLDL(ldl1), concatLDL(suiteLDL(ldl1), ldl2));
}

/**
 * @brief Fonction Ajoute En Tete Toute Liste.
 * 
 * @param x Un entier.
 * @param ldl Une liste de liste.
 * @return Renvoie une liste de liste avec x en tête de toutes les listes.
 */
LDL AETTL(int x, LDL ldl)
{
    if (estVideLDL(ldl))
        return ldl;

    else
        return ajouteLDL(ajoute(x, ldl->element), AETTL(x, suiteLDL(ldl)));
}

/**
 * @brief Fonction Ajoute Toute Position.
 * 
 * @param x Un entier.
 * @param l Une liste.
 * @return Renvoie la liste de liste avec x à toute les positions dans la liste l.
 */
LDL ATP(int x, Liste l)
{
    if (estVide(l))
    {
        LDL tmp;
        initVideLDL(&tmp);
        return ajouteLDL(ajoute(x, l), tmp);
    }

    else
        return ajouteLDL(
            ajoute(x, l),
            AETTL(premier(l), ATP(x, suite(l))));
}

/**
 * Fonction Ajoute Toute Liste Toute Position.
 * @param x Un entier.
 * @param l Une liste de liste.
 * @return Renvoie la liste avec x à toute les positions dans les listes.
 */
LDL ATLTP(int x, LDL ldl)
{
    if (estVideLDL(ldl))
        return ldl;

    else
        return concatLDL(ATP(x, premierLDL(ldl)), ATLTP(x, suiteLDL(ldl)));
}

/**
 * @brief Fonction permutation.
 * 
 * @param n Un entier.
 * @return Renvoie la liste des permutations de [1...n].
 */
LDL permutation(int n)
{
    if (n == 0)
    {
        Liste l;
        initVide(&l);

        LDL ldl;
        initVideLDL(&ldl);
        ldl = ajouteLDL(l, ldl);

        return ldl;
    }

    else
        return ATLTP(n, permutation(n - 1));
}

/**
 * Commentaire de la fonction permutation:
 * Nous remarquons qu'il y a beaucoup de copie de liste dans nos fonctions.
 * Il aurait été plus optimisé si nous passions nos listes en inout dans les arguments des sous-fonctions 
 * de permutation. Notamment, en utlisant des pointeurs.
 * Cela permettrait de rendre beaucoup plus efficace notre programme, en allouant moins de mémoire.
 */

// Exerice 8
/*Déclaration de la structure File : version 1 du poly. */
typedef struct FileV1Struct
{
    int nombre;
    struct FileV1Struct *entree;
    struct FileV1Struct *sortie;
} FileV1Struct;
typedef FileV1Struct *FileV1;

void ajouteFileV1(int x, FileV1 **f)
{
    FileV1 tmp = (FileV1)malloc(sizeof(FileV1Struct));
    tmp->nombre = x;
    tmp->sortie = NULL;

    if (*f == NULL)
        *f = &tmp;

    else
        (**f)->entree = tmp;
}

void sortieV1(int *x, FileV1 **f)
{
    if (*f != NULL)
    {
        FileV1 *tmp = &((**f)->sortie);
        (**f)->entree = (*tmp)->sortie;
        *x = (**f)->nombre;
        free(tmp);
    }
}

/*Déclaration de la structure File : version 2 du poly. */
typedef struct FileV2Struct
{
    int nombre;
    struct FileV2Struct *suivant;
} FileV2Struct;
typedef FileV2Struct *FileV2;

void ajouteFileV2(int x, FileV2 **f)
{

    FileV2 tmp = (FileV2)malloc(sizeof(FileV2Struct));
    tmp->nombre = x;
    tmp->suivant = NULL;

    if (*f == NULL)
        *f = &tmp;

    else
    {
        tmp->suivant = (**f)->suivant;
        (**f)->suivant = tmp;
    }
}

void sortirV2(int *x, FileV2 **f)
{
    if (*f != NULL)
    {
        FileV2 *tmp = &((**f)->suivant);
        (**f)->suivant = (*tmp)->suivant;
        *x = (**f)->nombre;
        free(tmp);
    }
}

int main()
{
    Liste l0, l1, l2, l3, l4, l5;

    initVide(&l0);
    initVide(&l1);
    initVide(&l2);
    initVide(&l3);
    initVide(&l4);
    initVide(&l5);

    empile(0, &l0);
    empile(4, &l0);

    empile(5, &l1);
    empile(4, &l1);
    empile(3, &l1);
    empile(0, &l1);
    empile(2, &l1);

    empile(5, &l2);
    empile(4, &l2);
    empile(0, &l2);
    empile(2, &l2);
    empile(0, &l2);

    empile(0, &l3);
    empile(0, &l3);
    empile(0, &l3);

    empile(2, &l4);
    empile(2, &l4);
    empile(0, &l4);
    empile(0, &l4);
    empile(0, &l4);

    empile(0, &l5);
    empile(1, &l5);
    empile(0, &l5);

    assert(zeroEnDeuxiemePosition(l0));
    assert(zeroEnDeuxiemePosition(l1));
    assert(zeroEnDeuxiemePosition(l3));
    assert(!zeroEnDeuxiemePosition(l2));

    assert(!queDesZeros(l1));
    assert(!queDesZeros(l2));
    assert(queDesZeros(l3));

    assert(compte0InitiauxRec(l2) == 1);
    assert(compte0InitiauxRec(l3) == 3);
    assert(compte0InitiauxRec(l4) == 3);
    assert(compte0InitiauxRec(l5) == 1);

    assert(compte0InitiauxIter(l2) == 1);
    assert(compte0InitiauxIter(l3) == 3);
    assert(compte0InitiauxIter(l4) == 3);
    assert(compte0InitiauxIter(l5) == 1);

    assert(compte0InitiauxRecIn(l2) == 1);
    assert(compte0InitiauxRecIn(l3) == 3);
    assert(compte0InitiauxRecIn(l4) == 3);
    assert(compte0InitiauxRecIn(l5) == 1);

    assert(compte0InitiauxRecInout(l2) == 1);
    assert(compte0InitiauxRecInout(l3) == 3);
    assert(compte0InitiauxRecInout(l4) == 3);
    assert(compte0InitiauxRecInout(l5) == 1);

    nombreMalloc = 0;
    LDL ldl = permutation(5);
    printf("Nombre de malloc effectué dans la fonction permutation: %d\n", nombreMalloc);

    return 0;
}
