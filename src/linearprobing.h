#pragma once

struct KeyValue
{
    uint32_t key;
    uint32_t value;
};

const uint32_t table1Size = 32;
const uint32_t table2Size = 32;

const uint32_t kEmpty = 0xffffffff;

KeyValue* create_hashtable(uint32_t tableSize);

void insert_hashtable(KeyValue* hashtable, const KeyValue* kvs, uint32_t num_kvs, uint32_t tableSize);

void lookup_hashtable(KeyValue* hashtable, KeyValue* kvs, uint32_t num_kvs);

void delete_hashtable(KeyValue* hashtable, const KeyValue* kvs, uint32_t num_kvs);

std::vector<KeyValue> iterate_hashtable(KeyValue* hashtable);

void destroy_hashtable(KeyValue* hashtable);

// void transfer_data(KeyValue* hostArr, KeyValue* deviceArr, uint32_t tableSize)