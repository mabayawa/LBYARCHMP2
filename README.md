# LBYARCHMP2
Submission for MP2 in LBYARCH
<br>
<br>
Submitted By:
<br>
BIACORA, MARCUS BRUNO MAANO
<br>
ROBLES, VANCE GYAN MAGNAYE
<br>
<br>
Submitted To:
<br>
SIR CARLO DELA CRUZ ADRIANO
<br>
Section S11

# COMPILATION COMMANDS
```
run
```
or

```
nasm -f win64 distance_asm.asm
gcc -c main.c -o cfile.obj -m64
gcc cfile.obj distance_asm.obj -o cfile.exe -m64
cfile.exe
```
# SPECS
![specs1](https://github.com/user-attachments/assets/c60febc4-f7e9-4469-982a-16c3691c93fe)
![specs2](https://github.com/user-attachments/assets/99c7bfe7-821f-4f2c-8e1b-62fb69441895)

# I. COMPARATIVE EXECUTION TIME AND ANALYSIS
![image](https://github.com/user-attachments/assets/e6f4614a-87e9-458f-821d-3f20e50b21a5)
![image](https://github.com/user-attachments/assets/30cf6192-c600-403f-89c8-2138b4cc1ae3)
![image](https://github.com/user-attachments/assets/10a019b8-5766-4ca1-a4c4-ba866c03ed6e)

| Kernel Number (Size of vectors) | Type  |  Time (seconds)  |
|:-------------:|:-----:|:----------------:|
| 1 (2^20)      | ASM   | 0.001333 |
|               | C     | 0.009133 |
| 2 (2^24)      | ASM   | 0.020633 |
|               | C     | 0.152767 |
| 3 (2^28)      | ASM   | 0.337033 |
|               | C     | 2.468700 |

| Size of vectors | Difference in Time |
|:-----:|:--------:|
| 2^20  |  0.0078  |
| 2^24  | 0.132134 |
| 2^28  | 2.131667 |

After running the files, these were the results that were given by the program. It is clear that the SIMD implementation in assembly has a faster runtime that the implementation in C. In C, computation is done over and over which can take time for the memory while the implementation in assembly can perform the same computation to multiple values in a singular instruction. This is proven when the vector size is increased, the gap between the average time of execution also increases. 

# II. PROGRAM OUTPUT WITH CORRECTNESS CHECKS
![image](https://github.com/user-attachments/assets/aa4cb38b-bb3b-49e6-92d3-18fecb8d3d1c)
![image](https://github.com/user-attachments/assets/9e2f8caa-9a47-41f7-b596-7fe9df774bc8)
![image](https://github.com/user-attachments/assets/2e849d6c-29e2-4419-808a-604a543adc26)
![image](https://github.com/user-attachments/assets/a5280692-fe1a-4fae-94b8-e51405ed8ec6)
![image](https://github.com/user-attachments/assets/c6ff8586-dd3a-4edb-a62b-756c6c687375)

# III. SHORT VIDEOS
https://github.com/user-attachments/assets/5f6208a1-7043-4e4a-bc0f-4db08424cd6a


