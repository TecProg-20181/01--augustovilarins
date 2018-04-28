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
        for (unsigned int j = 0; j < image.image_width; ++j) {
            Pixel media = {0, 0, 0};

            int min_image_height = min(i + blur_scale/2, image.image_height - 1);
            int min_image_width = min(i + blur_scale/2, image.image_width - 1);
            for(unsigned int x = max(0, i - blur_scale/2); x <= min_image_height; ++x) {
                for(unsigned int y = max(0,j - blur_scale/2); y <= min_image_width; ++y) {
                    media.red += image.pixel[x][y].red;
                    media.green += image.pixel[x][y].green;
                    media.blue += image.pixel[x][y].blue;
                }
            }

            media.red /= blur_scale * blur_scale;
            media.green /= blur_scale * blur_scale;
            media.blue /= blur_scale * blur_scale;

            image.pixel[i][j].red = media.red;
            image.pixel[i][j].green = media.green;
            image.pixel[i][j].blue = media.blue;
        }
    }
}

Image rotate_right_90_degrees(Image image) {
    Image rotated;

    rotated.image_width = image.image_height;
    rotated.image_height = image.image_width;

    for (unsigned int i = 0, y = 0; i < rotated.image_height; ++i, ++y) {
        for (int j = rotated.image_width - 1, x = 0; j >= 0; --j, ++x) {
            rotated.pixel[i][j].red = image.pixel[x][y].red;
            rotated.pixel[i][j].green = image.pixel[x][y].green;
            rotated.pixel[i][j].blue = image.pixel[x][y].blue;
        }
    }

    return rotated;
}

Image invert_colors(Image image) {
    for (unsigned int i = 0; i < image.image_height; ++i) {
        for (unsigned int j = 0; j < image.image_width; ++j) {
            image.pixel[i][j].red = 255 - image.pixel[i][j].red;
            image.pixel[i][j].green = 255 - image.pixel[i][j].green;
            image.pixel[i][j].blue = 255 - image.pixel[i][j].blue;
        }
    }

    return image;

}

Image cut_image(Image image, int x, int y, int image_width, int image_height) {

    Image cuted;

    cuted.image_width = image_width;
    cuted.image_height = image_height;

    for(int i = 0; i < image_height; ++i) {
        for(int j = 0; j < image_width; ++j) {
            cuted.pixel[i][j].red = image.pixel[i + y][j + x].red;
            cuted.pixel[i][j].green = image.pixel[i + y][j + x].green;
            cuted.pixel[i][j].blue = image.pixel[i + y][j + x].blue;
        }
    }

    return cuted;
}

Image sepia(Image image) {
    for (unsigned int x = 0; x < image.image_height; ++x) {
        for (unsigned int j = 0; j < image.image_width; ++j) {
            unsigned short int pixel[3];
            pixel[0] = image.pixel[x][j].red;
            pixel[1] = image.pixel[x][j].green;
            pixel[2] = image.pixel[x][j].blue;

            unsigned int aux =  pixel[0] * .393 + pixel[1] * .769 + pixel[2] * .189;
            unsigned int smaller = min(aux, 255);
            image.pixel[x][j].red = smaller;

            aux =  pixel[0] * .349 + pixel[1] * .686 + pixel[2] * .168;
            smaller = min(aux, 255);
            image.pixel[x][j].green = smaller;

            aux =  pixel[0] * .272 + pixel[1] * .534 + pixel[2] * .131;
            smaller = min(aux, 255);
            image.pixel[x][j].blue = smaller;
        }
    }

    return image;
}

Image mirror(Image image) {
    int horizontal = 0;

    Pixel pixel_aux;

    scanf("%d", &horizontal);

    if (horizontal == 1)
        image.image_width /= 2;
    else
        image.image_height /= 2;

    for (int i = 0; i < image.image_height; ++i) {
        for (int j = 0; j < image.image_width; ++j) {
            int x = i, y = j;

            if (horizontal == 1)
                y = image.image_width - 1 - j;
            else
                x = image.image_height - 1 - i;

            pixel_aux.red = image.pixel[i][j].red;
            pixel_aux.green = image.pixel[i][j].green;
            pixel_aux.blue = image.pixel[i][j].blue;

            image.pixel[i][j].red = image.pixel[x][y].red;
            image.pixel[i][j].green = image.pixel[x][y].green;
            image.pixel[i][j].blue = image.pixel[x][y].blue;

            image.pixel[x][y].red = pixel_aux.red;
            image.pixel[x][y].green = pixel_aux.green;
            image.pixel[x][y].blue = pixel_aux.blue;
        }
    }

    return image;
}

Image read_image(Image image) {
    int max_color;
    char image_type[4];

    // read type of image
    scanf("%s", image_type);

    // read width height and color of image
    scanf("%u %u %d", &image.image_width, &image.image_height, &max_color);

    // read all pixels of image
    for (unsigned int i = 0; i < image.image_height; ++i) {
        for (unsigned int j = 0; j < image.image_width; ++j) {
            scanf("%hu %hu %hu", &image.pixel[i][j].red,
                                 &image.pixel[i][j].green,
                                 &image.pixel[i][j].blue);
        }
    }

    return image;
}

void write_image(Image image) {
    // print type of image
    printf("P3\n");
    // print width height and color of image
    printf("%u %u\n255\n", image.image_width, image.image_height);

    // print pixels of image
    for (unsigned int i = 0; i < image.image_height; ++i) {
        for (unsigned int j = 0; j < image.image_width; ++j) {
            printf("%hu %hu %hu ", image.pixel[i][j].red,
                                   image.pixel[i][j].green,
                                   image.pixel[i][j].blue);

        }
        printf("\n");
    }
}


int main() {
    Image image;
    int option, operation;

    image = read_image(image);

    scanf("%d", &option);

    for(int i = 0; i < option; ++i) {

        scanf("%d", &option);

        switch(option) {
            case 1: { // Escala de Cinza
                image = grey_scale(image);
                break;
            }
            case 2: {
                image = sepia(image);
                break;
            }
            case 3: {
                unsigned int scale;
                scanf("%d", &scale);
                blur(image,scale);
                break;
            }
            case 4: { // Rotacao
                int counter;
                scanf("%d", &counter);
                counter %= 4;
                for (int j = 0; j < counter; ++j) {
                    image = rotate_right_90_degrees(image);
                }
                break;
            }
            case 5: {
                image = mirror(image);
                break;
            }
            case 6: {
                invert_colors(image);
                break;
            }
            case 7: {
                int x, y;
                scanf("%d %d", &x, &y);
                int image_width, image_height;
                scanf("%d %d", &image_width, &image_height);

                image = cut_image(image, x, y, image_width, image_height);
                break;
            }
        }
    }

    write_image(image);
    return 0;
}
