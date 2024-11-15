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

- [1.0 changelog](docs/change-logs/CHANGELOG-1.0.md)

## For Developers

### [Design Specifications](docs/design-specs/design-specs-1.0.md)

### Building from Source Code

Used build system: `CMake 3.29` - `Desktop Qt 6.6.2 MinGW 64-bit`

Make sure to specify the compiler path in CMake options:
`"-DCMAKE_PREFIX_PATH=C:/path/to/Qt/x.x.x/mingw_64"`

## Collaborators

- [Mikhael Mounay Khalil](https://github.com/MikhaelMounay)
- [Kirollos Mounir](https://github.com/KirollosFady)
- Marcelino Sedhum
- [Omar Khalil](https://github.com/omarramy22)
- [Omar Youssef](https://github.com/omaaryouussef)
