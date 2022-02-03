if "%1" == "cof" goto coff_file_format
:elf_file_format
@echo dump for ELF/DWARF
"C:\Program Files (x86)\Microchip\xc16\v1.35\bin\xc16-objdump" -omf=elf -g -S %2\%3.%4.elf > %2\%3.%4.lst
goto end
:coff_file_format
@echo dump for COFF
"C:\Program Files (x86)\Microchip\xc16\v1.35\bin\xc16-objdump" -omf=coff -g -S %2\%3.%4.cof > %2\%3.%4.lst
:end