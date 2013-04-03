#include "../lib/test.c"
#include "../lib/params.c"


void shouldGetNumberOfProcessOrThreads() {
	int argc = 2;
	char const *argv[] = {
		"programName.out",
		"15"
	};
	int result = getNumberOfProcessOrThreadNumber(argc, argv);
	int expectedNumberOfProcessOrThread = 15;
	assertThat(result, expectedNumberOfProcessOrThread, "shouldGetNumberOfProcessOrThreads");
}

int	main() {
	shouldGetNumberOfProcessOrThreads();
	return 0;
}