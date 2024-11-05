#include <stdio.h>
#include <ctype.h>

int isSpace(const char c)
{
    return ((c == ' ') || (c == '\t') || (c == '\n'));
}

int isNumber(const char c)
{
    return (c >= '0') && (c <= '9');
}

int main()
{
    char c;
    int isStartOfSentence = 1, isQuote = 0;

    printf("Hello, please enter some sentences into the machine:\n");
    while ((c = getchar()) != EOF)
    {
        if (!isNumber(c))
        {
            if (isQuote) /* in quote */
                c = toupper(c);
            else if (isStartOfSentence && !isSpace(c)) /* first letter of a sentence */
            {
                c = toupper(c);
                isStartOfSentence = 0;
            }
            else /* normal characters */
                c = tolower(c);

            if (c == '"') /* start & end of quote */
                isQuote = isQuote ? 0 : 1;

            if (c == '.')
                isStartOfSentence = 1;

            /* output */
            putchar(c);
        }
    }

    return 0;
}
