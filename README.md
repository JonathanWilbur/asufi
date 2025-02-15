# asufi - Assembler for UEFI

- [x] Stage 1: Hand-craft a UEFI Hello World executable
- [ ] Stage 2: Write a hex assembler
- [ ] Stage 3: Write a hex++ assembler
- [ ] Stage 4: Write an assembly assembler

## Why?

I am trying to write a C compiler that:

1. Runs in a UEFI environment (difficulty: impossible)
2. Can compile the Linux kernel, even if it is just a really old simple version. (difficulty: impossible)

I want this C compiler to be bootstrapped using only a very small, auditable
binary so you can ensure that there are no backdoors whatsoever in the Linux
kernel that you build, including those that might have been introduced from
build tools rather than the source code. So we need this small, auditable binary
to build something, perhaps recursively, until we bootstrap a UEFI C compiler.

This small, auditable binary will be a program that can be viewed and understood
by using the UEFI shell's standard `hexedit` command, so that nothing except the
underlying firmware has to be trusted. Further, this binary must be able to
build itself. I can think of no better solution than a hexadecimal assembler.

The idea is that it would simply take hexadecimal bytes and convert them to
bytes, but these hexadecimal bytes could be split across lines and have comments
so that each byte can be annotated with what it actually does, thereby making
this tiny binary extremely understandable and reproducible.

One that is working, the idea is to build a "hex++" assembler, which will add
features like padding, labels, and maybe macros. After this is working, it is
my hope that I can build a C compiler based off ChibiCC that can, in turn,
compile a modified TinyCC that compiles the Linux Kernel.

I do not consider it cheating to compile these things on a non-trusted machine
such as my personal computer, then convert the byte code back into hex, as long
as I can annotate the hex and explain what almost every instruction is doing. I
am assuming that, since a hexadecimal file is not an executable, it cannot be
used to "hack" your EFI environment, so it is valid to include these hex files
in the EFI image, as long as they are actually assembled / compiled with
trustworthy, audited tools. However, I do not want to rely on gigantic hex
files, because, at some point, it would take forever to review them for a
sufficiently complex program like TinyCC. As such, I am hoping to produce a
hex file that is less than 10K bytes or so that can compile TinyCC for UEFI,
It may even be sufficient to use ChibiCC to produce the assembly for TinyCC, and
write an assembler in hex++. Time and experimentation will tell which approach
is preferable.

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

