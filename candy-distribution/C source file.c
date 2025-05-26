#include <stdio.h>
#include <stdlib.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

void distributeCandies(int *ratings, int n)
{
    int *candies = (int *)malloc(n * sizeof(int));
    if (!candies)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return;
    }

    for (int i = 0; i < n; i++)
    { // Initializing all students with at least one candy
        candies[i] = 1;
    }

    for (int i = 1; i < n; i++)
    { // Left to Right Pass
        if (ratings[i] > ratings[i - 1])
        {
            candies[i] = candies[i - 1] + 1;
        }
    }

    printf("After left-to-right pass: "); // Debugging output after left-to-right pass
    for (int i = 0; i < n; i++)
    {
        printf("%d ", candies[i]);
    }
    printf("\n");

    for (int i = n - 2; i >= 0; i--)
    { // Right to Left Pass
        if (ratings[i] > ratings[i + 1])
        {
            candies[i] = max(candies[i], candies[i + 1] + 1);
        }
    }

    printf("After right-to-left pass: "); // Debugging output after right-to-left pass
    for (int i = 0; i < n; i++)
    {
        printf("%d ", candies[i]);
    }
    printf("\n");

    int totalCandies = 0; // Calculating the total required candies
    for (int i = 0; i < n; i++)
    {
        totalCandies += candies[i];
    }

    FILE *outputFile = fopen("output.txt", "w"); // To write output to output.txt
    if (!outputFile)
    {
        fprintf(stderr, "Error opening output file.\n");
        free(candies);
        return;
    }

    fprintf(outputFile, "Total Required Candies: %d\n", totalCandies);
    fprintf(outputFile, "Candy Distribution: [");
    for (int i = 0; i < n; i++)
    {
        fprintf(outputFile, "%d", candies[i]);
        if (i < n - 1)
            fprintf(outputFile, ", ");
    }
    fprintf(outputFile, "]\n");

    fclose(outputFile);
    free(candies);
}

int main()
{
    FILE *inputFile = fopen("input.txt", "r");
    if (!inputFile)
    {
        fprintf(stderr, "Error opening input file.\n");
        return -1;
    }

    int n;
    if (fscanf(inputFile, "%d", &n) != 1) // Reading number of students
    {
        fprintf(stderr, "Error reading number of students.\n");
        fclose(inputFile);
        return -1;
    }

    int *ratings = (int *)malloc(n * sizeof(int));
    if (!ratings)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        fclose(inputFile);
        return -1;
    }

    for (int i = 0; i < n; i++)
    { // Reading ratings
        if (fscanf(inputFile, "%d", &ratings[i]) != 1)
        {
            fprintf(stderr, "Error reading ratings.\n");
            free(ratings);
            fclose(inputFile);
            return -1;
        }
    }

    distributeCandies(ratings, n);
    fclose(inputFile);
    free(ratings);
    return 0;
}