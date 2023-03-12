section .text
    global strlen

strlen:
    mov rax, 0
loop:
    cmp byte [rdi + rax], 0
    je end
    inc rax
    jmp loop
end:
    ret
