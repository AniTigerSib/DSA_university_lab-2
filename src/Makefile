CPP=g++
CFLAGS:=-Wall -Wextra -g -c
FOLDER=../build/
OBJS1=$(addprefix $(FOLDER),main_with_time.o sequence_gen.o sequence_test.o)
OBJS2=$(addprefix $(FOLDER),main_with_count.o sequence_gen.o sequence_test.o)
OBJS_TEST=$(addprefix $(FOLDER),main.o sequence_gen.o sequence_test.o)

all:

build_test: main.o sequence_gen.o sequence_test.o
	$(CPP) $(OBJS_TEST) -o $(FOLDER)sequence_test
	$(MAKE) clean_objs

build_with_time_test: main_with_time.o sequence_gen.o sequence_test.o
	$(CPP) $(OBJS1) -o $(FOLDER)sequence_sort_times
	$(MAKE) clean_objs

build_with_count_test: main_with_count.o sequence_gen.o sequence_test.o
	$(CPP) $(OBJS2) -o $(FOLDER)sequence_sort_count
	$(MAKE) clean_objs

rebuild: clean build

main.o: main.cpp sequence_gen.hpp
	$(CPP) $(CFLAGS) $< -o $(FOLDER)$@

main_with_time.o: main.cpp sequence_gen.hpp
	$(CPP) $(CFLAGS) -D TIME_TEST -D QUICK_STD_TEST $< -o $(FOLDER)$@

main_with_count.o: main.cpp sequence_gen.hpp
	$(CPP) $(CFLAGS) -D COMPARE_COUNT_TEST -D QUICK_STD_TEST $< -o $(FOLDER)$@

sequence_gen.o: sequence_gen.cpp sequence_gen.hpp
	$(CPP) $(CFLAGS) $< -o $(FOLDER)$@

sequence_sort.o: sequence_sort.cpp sequence_sort.hpp
	$(CPP) $(CFLAGS) $< -o $(FOLDER)$@

sequence_test.o: sequence_test.cpp sequence_test.hpp
	$(CPP) $(CFLAGS) $< -o $(FOLDER)$@

clean_objs:
	rm -rf $(OBJS1) $(OBJS2) $(OBJS_TEST)

clean: clean_objs
	rm -rf $(FOLDER)*