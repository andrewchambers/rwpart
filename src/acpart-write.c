#include <err.h>
#include <stdlib.h>

#include <libfdisk/libfdisk.h>

int main(int argc, char **argv) {
  int rc, part_n;
  uint64_t part_start, part_sz, total_written;
  struct fdisk_context *ctx;
  struct fdisk_partition *pa;
  char buf[16384];
  FILE *f;

  if (argc < 3)
    errx(1, "usage: %s DEV/IMAGE PART < data", argv[0]);

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

  f = fopen(argv[1], "rb+");
  if (!f)
    err(1, "unable to open %s", argv[1]);

  if (fseek(f, part_start, SEEK_SET) != 0)
    err(1, "unable to seek");

  total_written = 0;

  while (1) {
    size_t n_read;

    n_read = fread(buf, 1, sizeof(buf), stdin);
    if (n_read == 0) {
      if (!feof(stdin))
        err(1, "unable to read stdin");
      break;
    }
    if ((total_written + n_read) > part_sz)
      errx(1, "input data larger than partition size");

    if (fwrite(buf, 1, n_read, f) != n_read)
      err(1, "error writing partition");

    total_written += n_read;
  }

  if (fflush(f) != 0)
    errx(1, "unable to flush data");

  fclose(f);

  return 0;
}