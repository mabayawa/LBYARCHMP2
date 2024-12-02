nasm -f win64 distance_asm.asm
gcc -c main.c -o cfile.obj -m64
gcc cfile.obj distance_asm.obj -o cfile.exe -m64
cfile.exe