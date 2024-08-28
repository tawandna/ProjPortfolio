SHELL := /bin/bash
FLAG =-Wall -Wextra -Werror
FILE = t1.txt t2.txt t3.txt
CHECK = valgrind -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all
PROG = ./s21_grep

all: s21_grep tests
s21_grep:
	gcc $(FLAG) Grep.c -o s21_grep

tests:
	-diff <($(PROG) He $(FILE)) <(grep He $(FILE))
	-diff <($(PROG) -e He $(FILE)) <(grep -e He $(FILE))
	-diff <($(PROG) -i He $(FILE)) <(grep -i He $(FILE))
	-diff <($(PROG) -iv He $(FILE)) <(grep -iv He $(FILE))
	-diff <($(PROG) -in He $(FILE)) <(grep -in He $(FILE))
	-diff <($(PROG) -ie "^he" $(FILE)) <(grep -ie "^he" $(FILE))
	-diff <($(PROG) -ince "^he" $(FILE)) <(grep -ince "^he" $(FILE))
	-diff <($(PROG) -v He $(FILE)) <(grep -v He $(FILE))
	-diff <($(PROG) -c He $(FILE)) <(grep -c He $(FILE))
	-diff <($(PROG) -l He $(FILE)) <(grep -l He $(FILE))
	-diff <($(PROG) -n He $(FILE)) <(grep -n He $(FILE))
	-diff <($(PROG) -nh He $(FILE)) <(grep -nh He $(FILE))
	-diff <($(PROG) -cl He $(FILE)) <(grep -cl He $(FILE))
	-diff <($(PROG) -ln He $(FILE)) <(grep -ln He $(FILE))
	-diff <($(PROG) -nv He $(FILE)) <(grep -nv He $(FILE))
	-diff <($(PROG) -lin He $(FILE)) <(grep -lin He $(FILE))
	-diff <($(PROG) -vcn He $(FILE)) <(grep -vcn He $(FILE))
	-diff <($(PROG) -cih He $(FILE)) <(grep -cih He $(FILE))
	#------//Memory-leak Tests//------
	$(CHECK) $(PROG) He  t1.txt t2.txt t3.txt
	#$(CHECK) $(PROG) -n -e He -e he $(FILE)
	#$(CHECK) $(PROG)  -i He $(FILE)
	#$(CHECK) $(PROG) -iv He $(FILE)
	#$(CHECK) $(PROG) -in He $(FILE)
	#$(CHECK) $(PROG) -e He $(FILE)
	#$(CHECK) $(PROG) -c He $(FILE)
	#$(CHECK) $(PROG) -l He $(FILE)
	#$(CHECK) $(PROG) -n He $(FILE)
	#$(CHECK) $(PROG) -ince He $(FILE)

 clean:
	rm -rf s21_grep