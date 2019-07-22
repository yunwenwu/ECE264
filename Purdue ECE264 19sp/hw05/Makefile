SRC_C = mintf.c
SRC_H = mintf.h clog.h miniunit.h
TEST_C = test_mintf.c
TEST_EXPECTED = test_mintf.txt
TEST_ACTUAL = actual.txt
EXECUTABLE = test_mintf
ASG_NICKNAME = HW04
CFLAGS = -g -std=c99 -Wall -Wshadow -Wvla -Werror -pedantic
CFLAGS_GCOV = $(CFLAGS) -fprofile -arcs -ftest -coverage


test_mintf: $(TEST_C) $(SRC_C)
	gcc $(CFLAGS) -o $(EXECUTABLE) $(TEST_C) $(SRC_C)

test: $(EXECUTABLE)
	./$(EXECUTABLE) > $(TEST_ACTUAL)
	@diff -b $(TEST_ACTUAL) $(TEST_EXPECTED) &> /dev/null
	if [ $$? eq 0 ]; then
	./echo_color green "Test passed: actual.txt matches test_mintf.txt\n"
	else
	./echo_color red "Test failed: actual.txt does NOT match test_mintf.txt\n"
	fi
	
submit: clog.h Makefile miniunit.h echo_color.c
	264submit HW04 mintf.c test_mintf.c test_mintf.txt miniunit.h clog.h

pretest:
	264test hw04

coverage:
	gcc $(CFLAGS_GCOV) -o $(EXECUTABLE) $(TEST_C) $(SRC_C)
	./$(EXECUTABLE)
	gcov -f mintf.c
	
debug: $(TEST_C) $(SRC_C)
	gcc $(CFLAGS) -DDEBUG -o $(EXECUTABLE) $(TEST_C) $(SRC_C)

echo_color: echo_color.c
	gcc $(CFLAGS) -DDEBUG -o echo_color echo_color.c

clean:
	rm -f $(EXECUTABLE) echo_color $(TEST_ACTUAL)

.PHONY: all clean