#include <stdio.h>

int main (int argc, char *argv[])
{
    // Handle user input incorrectness
    if (argc < 2 || argc > 4)
    {
        printf("Usage: ./organizer /folder\n");
        printf("       ./organizer --preview /folder\n");
        return 1;
    }
}