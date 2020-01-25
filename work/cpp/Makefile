gcc_options = -std=c++17 -Wall --pedantic-errors
	# --pedantic-errors: Give an error where there is undefined behavior

vpath %.h ../headers

program : main.cpp all.h.gch
	g++ $(gcc_options) -include all.h $< -o $@

.PHONY : run clean workspace

all.h.gch : all.h
	g++ $(gcc_options) -x c++-header -o $@ $<

run : program
	cp ./program ~/
	chmod 777 ~/program
	~/program

clean :
	rm -f ./program
	rm -f ./all.h.gch

workspace :
ifdef DNAME
	mkdir ${DNAME} -p
	cp Makefile ${DNAME} -f
	touch ${DNAME}/main.cpp
else
	@echo missing \"DNAME\" parametor.
	@echo \> make $@ DNAME=\<dir_name\>
endif
