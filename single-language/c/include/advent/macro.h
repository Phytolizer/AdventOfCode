#ifndef ADVENT_MACRO_H_
#define ADVENT_MACRO_H_

#define ADVENT_MAIN int main(int argc, char** argv) \
{ \
	for (int i = 1; i < argc; i++) { \
		solve_file(argv[i]); \
	} \
}

#endif  // ADVENT_MACRO_H_

