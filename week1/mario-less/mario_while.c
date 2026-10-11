#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    do
    {
        height = get_int("Height: ");
    }
    while (height < 1);

    int row = 0;

    while (row < height)
    {
        int spaces = height - row - 1;
        int count = 0;

        while (count < spaces)
        {
            printf(" ");
            count++;
        }

        count = 0;

        while (count <= row)
        {
            printf("#");
            count++;
        }

        printf("\n");
        row++;
    }
}
