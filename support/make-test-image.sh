set -eux
# Create disk.
dd if=/dev/zero of=disk.img bs=1M count=128

# Setup partitoins.
parted --script disk.img \
    mktable msdos mkpart primary 2048s 100% set 1 boot on

# Setup first partition with syslinux.
./acpart-read ./disk.img 0 > 0.img
mkfs.vfat 0.img
syslinux --install 0.img
./acpart-write ./disk.img 0 < 0.img

# Install master boot record.
syslinux_dir="$(dirname $(realpath $(which syslinux)))"
mbr_bin="$syslinux_dir/../share/syslinux/mbr.bin"
dd bs=440 count=1 conv=notrunc if="$mbr_bin" of=disk.img

