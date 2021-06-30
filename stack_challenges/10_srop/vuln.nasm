; nasm vuln.nasm -f elf64
; ld vuln.o -o vuln -z noexecstack

global _start

section .text
_start:
    ;char buf[0x100]
    enter 0x100, 0

    call timer

    ; write(1, message, len)
    mov rax, 1
    mov rdi, 1
    mov rsi, message
    mov rdx, len
    syscall

    ; read(0, buf, 0x1000)
    mov rax, 0
    mov rdi, 0
    mov rsi, rsp
    mov rdx, 0x1000
    syscall

    ; epilogue
    leave
    ret

timer:
    ;alarm
    mov rdi, 0xf
    mov rax, 0x25
    syscall
    ret

section .data
    message: db "To pass this challenge you need to get a shell using /bin/sh"
    len: equ $-message
