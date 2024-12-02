section .text
bits 64

global calculate_distances_asm

calculate_distances_asm:
    ; Parameters (n, X1, X2, Y1, Y2, Z) in rcx, rdx, r8, r9, [rsp + 40], [rsp + 48]
    mov r10, rcx               ; r10 = n
    mov r11, rdx               ; r11 = X1
    mov r12, r8                ; r12 = X2
    mov r13, r9                ; r13 = Y1
    mov r14, [rsp + 40]        ; r14 = Y2
    mov r15, [rsp + 48]        ; r15 = Z

loop_start:
    ; Load X1[i] and X2[i]
    movss xmm0, [r11]  ; x1
    movss xmm1, [r12]  ; x2

    ; Load Y1[i] and Y2[i]
    movss xmm2, [r13]  ; y1
    movss xmm3, [r14]  ; y2

    subss xmm1, xmm0    ; xmm1 = X2[i] - X1[i]
    subss xmm3, xmm2    ; xmm3 = Y2[i] - Y1[i]

    mulss xmm1, xmm1    ; xmm1 = (X2[i] - X1[i])^2
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
    jnz loop_start      ; Repeat
    ret
