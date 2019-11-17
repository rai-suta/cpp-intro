gcc_options = -std=c++17 -Wall --pedantic-errors
	# --pedantic-errors: Give an error where there is undefined behavior

program : main.cpp all.h all.h.gch
	g++ $(gcc_options) -include all.h $< -o $@

workspace :
ifdef DNAME
	mkdir ${DNAME} -p
	cp all.h Makefile ${DNAME} -f
	touch ${DNAME}/main.cpp
else
	@echo missing \"DNAME\" parametor.
	@echo \> make $@ DNAME=\<dir_name\>
endif

all.h.gch : all.h
	g++ $(gcc_options) -x c++-header -o $@ $<

run : program
	./program

clean :
	rm -f ./program
	rm -f ./all.h.gch

.PHONY : run clean

