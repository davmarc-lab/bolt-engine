#pragma once

// --- MACROS ---

// Math
#define BTMIN(a, b)	((a) < (b) ? (a) : (b))
// #define BTMININC(a, b)	((a) <= (b) ? (a) : (b))
#define BTMAX(a, b)	((a) > (b) ? (a) : (b))
// #define BTMAXINC(a, b)	((a) >= (b) ? (a) : (b))

// --- TYPEDEF ---

// Base Types
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef char i8;
typedef short i16;
typedef int i32;
typedef long long i64;

// should be better
typedef bool b8;

typedef float f32;
typedef double f64;

// constexpression
#define BT_CONSTEXPR constexpr
#define BT_AUTOCONST const auto

// Check errors
#define STATIC_ASSERT static_assert

STATIC_ASSERT(sizeof(u8) == 1, "Expected u8 to be 1 byte.");
STATIC_ASSERT(sizeof(i8) == 1, "Expected i8 to be 1 byte.");

STATIC_ASSERT(sizeof(u16) == 2, "Expected u16 to be 2 bytes.");
STATIC_ASSERT(sizeof(i16) == 2, "Expected i16 to be 2 bytes.");

STATIC_ASSERT(sizeof(u32) == 4, "Expected u32 to be 4 bytes.");
STATIC_ASSERT(sizeof(i32) == 4, "Expected i32 to be 4 bytes.");
STATIC_ASSERT(sizeof(f32) == 4, "Expected f32 to be 4 bytes.");

STATIC_ASSERT(sizeof(u64) == 8, "Expected u64 to be 8 bytes.");
STATIC_ASSERT(sizeof(i64) == 8, "Expected i64 to be 8 bytes.");
STATIC_ASSERT(sizeof(f64) == 8, "Expected f64 to be 8 bytes.");
