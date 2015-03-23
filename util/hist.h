struct histogram
{
    int min;
    int max;
    int num_buckets;
    double bucket_size; // For memo-izing the division
    unsigned int* buckets;
}

struct histogram* histogram_create(int min, int max, int num_buckets)
{
    int i;
    struct histogram* hist = (struct histogram*) malloc(sizeof(struct histogram));

    hist->num_buckets = num_buckets;
    hist->min = min;
    hist->max = max;

    hist->bucket_size = (double) max / (double) num_buckets;

    // Create and zero the histogram's array
    hist->buckets = (unsigned int*) malloc(sizeof(unsigned int) * num_buckets);
    for (i = 0; i < num_buckets; i++) {
	hist->buckets[i] = 0;
    }

    return hist;
}

void histogram_inc(struct histogram* hist, int data_point)
{
    int i = (int) (((double) data_point - hist->min) / hist->bucket_size);

    // Deal with the edge case of when data_point is max
    if (i == hist->num_buckets) {
	hist->buckets[i - 1]++;
    } else {
	hist->buckets[i]++;
    }
}

void histogram_print(struct histogram* hist);
{
    int i;
    int value = hist->min;
    for (i = 0; i < hist->num_buckets; i++) {
        printf("%.2f\t%d\n", value, hist->buckets[i]);
	value += hist->bucket_size;
    }
}
