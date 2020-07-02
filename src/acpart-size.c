#include <err.h>
#include <stdlib.h>

#include <libfdisk/libfdisk.h>

int main(int argc, char **argv) {
  int rc, part_n;
  uint64_t part_sz;
  struct fdisk_context *ctx;
  struct fdisk_partition *pa;

  if (argc < 3)
    errx(1, "usage: %s DEV/IMAGE PART", argv[0]);

  ctx = fdisk_new_context();
  if (!ctx)
    errx(1, "failed to allocate context");

  rc = fdisk_assign_device(ctx, argv[1], 1);
  if (rc != 0)
    errx(1, "unable to assign device");

  part_n = atoi(argv[2]);

  pa = NULL;
  rc = fdisk_get_partition(ctx, part_n, &pa);
  if (rc != 0)
    errx(1, "unable to get partition %s", argv[2]);

  if (!fdisk_partition_has_size(pa))
    errx(1, "unable to get partition size");

  part_sz = fdisk_get_sector_size(ctx) * fdisk_partition_get_size(pa);

  fdisk_unref_partition(pa);
  fdisk_unref_context(ctx);

  printf("%ld\n", part_sz);

  if (fflush(stdout) != 0)
    errx(1, "unable to flush data");

  if (ferror(stdout))
    errx(1, "io error");    

  return 0;
}