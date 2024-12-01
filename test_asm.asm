section .text
    global asm_distance



;xmm0: x1 
;xmm1: x2
;xmm2: y1 
;xmm3: y2

;ret
;xmm0: [(x1 - x2)^2 + (y1 - y2)^2]

asm_distance:

    subsd xmm0, xmm1         
    mulsd xmm0, xmm0         
    subsd xmm2, xmm3         
    mulsd xmm2, xmm2         
    addsd xmm0, xmm2         
    sqrtsd xmm0, xmm0       

    ret
