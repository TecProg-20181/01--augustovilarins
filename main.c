#include <stdio.h>

typedef struct _pixel {
    unsigned short int red;
    unsigned short int green;
    unsigned short int blue;
} Pixel;

typedef struct _image {
    Pixel pixel[512][512];
    unsigned int image_width;
    unsigned int image_height;
} Image;

int min(int a, int b){
  if (a > b)
    return b;
return a;
}

int max(int a, int b){
  if (a > b)
    return a;
return b;
}


int compare_pixels(Pixel pixel1, Pixel pixel2) {
    if (pixel1.r == pixel2.r &&
        pixel1.g == pixel2.g &&
        pixel1.b == pixel2.b)
        return 1;
    return 0;
}


Image grey_scale(Image image) {

    for (unsigned int i = 0; i < image.image_height; ++i) {
        for (unsigned int j = 0; j < image.image_width; ++j) {
          int media = image.pixel[i][j].red +
                      image.pixel[i][j].green +
                      image.pixel[i][j].blue;
          media /= 3;
          image.pixel[i][j].red = media;
          image.pixel[i][j].green = media;
          image.pixel[i][j].blue = media;
        }
    }

    return image;
}

void blur(Image image, unsigned int blur_scale) {
    for (unsigned int i = 0; i < image.image_height; ++i) {
        for (unsigned int j = 0; j < image_width; ++j) {
            Pixel media = {0, 0, 0};

            int min_image_height = min(i + blur_scale/2, image.image_height - 1);
            int min_image_width = min(i + blur_scale/2, image.image_width - 1);
            for(unsigned int x = max(0, i - blur_scale/2); x <= min_image_height; ++x) {
                for(unsigned int y = max(0,j - blur_scale/2); y <= min_image_width; ++y) {
                    media.r += pixel[x][y][0];
                    media.g += pixel[x][y][1];
                    media.b += pixel[x][y][2];
                }
            }

            media.red /= blur_scale * blur_scale;
            media.green /= blur_scale * blur_scale;
            media.blue /= blur_scale * blur_scale;

            pixel[i][j].red = media.red;
            pixel[i][j].green = media.green;
            pixel[i][j].blue = media.blue;
        }
    }
}

Image rotate_right_90_degrees(Image img) {
    Image rotated;

    rotated.image_width = image.image_height;
    rotated.image_height = image.image_width;

    for (unsigned int i = 0, y = 0; i < rotated.image_height; ++i, ++y) {
        for (int j = rotated.image_width - 1, x = 0; j >= 0; --j, ++x) {
            rotated.pixel[i][j][0] = image.pixel[x][y][0];
            rotated.pixel[i][j][1] = image.pixel[x][y][1];
            rotated.pixel[i][j][2] = image.pixel[x][y][2];
        }
    }

    return rotated;
}

void invert_colors(unsigned short int pixel[512][512][3],
                    unsigned int image_width, unsigned int image_height) {
    for (unsigned int i = 0; i < image_height; ++i) {
        for (unsigned int j = 0; j < image_width; ++j) {
            pixel[i][j][0] = 255 - pixel[i][j][0];
            pixel[i][j][1] = 255 - pixel[i][j][1];
            pixel[i][j][2] = 255 - pixel[i][j][2];
        }
    }
}

Image cut_image(Image image, int x, int y, int image_width, int image_height) {
    Image cuted;

    cuted.image_width = image_width;
    cuted.image_height = image_height;

    for(int i = 0; i < image_height; ++i) {
        for(int j = 0; j < image_width; ++j) {
            cuted.pixel[i][j][0] = img.pixel[i + y][j + x][0];
            cuted.pixel[i][j][1] = img.pixel[i + y][j + x][1];
            cuted.pixel[i][j][2] = img.pixel[i + y][j + x][2];
        }
    }

    return cuted;
}


int main() {
    Image image;

    // read type of image
    char p3[4];
    scanf("%s", p3);

    // read width height and color of image
    int max_color;
    scanf("%u %u %d", &image.image_width, &image.image_height, &max_color);

    // read all pixels of image
    for (unsigned int i = 0; i < image.image_height; ++i) {
        for (unsigned int j = 0; j < image.image_width; ++j) {
            scanf("%hu %hu %hu", &image.pixel[i][j][0],
                                 &image.pixel[i][j][1],
                                 &image.pixel[i][j][2]);

        }
    }

    int options;
    scanf("%d", &options);

    for(int i = 0; i < options; ++i) {
        int option;
        scanf("%d", &option);

        switch(option) {
            case 1: { // Escala de Cinza
                img = grey_scale(image);
                break;
            }
            case 2: { // Filtro Sepia
                for (unsigned int x = 0; x < image.image_height; ++x) {
                    for (unsigned int j = 0; j < image.image_width; ++j) {
                        unsigned short int pixel[3];
                        pixel[0] = image.pixel[x][j][0];
                        pixel[1] = image.pixel[x][j][1];
                        pixel[2] = image.pixel[x][j][2];

                        int p =  pixel[0] * .393 + pixel[1] * .769 + pixel[2] * .189;
                        int menor_r = (255 >  p) ? p : 255;
                        image.pixel[x][j][0] = menor_r;

                        p =  pixel[0] * .349 + pixel[1] * .686 + pixel[2] * .168;
                        menor_r = (255 >  p) ? p : 255;
                        image.pixel[x][j][1] = menor_r;

                        p =  pixel[0] * .272 + pixel[1] * .534 + pixel[2] * .131;
                        menor_r = (255 >  p) ? p : 255;
                        image.pixel[x][j][2] = menor_r;
                    }
                }

                break;
            }
            case 3: { // Blur
                int size = 0;
                scanf("%d", &size);
                blur(img.h, image.pixel, size, image.w);
                break;
            }
            case 4: { // Rotacao
                int counter= 0;
                scanf("%d", &counter);
                counter %= 4;
                for (int j = 0; j < counter; ++j) {
                    image = rotate_right_90_degrees(image);
                }
                break;
            }
            case 5: { // Espelhamento
                int horizontal = 0;
                scanf("%d", &horizontal);

                int image_width = image.image_width, h = image.image_height;

                if (horizontal == 1) image_width /= 2;
                else image_height /= 2;

                for (int i2 = 0; i2 < image_height; ++i2) {
                    for (int j = 0; j < image_width; ++j) {
                        int x = i2, y = j;

                        if (horizontal == 1) y = image.image_width - 1 - j;
                        else x = image.image_height - 1 - i2;

                        Pixel aux1;
                        aux1.r = image.pixel[i2][j][0];
                        aux1.g = image.pixel[i2][j][1];
                        aux1.b = image.pixel[i2][j][2];

                        image.pixel[i2][j][0] = image.pixel[x][y][0];
                        image.pixel[i2][j][1] = image.pixel[x][y][1];
                        image.pixel[i2][j][2] = image.pixel[x][y][2];

                        image.pixel[x][y][0] = aux1.r;
                        image.pixel[x][y][1] = aux1.g;
                        image.pixel[x][y][2] = aux1.b;
                    }
                }
                break;
            }
            case 6: { // Inversao de Cores
                invert_colors(image.pixel, image.image_width, image.image_height;
                break;
            }
            case 7: { // Cortar Imagem
                int x, y;
                scanf("%d %d", &x, &y);
                int image_width, image_height;
                scanf("%d %d", &image_width, &image_height);

                image = cut_image(img, x, y, image_width, image_height);
                break;
            }
        }

    }

    // print type of image
    printf("P3\n");
    // print width height and color of image
    printf("%u %u\n255\n", image.image_width, image.image_height);

    // print pixels of image
    for (unsigned int i = 0; i < image.image_height; ++i) {
        for (unsigned int j = 0; j < image.image_width; ++j) {
            printf("%hu %hu %hu ", image.pixel[i][j][0],
                                   image.pixel[i][j][1],
                                   image.pixel[i][j][2]);

        }
        printf("\n");
    }
    return 0;
}
