/**
* @file     prob36.c
* @author   Stavros Vagionitis
* @date     29 Mar 2015
* @brief    [Problem 36 in Project Euler](https://projecteuler.net/problem=36)
*           Double-base palindromes
*           =======================
*           The decimal number, 585 = 1001001001 (binary), is palindromic in both bases.
*
*           Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.
*
*           (Please note that the palindromic number, in either base, may not include leading zeros.)
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/**
 * \brief Count the digits of a number
 *
 * \param   n     The number to count the digits
 * \return the number of digits.
 */
uint64_t count_digits(const uint64_t n)
{
    uint64_t counter = 0;
    uint64_t num = n;

    while(num)
    {
        num/=10;
        counter++;
    }

    return counter;
}

/**
 * \brief Compute the exponential power for uint64_t
 *
 * \param   base    The base to be expanded.
 * \param   exp     The exponential.
 * \return  the computed power exponential.
 */
uint64_t pow1(uint64_t base, uint64_t exp)
{
    uint64_t t = 1;

    if (exp == 0)
        return 1;
    else if (exp == 1)
        return base;
    else if (exp == 2)
        return base * base;
    else
    {
        for(uint64_t i = 0;i<exp;i++)
            t*=base;
    }

    return t;
}

/**
 * \brief Check if a number is truncatable prime
 *        See http://en.wikipedia.org/wiki/Truncatable_prime
 *        for more info
 *
 * \param   num    The number to check
 * \return  1 if truncatable prime, 0 otherwise.
 */
uint8_t isPalindrome(const uint64_t num)
{
    uint64_t cd = count_digits(num);
    uint64_t n_left2right = num;
    uint64_t n_right2left = num;


    // One digit number is palindrome
    if (cd == 1)
        return 1;

    uint64_t dec = pow1(10, cd-1);
    while(n_right2left || n_left2right)
    {
        // Get the most right digit
        uint64_t d_right2left = n_right2left % 10;
        n_right2left /= 10;

        // Get the most left digit
        uint64_t d_left2right = n_left2right / dec;
        n_left2right -= d_left2right * dec;
        dec /=10;

#if 0
        fprintf(stdout, "d_right2left: %ju d_left2right: %ju\n", d_right2left, d_left2right);
#endif

        if (d_right2left != d_left2right)
            return 0;
    }

    return 1;
}

/**
 * \brief Count the leading zeros of a uint64 number.
 *        See http://en.wikipedia.org/wiki/Find_first_set
 *        for more info.
 *
 * \param   num  The number to count the leading zeros
 * \return  the number of counted leading zeros.
 */
uint64_t count_leading_zeros(const uint64_t num)
{
    uint64_t n = num;
    uint64_t c = 0;

    if (n == 0)
        return sizeof(n) * 8;

    while((n & 0x8000000000000000) == 0)
    {
        c++;
        n <<= 1;
    }

    return c;
}

/**
 * \brief Reverse the bits of a number.
 *        The reversed bits are moved to
 *        such positions as the counted leading zeros
 *        before it was reversed. The algorithm was retrieved by
 *        https://graphics.stanford.edu/~seander/bithacks.html#BitReverseObvious
 *
 * \param   num  The number to reverse the bits
 * \return  the number with reverted bits.
 */
uint64_t reverse_bits(const uint64_t num)
{
    uint64_t n = num;
    uint64_t r = n;
    uint64_t s = sizeof(n) * 8;

    uint64_t clz = count_leading_zeros(num);

    for (n >>= 1; n; n >>= 1)
    {
      r <<= 1;
      r |= n & 1;
      s--;
    }
    r <<= --s; // shift when n's highest bits are zero

    // Move it for counted leading zeros.
    r >>= clz;

    return r;
}

/**
 * \brief The solution using a naive way.
 *
 * \param   num  Max number to check.
 * \return  1 if everything is ok, 0 if not.
 */
uint8_t solution1(uint64_t num)
{
    uint64_t sum = 0;
    for (uint64_t i = 1;i<num;i++)
    {
        if (isPalindrome(i) && (i == reverse_bits(i)))
        {
            fprintf(stdout, "Palindrome: %ju\n", i);
            sum += i;
        }
    }

    fprintf(stdout, "The sum of palindromes up to %ju is %ju\n", num, sum);

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
