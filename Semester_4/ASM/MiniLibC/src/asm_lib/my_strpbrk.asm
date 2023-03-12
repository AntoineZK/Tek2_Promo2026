section .text
    global strpbrk
    extern strlen

strpbrk:
    mov rcx, 0
    mov r10, 0
    mov r11, rdi
    mov rdi, rsi
    call strlen
    cmp rax, 0
    je error
    mov rsi, rdi
    mov rdi, r11
loop1:
    cmp byte [rdi + rcx], 0
    je end
    mov rdx, 0
loop2:
    mov rax, [rdi + rcx]
    mov r9, [rsi + rdx]
    cmp al, r9b
    je found
    inc rdx
    cmp byte [rsi + rdx], 0
    je next
    jmp loop2
next:
    inc rcx
    mov r10, rcx
    jmp loop1
found:
    mov rax, rdi
    add rax, rcx
    ret
end:
    mov rax, 0
    ret
error:
    mov rax, 0
    ret
; vide l'un dans l'autre