/*
    lyrebird_compose.c
    (cc) BY 2019 Pete Laric
    http://www.PeteLaric.com

    Converts a binary file containing arbitrary data to music in .lyrebird format.
 
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



// stolen from https://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format
const char *bit_rep[16] = {
    [ 0] = "0000", [ 1] = "0001", [ 2] = "0010", [ 3] = "0011",
    [ 4] = "0100", [ 5] = "0101", [ 6] = "0110", [ 7] = "0111",
    [ 8] = "1000", [ 9] = "1001", [10] = "1010", [11] = "1011",
    [12] = "1100", [13] = "1101", [14] = "1110", [15] = "1111",
};

void print_byte(uint8_t byte)
{
    printf("%s%s", bit_rep[byte >> 4], bit_rep[byte & 0x0F]);
}



/* Creates a temporary file, writes the source filename to it, appends the rest of the source file, then
   closes and reopens this temp file ~as~ the source file! */
void prepend_filename(FILE *infile, char *filename)
{
    
    FILE *outfile = fopen("temp.dat", "wb");
    
    fprintf(outfile, "%s\n", filename);
    
    while (!feof(infile))
    {
        
        unsigned char c = fgetc(infile);
        if (feof(infile)) break;
        
        fputc(c, outfile);
        
    }
    
    // close both files
    fclose(outfile);
    fclose(infile);
    
    // now here's the brilliant part, lol
    infile = fopen("temp.dat", "rb");
    
}



int extract_chord_component(unsigned char c, unsigned char mask, int shift)
{
    
    int chord_component = (c & mask) >> shift;
    
    return chord_component;
    
}



int extract_soprano_voice(unsigned char c)
{
    unsigned char mask = 0;
    int shift = 0;
    int chord_component = 0;
    // soprano
    mask = 192;
    shift = 6;
    chord_component = extract_chord_component(c, mask, shift);
    return chord_component;
}

int extract_alto_voice(unsigned char c)
{
    unsigned char mask = 0;
    int shift = 0;
    int chord_component = 0;
    // alto
    mask = 48;
    shift = 4;
    chord_component = extract_chord_component(c, mask, shift);
    return chord_component;
}

int extract_tenor_voice(unsigned char c)
{
    unsigned char mask = 0;
    int shift = 0;
    int chord_component = 0;
    // tenor
    mask = 12;
    shift = 2;
    chord_component = extract_chord_component(c, mask, shift);
    return chord_component;
}

int extract_bass_voice(unsigned char c)
{
    unsigned char mask = 0;
    int shift = 0;
    int chord_component = 0;
    // bass
    mask = 3;
    shift = 0;
    chord_component = extract_chord_component(c, mask, shift);
    return chord_component;
}


void encode_char(unsigned char c, char *str)
{
    
    //unsigned char c = 69;
    
    printf("%c: %i\n", c, c);
    print_byte(c);
    printf("\n");
    
    // extract chord components
    
    // soprano
    int soprano_note = extract_soprano_voice(c);
    printf("soprano voice: ");
    printf("%c: %i\n", soprano_note, soprano_note);
    
    // alto
    int alto_note = extract_alto_voice(c);
    printf("alto voice: ");
    printf("%c: %i\n", alto_note, alto_note);
    //sprintf(str, "%i ", alto_note, alto_note);
    
    // tenor
    int tenor_note = extract_tenor_voice(c);
    printf("tenor voice: ");
    printf("%c: %i\n", tenor_note, tenor_note);
    
    // bass
    int bass_note = extract_bass_voice(c);
    printf("bass voice: ");
    printf("%c: %i\n", bass_note, bass_note);
    
    printf("\n");
    
    sprintf(str, "%i %i %i %i\n", soprano_note, alto_note, tenor_note, bass_note);
    
}


void bin2music(FILE *infile, FILE *outfile)
{
    
    char *str = malloc(100);
    
    while (!feof(infile))
    {
        
        unsigned char c = fgetc(infile);
        if (feof(infile)) break;
        
        //printf("%c", c);
        encode_char(c, str);
        
        //fprintf(outfile, "%c", c);
        fprintf(outfile, "%s", str);
        
    }
    
    free(str);
    
}



int main(int argc, char *argv[])
{
    
    // make sure the user specified an input file
    if (argc < 2)
    {
        printf("\n\n");
        printf("    usage: lyrebird_compose [input_filename]\n\n");
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
    
    prepend_filename(infile, argv[1]);
    
    char output_filename[] = "song.lyrebird.txt";
    
    // open the output file
    FILE *outfile = fopen(output_filename, "wb");
    
    // steganographize (??) the file...
    bin2music(infile, outfile);
    
    fclose(infile);
    fclose(outfile);
    
    printf("%s written to disk.\n\n", output_filename);
     
    
    return 0;
    
}
