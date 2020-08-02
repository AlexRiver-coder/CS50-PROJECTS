#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
//bool function at the line 100
    bool isjpeg(BYTE * im);
    
// Check to see if the user has inserted the correct amount of command-line argument    
    if (argc != 2)
    {
        printf("insert only one command-line argument\n");
        return 1;
    }
    
    FILE *ptr = fopen(argv[1], "r");
    
    if (ptr == NULL)
    {
        printf("This foresinc image can not be oppened");
        return 1;
    }
    
// pointer to store the images    
    BYTE *image;
    image = malloc(512);
    
// pointer to store the name of the file    
    char *filename;
    filename = malloc(18);
    
// Variable to count the number of jpeg images we found
    int count = 0;

// Pointer used to point to the actual file we are writing    
    FILE *img;
    
// Loop to look through all the bytes inside the file  

    while (fread(image, 1, 512, ptr) == 512)
    {
        if (isjpeg(image))
        {
// Creates a file and start writing the image until it founds another jpg image begnning            
            if (count == 0)
            {
                sprintf(filename, "%03i.jpg", count);
                img = fopen(filename, "w");
                count++;
            }
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", count);
                img = fopen(filename, "w");
                count++;
            }
        }
// Writes in the new file the image bytes        
        fwrite(image, 1, 512, img);
    }
    
// Close the opened files and free the mallocs
    fclose(ptr);
    fclose(img);
    free(image);
    free(filename);
    free(img);
    return 0;
}    
























// Checks for the start and end of a JPEG

bool isjpeg(BYTE *im)
{
    int count = 0;
    for (int i = 0; i < 4; i++)
    {
        if (im[i] == 0xff || im[i] == 0xd8 || (im[i] & 0xf0) == 0xe0)
        {
            count++;
        }
    }
    
    if (count == 4)
    {
        return true;
    }
    
    else
    {
        count = 0;
        return false;
    }
}

