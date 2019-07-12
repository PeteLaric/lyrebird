#include <stdio.h>
#include <stdlib.h>



// stolen from https://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format
const char *bit_rep[16] = {
    [ 0] = "0,0,0,0", [ 1] = "0,0,0,1", [ 2] = "0,0,1,0", [ 3] = "0,0,1,1",
    [ 4] = "0,1,0,0", [ 5] = "0,1,0,1", [ 6] = "0,1,1,0", [ 7] = "0,1,1,1",
    [ 8] = "1,0,0,0", [ 9] = "1,0,0,1", [10] = "1,0,1,0", [11] = "1,0,1,1",
    [12] = "1,1,0,0", [13] = "1,1,0,1", [14] = "1,1,1,0", [15] = "1,1,1,1",
};

void print_byte(uint8_t byte)
{
    printf("%s,%s", bit_rep[byte >> 4], bit_rep[byte & 0x0F]);
}



int main()
{
    
    FILE *outfile = fopen("exhaustive_bytes.bin", "wb");
    
    int i = 0;
    
    for (i = 0; i < 256; i++)
    {
        
        unsigned char c = (unsigned char)i;
        //fprintf(outfile, "%c", c);
        fputc(c, outfile);
        print_byte(c);
        printf("\n");
        
    }
    
    fclose(outfile);
    
    return 0;
    
}
