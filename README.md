# acpart

Simple tools for reading/writing partitions without root.

## Examples

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
