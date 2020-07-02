set -eux
dd if=/dev/zero of=disk.img bs=1M count=4
parted --script disk.img \
    mktable msdos mkpart primary 2048s 100% set 1 boot on