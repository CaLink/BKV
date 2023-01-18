#include "Glyph.h"



void PCF_FontDumpGlpyh(PCF_Font *font, int c)
{
    int w, h;
    int line_bsize;
    CharInfoRec *glyph;
    BitmapFontRec *bitmapFont;

    bitmapFont  = font->xfont.fontPrivate;
    printf("Number of chars in font: %d\n",  bitmapFont->num_chars);
    if(c >= bitmapFont->num_chars){
        printf("No glyph for char %d\n",c);
        return;
    }
    glyph = &bitmapFont->metrics[c];

    w = glyph->metrics.rightSideBearing - glyph->metrics.leftSideBearing;
    h = glyph->metrics.ascent + glyph->metrics.descent;

    printf("\tleft side bearing: %d\n",glyph->metrics.leftSideBearing);
    printf("\tright side bearing: %d\n",glyph->metrics.rightSideBearing);
    printf("\twidth: %d\n",glyph->metrics.characterWidth);
    printf("\tascent: %d\n",glyph->metrics.ascent);
    printf("\tdescent: %d\n",glyph->metrics.descent);
    printf("\tattributes: %d\n",glyph->metrics.attributes);

    printf("Ink metrics:\n");
    xCharInfo *ink = &bitmapFont->ink_metrics[c];
    printf("\tleft side bearing: %d\n",ink->leftSideBearing);
    printf("\tright side bearing: %d\n",ink->rightSideBearing);
    printf("\twidth: %d\n",ink->characterWidth);
    printf("\tascent: %d\n",ink->ascent);
    printf("\tdescent: %d\n",ink->descent);
    printf("\tattributes: %d\n",ink->attributes);

    /* FontRec.Glyph seems to be the line padding in number of bytes.
     * byte = 1, short = 2, int = 4
     * The pcf format has PCF_GLYPH_PAD_INDEX(format)
     * which indicates if lines are aligned to bytes(1), shorts(2)
     * or ints(4). pcfReadFont compares that to its glyph param and
     * re-pad the data to fit the format.
     * */
    printf("font->glyph is %d\n", font->xfont.glyph);
    line_bsize = ceil(w/(font->xfont.glyph * 8.0))*font->xfont.glyph; /*in bytes*/
    printf("Each glyph line will be %d bytes\n",line_bsize);


    unsigned char *glyph_line;
    unsigned char byte;
    glyph_line = (unsigned char*)glyph->bits;
    for(int i = 0; i < h; i++){
        glyph_line = (unsigned char*)glyph->bits + (i * line_bsize);
        int nbytes = ceil(w/(8.0));
        for(int j = 0; j < nbytes; j++){
            byte = *(unsigned char*)(glyph_line + j);
            for(int k = 0; k < 8; k++){
                printf("%c", (byte & (1 << k)) ? '#': '.');
            }
        }
        printf("\n");
    }
    printf("\n");
}

