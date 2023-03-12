section .text
    global strcasecmp

strcasecmp:
    mov rax, 0
    mov rbx, 0
loop:
    mov al, byte [rdi]
    mov bl, byte [rsi]
check_rax:
    cmp al, 'A'
    jl check_rbx
    cmp al, 'Z'
    jg check_rbx
    sub al, 'A' - 'a'
check_rbx:
    cmp bl, 'A'
    jl loop_part2
    cmp bl, 'Z'
    jg loop_part2
    sub bl, 'A' - 'a'
loop_part2:
    cmp al, bl
    jne check_diff
    cmp byte [rdi], 0
    je end
    inc rdi
    inc rsi
    jmp loop
check_diff:
    sub rax, rbx
end:
    ret
