; Just a basic EFI application that prints "Hello World!"
BITS 64

main:
    enter 0x20, 0
    mov rcx, [rdx + 0x40]       ; EFI_SYSTEM_TABLE->ConOut
    lea rdx, [rel next_instr]   ; Get address of start of next instruction
next_instr:

    ; The string is 0x2000 bytes before the instruction pointer, except the IP
    ; points to the end of the instruction, which means that we also need to
    ; subtract 15 bytes for this instruction and those that came before it.
    ; That gives us the address of the string. Load it into %rdx to become the
    ; second argument.
    sub rdx, 0x200E             ; Subtract 0x2000, plus 0xE for our offset into .text, to get the start of .rdata.
    call [rcx + 0x08]           ; Call EFI_SIMPLE_OUTPUT_PROTOCOL->OutputString
    xor eax, eax                ; Set eax to 0, which will be our return status.
    leave
    ret
