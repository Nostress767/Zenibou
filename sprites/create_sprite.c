#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  FILE *fp = fopen(argv[1], "rb");

  png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  png_infop info = png_create_info_struct(png);
  png_init_io(png, fp);
  png_read_info(png, info);

  int width = png_get_image_width(png, info);
  int height = png_get_image_height(png, info);

  // Decompress/Read single pixel data
  unsigned char** rows = malloc(sizeof(unsigned char*) * height);
  for(int i = 0; i < height; i++)
    rows[i] = malloc(4 * width);
  png_read_image(png, rows);
  fclose(fp);

  // Reverse row order (from "left to right, top to bottom" to "left to right, bottom to top")
  unsigned char** reverse_rows = malloc(sizeof(unsigned char*) * height);
  for(int i = 0; i < height; i++){
    reverse_rows[i] = malloc(4 * width);
    memcpy(reverse_rows[i], rows[height - 1 - i], 4 * width);}

  // Change from .png to .h
  argv[1][strlen(argv[1]) - 1] = ' '; argv[1][strlen(argv[1]) - 2] = ' '; argv[1][strlen(argv[1]) - 3] = 'h';
  
  // Begin metaprogramming
  FILE* outfile = fopen(argv[1],"w");

  fprintf(outfile, "#ifndef _SEROKUCHI_SPRITESHEET%dX%d_H_\n#define _SEROKUCHI_SPRITESHEET%dX%d_H_\n\n",width/16,height/6,width/16,height/6);
  fprintf(outfile, "#include <stdint.h>\n#include <string.h>\n#include <stdlib.h>\n\n");

  fprintf(outfile, "static uint32_t ASSTest%dx%d[%d][%d] = {\n",width/16,height/6,height,width);
  for(int i = 0; i < height; i++){
    fprintf(outfile, "{");
    for(int j = 0; j < width; j++)
      fprintf(outfile, "0x%02X%02X%02X%02X%s", reverse_rows[i][j*4], reverse_rows[i][j*4+1], reverse_rows[i][j*4+2], reverse_rows[i][j*4+3], j == width - 1 ? "" : ",");
    fprintf(outfile, "}%s\n",i == height - 1 ? "" : ",");}
  fprintf(outfile, "};\n\n");
  //fprintf(outfile, "uint32_t* ASSTest%dx%d(void){\n",width/16,height/6);
  ////fprintf(outfile, "uint32_t* test = malloc(%d);\n", width * height * 4);
  //fprintf(outfile, "static uint32_t test[%d] = {", width * height * 4);
  //for(int i = 0; i < height; i++){
  //  //fprintf(outfile, "{");
  //  for(int j = 0; j < width; j++)
  //    fprintf(outfile, "0x%02X%02X%02X%02X%s", reverse_rows[i][j*4+3], reverse_rows[i][j*4], reverse_rows[i][j*4+1], reverse_rows[i][j*4+2], j == width - 1 ? "" : ",");
  //  fprintf(outfile, "%s\n", i == height - 1 ? "" : ",");}
  ////  fprintf(outfile, "}%s\n", i == height - 1 ? "" : ",");}
  //fprintf(outfile, "}\nreturn &test;}\n\n");
  fprintf(outfile, "void DrawSpriteTest%dx%d(int32_t x, int32_t y, const char* text, uint32_t scale){\n",width/16,height/6);
  fprintf(outfile, "  int32_t text_x = 0, text_y = 0;\n");
  fprintf(outfile, "  size_t str_len = strlen(text);\n");
  fprintf(outfile, "  for(size_t i = 0; i < str_len; i++){\n");
  fprintf(outfile, "    if(text[i] == '\\n'){\n");
  fprintf(outfile, "      text_x = 0; text_y -= %d * scale;}\n", height/6);
  fprintf(outfile, "    else{\n");
  fprintf(outfile, "      uint32_t char_index_x = (text[i] - 32) %% 16, char_index_y = (text[i] - 32) / 16;\n");
  fprintf(outfile, "      if(scale > 1){\n");
  fprintf(outfile, "        for(uint32_t j = 0; j < %d; j++)\n",width/16);
  fprintf(outfile, "          for(uint32_t k = 0; k < %d; k++)\n",height/6);
  fprintf(outfile, "            for (uint32_t scaled_i = 0; scaled_i < scale; scaled_i++)\n");
  fprintf(outfile, "              for (uint32_t scaled_j = 0; scaled_j < scale; scaled_j++)\n");
  fprintf(outfile, "                D(x + text_x + (k * scale) + scaled_i, y + text_y + (j * scale) + scaled_j, ASSTest%dx%d[char_index_y * %d + j][char_index_x*%d + k]);}\n",width/16,height/6,height/6,width/16);
  fprintf(outfile, "      else{\n");
  fprintf(outfile, "        for(uint32_t j = 0; j < %d; j++)\n",width/16);
  fprintf(outfile, "          for(uint32_t k = 0; k < %d; k++)\n",height/6);
  fprintf(outfile, "            D(x + text_x + k, y + text_y + j, ASSTest%dx%d[char_index_y * %d + j][char_index_x*%d + k]);}\n",width/16,height/6,height/6,width/16);
  fprintf(outfile, "      text_x += %d * scale ;}}\n",width/16);
  fprintf(outfile, "}\n\n");
  fprintf(outfile, "#endif\n");

  fclose(outfile);

  return 0;
}
