# asufi - Assembler for UEFI

- [x] Stage 1: Hand-craft a UEFI Hello World executable
- [ ] Stage 2: Write a hex assembler
- [ ] Stage 3: Write a hex++ assembler
- [ ] Stage 4: Write an assembly assembler

## Compiling Hex with only Linux Commands

Run this command

```
awk -F# '{print $1}' hex.txt | tr -d '[:space:]' | xxd -r -p > output.bin
```

## "Debug Builds"

To view the hex, run:

```
awk -F# '{print $1}' hex.txt | tr -d '[:space:]' > output.b16
```

## Getting a UEFI Shell on QEMU

Install OVMF via `sudo apt-get install ovmf`.

Then run:

```bash
sudo qemu-system-x86_64 \
  -drive if=pflash,format=raw,readonly=on,file=/usr/share/OVMF/OVMF_CODE.fd \
  -drive if=pflash,format=raw,file=/usr/share/OVMF/OVMF_VARS.fd
```

## Getting an EFI Application Running on the UEFI Shell in QEMU

Run these steps to copy the EFI binary to the FAT image:

```bash
dd if=/dev/zero of=fat.img bs=1M count=64
mkfs.vfat fat.img
sudo mkdir -p /mnt/fat
sudo mount -o loop fat.img /mnt/fat
sudo cp output.bin /mnt/fat/hello.efi
sudo umount /mnt/fat
```

Then run this to mount that partition.

```bash
sudo qemu-system-x86_64 -m 1024 \
  -drive if=pflash,format=raw,readonly=on,file=/usr/share/OVMF/OVMF_CODE.fd \
  -drive if=pflash,format=raw,file=/usr/share/OVMF/OVMF_VARS.fd \
  -drive file=fat.img,if=virtio,format=raw
```

Press ESC as soon as it boots up, and navigate to
`Boot Manager` > `EFI Internal Shell`. At the shell prompt, type in `fs0:` to
use the first (and only) EFI filesystem. Then run `hello.efi`. If you saw
`Hello World!` on the screen, it succeeded.

## Notes

It seems like, from experience, the EFI shell _requires_ a `.reloc` section,
even if you have no relocations. In this case you will still need to set the
relocs stripped flag and create a `BASERELOC` directory entry, which may have
a size of zero.

The checksum field does NOT have to be correct, at least on OVMF, it seems.
