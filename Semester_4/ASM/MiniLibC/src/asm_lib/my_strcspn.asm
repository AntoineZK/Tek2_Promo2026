section .text
    global strcspn
    extern strlen

strcspn:
    mov rdx, 0
    mov r10, 0
    mov r11, rdi
    mov rdi, rsi
    call strlen
    cmp rax, 0
    je error
    mov rsi, rdi
    mov rdi, r11
loop1:
    cmp byte [rdi + rdx], 0
    je end
    mov rcx, 0
loop2:
    mov rax, [rdi + rdx]
    mov rbx, [rsi + rcx]
    cmp al, bl
    je end
    inc rcx
    cmp byte [rsi + rcx], 0
    jne loop2
    je next
next:
    inc rdx
    inc r10
    jmp loop1
end:
    mov rax, r10
    ret
error:
    mov rdi, r11
    call strlen
    ret
