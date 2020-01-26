CXXFLAGS = -std=c++17 -Wall --pedantic-errors -I headers
LDLIBS = -lstdc++fs

vpath %.h ./headers

%/main : %/main.cpp all.h.gch
	g++ $(CXXFLAGS) -include all.h -o $@ $< $(LDLIBS)

all.h.gch : all.h
	g++ $(CXXFLAGS) -x c++-header -o $@ $<

.PHONY : %.run
%.run :
	$(eval is_dir := file $* | grep directory$)
	$(eval program := $(if $(shell $(is_dir)), $*/main, $*))
	make $(program)
	$(program)

.PHONY : %.run-home
%.run-home :
	$(eval is_dir := file $* | grep directory$)
	$(eval program := $(if $(shell $(is_dir)), $*/main, $*))
	$(eval pg_name := $(notdir $(program)))
	make $(program)
	cp $(program) ~/$(pg_name)
	chmod u+x ~/$(pg_name)
	~/$(pg_name)

.PHONY : clean
clean :
	rm -f ./all.h.gch
	rm -f */main
