section .text
    global strrchr
    extern strlen

strrchr:
    call strlen
    add rax, rdi
loop:
    cmp byte [rax], sil
    je end
    cmp rax, rdi
    je end_error
    dec rax
    jmp loop
end_error:
    mov rax, 0
    ret
end:
    ret
