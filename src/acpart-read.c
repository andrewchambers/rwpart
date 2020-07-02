#include <err.h>
#include <stdlib.h>

#include <libfdisk/libfdisk.h>

int main(int argc, char **argv) {
  int rc, part_n;
  uint64_t part_start, part_sz, total_read;
  struct fdisk_context *ctx;
  struct fdisk_partition *pa;
  char buf[16384];
  FILE *f;

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

  part_start = fdisk_get_sector_size(ctx) * fdisk_partition_get_start(pa);
  part_sz = fdisk_get_sector_size(ctx) * fdisk_partition_get_size(pa);

  fdisk_unref_partition(pa);
  fdisk_unref_context(ctx);

  f = fopen(argv[1], "r");
  if (!f)
    err(1, "unable to open %s", argv[1]);

  if (fseek(f, part_start, SEEK_SET) != 0)
    err(1, "unable to seek");

  total_read = 0;
  while (total_read != part_sz) {
    size_t n_read, to_read;
    
    to_read = sizeof(buf);
    if (total_read + to_read > part_sz)
      to_read = part_sz - total_read;

    n_read = fread(buf, 1, to_read, f);
    if (n_read != to_read) 
        err(1, "unable to read partition");
    if (fwrite(buf, 1, n_read, stdout) != n_read)
      err(1, "error writing ouput");
    total_read += n_read;
  }

  fclose(f);

  if (fflush(stdout) != 0)
    errx(1, "unable to flush data");

  return 0;
}