section .text
    global memcpy

memcpy:
    mov rax, rdi
    mov rcx, 0
loop:
    cmp rcx, rdx
    je end
    mov r8b, [rsi + rcx]
    mov [rax + rcx], r8b
    inc rcx
    jmp loop
end:
    ret