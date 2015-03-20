/**
* @file     prob24.c
* @author   Stavros Vagionitis
* @date     20 Mar 2015
* @brief    [Problem 24 in Project Euler](https://projecteuler.net/problem=24)
*           Lexicographic permutations
*           ==========================
*           A permutation is an ordered arrangement of objects. For example,
*           3124 is one possible permutation of the digits 1, 2, 3 and 4. If all of
*           the permutations are listed numerically or alphabetically, we call it
*           lexicographic order. The lexicographic permutations of 0, 1 and 2 are:
*
*           012   021   102   120   201   210
*
*           What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9?
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/**
 * \brief Print in stdout the elements of the array.
 *
 * \param   arr     The array to print.
 * \param   sz      The size of the array.
 */
void print_array(uint64_t arr[], uint64_t sz)
{
    for (uint64_t i = 0;i<sz;i++)
        fprintf(stdout, "%ju", arr[i]);
    fprintf(stdout, "\n");
}

/**
 * \brief Swap the elements of an array
 *
 * \param   arr     The array to print.
 * \param   i       The one position to swap.
 * \param   j       The other position to swap.
 */
void swap_array(uint64_t arr[], uint64_t i, uint64_t j)
{
    arr[i] ^= arr[j];
    arr[j] ^= arr[i];
    arr[i] ^= arr[j];
}

/**
 * \brief Get the next lexigographic permutation of an array.
 *        The algorithm used is known as Fischer and Krause algorithm.
 *        A good explanation here
 *        http://www.nayuki.io/page/next-lexicographical-permutation-algorithm
 *
 * \param   arr     The array to print.
 * \param   sz      The size of the array.
 */
uint8_t next_perm(uint64_t arr[], uint64_t sz)
{
    uint64_t i = sz - 1;
    uint64_t j = i;
    uint64_t k = j;

    while (i && arr[i - 1] >= arr[i])
        --i;

    if (!i)
        return 0;

    while (arr[j] <= arr[i - 1])
        --j;

    swap_array(arr, i - 1, j);

    while (i < k)
    {
        swap_array(arr, i, k);

        i++;k--;
    }

    return 1;
}

/**
 * \brief Calculate and print all the lexicographic permutations
 *        of an array.
 *
 * \param   arr     The array to permute
 * \param   sz      The size of the array.
 * \return  1 if everything is ok, 0 if not.
 */
uint8_t lexico_perm(uint64_t arr[], uint64_t sz)
{
    uint64_t c = 0;

    do
    {
        fprintf(stdout, "%ju. ", c);
        print_array(arr, sz);
        c++;

    }while(next_perm(arr, sz));

    return 1;
}

/**
 * \brief The solution using a naive way.
 *        The array is populated by it's index.
 *        For example a size 3, 5 and 7 array would be
 *
 *        {0, 1, 2}
 *        {0, 1, 2, 3, 4}
 *        {0, 1, 2, 3, 4, 5, 6}
 *
 *
 * \param   num  The size of the array..
 * \return  1 if everything is ok, 0 if not.
 */
uint8_t solution1(uint64_t num)
{
    uint64_t sz = num;

    uint64_t *arr = calloc(sz, sizeof(uint64_t));
    if (arr == NULL)
    {
        fprintf(stderr, "%s:%d Mem Alloc failed\n", __func__, __LINE__);
        return 0;
    }

    // Populate the array
    for (uint64_t i = 0;i<sz;i++)
        arr[i] = i;

    lexico_perm(arr, sz);

    if (arr)
        free(arr);

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
    fprintf(stdout, "%s <Size of the array.>\n", argv0);
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
