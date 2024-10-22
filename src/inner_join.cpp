#include "stdio.h"
#include "random"
#include "chrono"
#include "linearprobing.h"

std::vector<KeyValue> generate_random_keyvalues(std::mt19937& rnd, uint32_t numkvs, uint32_t max_id)
{
    std::uniform_int_distribution<uint32_t> val_dist(0, kEmpty - 1);
    std::uniform_int_distribution<uint32_t> id_dist(0, max_id);
    std::vector<KeyValue> kvs;
    kvs.reserve(numkvs);

    for (uint32_t i = 0; i < numkvs; i++)
    {
        uint32_t id = id_dist(rnd);
        uint32_t val = val_dist(rnd);
        kvs.push_back(KeyValue{id, val});
    }

    return kvs;
}

using Time = std::chrono::time_point<std::chrono::high_resolution_clock>;

Time start_timer() 
{
    return std::chrono::high_resolution_clock::now();
}


int main() {

    std::random_device rd;
    uint32_t seed = rd();
    std::mt19937 rnd(seed);  // mersenne_twister_engine

    printf("Random number generator seed = %u\n", seed);

    std::vector<KeyValue> t1 = generate_random_keyvalues(rnd, table1Size, 5);
    std::vector<KeyValue> t2 = generate_random_keyvalues(rnd, table2Size, 10);

    Time timer = start_timer();

    KeyValue* t1Device = create_hashtable(table1Size);
    const uint32_t num_insert_batches = 16;
    uint32_t num_inserts_per_batch = (uint32_t)t1.size() / num_insert_batches;
    for (uint32_t i = 0; i < num_insert_batches; i++)
    {
        insert_hashtable(t1Device, t1.data() + i * num_inserts_per_batch, num_inserts_per_batch, table1Size);
    }
    KeyValue* t2Device = create_hashtable(table2Size);
    num_inserts_per_batch = (uint32_t)t2.size() / num_insert_batches;
    for (uint32_t i = 0; i < num_insert_batches; i++)
    {
        insert_hashtable(t2Device, t2.data() + i * num_inserts_per_batch, num_inserts_per_batch, table2Size);
    }
    printf("Insertion complete\n");
    

}