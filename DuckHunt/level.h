#ifndef LEVEL_H
#define LEVEL_H

/*

Chaque niveau est représenté par un tableau de 3 cases contenant le nombre de chaque type de canard qu'il y aura:
int level[] = {nb_type0, nb_type1, nb_type2};

*/

#define NB_LEVEL 5

const int levels[NB_LEVEL][3]  {
                    {4, 4, 2},
                    {3, 3, 4},
                    {2, 2, 6},
                    {1, 1, 8},
                    {0, 0, 10}
                };

#endif
