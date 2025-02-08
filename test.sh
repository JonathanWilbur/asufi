#!/bin/sh
# This is only meant to work on my computer. I'll set up something nicer for you
# if you need it.
awk -F# '{print $1}' hex.txt | tr -d '[:space:]' | xxd -r -p > output.bin
dd if=/dev/zero of=fat.img bs=1M count=64
mkfs.vfat fat.img
sudo mkdir -p /mnt/fat
sudo mount -o loop fat.img /mnt/fat
sudo mkdir -p /mnt/fat/EFI/BOOT
sudo cp output.bin /mnt/fat/hello.efi
sudo cp /usr/share/OVMF/DEBUGX64_Shell.efi /mnt/fat/EFI/BOOT/BOOTX64.EFI
sudo umount /mnt/fat
sudo qemu-system-x86_64 -m 1024 \
  -bios /usr/share/OVMF/DEBUGX64_OVMF.fd \
  -drive if=pflash,format=raw,readonly=on,file=/usr/share/OVMF/DEBUGX64_OVMF_CODE.fd \
  -drive if=pflash,format=raw,file=/usr/share/OVMF/DEBUGX64_OVMF_VARS.fd \
  -drive file=fat.img,if=virtio,format=raw
  # -serial file:serial.log \
  # -debugcon file:debug.log -global isa-debugcon.iobase=0x402
