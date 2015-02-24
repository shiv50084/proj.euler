/**
* @file     prob4.c
* @author   Stavros Vagionitis
* @date     xx Feb 2015
* @brief    [Problem 4 in Project Euler](https://projecteuler.net/problem=4)
*           Largest palindrome product
*           ==========================
*           A palindromic number reads the same both ways. The largest palindrome
*           made from the product of two 2-digit numbers is 9009 = 91 × 99.
*
*           Find the largest palindrome made from the product of two 3-digit numbers.
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/**
 * \brief Check if the number is palindrome.
 *
 * \param   num     The number to check if it's palindrome.
 * \return  1 if it's palindrome, 0 if not.
 */
uint8_t isPalindrome(const uint64_t num)
{
    uint64_t n = num;
    uint64_t count_digits = 0;
    uint8_t *numb = NULL;
    uint8_t *tmp = NULL;

    // Save digits of the number in
    // an array.
    while(n)
    {
        count_digits++;

        tmp = realloc(numb, count_digits * sizeof(uint8_t));
        if (tmp != NULL)
            numb = tmp;
        else
        {
            fprintf(stderr, "%s:%d Mem Alloc failed\n", __func__, __LINE__);

            if (numb)
                free(numb);

            return 0;
        }

        numb[count_digits-1] = n%10;

        n/=10;
    }

    for(uint64_t i = 0;i<count_digits;i++)
        if (numb[i] != numb[count_digits - 1 - i])
            return 0;

    if(numb)
        free(numb);

    return 1;
}

/**
 * \brief The solution using a naive way.
 *
 * \param   num  Number to do something.
 * \return  1 if everything is ok, 0 if not.
 */
uint8_t solution1(uint64_t num)
{

    if(isPalindrome(num))
        fprintf(stdout, "It's palindrome.\n");
    else
        fprintf(stdout, "It's not palindrome.\n");

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
    fprintf(stdout, "%s <Number to do something.>\n", argv0);
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
