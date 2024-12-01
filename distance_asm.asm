section .text
bits 64

global calculate_distances_asm

calculate_distances_asm:
    ; Function prologue
    push rbp
    mov rbp, rsp
    push rbx

    ; Parameters (n, X1, X2, Y1, Y2, Z) in rdi, rsi, rdx, rcx, r8, r9
    mov r10, rdi        ; r10 = n
    mov r11, rsi        ; r11 = X1
    mov r12, rdx        ; r12 = X2
    mov r13, rcx        ; r13 = Y1
    mov r14, r8         ; r14 = Y2
    mov r15, r9         ; r15 = Z

loop_start:
    cmp r10, 0          ; Check if n == 0
    jz loop_end

    ; Load X1[i] and X2[i]
    movss xmm0, [r11]   ; xmm0 = X1[i]
    movss xmm1, [r12]   ; xmm1 = X2[i]
    subss xmm1, xmm0    ; xmm1 = X2[i] - X1[i]
    mulss xmm1, xmm1    ; xmm1 = (X2[i] - X1[i])^2

    ; Load Y1[i] and Y2[i]
    movss xmm2, [r13]   ; xmm2 = Y1[i]
    movss xmm3, [r14]   ; xmm3 = Y2[i]
    subss xmm3, xmm2    ; xmm3 = Y2[i] - Y1[i]
    mulss xmm3, xmm3    ; xmm3 = (Y2[i] - Y1[i])^2

    ; Compute sqrt(dx^2 + dy^2)
    addss xmm1, xmm3    ; xmm1 = dx^2 + dy^2
    sqrtss xmm1, xmm1   ; xmm1 = sqrt(dx^2 + dy^2)

    ; Store result in Z[i]
    movss [r15], xmm1   ; Z[i] = sqrt(dx^2 + dy^2)

    ; Increment pointers and decrement n
    add r11, 4          ; X1++
    add r12, 4          ; X2++
    add r13, 4          ; Y1++
    add r14, 4          ; Y2++
    add r15, 4          ; Z++
    dec r10             ; n--
    jmp loop_start      ; Repeat

loop_end:
    pop rbx
    pop rbp
    ret
