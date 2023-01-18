#ifndef LSBFirst
#define LSBFirst    0
#define MSBFirst    1
#endif

#define Successful      85
#define AllocError      80

#if defined(__need_NULL)
#undef NULL
#ifdef __cplusplus
#  if !defined(__MINGW32__) && !defined(_MSC_VER)
#    define NULL __null
#  else
#    define NULL 0
#  endif
#else
#  define NULL ((void*)0)
#endif
#ifdef __cplusplus
#if defined(_MSC_EXTENSIONS) && defined(_NATIVE_NULLPTR_SUPPORTED)
namespace std { typedef decltype(nullptr) nullptr_t; }
using ::std::nullptr_t;
#endif
#endif
#undef __need_NULL
#endif /* defined(__need_NULL) */


typedef struct _Font {
    int         refcnt;
    FontInfoRec info;
    char        bit;
    char        byte;
    char        glyph;
    char        scan;
    BitmapFontRec        *fontPrivate;
}FontRec;
typedef struct _Font *FontPtr;

typedef struct{
    FontRec xfont;
}PCF_Font;

typedef struct {
    Sint16 leftSideBearing,
           rightSideBearing,
           characterWidth,
           ascent,
           descent;
    Uint16 attributes;
} xCharInfo;

typedef struct _CharInfo {
    xCharInfo   metrics;    /* info preformatted for Queries */
    char       *bits;       /* pointer to glyph image */
}CharInfoRec;
typedef struct _CharInfo *CharInfoPtr;

typedef struct _BitmapFont {
    unsigned    version_num;
    int         num_chars;
    int         num_tables;
    CharInfoPtr metrics;    /* font metrics, including glyph pointers */
    xCharInfo  *ink_metrics;    /* ink metrics */
    char       *bitmaps;    /* base of bitmaps, useful only to free */
    CharInfoPtr **encoding; /* array of arrays of char info pointers */
    CharInfoPtr pDefault;   /* default character */
}BitmapFontRec, *BitmapFontPtr;


PCF_Font *PCF_FontInit(PCF_Font *self, const char *filename)
void PCF_FontDumpGlpyh(PCF_Font *font, int c);