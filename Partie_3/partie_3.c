
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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
            return 
                estBlanc(img->fils[0]) && 
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
            return 
                estNoire(img->fils[0]) && 
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
            return 
                ConstruitComposee(Copie(img->fils[0]), Copie(img->fils[1]), Copie(img->fils[2]), Copie(img->fils[3]));
    }
}

bool tousFilsNul(image img)
{
    for (int i = 0; i < 3; i++)
        if(img->fils[0] != NULL)
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

int main()
{
    image noire = ConstruitNoire();
    image blanc = ConstruitBlanc();

    image img_NNNB = ConstruitComposee(ConstruitComposee(noire, noire, noire, blanc), ConstruitComposee(blanc, blanc, blanc, noire), noire, blanc);

    assert(estNoire(noire));
    assert(estBlanc(blanc));
    assert(!estNoire(blanc));
    assert(!estBlanc(noire));
    
    printf("Test de la fonction affichage.\n");
    affichageNormale(noire);
    affichageNormale(blanc);
    affichageNormale(img_NNNB);

    printf("\nAffichage de la fonction Copie.\n");
    affichageNormale(Copie(noire));
    affichageNormale(Copie(blanc));


    return 0;
}