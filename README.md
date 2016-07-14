# README #

Code to create all the downsample volumes of an input volume

## Executable Parameters #
The program can run without any parameters and will load a volume of size 256x256x256 localted in "./RAW/volume.raw". Some parameters can be passed to the program in the following way: 

```sh
$ program <volume_path> <width> <height> <depth> <bits>
```

where **<volume_path>** is the path of the file containing the volume; **<width>, <height>,** and **<depth>** the dimensions of the volume; and **<bits>** the number of bits of the volume (8 or 16).

