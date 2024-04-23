#include <cs50.h>
#include <stdio.h>

int get_height();
void print_hashes (int n);
void print_revhashes(int n, int maxheight);

int main(void)
{
    int h = get_height();

    //creating a loop to show the pyramid
    for (int i = 0; i < h; i++)
    {
        //It call the functions to print each line
        print_revhashes(i+1, h);
        printf("  ");
        print_hashes(i+1);
        printf("\n");
    }

}

int get_height()
{
    //This functions get the height of the pyramid
    int height;
    do
    {
        height = get_int("Height: ");
    } while (height < 1 || height > 8);
    return height;
}


void print_hashes(n){
    //This loop print the hashes n times

    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
}

void print_revhashes(n, maxh){
    //This loop print the empty space before the hashes line
    for (int i = 0; i < maxh-n;i++)
    {
        printf(" ");
    }

    //This loop print the hashes n times
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
}