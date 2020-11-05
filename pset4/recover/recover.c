//Programa que recupera imagens JPEGs de um cartao de memoria por Mari Rizzo

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

int main(int argc, char *argv[])
{
    //Open memory card
    // Check usage
    if (argc != 2)
    {
        //nao usei variavel de erro fprintf(stderr...
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Remember filenames
    char *file = argv[1];

    // Open file
    FILE *infile = fopen(file, "r");
    if (!infile)
    {
        fclose(infile);
        printf("Not image. Usage: ./recover image\n");
        return 2;
    }

    if (infile == NULL)
    {
        fclose(infile);
        printf("Could not create.\n");
        return 3;
    }

    // buffer space
    unsigned char buffer[512];

    // filename space
    char filename[8];

    // count image number
    char num_image = 0;

    // outfile is output file
    FILE *outfile;

    bool image_jpg = false;

    // repetition loop for reading the memory card
    while (fread(buffer, sizeof(buffer), 1, infile))
    {
        //First Three Bytes: 0xff 0xd8 0xff (AND) Last Byte: 0xe0, 0xe1, 0xe2, ..., 0xef
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (image_jpg)
            {
                //close infile
                fclose(outfile);

                //set false
                image_jpg = false;
            }

            // if it finds an image, it creates a new file with a new name
            // new file name
            sprintf(filename, "%03i.jpg", num_image);

            // opens a new file and assigns the name
            outfile = fopen(filename, "w");

            // copies the contents of the buffer into the new file
            fwrite(buffer, sizeof(buffer), 1, outfile);

            //set true
            image_jpg = true;

            //add count
            num_image++;
        }
        else
        {
            //if it is still a jpg
            if (image_jpg)
            {
                //keep recording the image
                fwrite(buffer, sizeof(buffer), 1, outfile);
            }
        }
    }
    //close infile
    fclose(infile);

    //close outfile
    fclose(outfile);

    //finish sucess
    return 0;
}
