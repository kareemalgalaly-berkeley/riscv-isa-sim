#ifndef GEMMINI_PARAMS_H
#define GEMMINI_PARAMS_H

#include <stdint.h>
#include <limits.h>

#define DIM 16
#define ADDR_LEN 32
#define BANK_NUM 4
#define BANK_ROWS 1024
#define ACC_ROWS 1024
#define MAX_BYTES 64
#define MAX_BLOCK_LEN (MAX_BYTES/(DIM*1))
#define MAX_BLOCK_LEN_ACC (MAX_BYTES/(DIM*4))

typedef uint32_t ind_t;
typedef float elem_t;
static const elem_t elem_t_max = 3.4028235E3;
static const elem_t elem_t_min = -3.4028235E3;
typedef float acc_t;
typedef double full_t;

#define ELEM_T_IS_FLOAT
#define ELEM_T_EXP_BITS 8
#define ELEM_T_SIG_BITS 24
#define ACC_T_EXP_BITS 8 
#define ACC_T_SIG_BITS 24
typedef uint32_t elem_t_bits;
typedef uint32_t acc_t_bits;  

#define HAS_MVIN_SCALE
typedef float scale_t;
typedef uint32_t scale_t_bits;

#define HAS_MVIN_ACC_SCALE
typedef float scale_acc_t;
typedef uint32_t scale_acc_t_bits;

typedef float acc_scale_t;
typedef uint32_t acc_scale_t_bits;

#define row_align(blocks) __attribute__((aligned(blocks*DIM*sizeof(elem_t))))
#define row_align_acc(blocks) __attribute__((aligned(blocks*DIM*sizeof(acc_t))))

#define MVIN_SCALE_IDENTITY 1.0

#define ACC_SCALE_IDENTITY 1.0

// Rounding right shift equation: https://riscv.github.io/documents/riscv-v-spec/#_vector_fixed_point_rounding_mode_register_vxrm
#define ROUNDING_RIGHT_SHIFT(x, shift) \
    ((x) / (1 << (shift)))

#ifdef __cplusplus
#define SAME_TYPE(x) decltype(x)
#else
#define SAME_TYPE(x) typeof(x)
#endif

#define ROUND_NEAR_EVEN(x) \
    ({ const SAME_TYPE(x) x_ = (x); \
         const long long i = x_; \
         const long long next = x_ < 0 ? x_ - 1 : x_ + 1; \
         SAME_TYPE(x) rem = x_ - i; \
         rem = rem < 0 ? -rem : rem; \
         SAME_TYPE(x) result = rem < 0.5 ? i : (rem > 0.5 ? next : ( \
                     i % 2 == 0 ? i : next)); \
         result; })

#define ACC_SCALE(x, scale) \
    ({float y = ROUND_NEAR_EVEN((x) * (scale)); y > INT8_MAX ? INT8_MAX : (y < INT8_MIN ? INT8_MIN : (acc_t)y);})

#define MVIN_SCALE(x, scale) \
    ({float y = ROUND_NEAR_EVEN((x) * (scale)); y > INT8_MAX ? INT8_MAX : (y < INT8_MIN ? INT8_MIN : (elem_t)y);})

#define ACC_SCALE_T_IS_FLOAT
#define ACC_SCALE_EXP_BITS 8
#define ACC_SCALE_SIG_BITS 24

#define ACC_READ_SMALL_WIDTH
#define ACC_READ_FULL_WIDTH

#endif // GEMMINI_PARAMS_H
