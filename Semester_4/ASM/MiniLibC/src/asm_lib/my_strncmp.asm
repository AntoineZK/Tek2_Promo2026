section .text
    global strncmp

strncmp:
	mov rcx, 0
loop:
	mov al, [rdi]
	mov bl, [rsi]
	cmp al, 0
	je end
	cmp bl, 0
	je end
	cmp al, bl
	jne end
	inc rdi
	inc rsi
	inc rcx
	cmp rdx, rcx
	je end
	jmp loop
end:
	movzx rax, al
	movzx rbx, bl
	sub rax, rbx
	ret
