section .text
    global strchr

strchr:
    mov rax, rdi
loop:
    cmp byte [rax], sil
    je end
    cmp byte [rax], 0
    je end_error
    inc rax
    jmp loop
end_error:
    mov rax, 0
    jmp end
end:
    ret
