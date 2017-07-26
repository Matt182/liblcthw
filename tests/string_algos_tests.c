#include "minunit.h"
#include <lcthw/string_algos.h>
#include <lcthw/bstrlib.h>
#include <time.h>

struct tagbstring IN_STR = bsStatic(
	"I have ALPHA beta ALPHA and orange ALPHA");
struct tagbstring ALPHA = bsStatic("ALPHA");
const int TEST_TIME = 1;

char *test_find_and_scan()
{
	StringScanner *scan = StringScanner_create(&IN_STR);
	mu_assert(scan != NULL, "Failed to make scanner.");

	int find_i = String_find(&IN_STR, &ALPHA);
	mu_assert(find_i > 0, "Failed to find ALPHA in test string.");

	int scan_i = StringScanner_scan(scan, &ALPHA);
	mu_assert(scan_i > 0, "Failrf to find ALPHA with scan.");
	mu_assert(scan_i == find_i, "find and scan doesnt match");

	scan_i = StringScanner_scan(scan, &ALPHA);
	mu_assert(sacn_i > find_i, "should find another alpha after first.");

	scan_i = StringScanner_scan(scan, &ALPHA);
	mu_assert(scan_i > find_i, "should find another ALPHA after first.");

	mu_assert(StringScanner_scan(scan, &ALPHA) == -1, "Shouldnt find it.");

	StringScanner_destroy(scan);

	return NULL;
}

char *test_binstr_perfomance()
{
	int i = 0;
	int found_at = 0;
	unsigned long find_count = 0;
	time_t elapsed = 0;
	time_t start = time(NULL);

	do {
		for (i = 0; i < 100; i++) {
			found_at = binstr(&IN_STR, 0, &ALPHA);
			mu_assert(found_at != BSTR_ERR, "Failed to find.");
			find_count++;
		}

		elapsed = time(NULL) - start;
	} while (elapsed <= TEST_TIME);

	debug("Binstr count: %ul. end time: %d, ops: %f", find_count, (int)elapsed, (double)find_count/elapsed);
	return NULL;
}

char *test_find_perfomance()
{

}
