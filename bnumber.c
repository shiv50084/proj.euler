#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

typedef struct bnum
{
    uint64_t sz_num;
    uint8_t *num;
}bnum_t;


bnum_t max_sz_bnum(const bnum_t bn1, const bnum_t bn2)
{
    if (bn1.sz_num >= bn2.sz_num)
        return bn1;
    else
        return bn2;
}

bnum_t min_sz_bnum(const bnum_t bn1, const bnum_t bn2)
{
    if (bn1.sz_num <= bn2.sz_num)
        return bn1;
    else
        return bn2;
}

uint64_t count_digits(uint64_t n)
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

uint8_t convert_num_to_bnum(const uint64_t n, bnum_t *bn)
{
    bn->sz_num = count_digits(n);

    bn->num = malloc(bn->sz_num * sizeof(uint8_t));
    if (bn->num == NULL)
    {
        fprintf(stderr, "%s:%d Mem Alloc failed\n", __func__, __LINE__);
        return 0;
    }

    uint64_t num = n;
    for (uint64_t i = bn->sz_num - 1;i != (uint64_t)(-1);i--)
    {
        bn->num[i] = (uint8_t)(num % 10);
        num/=10;
    }

#if 0
    // Debugging...
    for (uint64_t i = 0;i<bn->sz_num;i++)
    {
        if (i == 0)
            fprintf(stdout, "%s:%d %u", __func__, __LINE__, bn->num[i]);
        else if (i == bn->sz_num - 1)
            fprintf(stdout, "%u\n", bn->num[i]);
        else
            fprintf(stdout, "%u", bn->num[i]);
    }
#endif

    return 1;
}

uint8_t convert_string_to_bnum(const uint8_t str[], bnum_t *bn)
{
    bn->sz_num = strlen(str);

    bn->num = malloc(bn->sz_num * sizeof(uint8_t));
    if (bn->num == NULL)
    {
        fprintf(stderr, "%s:%d Mem Alloc failed\n", __func__, __LINE__);
        return 0;
    }

    for (uint64_t i = 0;i<bn->sz_num;i++)
        bn->num[i] = str[i] - 48;

#if 0
    // Debugging...
    for (uint64_t i = 0;i<bn->sz_num;i++)
    {
        if (i == 0)
            fprintf(stdout, "%s:%d %u", __func__, __LINE__, bn->num[i]);
        else if (i == bn->sz_num - 1)
            fprintf(stdout, "%u\n", bn->num[i]);
        else
            fprintf(stdout, "%u", bn->num[i]);
    }
#endif

    return 1;
}


uint8_t bnum_add(const bnum_t bn1, const bnum_t bn2, bnum_t *bn)
{
    uint64_t max_sz_num = max(bn1.sz_num, bn2.sz_num);


}

int main(int argc, char *arv[])
{
    bnum_t b;
    convert_num_to_bnum(123455, &b);

    for (uint64_t i = 0;i<b.sz_num;i++)
        fprintf(stdout, "%u", b.num[i]);

    fprintf(stdout, "\n");

    if (b.num)
        free(b.num);



    bnum_t b1;
    convert_string_to_bnum("543211", &b1);

    for (uint64_t i = 0;i<b1.sz_num;i++)
        fprintf(stdout, "%u", b1.num[i]);

    fprintf(stdout, "\n");

    if (b1.num)
        free(b1.num);

}
