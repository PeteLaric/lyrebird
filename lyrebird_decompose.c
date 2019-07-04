/*
    lyrebird_decompose.c
    (cc) BY 2019 Pete Laric
    http://www.PeteLaric.com
 
    Converts music in .lyrebird format to a binary file containing arbitrary data.
 
    Lyrebird is a musical steganography system that converts arbitrary data into listenable music,
    and vice-versa.  The goal of the project is to blur the line between artistic expression, which
    enjoys First Amendment protection against censorship, and other forms of speech that the U.S.
    government has erroneously claimed are exempt from such protections.  One relevant example of
    the latter is a technical drawing of a firearm that could allow a person to fabricate such a
    weapon using a 3D printer, or other CNC-type rapid prototyping equipment.
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define STRING_BUFFER_SIZE      1000



unsigned char SATB_to_byte(int S, int A, int T, int B)
{
    int rval = 0;
    
    int S_coef = 64,
        A_coef = 16,
        T_coef = 4,
        B_coef = 1;
    
    rval = S_coef * S + A_coef * A + T_coef * T + B_coef * B;
    
    return (unsigned char)rval;
}


void music2bin(FILE *infile, FILE *outfile)
{
    
    char *str = malloc(STRING_BUFFER_SIZE * sizeof(char));
    
    while (!feof(infile))
    {
        
        fgets(str, STRING_BUFFER_SIZE, infile);
        
        if (feof(infile)) break;
        
        int S = 0,
            A = 0,
            T = 0,
            B = 0;
        sscanf(str, "%i %i %i %i", &S, &A, &T, &B);
        
        printf("S:%i A:%i T:%i B:%i\n", S, A, T, B);
        
        unsigned char outbyte = SATB_to_byte(S, A, T, B);
        
        fputc(outbyte, outfile);
        
    }
    
    free(str);
    
}



int main(int argc, char *argv[])
{
    
    // make sure the user specified an input file
    if (argc < 2)
    {
        printf("\n\n");
        printf("    usage: lyrebird_decompose [input_filename]\n\n");
        exit(1);
    }
    
    // open the input file
    FILE *infile = fopen(argv[1], "rb");
    if (infile == NULL)
    {
        printf("\n\n");
        printf("    file %s not found!\n\n", argv[1]); // you fucking idiot
        exit(1);
    }
    
    char output_filename[] = "decomposed.file";
    
    // open the output file
    FILE *outfile = fopen(output_filename, "wb");
    
    // un-steganographize (??) the file...
    music2bin(infile, outfile);
    
    fclose(infile);
    fclose(outfile);
    
    printf("%s written to disk.\n\n", output_filename);
     
    
    return 0;
    
}
