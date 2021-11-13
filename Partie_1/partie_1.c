/**
 * Devoir Maison Algorithlique: Partie 1
 * Manitas Bahri, LDD2 IM2
 */

#include "entete.c"
#include <math.h>
#include <time.h>

/** Renvoie la valeur de exp(1). */
double e()
{
    int n = 1;
    long int n_fact = 1;
    long double result = 1;

    while (n <= 60)
    {
        n_fact *= n;
        result += 1./n_fact;
        n++;
    }

    return result;
}

/**
 * Calcul le flottant x à la puissance n.
 * @param x Un réel.
 * @param n Un entier relatif.
 * @return Renvoie le float x à la puissance n.
*/
float puissance_f(float x, int n)
{
    if (n == 0)
        return 1;
        
    else if (n > 0)
        return x * puissance_f(x, n - 1);

    else
        return puissance_f(1/x, -n);
}

/**
 * Calcul le double x à la puissance n.
 * @param x Un réel.
 * @param n Un entier relatif.
 * @return Renvoie le double de x à la puissance n.
*/
double puissance_d(double x, int n)
{
    if (n == 0)
        return 1;

    else if (n > 0)
        return x * puissance_d (x, n - 1);

    else
        return puissance_d(1/x, -n);
}

/**
 * Sous-fonction de puissance_term.  
 * @param x Un réel.
 * @param k Un entier positif.
 * @param acc L'accumulateur.
 * @param estPositive La puissance est positive.
 * @return Renvoie x à la puissance n.
*/
double puissance_term_rec(double x, int k, double acc, bool estPositive)
{
    if (k == 0)
        return estPositive ? acc : 1./acc;

    else
        return puissance_term_rec(x, k - 1, x * acc, estPositive);
}

/**
 * Calcul la valeur de x à la puissance n. 
 * Algorithme récursif terminal.
 * @param x Un réel.
 * @param n Un entier relatif.
 * @return Renvoie x à la puissance n.
*/
double puissance_term(double x, int n)
{
    puissance_term_rec(x, abs(n), 1, n > 0);
}

/**
 * Calcul la valeur de x à la puissance n. 
 * Algorithme itératif de compléxité n.
 * @param x Un réel.
 * @param n Un entier relatif.
 * @return Renvoie x à la puissance n.
*/
double puissance(double x, int n)
{
    double res = 1;
    for (int i = 1; i <= abs(n); i++)
        res *= x;
    
    return n>0 ? res : 1./res;
}

/**
 * Calcul la valeur de x à la puissance n. 
 * Algorithme itératif de compléxité log à base 2 de n.
 * @param x Un réel.
 * @param n Un entier relatif.
 * @return Renvoie x à la puissance n.
*/
double puissance_2(double x, int n)
{
    double y = x;
    double res = 1;
    int k = abs(n);

    while (k != 0)
    {
        if (k%2 == 1) res = res * y;

        k = k / 2;
        y = y * y;
    }
    
    return n>0 ? res : 1./res;
}

/**
 * Fonction Ackerman en version récursive.
 * @param n Un entier.
 * @param m Un entier.
 * @return Renvoie le résultat de la fonction ackerman.
 */
int ackerman_rec(int n, int m){
    if(n == 0)
        return m + 1;
    
    else if(m == 0)
        return ackerman_rec(n - 1, 1);
    
    else
        return ackerman_rec(n - 1, ackerman_rec(n, m - 1));    
}

/**
 * Fonction Ackerman en version itérative.
 * @param n Un entier.
 * @param m Un entier.
 * @return Renvoie le résultat de la fonction ackerman.
 */
int ackerman_it(int n, int m){
    if (n == 0)
        return m + 1;

    else {
        int r = 1;

        for (int i = 1; i <= m + 1; i++)
            r = ackerman_it(n - 1, r);

        return r;
    }
}

/**
 * Exerice 4 : Pseudo-Code Xn
 * Xn(entier: n)
 *  Si n = 0: Alors renvoie 1.
 *  Sinon:
 *      xn_prev := Xn(n - 1)
 *      renvoie xn_prev + 1./xn_prev
 */

/**
 * Fonction Xn en version récursive.
 * @param n Un entier.
 * @return Renvoie la valeur de Xn.
 */
double xn_rec(int n){
    if (n == 0)
        return 1;
    
    else
    {
        double xn_prev = xn_rec(n - 1);
        return xn_prev + 1./xn_prev;
    }
}

/**
 * Fonction Xn en version itérative.
 * @param n Un entier.
 * @return Renvoie la valeur de Xn.
 */
double xn_it(int n){
    double xn = 1;
    
    for (int i = 0; i < n; i++)
    {
        double xn_prev = xn;
        xn = xn_prev + 1./xn_prev;
    }

    return xn;
}

int main()
{
    // Exercice n°1
    double e_1 = e();
    printf("_____________\n");
    printf("\nExerice n°1\n");
    printf("exp(1) = %.10f\n", e_1);

    // Exercise n°2
    printf("_____________\n");
    printf("\nExerice n°2\n");

    for (int k = 0; k < 6; k++)
    {

        clock_t start_time_d = clock();
        double puissance_10_d = puissance_d(10, k);
        double x_d = 1 + 1/puissance_10_d;
        double result_d = puissance_d(x_d, puissance_10_d);
        clock_t end_time_d = clock();

        clock_t start_time_f = clock();
        float puissance_10_f = puissance_f(10, k);
        float x_f = 1 + 1/puissance_10_f;
        double result_f = puissance_d(x_f, puissance_10_f);
        clock_t end_time_f = clock();

        double execution_time_d = (double)(end_time_d - start_time_d)*1000.0 / CLOCKS_PER_SEC;
        double execution_time_f = (double)(end_time_f - start_time_f)*1000.0 / CLOCKS_PER_SEC;

        printf("[DOUBLE] k=%d => %.10f | Erreur: %.8f | Memoire: %ld | Temps: %.5f ms\n", k, result_d, fabs(e_1 - result_d), sizeof(result_d), execution_time_d);
        printf("[FLOAT]  k=%d => %.10f | Erreur: %.8f | Memoire: %ld | Temps: %.5f ms\n\n", k, result_f, fabs(e_1 - result_f), sizeof(result_d), execution_time_f);
    }

    // Exercise n°3
    printf("_____________\n");
    printf("\nExerice n°3\n");
    for (int i = 0; i < 5; i++)
    {
        printf("[Récursive] A(%d, %d) = %d\n", i, 0, ackerman_rec(i, 0));
        printf("[Itérative] A(%d, %d) = %d\n\n", i, 0, ackerman_it(i, 0));
    }

    // Exercise n°4
    printf("_____________\n");
    printf("\nExerice n°4\n");
    printf("[Récursive] Xn(100) = %.10f\n", xn_rec(100));
    printf("[Itérative] Xn(100) = %.10f\n\n", xn_it(100));
}
