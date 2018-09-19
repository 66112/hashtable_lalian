#pragma once
#include <stdio.h>
#include <malloc.h>
#include <assert.h>

typedef int KeyDataType;
typedef int ValueDataType;

typedef enum State
{
	EMPTY,
	DELETE,
	EXITS,
}State;

typedef struct HashData
{
	KeyDataType key;
	ValueDataType value;
	State state;
}HashData;

typedef struct HashTable
{
	HashData* _tables;
	size_t size;
	size_t capacity;
}HashTable;

void HashTableInit(HashTable* ht,size_t capacity);
HashData* HashTableFind(HashTable* ht, KeyDataType key);
int HashTableInsert(HashTable* ht, KeyDataType key, ValueDataType value);
int HashTableRemove(HashTable* ht, KeyDataType key);
void HashTableDestory(HashTable* ht);
void PrintHashTable(HashTable* ht);
