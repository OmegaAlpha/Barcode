#include <png.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 400
#define HEIGHT 300

int main(int argc, char **argv) {
  // Allokere minnet for bildet
  int row, col;
  png_bytep image[HEIGHT];
  for (row = 0; row < HEIGHT; row++)
    image[row] = (png_bytep) malloc(WIDTH * sizeof(png_byte));

  // Sett opp png-parametere
  png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png_ptr)
    return 1;

  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr)
    return 1;

  // Åpne filen for skriving
  FILE *fp = fopen("barcode.png", "wb");
  if (!fp)
    return 1;

  png_init_io(png_ptr, fp);

  // Sett opp parametere for bildet
  png_set_IHDR(png_ptr, info_ptr, WIDTH, HEIGHT, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
               PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

  // Skriv bildehovedet til filen
  png_write_info(png_ptr, info_ptr);

  // Generer strekkoden og lagre den i minnet
  for (row = 0; row < HEIGHT; row++) {
    png_byte *rowptr = image[row];
    for (col = 0; col < WIDTH; col++) {
      // Du kan implementere logikken for å generere strekkoden her
      // ...
      *rowptr++ = 0; // R
      *rowptr++ = 0; // G
      *rowptr++ = 0; // B
    }
  }

  // Skriv bildedataen til filen
  png_write_image(png_ptr, image);

  // Skriv sluttdata til filen
  png_write_end(png_ptr, NULL);

  // Lukk filen og frigjør minnet
  fclose(fp);
  for (row = 0; row < HEIGHT; row++)
    free(image[row]);
  png_destroy_write_struct(&png_ptr, &info_ptr);

  return 0;
}
