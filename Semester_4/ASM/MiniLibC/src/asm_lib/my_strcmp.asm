section .text
    global strcmp

strcmp:
    mov rdx, 0
    mov rcx, 0
loop:
    mov rax, [rdi + rdx]
    mov rbx, [rsi + rcx]
    cmp al, bl
    jne not_equal
    cmp al, 0
    je equal
    cmp bl, 0
    je not_equal
    inc rdx
    inc rcx
    jmp loop
not_equal:
    cmp al, bl
    jg greater
    jl less
greater:
    mov rax, 1
    ret
less:
    mov rax, -1
    ret
equal:
    mov rax, 0
    ret