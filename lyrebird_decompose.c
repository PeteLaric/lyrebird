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
 
 
    REVISION HISTORY

    2019-07-05: Source filename is now embedded into music by lyrebird_compose, and automatically
    extracted by lyrebird_decompose.  The only known issue with this feature is that if the source file
    resides in another directory, its path information will be embedded along with the filename.  If
    the computer decomposing the music has a different directory structure than the computer that composed
    the music, this could cause a write error.  One solution would be to strip all path information from
    the filename prior to embedding.
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define STRING_BUFFER_SIZE      1000



// replace all newline characters with null terminators
void strip_newline(char *str)
{
    int i = 0;
    for (i = 0; i < STRING_BUFFER_SIZE; i++)
    {
        if (str[i] == '\n' || str[i] == '\r') // if newline or carriage return
            str[i] = '\0';
    }
}



/* Copies the original source filename from the freshly-decomposed song.  Doesn't rewind the file,
   so reading commences from after the filename, effectively stripping it out of the data stream.
   Finally, copy the input file to a new file using the filename found within. */
void get_filename_and_copy(FILE *infile, char *filename)
{
    
    fgets(filename, STRING_BUFFER_SIZE, infile);
    
    strip_newline(filename); // make sure to remove any newline characters
    
    printf("Filename \"%s\" retrieved from music.\n", filename);
    
    FILE *outfile = fopen(filename, "wb");
    
    while (!feof(infile))
    {
        
        unsigned char c = fgetc(infile);
        if (feof(infile)) break;
        
        fputc(c, outfile);
        
    }
    
    // close both files
    fclose(outfile);
    fclose(infile);
    
}



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
    
    char temp_filename[] = "temp.dat";
    
    // open the temp file
    FILE *tempfile = fopen(temp_filename, "wb");
    
    // un-steganographize (??) the file...
    music2bin(infile, tempfile);
    
    fclose(infile);
    fclose(tempfile);
    
    // file has been un-steganographized... BUT, it still contains a filename within the data!
    
    //rewind(tempfile); // doesn't work because file is write-only
    // open the temp file (for read access this time)
    tempfile = fopen(temp_filename, "rb"); // rewinds it too
    
    char *output_filename = malloc(STRING_BUFFER_SIZE * sizeof(char));
    get_filename_and_copy(tempfile, output_filename); //read from
    
    printf("%s written to disk.\n\n", output_filename);
    
    free(output_filename);
    
    return 0;
    
}
