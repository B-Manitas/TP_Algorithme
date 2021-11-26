
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then

typedef enum
{
    FALSE,
    TRUE
} bool;

typedef struct bloc_image
{
    bool toutnoir;
    struct bloc_image *fils[4];
} bloc_image;

typedef bloc_image *image;

image ConstruitBlanc()
{
    return NULL;
}

image ConstruitNoire()
{
    image img = (image)malloc(sizeof(bloc_image));
    img->toutnoir = TRUE;

    for (int i = 0; i < 3; i++)
        img->fils[i] = NULL;

    return img;
}

image ConstruitComposee(image ihg, image ihd, image ibg, image ibd)
{
    image img = (image)malloc(sizeof(bloc_image));
    img->toutnoir = FALSE;
    img->fils[0] = ihg;
    img->fils[1] = ihd;
    img->fils[2] = ibg;
    img->fils[3] = ibd;

    return img;
}

bool estBlanc(image img)
{
    if (img == NULL)
        return TRUE;

    else
    {
        if (img->toutnoir)
            return FALSE;

        else
            return estBlanc(img->fils[0]) &&
                   estBlanc(img->fils[1]) &&
                   estBlanc(img->fils[2]) &&
                   estBlanc(img->fils[3]);
    }
}

bool estNoire(image img)
{
    if (img == NULL)
        return FALSE;

    else
    {
        if (img->toutnoir)
            return TRUE;

        else
            return estNoire(img->fils[0]) &&
                   estNoire(img->fils[1]) &&
                   estNoire(img->fils[2]) &&
                   estNoire(img->fils[3]);
    }
}

image Copie(image img)
{
    if (img == NULL)
        return ConstruitBlanc();

    else
    {
        if (img->toutnoir)
            return ConstruitNoire();

        else
            return ConstruitComposee(Copie(img->fils[0]), Copie(img->fils[1]), Copie(img->fils[2]), Copie(img->fils[3]));
    }
}

bool tousFilsNul(image img)
{
    for (int i = 0; i < 3; i++)
        if (img->fils[0] != NULL)
            return FALSE;

    return TRUE;
}

void affichageNormaleBis(image img)
{
    if (img == NULL)
        printf("B");

    else
    {
        if (img->toutnoir)
            printf("N");

        else
        {
            printf("+");
            affichageNormaleBis(img->fils[0]);
            affichageNormaleBis(img->fils[1]);
            affichageNormaleBis(img->fils[2]);
            affichageNormaleBis(img->fils[3]);
        }
    }
}

void affichageNormale(image img)
{
    affichageNormaleBis(img);
    printf("\n");
}

void affichageProfondeurBis(image img, int profondeur)
{
    if (img == NULL)
        printf("B%d ", profondeur);

    else
    {
        if (img->toutnoir)
            printf("N%d ", profondeur);

        else
        {
            printf("+%d ", profondeur);
            profondeur += 1;
            affichageProfondeurBis(img->fils[0], profondeur);
            affichageProfondeurBis(img->fils[1], profondeur);
            affichageProfondeurBis(img->fils[2], profondeur);
            affichageProfondeurBis(img->fils[3], profondeur);
        }
    }
}

void affichageProfondeur(image img)
{
    int n = 0;
    affichageProfondeurBis(img, n);
    printf("\n");
}

void rendMemoire(image *img)
{
    if ((*img) != NULL)
    {
        for (int i = 0; i < 4; i++)
            rendMemoire(&((*img)->fils[i]));

        free(*img);
    }

    *img = NULL;
}

image Transforme(image img)
{
    if (img == NULL)
        return ConstruitNoire();

    else
    {
        if (img->toutnoir)
            return ConstruitBlanc();

        else
            return ConstruitComposee(Transforme(img->fils[0]), Transforme(img->fils[1]), Transforme(img->fils[2]), Transforme(img->fils[3]));
    }
}

float Aire(image img)
{
    if (img == NULL)
        return 0;

    else
    {
        if (img->toutnoir)
            return 1;

        else
            return (Aire(img->fils[0]) + Aire(img->fils[1]) + Aire(img->fils[2]) + Aire(img->fils[3])) / 4;
    }
}

bool UnionNoire(image img1, image img2)
{
    if (img1 == NULL AND img2 == NULL)
        return FALSE;

    else if ((img1 != NULL AND img1->toutnoir) OR(img2 != NULL AND img2->toutnoir))
        return TRUE;

    else if (img1 == NULL AND !img2->toutnoir)
        return UnionNoire(img1, img2->fils[0]) AND
            UnionNoire(img1, img2->fils[1]) AND
                UnionNoire(img1, img2->fils[2]) AND
                    UnionNoire(img1, img2->fils[3]);

    else if (img2 == NULL AND !img1->toutnoir)
        return UnionNoire(img2, img1->fils[0]) AND
            UnionNoire(img2, img1->fils[1]) AND
                UnionNoire(img2, img1->fils[2]) AND
                    UnionNoire(img2, img1->fils[3]);

    else
        return UnionNoire(img1->fils[0], img2->fils[0]) AND
            UnionNoire(img1->fils[1], img2->fils[1]) AND
                UnionNoire(img1->fils[2], img2->fils[2]) AND
                    UnionNoire(img1->fils[3], img2->fils[3]);
}

void Negatif(image *img)
{
    if ((*img) == NULL)
        *img = ConstruitNoire();

    else if ((*img)->toutnoir)
        rendMemoire(img);

    else
        for (int i = 0; i < 4; i++)
            Negatif(&((*img)->fils[i]));
}

image CreateImageStr(char *str)
{
    if (*str == '+')
        return ConstruitComposee(CreateImageStr(str + 1), CreateImageStr(str + 2), CreateImageStr(str + 3), CreateImageStr(str + 4));

    else if (*str == 'N')
        return ConstruitNoire();

    else
        return ConstruitBlanc();
}

image Lecture()
{
    char str[100];
    printf("\nEnter your quadtree.\n=> ");
    scanf("%s", str);

    return CreateImageStr(str);
}

int BisCompteSousImageGris(image img)
{
    float aire = Aire(img);

    if (aire >= 1. / 3 && aire <= 2. / 3)
        return 1;

    else
        return 0;
}

int CompteSousImagegrise(image img)
{
    if (img == NULL)
        return BisCompteSousImageGris(img);

    else
        return BisCompteSousImageGris(img) +
               CompteSousImagegrise(img->fils[0]) +
               CompteSousImagegrise(img->fils[1]) +
               CompteSousImagegrise(img->fils[2]) +
               CompteSousImagegrise(img->fils[3]);
}

int main()
{
    image noire = ConstruitNoire();
    image blanc = ConstruitBlanc();

    image img_aff = ConstruitComposee(
        ConstruitNoire(),
        ConstruitComposee(ConstruitBlanc(), ConstruitBlanc(), ConstruitNoire(), ConstruitBlanc()),
        ConstruitBlanc(),
        ConstruitComposee(ConstruitNoire(),
                          ConstruitComposee(ConstruitNoire(), ConstruitNoire(), ConstruitBlanc(),
                                            ConstruitComposee(ConstruitNoire(), ConstruitBlanc(), ConstruitNoire(),
                                                              ConstruitNoire())),
                          ConstruitBlanc(),
                          ConstruitNoire()));

    image img_1 = ConstruitComposee(
        ConstruitComposee(ConstruitNoire(), ConstruitNoire(), ConstruitNoire(), ConstruitBlanc()),
        ConstruitComposee(ConstruitBlanc(), ConstruitBlanc(), ConstruitBlanc(), ConstruitNoire()),
        ConstruitNoire(), ConstruitBlanc());

    image img_2 = ConstruitComposee(ConstruitNoire(), ConstruitBlanc(), ConstruitNoire(),
                                    ConstruitComposee(ConstruitNoire(), ConstruitBlanc(), ConstruitNoire(), ConstruitBlanc()));

    image img_union_1 = ConstruitComposee(
        ConstruitComposee(ConstruitNoire(), ConstruitBlanc(), ConstruitNoire(), ConstruitBlanc()),
        ConstruitComposee(ConstruitBlanc(), ConstruitNoire(), ConstruitNoire(), ConstruitBlanc()),
        ConstruitBlanc(),
        ConstruitComposee(ConstruitNoire(), ConstruitNoire(), ConstruitBlanc(), ConstruitBlanc()));

    image img_union_2 = ConstruitComposee(
        ConstruitNoire(),
        ConstruitComposee(ConstruitNoire(), ConstruitBlanc(), ConstruitNoire(), ConstruitNoire()),
        ConstruitNoire(),
        ConstruitComposee(ConstruitNoire(), ConstruitBlanc(), ConstruitNoire(), ConstruitBlanc()));

    image img_grise_1 = ConstruitComposee(
        ConstruitNoire(),
        ConstruitComposee(ConstruitBlanc(), ConstruitNoire(), ConstruitBlanc(), ConstruitBlanc()),
        ConstruitBlanc(),
        ConstruitComposee(ConstruitNoire(), ConstruitBlanc(), ConstruitBlanc(), ConstruitBlanc()));

    image img_grise_2 = ConstruitComposee(
        ConstruitBlanc(),
        ConstruitNoire(),
        ConstruitComposee(ConstruitNoire(),
                          ConstruitComposee(ConstruitBlanc(), ConstruitNoire(), ConstruitBlanc(), ConstruitBlanc()),
                          ConstruitBlanc(),
                          ConstruitComposee(ConstruitNoire(),
                                            ConstruitBlanc(),
                                            ConstruitBlanc(),
                                            ConstruitBlanc())),
        ConstruitComposee(
            ConstruitNoire(),
            ConstruitComposee(ConstruitBlanc(), ConstruitNoire(), ConstruitBlanc(), ConstruitBlanc()),
            ConstruitBlanc(),
            ConstruitComposee(ConstruitNoire(), ConstruitNoire(), ConstruitBlanc(), ConstruitBlanc())));

    assert(estNoire(noire));
    assert(estBlanc(blanc));
    assert(!estNoire(blanc));
    assert(!estBlanc(noire));

    assert(!UnionNoire(img_union_1, img_union_2));

    printf("Test de la fonction affichage.\n");
    affichageNormale(noire);
    affichageNormale(blanc);
    affichageNormale(img_1);
    affichageNormale(img_aff);
    affichageProfondeur(img_aff);

    affichageProfondeur(noire);
    affichageProfondeur(blanc);
    affichageProfondeur(img_1);

    printf("\nAffichage de la fonction Copie.\n");
    affichageNormale(Copie(noire));
    affichageNormale(Copie(blanc));

    image img_1_rev = Transforme(img_1);
    affichageNormale(img_1_rev);

    printf("Aire(img_2): %f\n", Aire(img_2));

    rendMemoire(&img_1);

    printf("\nTest de la fonction Negatif.\n");
    affichageNormale(img_2);
    Negatif(&img_2);
    affichageNormale(img_2);

    // printf("\nTest de la fonction Lecture.\n");
    // affichageNormale(Lecture());

    assert(CompteSousImagegrise(img_grise_1) == 1);
    assert(CompteSousImagegrise(img_grise_2) == 4);

    return 0;
}