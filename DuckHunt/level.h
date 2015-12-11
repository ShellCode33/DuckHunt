#ifndef LEVEL_H
#define LEVEL_H

/*

Chaque niveau est représenté par un tableau de 3 cases contenant le nombre de chaque type de canard qu'il y aura:
int level[] = {nb_type0, nb_type1, nb_type2};

*/

#define NB_LEVEL 10

int levels[NB_LEVEL][3]  {
                    {5, 3, 2},
                    {4, 4, 2},
                    {4, 3, 3},
                    {3, 4, 3},
                    {2, 5, 3},
                    {2, 4, 4},
                    {1, 5, 4},
                    {1, 4, 5},
                    {0, 5, 5},
                    {0, 0, 10}
                };

#endif
