/**
* @file     prob39.c
* @author   Stavros Vagionitis
* @date     30 Mar 2015
* @brief    [Problem 39 in Project Euler](https://projecteuler.net/problem=39)
*           Integer right triangles
*           =======================
*           If p is the perimeter of a right angle triangle with integral length sides,
*           {a,b,c}, there are exactly three solutions for p = 120.
*
*           {20,48,52}, {24,45,51}, {30,40,50}
*
*           For which value of p ≤ 1000, is the number of solutions maximised?
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/**
 * \brief Given the perimeter, find how many solution exists
 *        for a right triangle. Use of Pythagorean theorem.
 *
 *        TODO There is a triple loop. Can be done better?
 *
 * \param   p   The perimeter of the right triangle.
 * \return  the count of the solutions.
 */
uint64_t countSolutionsPythagoreanTheorem(uint64_t p)
{
    uint64_t count_solutions = 0;

    for (uint64_t a = 1;a<p;a++)
    {
        for (uint64_t b = a;b<p;b++)
        {
            for (uint64_t c = b;c<p;c++)
            {
                if ((p == a + b + c) &&
                    (a*a + b*b == c*c))
                    count_solutions++;
            }
        }
    }

#if 0
    fprintf(stdout, "For p: %ju count: %ju\n", p, count_solutions);
#endif

    return count_solutions;
}

/**
 * \brief The solution using a naive way.
 *
 * \param   num  Max number to search.
 * \return  1 if everything is ok, 0 if not.
 */
uint8_t solution1(uint64_t num)
{

    uint64_t max_count_sol = 0;
    uint64_t max_val = 0;

    for (uint64_t i = 0;i<num;i++)
    {
        uint64_t cnt_sol = countSolutionsPythagoreanTheorem(i);
        if (cnt_sol > max_count_sol)
        {
            max_count_sol = cnt_sol;
            max_val = i;
        }
    }

    fprintf(stdout, "The number of solution maximised, %ju, for p: %ju\n", max_count_sol, max_val);

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
    fprintf(stdout, "%s <Max number to search.>\n", argv0);
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
