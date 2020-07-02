# rwpart

Simple tools manipulating partitions without root. Can be run against
raw disk image files or block devices. 

## Examples

Basic usage:

```
# Read a partition.
$ rwpart-read ./disk.img 0 > 0.img

# Write a partition.
$ rwpart-write ./disk.img 0 < 0.img

# Print offset of partition 0
$ rwpart-offset ./disk.img 0

# Print size of partition 0
$ rwpart-size ./disk.img 0
```

Creating a bootable image without root:

```
set -eux

# Create disk.
dd if=/dev/zero of=disk.img bs=1M count=128

# Setup partitions.
parted --script disk.img \
    mktable msdos mkpart primary 2048s 100% set 1 boot on

# Setup first partition with syslinux.
rwpart-read ./disk.img 0 > 0.img
mkfs.vfat 0.img
syslinux --install 0.img
rwpart-write ./disk.img 0 < 0.img

# Install master boot record.
syslinux_dir="$(dirname $(realpath $(which syslinux)))"
mbr_bin="$syslinux_dir/../share/syslinux/mbr.bin"
dd bs=440 count=1 conv=notrunc if="$mbr_bin" of=disk.img

# Boot image (Will say no kernel or config).
qemu-system-x86_64 disk.img
```

## Building

Install libfdisk, which comes from util-linux.

Run make:
```
$ make
```

