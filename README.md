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
