section .text
    global memset

memset:
    mov rax, rdi
    mov rcx, 0
loop:
    cmp rdx, rcx
    je end
    mov byte [rax + rcx], sil
    inc rcx
    jmp loop
end:
    ret