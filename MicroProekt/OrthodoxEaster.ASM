format PE console
entry start

include 'win32ax.inc'

section '.data' data readable writable

        strGetYear   db 'Hello! this is Orthodox Easter calculator,write your year? ',10, 0
        strIncorYear db 'Sorry, Incorrect year, your year should be from 1970 and up to 3000', 10, 0
        aprilEaster db 'Easter will be on %d of april in %d',10,0
        mayEaster db 'Easter will be on %d of may in %d',10,0
        strScanInt   db '%d', 0

        year         dd 0
        a            dd ?
        b            dd ?
        c            dd ?
        d            dd ?
        e            dd ?
        f            dd ?
        sum          dd 0

section '.code' code readable executable

start:
; 1) vector input
        push strGetYear;giving a user to input a year
        call [printf];showing that

        push year
        push strScanInt
        call [scanf]
        mov eax, [year]
        cmp eax, 1969;trying to check value of input year if its correct
        jg  calcYear;the first check complete
fail:
; fail year. it should be more than 1970 and less great than 3000
        push strIncorYear;showing danger message, that input was incorrect
        call [printf]
        jmp finish;end of program
calcYear:
        cmp eax, 3000;second check of input year
        jg fail;end of program
        ;first division
        mov edx,0;clearing register for clear computation
        mov ecx, 19 ;number to div for
        div ecx   ;division
        mov [a],edx ;saving result to the first coef a=year%19
        ;second division
        mov eax, [year] ;taking year again to cash
        mov edx,0;clearing register for clear computation
        mov ecx, 4; number to divide for
        div ecx ;making division
        mov [b],edx;saving 2ond coef b = year%4
        ;third division
        mov eax, [year] ;taking year again to cash
        mov edx,0;clearing register for clear computation
        mov ecx, 7; number to divide for
        div ecx
        mov [c],edx; saving to c coef c = year%7
        ;first sum
        mov  eax, [a] ; ax = 5
        mov edx,0     ;edx = 0 ;clearing register for clear computation
        mov  ecx, 19  ; cx = 19
        mul  ecx      ; ax = ax * cx   ; actually dx:ax = ax * cx
        add eax,15  ;eax = 19a+15
        ;forth division
        mov edx,0   ;clearing register for clear computation
        mov ecx, 30
        div ecx
        mov [d],edx  ; d = (19a+15)%30
        ;second sum
        mov  eax, [b] ; ax = 5
        mov edx,0     ;edx = 0;clearing register for clear computation
        mov  ecx, 2  ; cx = 2
        mul  ecx      ; ax = ax * cx   ; actually dx:ax = ax * cx
        add [sum], eax  ;sum = 2b
        ;third sum
        mov  eax, [c] ; ax = 5
        mov edx,0     ;edx = 0;clearing register for clear computation
        mov  ecx, 4  ; cx = 4
        mul  ecx      ; ax = ax * cx   ; actually dx:ax = ax * cx
        add [sum], eax ;sum = 2b+4c
        ;forth sum
        mov  eax, [d] ; ax = 5
        mov edx,0     ;edx = 0 ;clearing register for clear computation
        mov  ecx, 6  ; cx = 6
        mul  ecx      ; ax = ax * cx   ; actually dx:ax = ax * cx
        add [sum], eax ;sum = 2b+4c+6d
        ;fifth sum
        add [sum], 6 ;sum = 2b+4c+6d+6
        ;fifth division
        mov eax, [sum] ; sum = 2b+4c+6d+6
        mov edx,0;clearing reg for clear computation
        mov ecx, 7; number to divide for
        div ecx ;dividing
        mov [e],edx;saving res to e coef  e = sum%7
        ;sixth sum
        mov  eax, [d]
        add eax, [e]
        add [f], eax ;e+d=f
        cmp [f],26 ; if grater than it will be amy
        jg may ;easter will be in may if f > 26
        ;continue if april
        ;seventh sum
        add [f],4; f +=4
        push [year]
        push [f]
        push aprilEaster
        call [printf]



finish:
      call [getch]
      push 0
      call [ExitProcess]
may:
    add [f],-26;f-=26
    push [year]
    push [f]
    push mayEaster
    call [printf]
    jmp finish

                                

;-------------------------------third act - including HeapApi--------------------------
                                                 
section '.idata' import data readable
    library kernel, 'kernel32.dll',\
            msvcrt, 'msvcrt.dll',\
            user32,'USER32.DLL'

include 'api\user32.inc'
include 'api\kernel32.inc'
    import kernel,\
           ExitProcess, 'ExitProcess',\
           HeapCreate,'HeapCreate',\
           HeapAlloc,'HeapAlloc'
  include 'api\kernel32.inc'
    import msvcrt,\
           printf, 'printf',\
           scanf, 'scanf',\
           getch, '_getch'