# Huffman File Zipper

> A desktop application to compress text files based on the lossless compression algorithm [Huffman Coding](https://en.wikipedia.org/wiki/Huffman_coding).

## User Manual

### Compressing a Text file

1. Press the *Browse* button and choose a `.txt` file.
2. If you want to save the compressed file as a binary file, check the *Save compressed data to binary file* checkbox.
3. If you want to save the file to a human-readable format instead, make sure to uncheck this checkbox.
4. Press *Compress* and choose a destination to save the compressed file to.
5. Happy compression! :)

### Decompressing an HFZ or HFZB file

1. Press the *Browse* button and choose a `.hfz` or a `.hfzb` file.
2. Press *Decompress* and choose a destination to save the extracted file to.
3. Happy extraction, too! :)

## Change Logs

- [1.0 changelog](change-logs/CHANGELOG-1.0.md)

## For Developers

### [Design Specifications](design-specs/design-specs-1.0.md)

### Building from Source Code

Used build system:
- `CMake 3.29` [![CMake 3](https://img.shields.io/badge/-CMake%203-064F8C?logo=cmake&logoColor=white&style=flat-square)](https://cmake.org/)
- `Desktop Qt 6.6.2 MinGW 64-bit` [![Qt C++ 6](https://img.shields.io/badge/-Qt%20C%2B%2B%206-41CD52?logo=Qt&logoColor=white&style=flat-square)](https://www.qt.io/)

> Make sure to specify the compiler path in CMake options:
`"-DCMAKE_PREFIX_PATH=C:/path/to/Qt/x.x.x/mingw_64"`

Dependencies:
- `GoogleTest 1.15.2` [![CMake 3](https://img.shields.io/badge/-GoogleTest-4285F4?logo=Google&logoColor=white&style=flat-square)](https://github.com/google/googletest)

## Collaborators

- [Mikhael Mounay Khalil](https://github.com/MikhaelMounay)
- [Marcelino Sedhum](https://github.com/marcelinoSamer)
- [Kirollos Mounir](https://github.com/KirollosFady)
- [Omar Khalil](https://github.com/omarramy22)
- [Omar Youssef](https://github.com/omaaryouussef)
