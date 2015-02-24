/**
* @file     prob5.c
* @author   Stavros Vagionitis
* @date     xx Feb 2015
* @brief    [Problem 5 in Project Euler](https://projecteuler.net/problem=5)
*           Smallest multiple
*           =================
*           2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.
*
*           What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/**
 * \brief Check if a number is multiple of another number.
 *
 * \param   num     The number to check if it's multiple
 * \param   mult    The multiple to be checked.
 * \return  1 if it's multiple, 0 if not.
 */
uint8_t isMultiple(uint64_t num, uint64_t mult)
{
    if (num % mult == 0)
        return 1;
    else
        return 0;
}

/**
 * \brief The solution using a naive way.
 *
 * \param   num  The max number that are going to check if evenly divisible.
 * \return  1 if everything is ok, 0 if not.
 */
uint8_t solution1(uint64_t num)
{
    uint64_t i = 1;
    uint8_t isDivisible = 1;

    while(1)
    {
        isDivisible = 1;

        for(uint64_t j = 1;j<=num;j++)
            if(!isMultiple(i, j))
            {
                isDivisible = 0;
                break;
            }

        if(isDivisible)
            break;

        i++;
    }

    fprintf(stdout, "Smallest number evenly divisible: %ju\n", i);

    return 1;
}

/**
 * \brief Usage of this program.
 *
 * \param   argv0   The first argument string which is the current executable.
 * \return  -1.
 */
int usage(char *argv0)
{
    fprintf(stdout, "%s <Max number to check.>\n", argv0);
    return -1;
}


int main(int argc, char *argv[])
{
    if (argc != 2)
        return usage(argv[0]);

    uint64_t num = strtoull(argv[1], NULL, 10);

    solution1(num);

    return 0;
}
