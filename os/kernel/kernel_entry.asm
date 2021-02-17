extern main ;tell assembler that main is the external function so ignore the assembler / compiler if main is not found in code.

_start:
  call main ;call external main function.
  jmp $
    


