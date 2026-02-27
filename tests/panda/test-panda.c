/*
Description:
	Unit tests for the PANDA algorithm.
	Tests that the generated PANDA network matches a reference network
	within a configurable tolerance on edge weights.

Authors:
	Marouen Ben Guebila 5/19
	Updated 2/26

Reference:
	https://github.com/deftio/travis-ci-cpp-example
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define S_OK (0)
#define E_FAIL (-1)
#define BUFSIZE 10000

/* ---------- helpers ---------- */

/* Compare two floats with an absolute epsilon tolerance */
static int float_eq(float a, float b, float eps) {
	return fabsf(a - b) <= eps;
}

/* ---------- test: network edge-weight comparison ---------- */

int test_panda_network(const char *ref_file, const char *test_file,
                       float tolerance) {
	FILE *fref  = fopen(ref_file,  "r");
	FILE *ftest = fopen(test_file, "r");
	float D_ref, D_test, P_ref, P_test;
	char tf_ref[BUFSIZE], gene_ref[64];
	char tf_test[BUFSIZE], gene_test[64];
	int line = 0;
	int mismatches = 0;

	if (!fref) {
		fprintf(stderr, "ERROR: cannot open reference file '%s'\n", ref_file);
		return E_FAIL;
	}
	if (!ftest) {
		fprintf(stderr, "ERROR: cannot open test file '%s'\n", test_file);
		fclose(fref);
		return E_FAIL;
	}

	fprintf(stderr, "Comparing PANDA networks (tolerance=%.6f) ...\n", tolerance);

	while (fscanf(fref,  "%s\t%s\t%f\t%f", tf_ref,  gene_ref,  &P_ref,  &D_ref)  == 4 &&
	       fscanf(ftest, "%s\t%s\t%f\t%f", tf_test, gene_test, &P_test, &D_test) == 4) {
		line++;

		/* Check TF and gene names match */
		if (strcmp(tf_ref, tf_test) != 0 || strcmp(gene_ref, gene_test) != 0) {
			fprintf(stderr, "FAIL line %d: name mismatch (%s %s) vs (%s %s)\n",
			        line, tf_ref, gene_ref, tf_test, gene_test);
			mismatches++;
			if (mismatches >= 10) {
				fprintf(stderr, "Too many mismatches, aborting.\n");
				break;
			}
			continue;
		}

		/* Check edge weight within tolerance */
		if (!float_eq(D_ref, D_test, tolerance)) {
			fprintf(stderr, "FAIL line %d (%s -> %s): D_ref=%f  D_test=%f  diff=%f\n",
			        line, tf_ref, gene_ref, D_ref, D_test, fabsf(D_ref - D_test));
			mismatches++;
			if (mismatches >= 10) {
				fprintf(stderr, "Too many mismatches, aborting.\n");
				break;
			}
		}
	}

	fclose(fref);
	fclose(ftest);

	if (line == 0) {
		fprintf(stderr, "FAIL: no lines read - check file format\n");
		return E_FAIL;
	}

	fprintf(stderr, "Compared %d edges, %d mismatches\n", line, mismatches);
	return (mismatches == 0) ? S_OK : E_FAIL;
}

/* ---------- test: output file sanity checks ---------- */

int test_panda_output_format(const char *file) {
	FILE *f = fopen(file, "r");
	char tf[BUFSIZE], gene[64];
	float P, D;
	int line = 0;

	if (!f) {
		fprintf(stderr, "ERROR: cannot open file '%s'\n", file);
		return E_FAIL;
	}

	fprintf(stderr, "Checking PANDA output format ...\n");

	while (fscanf(f, "%s\t%s\t%f\t%f", tf, gene, &P, &D) == 4) {
		line++;

		/* TF and gene names should be non-empty */
		if (strlen(tf) == 0 || strlen(gene) == 0) {
			fprintf(stderr, "FAIL line %d: empty TF or gene name\n", line);
			fclose(f);
			return E_FAIL;
		}

		/* Prior P should be 0 or 1 */
		if (P != 0.0f && P != 1.0f) {
			fprintf(stderr, "FAIL line %d: prior P=%f (expected 0 or 1)\n", line, P);
			fclose(f);
			return E_FAIL;
		}

		/* Edge weight D should be finite */
		if (!isfinite(D)) {
			fprintf(stderr, "FAIL line %d: edge weight D=%f is not finite\n", line, D);
			fclose(f);
			return E_FAIL;
		}
	}

	fclose(f);

	if (line == 0) {
		fprintf(stderr, "FAIL: output file is empty\n");
		return E_FAIL;
	}

	fprintf(stderr, "Format OK: %d edges, all valid\n", line);
	return S_OK;
}

/* ---------- test: output is non-trivial (edges have nonzero weights) ---------- */

int test_panda_nonzero_edges(const char *file) {
	FILE *f = fopen(file, "r");
	char tf[BUFSIZE], gene[64];
	float P, D;
	int line = 0;
	int nonzero = 0;

	if (!f) {
		fprintf(stderr, "ERROR: cannot open file '%s'\n", file);
		return E_FAIL;
	}

	fprintf(stderr, "Checking PANDA output has nonzero edge weights ...\n");

	while (fscanf(f, "%s\t%s\t%f\t%f", tf, gene, &P, &D) == 4) {
		line++;
		if (fabsf(D) > 1e-6f)
			nonzero++;
	}

	fclose(f);

	if (line == 0) {
		fprintf(stderr, "FAIL: output file is empty\n");
		return E_FAIL;
	}

	float pct = 100.0f * nonzero / line;
	fprintf(stderr, "Nonzero edges: %d / %d (%.1f%%)\n", nonzero, line, pct);

	/* Expect at least 50% of edges to be nonzero in a real network */
	if (pct < 50.0f) {
		fprintf(stderr, "FAIL: too few nonzero edges\n");
		return E_FAIL;
	}

	return S_OK;
}

/* ---------- test runner ---------- */

int main(int argc, char **argv) {
	int result = S_OK;
	float tolerance = 0.01f; /* tolerance for float comparison */

	printf("=== PANDA Test Suite ===\n\n");

	if (argc < 3) {
		fprintf(stderr, "Usage: %s <reference_network> <test_network>\n", argv[0]);
		return E_FAIL;
	}

	/* Test 1: Output format validation */
	printf("[1/3] Output format validation ... ");
	if (test_panda_output_format(argv[2]) == S_OK)
		printf("PASSED\n");
	else {
		printf("FAILED\n");
		result = E_FAIL;
	}

	/* Test 2: Nonzero edge check */
	printf("[2/3] Nonzero edge check ... ");
	if (test_panda_nonzero_edges(argv[2]) == S_OK)
		printf("PASSED\n");
	else {
		printf("FAILED\n");
		result = E_FAIL;
	}

	/* Test 3: Network comparison against reference */
	printf("[3/3] Network comparison ... ");
	if (test_panda_network(argv[1], argv[2], tolerance) == S_OK)
		printf("PASSED\n");
	else {
		printf("FAILED\n");
		result = E_FAIL;
	}

	printf("\n=== %s ===\n", result == S_OK ? "ALL TESTS PASSED" : "SOME TESTS FAILED");
	return result;
}
