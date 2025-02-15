# I created this Makefile so we could write hex programs in assembly first
io.hex:	io.S
	nasm -f bin io.S -o io.bin
	# hexdump -v -e '/1 "%02x "' io.bin > io.hex
	ndisasm -b 64 io.bin | awk '{print $$2, "\t\t\t#", $$3, $$4, $$5, $$6, $$7, $$8, $$9, $$10, $$11, $$12, "offset", $$1, " :"}' > io.hex
	rm io.bin
