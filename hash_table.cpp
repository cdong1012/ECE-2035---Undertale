/*
 Student Name: Chuong Dong
 Date: 03/27/2019

=======================
ECE 2035 Project 2-1:
=======================
This file provides definition for the structs and functions declared in the
header file. It also contains helper functions that are not accessible from
outside of the file.

FOR FULL CREDIT, BE SURE TO TRY MULTIPLE TEST CASES and DOCUMENT YOUR CODE.

===================================
Naming conventions in this file:
===================================
1. All struct names use camel case where the first letter is capitalized.
  e.g. "HashTable", or "HashTableEntry"

2. Variable names with a preceding underscore "_" will not be called directly.
  e.g. "_HashTable", "_HashTableEntry"

  Recall that in C, we have to type "struct" together with the name of the struct
  in order to initialize a new variable. To avoid this, in hash_table.h
  we use typedef to provide new "nicknames" for "struct _HashTable" and
  "struct _HashTableEntry". As a result, we can create new struct variables
  by just using:
    - "HashTable myNewTable;"
     or
    - "HashTableEntry myNewHashTableEntry;"

  The preceding underscore "_" simply provides a distinction between the names
  of the actual struct defition and the "nicknames" that we use to initialize
  new structs.
  [See Hidden Definitions section for more information.]

3. Functions, their local variables and arguments are named with camel case, where
  the first letter is lower-case.
  e.g. "createHashTable" is a function. One of its arguments is "numBuckets".
       It also has a local variable called "newTable".

4. The name of a struct member is divided by using underscores "_". This serves
  as a distinction between function local variables and struct members.
  e.g. "num_buckets" is a member of "HashTable".

*/

/****************************************************************************
* Include the Public Interface
*
* By including the public interface at the top of the file, the compiler can
* enforce that the function declarations in the the header are not in
* conflict with the definitions in the file. This is not a guarantee of
* correctness, but it is better than nothing!
***************************************************************************/
#include "hash_table.h"


/****************************************************************************
* Include other private dependencies
*
* These other modules are used in the implementation of the hash table module,
* but are not required by users of the hash table.
***************************************************************************/
#include <stdlib.h>   // For malloc and free
#include <stdio.h>    // For printf


/****************************************************************************
* Hidden Definitions
*
* These definitions are not available outside of this file. However, because
* the are forward declared in hash_table.h, the type names are
* available everywhere and user code can hold pointers to these structs.
***************************************************************************/
/**
 * This structure represents an a hash table.
 * Use "HashTable" instead when you are creating a new variable. [See top comments]
 */
struct _HashTable {
  /** The array of pointers to the head of a singly linked list, whose nodes
      are HashTableEntry objects */
  HashTableEntry** buckets;

  /** The hash function pointer */
  HashFunction hash;

  /** The number of buckets in the hash table */
  unsigned int num_buckets;
};

/**
 * This structure represents a hash table entry.
 * Use "HashTableEntry" instead when you are creating a new variable. [See top comments]
 */
struct _HashTableEntry {
  /** The key for the hash table entry */
  unsigned int key;

  /** The value associated with this hash table entry */
  void* value;

  /**
  * A pointer pointing to the next hash table entry
  * NULL means there is no next entry (i.e. this is the tail)
  */
  HashTableEntry* next;
};


/****************************************************************************
* Private Functions
*
* These functions are not available outside of this file, since they are not
* declared in hash_table.h.
***************************************************************************/
/**
* createHashTableEntry
*
* Helper function that creates a hash table entry by allocating memory for it on
* the heap. It initializes the entry with key and value, initialize pointer to
* the next entry as NULL, and return the pointer to this hash table entry.
*
* @param key The key corresponds to the hash table entry
* @param value The value stored in the hash table entry
* @return The pointer to the hash table entry
*/
static HashTableEntry* createHashTableEntry(unsigned int key, void* value) {
    /** Create a pointer pointing to an empty hash table entry **/
    HashTableEntry* HTEPointer = (HashTableEntry*)malloc(sizeof(HashTableEntry));
    if(HTEPointer) { // if the pointer is not null -> malloc successfully
        HTEPointer->key = key; // assign the key 
        HTEPointer->value = value;// assign the value
        HTEPointer->next = NULL; // set the next pointer pointing to null
        return HTEPointer; // return the pointer to the hash table entry
    } else { // this pointer is null -> malloc fail
        fprintf(stderr, "Can not allocate space for more Hash Table Entry... Try freeing some stuff!\n");
        return NULL;
    }
}

/**
* findItem
*
* Helper function that checks whether there exists the hash table entry that
* contains a specific key.
*
* @param hashTable The pointer to the hash table.
* @param key The key corresponds to the hash table entry
* @return The pointer to the hash table entry, or NULL if key does not exist
*/
static HashTableEntry* findItem(HashTable* hashTable, unsigned int key) {
    if(hashTable) { // check if hashTable is pointing to null or not
        /** get the index in buckets from the key **/
        unsigned int index = hashTable->hash(key);
        /** create a pointer pointing to the first Hash table entry in the right bucket **/
        HashTableEntry* HTE = hashTable->buckets[index];
        if(HTE) { // if the pointer is not null
            while(HTE) { // loop until HTE becomes null
                /** if the key in the hash table entry matches the given key **/
                if(HTE->key == key) {
                    return HTE; // return the pointer to the right entry
                }
                HTE = HTE->next; // if not found, the pointer point to the next entry
            }
        } else { // the pointer is null, return null
            return NULL;
        }
        return NULL; // if after the search and still haven't found a match, return null
    } else { // hash table pointing to null, so return null
        return NULL;
    }
}

/****************************************************************************
* Public Interface Functions
*
* These functions implement the public interface as specified in the header
* file, and make use of the private functions and hidden definitions in the
* above sections.
****************************************************************************/
// The createHashTable is provided for you as a starting point.
HashTable* createHashTable(HashFunction hashFunction, unsigned int numBuckets) {
  // The hash table has to contain at least one bucket. Exit gracefully if
  // this condition is not met.
  if (numBuckets==0) {
    printf("Hash table has to contain at least 1 bucket...\n");
    exit(1);
  }

  // Allocate memory for the new HashTable struct on heap.
  HashTable* newTable = (HashTable*)malloc(sizeof(HashTable));

  // Initialize the components of the new HashTable struct.
  newTable->hash = hashFunction;
  newTable->num_buckets = numBuckets;
  newTable->buckets = (HashTableEntry**)malloc(numBuckets*sizeof(HashTableEntry*));

  // As the new buckets contain indeterminant values, init each bucket as NULL.
  unsigned int i;
  for (i=0; i<numBuckets; ++i) {
    newTable->buckets[i] = NULL;
  }

  // Return the new HashTable struct.
  return newTable;
}

HashTableEntry* destroyHashTableEntry(HashTableEntry* hashTableEntry); // helper function
void destroyHashTable(HashTable* hashTable){
    if (hashTable) { // if the pointer is not null, destroy it
        if (hashTable->buckets) { // if the pointer to the buckets is not null, destroy
            /** for loop to go through every bucket **/
            for (int i = 0; i < hashTable->num_buckets; i++) {
                /** create a pointer pointing to the first HTE of the bucket **/
                HashTableEntry* HTE = hashTable->buckets[i];
                while(HTE){ // loop to destroy until the pointer point to null
                    // destroy the entry and return the next pointer to nextHTE
                    free(HTE->value);
                    HashTableEntry* nextEntry = destroyHashTableEntry(HTE);
                    HTE = nextEntry;
                }
            } // done freeing all the buckets
            free(hashTable->buckets); // free the array of pointer to the buckets
        }
        free(hashTable); // finally free the hash table
    } // else there is nothing to be done
}

void* insertItem(HashTable* hashTable, unsigned int key, void* value) {
    if(!hashTable) { // if hashTable point to null, return null
        return NULL;
    }   
    /** get the index in the buckets from the given key **/
    unsigned int index = hashTable->hash(key);
    /** find the entry that has the same key with the function findKey **/
    HashTableEntry* findResult = findItem(hashTable, key);
    if(!findResult) { //if findResult is null -> no entry with the key
        if(!hashTable->buckets[index]) { // if the bucket is empty
            /**insert it directly in the first position in the bucket **/
            HashTableEntry* result = createHashTableEntry(key, value);
            hashTable->buckets[index] = result;
            return NULL;
        } // else we insert it at the end
        /** HTE point to the first entry in the bucket **/
        HashTableEntry* HTE = hashTable->buckets[index];
        while(HTE) { // loop until HTE point to null or until return
            if(!HTE->next) { // if the next pointer point to null, insert the entry
                HTE->next = createHashTableEntry(key, value);
                return NULL;
            }
            // HTE points to the next entry
            HTE = HTE->next;
        }// if we haven't return after this loop, return null
        return NULL;
    } // else find result is legit, we just change the value
    void* result = findResult->value; // store the old value
    findResult->value = value; // update the value in the entry
    return result;
}

void* getItem(HashTable* hashTable, unsigned int key) {
    if(!hashTable) { // if hashTable point to null, return null
        return NULL;
    }
    /** item point to the entry with the given key **/
    HashTableEntry* item = findItem(hashTable, key);
    if(item) { // if item is not pointing to null
        return item->value; // return that entry's value
    } else { // else the item is pointing to null, return null
        return NULL; 
    }
}

void* removeItem(HashTable* hashTable, unsigned int key) {
    if(!hashTable) { // if hashTable point to null, return null
        return NULL;
    }
    /** removeHTE points to the entry to be removed **/
    HashTableEntry* removeHTE = findItem(hashTable, key);
    if(!removeHTE) { // if removeHTE points to null, return null
        return NULL;
    }
    /** get the index in buckets from the given key **/
    unsigned int index = hashTable->hash(key);
    /** HTE points to the first entry in the bucket **/
    HashTableEntry* HTE = hashTable->buckets[index];
    if(HTE == removeHTE) { // if the entry to be removed in also the first entry
        void* result = removeHTE->value; // store the old value into result
        /** free the entry and store the pointer to next(which is null) into the bucket **/
        hashTable->buckets[index] = destroyHashTableEntry(removeHTE);
        return result; // return the old value
    } // else we have to look for the entry with the right key
    while(HTE) { // loop until HTE points to null
        /** if the next pointer of HTE point to the entry to be removed **/
        if(HTE->next == removeHTE) {
            void* result = removeHTE->value; // store the old value into result
            /** free the entry and store the next pointer to the next value of the deleted entry **/
            removeHTE = destroyHashTableEntry(removeHTE);
            return result;
        }
        HTE = HTE->next; // HTE point to the next entry
    }// if after the while loop we haven't return, return null
    return NULL;
}

void deleteItem(HashTable* hashTable, unsigned int key) {
    free(removeItem(hashTable, key));//free the value returned after remove the item
}

/**
 * destroyHashTableEntry
 *
 * Destroy the hash table entry being passed in. Freeing key, value and next
 * Return the next value(HashTableEntry *)
 */
HashTableEntry* destroyHashTableEntry(HashTableEntry* hashTableEntry) {
    HashTableEntry* result = hashTableEntry->next;
    //free(hashTableEntry->value);
    free(hashTableEntry);
    return result;
}
