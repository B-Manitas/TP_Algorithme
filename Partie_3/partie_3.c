
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

void rendMemoire(image img)
{
    if (img != NULL)
    {
        for (int i = 0; i < 3; i++)
            rendMemoire(img->fils[i]);

        free(img);
    }
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

int main()
{
    image noire = ConstruitNoire();
    image blanc = ConstruitBlanc();

    image img_1 = ConstruitComposee(
        ConstruitComposee(ConstruitNoire(), ConstruitNoire(), ConstruitNoire(), ConstruitBlanc()),
        ConstruitComposee(ConstruitBlanc(), ConstruitBlanc(), ConstruitBlanc(), ConstruitNoire()),
        ConstruitNoire(), ConstruitBlanc());

    image img_2 = ConstruitComposee(ConstruitNoire(), ConstruitBlanc(), ConstruitNoire(),
                                    ConstruitComposee(ConstruitNoire(), ConstruitBlanc(), ConstruitNoire(), ConstruitBlanc()));

    assert(estNoire(noire));
    assert(estBlanc(blanc));
    assert(!estNoire(blanc));
    assert(!estBlanc(noire));

    printf("Test de la fonction affichage.\n");
    affichageNormale(noire);
    affichageNormale(blanc);
    affichageNormale(img_1);

    printf("\nAffichage de la fonction Copie.\n");
    affichageNormale(Copie(noire));
    affichageNormale(Copie(blanc));

    image img_1_rev = Transforme(img_1);
    affichageNormale(img_1_rev);

    printf("Aire(img_2): %f\n", Aire(img_2));

    rendMemoire(img_1);

    return 0;
}