#pragma once
#include <stdio.h>
#include <malloc.h>
#include <assert.h>

#define _PrimeSize 15
static const unsigned long _PrimeList[_PrimeSize] = {
	53 ,   97,    193,    389,    769,
	1543,  3079,  6151,   12289,  24593,
	49157, 98317, 196613, 393241, 786433
};
typedef int KeyData;
typedef int ValueData;

typedef struct HashData
{
	KeyData _key;
	ValueData _value;
	struct HashData* _next;
}HashData;

typedef struct HashTable
{
	HashData** _data;
	size_t capacity;
	size_t size;
}HashTable;

size_t CheckPrime(size_t capacity);
void IncreaseCapacity(HashTable* ht);
void HashTableInit(HashTable* ht, size_t capacity);
HashData* HashTableFind(HashTable* ht, KeyData key);
int HashTableInsert(HashTable* ht, KeyData key, ValueData value);
int HashTableRemove(HashTable* ht, KeyData key);
void HashTableDestory(HashTable* ht);
void PrintHashTable(HashTable* ht);


