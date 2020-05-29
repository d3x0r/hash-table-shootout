#include <inttypes.h>
#include <string>

#include "../dc8a5638fa75520376911b05faf9fc88/genhash.h"

struct cpp_flower_cursor {
    struct flower_hash_lookup_block_cursor *cursor;
    cpp_flower_cursor( struct flower_hash_lookup_block *hash ) {
        cursor = flowerHashGetCursor( hash );
    }
    void setEnd() {
        cursor->n = -1;
    }
    // prefix operator
    struct cpp_flower_cursor& operator++() {
        // no-op?
        return *this;
    }
    struct cpp_flower_cursor& operator++(int ){
        return *this;
    }
    bool operator==(const struct cpp_flower_cursor& other) const { return cursor->n == other.cursor->n; }
    bool operator!=(const struct cpp_flower_cursor& other) const { return cursor->n != other.cursor->n; }
};

struct cpp_flower_pot {

    struct flower_hash_lookup_block *hash;
    cpp_flower_pot() {
        //hash = InitFlowerHash( IFHEO_IMMUTABLE|IFHEO_NO_DUPLICATES );
        hash = InitFlowerHash( IFHEO_CONVERTIBLE|IFHEO_NO_DUPLICATES );

        // this fails.
        //hash = InitFlowerHash( IFHEO_DENSE|IFHEO_NO_DUPLICATES );
    }
    int it;
public:
    struct cpp_flower_cursor& begin(){
        return (new cpp_flower_cursor( hash ))[0];
    }
    struct cpp_flower_cursor& end() {
        struct cpp_flower_cursor* cursor = new struct cpp_flower_cursor(hash);
        cursor->setEnd();
        return *cursor;
    }
};

typedef struct cpp_flower_pot hash_t;
typedef struct cpp_flower_pot str_hash_t;

#define SETUP hash_t hash; str_hash_t str_hash;

#define RESERVE_INT(size) /*hash.reserve(size);*/
#define RESERVE_STR(size) /*str_hash.reserve(size);*/
#define LOAD_FACTOR(map)  getFlowerHashLoad( map.hash )

#define INSERT_INT_INTO_HASH(key, value) { int key_ = key; uintptr_t* out; AddFlowerHashEntry( hash.hash, (uint8_t const*)&(key_), 4, &out ) ; out[0] = value; }
#define DELETE_INT_FROM_HASH(key) DeleteFlowerHashEntry( hash.hash, (uint8_t const*)&(key), 4 )
#define FIND_INT_EXISTING_FROM_HASH(key) if( FlowerHashShallowLookup( hash.hash, (uint8_t const*)&(key), 4 ) ) { printf("error"); exit(1); }
#define FIND_INT_MISSING_FROM_HASH(key) if( FlowerHashShallowLookup( hash.hash, (uint8_t const*)&(key), 4 ) ) { printf("error"); exit(2); }
#define FIND_INT_EXISTING_FROM_HASH_COUNT(key, count) \
    if( FlowerHashShallowLookup( hash.hash, (uint8_t const*)&(key), 4 ) ) { count++; }
#define CHECK_INT_ITERATOR_VALUE(iterator, value) \
    {  if(flowerHashGet( hash.hash, iterator.cursor )[0] != value) { printf("error"); exit(3); } }

#define sdat(v)  (v)
//#define sdat(v)  (v.data())
#define sdatlen(v)  (strlen(v))
//#define sdatlen(v)  (v.size())

#define INSERT_STR_INTO_HASH(key, value) { uintptr_t* out; AddFlowerHashEntry( str_hash.hash, (uint8_t const*)sdat(key), sdatlen(key), &out ); out[0] = value; }
#define DELETE_STR_FROM_HASH(key) DeleteFlowerHashEntry( str_hash.hash, (uint8_t*)sdat(key), sdatlen(key));
#define FIND_STR_EXISTING_FROM_HASH(key) if( !FlowerHashShallowLookup( str_hash.hash, (uint8_t const*)sdat(key), sdatlen(key) ) ) { printf("error"); exit(4); }
#define FIND_STR_MISSING_FROM_HASH(key) if( FlowerHashShallowLookup( str_hash.hash, (uint8_t const*)sdat(key), sdatlen(key) ) ) { printf("error"); exit(5); }
#define FIND_STR_EXISTING_FROM_HASH_COUNT(key, count) \
    if( FlowerHashShallowLookup( str_hash.hash, (uint8_t const*)sdat(key), sdatlen(key) ) ) {count++;}

#include "template.c"

