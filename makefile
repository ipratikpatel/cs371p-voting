all:
	make Voting.zip

clean:
	rm -f Voting.log
	rm -f Voting.zip
	rm -f RunVoting
	rm -f RunVoting.out
	rm -f RunVoting.tmp
	rm -f TestVoting
	rm -f TestVoting.out

diff: RunVoting RunVoting.in RunVoting.out
	RunVoting < RunVoting.in > RunVoting.tmp
	diff RunVoting.out RunVoting.tmp
	rm RunVoting.tmp

doc: Voting.c++
	doxygen Doxyfile

turnin-list:
	turnin --list aizhuli cs371ppj2

turnin-submit: Voting.zip
	turnin --submit aizhuli cs371ppj2 Voting.zip

turnin-verify:
	turnin --verify aizhuli cs371ppj2

Voting.log:
	git log > Voting.log

Voting.zip: makefile                                  \
             Voting.c++ Voting.h Voting.log           \
             RunVoting.c++ RunVoting.in RunVoting.out \
             UVaVoting.c++                            \
             TestVoting.c++ TestVoting.out
	zip -r Voting.zip                               \
	       makefile html/                           \
           Voting.c++ Voting.h Voting.log           \
           RunVoting.c++ RunVoting.in RunVoting.out \
           UVaVoting.c++                            \
           TestVoting.c++ TestVoting.out

RunVoting: Voting.h Voting.c++ RunVoting.c++
	g++ -pedantic -std=c++0x -Wall Voting.c++ RunVoting.c++ -o RunVoting

RunVoting.out: RunVoting RunVoting.in
	valgrind RunVoting < RunVoting.in > RunVoting.out

TestVoting: Voting.h Voting.c++ TestVoting.c++
	g++ -pedantic -std=c++0x -Wall Voting.c++ TestVoting.c++ -o TestVoting -lgtest -lpthread -lgtest_main

TestVoting.out: TestVoting
	valgrind TestVoting > TestVoting.out

