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
![467552079_929909779067732_5412604582251584298_n](https://github.com/user-attachments/assets/d7cd9ecf-e2d2-4c05-957f-2948a16c4819)
![462575662_941653487292336_7320289220641923816_n](https://github.com/user-attachments/assets/63c15242-a4cd-4fb2-a4b6-0fff42a0e485)
![462562066_1132490791779564_813148806912308165_n](https://github.com/user-attachments/assets/ca6e0639-d108-4cd2-a6a0-8dace0d29931)
| Kernel Number (Size of vectors) | Type  |  Time (seconds)  |
|:-------------:|:-----:|:----------------:|
| 1 (2^20)      | ASM   | 0.001267 seconds |
|               | C     | 0.009800 seconds |
| 2 (2^24)      | ASM   | 0.020833 seconds |
|               | C     | 0.154867 seconds |
| 3 (2^27)      | ASM   | 0.172067 seconds |
|               | C     | 1.242567 seconds |

After running the files, these were the results that were given by the program. It is clear that the SIMD implementation in assembly has a faster runtime that the implementation in C. In C, computation is done over and over which can take time for the memory while the implementation in assembly can perform the same computation to multiple values in a singular instruction. This is proven when the vector size is increased, the gap between the average time of execution also increases. 

# II. PROGRAM OUTPUT WITH CORRECTNESS CHECKS
![image](https://github.com/user-attachments/assets/aa4cb38b-bb3b-49e6-92d3-18fecb8d3d1c)
![image](https://github.com/user-attachments/assets/9e2f8caa-9a47-41f7-b596-7fe9df774bc8)
![image](https://github.com/user-attachments/assets/2e849d6c-29e2-4419-808a-604a543adc26)
![image](https://github.com/user-attachments/assets/a5280692-fe1a-4fae-94b8-e51405ed8ec6)
![image](https://github.com/user-attachments/assets/c6ff8586-dd3a-4edb-a62b-756c6c687375)

# III. SHORT VIDEOS
https://github.com/user-attachments/assets/5f6208a1-7043-4e4a-bc0f-4db08424cd6a


