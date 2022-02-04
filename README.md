# rpncalc

simple rpn calculator inspired by emacs calc

To build:
```sh
DIR=build
meson $DIR
cd $DIR
ninja
```
To execute:
```sh
./rpncalc
```
Installation (inside build dir):
```sh
# needs root perms
sudo ninja install # alternatively: sudo samu install if you are using samurai
```
![screenshot](https://user-images.githubusercontent.com/26441684/152613858-7ac34fb0-496f-4716-a4ba-044a7f21d6c1.png)
