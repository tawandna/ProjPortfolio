SHELL := /bin/bash
FLAG =-Wall -Wextra -Werror
FILE = cat_test.txt
CHECK = valgrind -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all

all: s21_cat tests
s21_cat: 
	gcc $(FLAG) Cat.c -o s21_cat

tests:
	-diff <(./s21_cat $(FILE)) <(cat $(FILE))
	-diff <(./s21_cat -e $(FILE)) <(cat -e $(FILE))
	-diff <(./s21_cat -t $(FILE)) <(cat -t $(FILE))
	-diff <(./s21_cat -s $(FILE)) <(cat -s $(FILE))
	-diff <(./s21_cat --squeeze-blank $(FILE)) <(cat -s $(FILE))
	-diff <(./s21_cat -n $(FILE)) <(cat -n $(FILE))
	-diff <(./s21_cat --number $(FILE)) <(cat -n $(FILE))
	-diff <(./s21_cat -b $(FILE)) <(cat -b $(FILE))
	-diff <(./s21_cat --number-nonblank $(FILE)) <(cat -b $(FILE))
	-diff <(./s21_cat --number-nonblank --number $(FILE)) <(cat --number-nonblank --number $(FILE))
	-diff <(./s21_cat --number-nonblank --squeeze-blank $(FILE)) <(cat --number-nonblank --squeeze-blank $(FILE))
	-diff <(./s21_cat --number --squeeze-blank $(FILE)) <(cat --number --squeeze-blank $(FILE))
	-diff <(./s21_cat -et $(FILE)) <(cat -et $(FILE))
	-diff <(./s21_cat -snb $(FILE)) <(cat -snb $(FILE))
	-diff <(./s21_cat -etb $(FILE)) <(cat -etb $(FILE))
	-diff <(./s21_cat -etsnb $(FILE)) <(cat -etsnb $(FILE))
	#------//Memory leak Tests//------
	 $(CHECK) ./s21_cat $(FILE)
	 #$(CHECK) ./s21_cat -n $(FILE)
	 #$(CHECK) ./s21_cat -e $(FILE)
	 #$(CHECK) ./s21_cat -b $(FILE)
	 #$(CHECK) ./s21_cat -t $(FILE)
	 #$(CHECK) ./s21_cat -s $(FILE)
	 #$(CHECK) ./s21_cat -etsnb $(FILE)
	 #$(CHECK) ./s21_cat $(FILE)

clean:
	rm -rf s21_cat
