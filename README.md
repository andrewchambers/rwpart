# acpart

Simple tools manipulating partitions without root. Can be run against
raw disk image files or block devices. 

## Examples

Basic usage:

```
# Read a partition.
$ acpart-read ./disk.img 0 > out.bin

# Write a partition.
$ acpart-write ./disk.img 0 < in.bin

# Print offset of partition 0
$ acpart-offset ./disk.img 0

# Print size of partition 0
$ acpart-size ./disk.img 0
```

Creating a bootable ext4 image without root:

```
TODO...
```

## Building

Install libfdisk, which comes from util-linux.

Run make:
```
$ make
```

