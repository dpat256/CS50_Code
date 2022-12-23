#include <stdio.h>

int get_height(void);
void create_pyramid(int height);

int main(void) 
{
    int height;
    height = get_height();

    printf("The height is %d.\n", height);

    create_pyramid(height);
}

int get_height(void)
{
    int height;
    do
    {
        printf("Please enter the height of Mario's pyramid(Must be integer between 1 and 8): ");
        scanf("%d", &height);
    } while (height < 1 || height > 8);
    return height;
    
}

void create_pyramid(int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = height; j > 0; j--)
        {
            if(j > i)
            {
                printf(" "); 
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
        
    }
}