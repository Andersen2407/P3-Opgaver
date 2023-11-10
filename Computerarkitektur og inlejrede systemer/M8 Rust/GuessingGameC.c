#include <stdio.h>
#include <stdlib.h>
#include <time.h>   // include

void main()
{
    // Random time generator.
    srand(time(NULL));

    // The random number to guess from [1-100] inclusive.
    int secret_number = (rand() % 100) + 1;
    
    // The user guess (string).
    char guessInput[3];
    
    // The int value our guess is converted to
    int guess;

    // Lets loop until we break when we find the secret number.
    while (1)
    {
        // User input: guess the number please!
        printf("Guess a number:\n");
        scanf("%s", guessInput);

        // Argument to int (atoi)
        // We need to convert the char guess to an int.
        int guess = atoi(guessInput);
        
        // If the convertion failed.
        if (guess == 0) // if guess is 0
        {
            // Print error and ask again.
            printf("Error: Invailed input.\n");
            continue; // continue
        }

        // If out guess was to small.
        if (guess < secret_number)
            printf("Too small!\n"); // print
        
        // Else if the guess was too large.
        else if (guess > secret_number) // if guess > secret_number
            printf("Too big!\n");

        // Othervise we where right!
        else
        {
            printf("You guessed the number!");
            exit(0);
        }
    }
}
