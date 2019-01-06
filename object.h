#ifndef clox_object_h
#define clox_object_h

#include "common.h"
#include "value.h"

#define OBJ_TYPE(value)     (AS_OBJ(value)->type)

#define IS_STRING(value)    isObjType(value, OBJ_STRING)

typedef enum {
    OBJ_STRING
} ObjType;

struct sObj {
    ObjType type
}

struct sObjString {
    Obj obj,
    int length,
    char* chars
}

static inline bool isObjType(Value value, ObjType type) {
    return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

#endif
