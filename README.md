# QuickLing
## Text File Translator

This is a simple GUI wrapper written in C for translating text files using the translate-shell

## Features

- Translate text files from one language to another.
- Support for various language pairs.
- User-friendly interface.

## Example
<img src="https://github.com/TamirRothschild/QuickLing/blob/main/assets/example3.png" alt="gtk-translate"/>

## Requirements

- Linux-based operating system.
- trans command-line utility. Install it using the following command:
###### Debian
  ```bash
  sudo apt-get install translate-shell
  ```
###### Arch
  ```bash
  sudo pacman -S translate-shell
  ```
###### Fedora
  ```bash
  sudo dnf install translate-shell
  ```

## How To Build
###### Terminal:
```bash
git clone https://github.com/TamirRothschild/QuickLing
cd /source
gcc `pkg-config --cflags --libs gtk+-3.0` -o translator main.c
./translator
```

## Thanks
https://github.com/soimort/translate-shell
