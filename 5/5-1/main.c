#include <ctype.h>
#include <stdio.h>
int getch(void);
void ungetch(int);
int getint(int *pn);

int main(void)
{
    int num;
    int type;
    while((type = getint(&num)) != EOF)
    {
        if(type > 0)
            printf("%d\n", num);
    }
    return 0;
}

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
    int c, sign, saw_sign = 0;
    while (isspace(c = getch())) /* skip white space */
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c); /* it is not a number */
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
    {
        saw_sign = 1;
        c = getch();
    }
    if(!isdigit(c))
    {
        ungetch(c);
        if(saw_sign)
            ungetch(sign == -1 ? '-' : '+');
        return 0;
    }
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}

#define BUFSIZE 100
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */
int getch(void) /* get a (possibly pushed-back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();//如果有之前超前读取的字符在缓冲数组中则先返回缓冲数组中的字符
}
void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = (char)c;
}
