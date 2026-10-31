<h1 align="center">Hex Dump Viewer</h1>

<div align="center">
  
   [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
   [![Issues](https://custom-icon-badges.herokuapp.com/github/issues-raw/ayaantajwar/hex-dump-viewer?logo=github)](https://github.com/AyaanTajwar/hex-dump-viewer/issues)
   [![Size](https://img.shields.io/github/languages/code-size/ayaantajwar/hex-dump-viewer)](https://github.com/AyaanTajwar/hex-dump-viewer)
   
</div>

Simple CLI hex dump viewer in C.

ㅤ
## Example

First column is the offset. Second column are the raw bytes. Third column is ASCII representation.

```console
$ hd -i examples/Text.txt
00000000 4C 6F 72 65 6D 20 69 70 73 75 6D 20 64 6F 6C 6F Lorem ipsum dolo
00000010 72 20 73 69 74 20 61 6D 65 74 2C 20 63 6F 6E 73 r sit amet, cons
00000020 65 63 74 65 74 75 72 20 61 64 69 70 69 73 63 69 ectetur adipisci
00000030 6E 67 20 65 6C 69 74 2C 20 73 65 64 20 64 6F 20 ng elit, sed do
00000040 65 69 75 73 6D 6F 64 20 74 65 6D 70 6F 72 20 69 eiusmod tempor i
00000050 6E 63 69 64 69 64 75 6E 74 20 75 74 20 6C 61 62 ncididunt ut lab
00000060 6F 72 65 20 65 74 20 64 6F 6C 6F 72 65 20 6D 61 ore et dolore ma
00000070 67 6E 61 20 61 6C 69 71 75 61 2E                gna aliqua.
```
ㅤ
## Build

```powershell
gcc -Wall -Wextra -O2 main.c -o hd.exe
```
ㅤ
## Usage

```powershell
hd -i <file>
```
ㅤ
## Known limitations / planned

- Offsets are `int`, so files over 2 GB show wrong offsets
- Reads byte-by-byte with `fgetc`; switching to `fread` is planned
- More flags and a GUI are planned
