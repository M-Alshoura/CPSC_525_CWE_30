EXES = vulnerable_random exploit

.PHONY: all clean install
all: $(EXES)

$(EXES) : Makefile

vulnerable_random: vulnerable_random.cpp Makefile
	g++ -O2 -Wall -DSTORED_SECRET=\"super\ secret\ encrypted\ message\" $< -o $@

exploit: exploit.cpp
	g++ -O2 -Wall exploit.cpp -o exploit

clean: Makefile
	/bin/rm -f *~
	/bin/rm -f $(EXES)