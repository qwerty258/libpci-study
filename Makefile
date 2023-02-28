
pcidump2cvs:
	gcc pcidump2cvs.c -o pcidump2cvs.elf -lpci

clean:
	rm *.o *.elf
