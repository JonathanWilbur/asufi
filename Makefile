# I created this Makefile so we could write hex programs in assembly first

hex/hello.hex:	pe/hello.hex text/hello.S
	nasm -f bin text/hello.S -o text/hello.bin
	ls -lah text/hello.bin
	truncate -s 1024 text/hello.bin
	cat pe/hello.hex > hex/hello.hex
	ndisasm -b 64 text/hello.bin | awk '{print $$2, "\t\t\t#", $$3, $$4, $$5, $$6, $$7, $$8, $$9, $$10, $$11, $$12, "offset", $$1, "\t:"}' >> hex/hello.hex
	rm text/hello.bin

# TODO: Create a target to spin up the VM
