# BMP Image Processing Library

This library, inspired by concepts from the "cips2ed" book, is a comprehensive C library created from scratch for BMP image processing. It includes a range of image transformations, filters, cropping capabilities, and more, and it is compiled as a shared object `.so`.

## Features

- **Edge Detection:** Identify edges within images to highlight significant features.
- **Cropping:** Trim images to focus on specific regions.
- **Black and White Conversion:** Transform images into grayscale.
- **Histogram Generation:** Analyze and modify image brightness and contrast through histograms.
- **Background Removal:** Erase specific backgrounds from images.

The library is designed to be scalable, with ongoing developments to extend its functionalities.

## Getting Started

### Compiling the Library

1. Clone the repository:
    ```bash
    git clone https://github.com/DanielW98/BMP_Image_Processing.git
    cd BMP_Image_Processing
    ```

2. Compile the library using the provided Makefile:
    ```bash
    make -f Makefile
    ```

### Creating a Shared Library

1. After compiling, create a shared library from the object files:
    ```bash
    gcc -shared -o libbmp.so bmp_new/*.o
    ```

2. Move the shared library to a standard library path or a custom path:
    ```bash
    mv libbmp.so /usr/local/lib
    ```

    For a custom path, remember to set the `LD_LIBRARY_PATH` environment variable:
    ```bash
    export LD_LIBRARY_PATH=/path/to/your/library:$LD_LIBRARY_PATH
    ```

### Linking the Library

When compiling your application that uses the BMP library, link against the shared library:

```bash
gcc -o your_app your_app.c -lbmp
```

## Usage

Include the library in your C project and use the provided functions to manipulate BMP images. Here's a quick example to crop an image:

```c
#include "bmp.h"

int main() {
    BMP_Image *image = BMP_Open("path_to_image.bmp");
    BMP_Image *cropped_image = BMP_Crop(image, 140, 595, 449, 449);
    BMP_Save(cropped_image, "path_to_save_image.bmp");
    BMP_Free(image);
    BMP_Free(cropped_image);
    return 0;
}
```

## Contributing

Your contributions are very valuable! Feel free to enhance existing functionalities or add new ones to the BMP Image Processing library. Please fork the repository and submit a pull request with your improvements.

## License

The library is provided under the MIT License, detailed in the LICENSE file.

Project inception: March 2021.