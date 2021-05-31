CXX=gсс
CFLAGS= -c -Wall -Werror
CPPFLAGS_TEST = -Wall -Wextra -Werror -I thirdparty -I src -MP -MMD
LIBI = obj/src/libin
LIBC = obj/src/libcalc
GEO = obj/src/geometry


bin/geometry.exe: $(GEO)/main.o $(GEO)/structFunctions.o $(LIBC)/calc.o $(LIBI)/in.o 
		$(CXX) -I src -Wall -Werror -o bin/geometry.exe $(GEO)/main.o $(GEO)/structFunctions.o $(LIBC)/calc.o $(LIBI)/in.o

$(LIBC)/calc.a: $(LIBC)/calc.o
		ar rcs $@ $^

$(LIBI)/in.a: $(LIBI)/in.o
		ar rcs $@ $^

$(LIBC)/calc.o: src/libcalc/calc.cpp
		$(CXX) -I src $(CFLAGS) -MMD -o $(LIBC)/calc.o src/libcalc/calc.cpp

$(LIBI)/in.o: src/libin/in.cpp
		$(CXX) -I src $(CFLAGS) -MMD -o $(LIBI)/in.o src/libin/in.cpp

$(GEO)/structFunctions.o: src/geometry/structFunctions.cpp
		$(CXX) -I src $(CFLAGS) -MMD -o $(GEO)/structFunctions.o src/geometry/structFunctions.cpp

$(GEO)/main.o: src/geometry/main.cpp
		$(CXX) -I src $(CFLAGS) -MMD -o $(GEO)/main.o src/geometry/main.cpp

-include main.d in.d calc.d structFunctions.d

.PHONY: test
test: bin/test

bin/test: $(LIBI)/in.a $(LIBC)/calc.a obj/test/test.o
	$(CXX) -I src -Wall -Werror -o bin/test obj/test/main.o $(LIBI)/in.a $(LIBC)/calc.a

obj/test/test.o: test/main.cpp
		$(CXX) -I src $(CFLAGS) -MMD -o obj/test/main.o test/main.cpp

.PHONY: clean

clean: 
	rm -rf $(GEO)/*.o $(GEO)/*.d $(LIBC)/*.o $(LIBC)/*.d $(LIBI)/*.o $(LIBI)/*.d bin/*.exe
