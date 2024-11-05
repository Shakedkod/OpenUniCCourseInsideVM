#include <stdio.h>
#include <ctype.h>

int main()
{
    char c, isStartOfSentence = 1, isQuote = 0;

    printf("Hello, please enter some sentences into the machine:\n");
    while ((c = getchar()) != EOF)
    {
        if (!isdigit(c))
        {
            if (isQuote) /* in quote */
                c = toupper(c);
            else if (isStartOfSentence && !isspace(c)) /* first letter of a sentence */
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
            printf("%c", c);
        }
    }

    return 0;
}
