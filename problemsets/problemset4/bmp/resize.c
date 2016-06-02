/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
    
    // check if reszie parameter is valid
    int n = atoi(argv[1]);
    if (n <= 0 || n > 100)
    {
        printf("Resize parameter n must be a positive integer less than or equal to 100\n");
        return 2;
    }
    
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    
    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf_in;
    fread(&bf_in, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi_in;
    fread(&bi_in, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf_in.bfType != 0x4d42 || bf_in.bfOffBits != 54 || bi_in.biSize != 40 || 
        bi_in.biBitCount != 24 || bi_in.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }
    
    // initialize outfile's bitmaps
    BITMAPFILEHEADER bf_out = bf_in;
    BITMAPINFOHEADER bi_out = bi_in;
    
    bi_out.biHeight *= n;
    bi_out.biWidth *= n;
    
    // determine padding for scanlines
    int padding_in =  (4 - (bi_in.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding_out =  (4 - (bi_out.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    bi_out.biSizeImage = (bi_out.biWidth * sizeof(RGBTRIPLE) + padding_out) * abs(bi_out.biHeight);
    bf_out.bfSize = bi_out.biSizeImage + 54;
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_out, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_out, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi_in.biHeight); i < biHeight; i++)
    {
        for (int k = 0; k < n; k++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi_in.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                for (int m = 0; m < n; m++)
                {   
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            
            // skip over padding, if any
            fseek(inptr, padding_in, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int m = 0; m < padding_out; m++)
            {
                fputc(0x00, outptr);
            }
            
            fseek(inptr, -(bi_in.biWidth * 3 + padding_in), SEEK_CUR);
        }
        
        fseek(inptr, bi_in.biWidth * 3 + padding_in, SEEK_CUR);
      
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
