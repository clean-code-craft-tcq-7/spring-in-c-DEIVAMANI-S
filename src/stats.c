#include "../src/stats.h"

#include <stddef.h>
#include <float.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

/**
 * Checks if the input array is valid and does not contain absurd values.
 * Returns:
 *   -1 → invalid pointer or count overflow
 *    1 → absurd value found (<0 or >100000)
 *    0 → OK
 */
int checkValueAbsurdity(const float* numbers, int count) {
    if (numbers == NULL || count < 0 || count >(INT_MAX / (int)sizeof(float))) {
        return -1;
    }

    for (int i = 0; i < count; i++) {
        assert(i >= 0 && i < count && "Array index out of bounds");
        if (numbers[i] < 0.0f || numbers[i] > 100000.0f) {
            return 1;
        }
    }
    return 0;
}

/**
 * Sets statistics fields to NaN.
 * Returns 0 on success, -1 if null pointer.
 */
int setStatisticstoNaN(struct Stats* statistics) {
    if (statistics == NULL) {
        return -1;
    }
    statistics->min = NAN;
    statistics->max = NAN;
    statistics->average = NAN;
    return 0;
}

/**
 * Computes min, max, and average from the given array.
 * Ignores NaN values in the data.
 */
struct Stats compute_statistics(const float* numbers, int count) {
    struct Stats stats;
    float sum = 0.0f;
    int validValuesCount = 0;

    // Initialize with extreme values
    stats.min = FLT_MAX;
    stats.max = -FLT_MAX;
    stats.average = 0.0f;

    // Validate data
    int absurdityValidation = checkValueAbsurdity(numbers, count);
    if (count <= 0 || absurdityValidation != 0) {
        setStatisticstoNaN(&stats);
        return stats;
    }

    // Process numbers
    for (int i = 0; i < count; i++) {

        //One of the value in batch is invalid
        if(isnan(numbers[i])) {
            continue; // skip NaNs
        }
        validValuesCount++;
        if (numbers[i] < stats.min) {
            stats.min = numbers[i];
        }
        if (numbers[i] > stats.max) {
            stats.max = numbers[i];
        }
        sum += numbers[i];
    }

    //Compute average
    if(validValuesCount > 0) {
        stats.average = sum / validValuesCount;
    }
    else {
        setStatisticstoNaN(&stats);
    }

    return stats;
}
