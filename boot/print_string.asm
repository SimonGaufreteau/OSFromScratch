print_string:
    pusha
    mov ah, 0x0e
loop:
    mov al, [bx]
    int 0x10
    add bx, 1
    mov al, [bx]
    cmp al, 0
    jne loop
    popa
    ret