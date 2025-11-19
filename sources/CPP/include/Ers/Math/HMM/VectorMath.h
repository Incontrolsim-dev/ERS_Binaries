#pragma once
// clang-format off
/*
  HandmadeMath.h v2.0.0

  This is a single header file with a bunch of useful types and functions for
  games and graphics. Consider it a lightweight alternative to GLM that works
  both C and C++.

  =============================================================================
  CONFIG
  =============================================================================

  By default, all angles in Handmade Math are specified in radians. However, it
  can be configured to use degrees or turns instead. Use one of the following
  defines to specify the default unit for angles:

    #define HANDMADE_MATH_USE_RADIANS
    #define HANDMADE_MATH_USE_DEGREES
    #define HANDMADE_MATH_USE_TURNS

  Regardless of the default angle, you can use the following functions to
  specify an angle in a particular unit:

    EAngleRad(radians)
    EAngleDeg(degrees)
    EAngleTurn(turns)

  The definitions of these functions change depending on the default unit.

  -----------------------------------------------------------------------------

  Handmade Math ships with SSE (SIMD) implementations of several common
  operations. To disable the use of SSE intrinsics, you must define
  HANDMADE_MATH_NO_SSE before including this file:

    #define HANDMADE_MATH_NO_SSE
    #include "HandmadeMath.h"

  -----------------------------------------------------------------------------

  To use Handmade Math without the C runtime library, you must provide your own
  implementations of basic math functions. Otherwise, HandmadeMath.h will use
  the runtime library implementation of these functions.

  Define HANDMADE_MATH_PROVIDE_MATH_FUNCTIONS and provide your own
  implementations of ESINF, ECOSF, ETANF, EACOSF, and ESQRTF
  before including HandmadeMath.h, like so:

    #define HANDMADE_MATH_PROVIDE_MATH_FUNCTIONS
    #define ESINF MySinF
    #define ECOSF MyCosF
    #define ETANF MyTanF
    #define EACOSF MyACosF
    #define ESQRTF MySqrtF
    #include "HandmadeMath.h"

  By default, it is assumed that your math functions take radians. To use
  different units, you must define EANGLE_USER_TO_INTERNAL and
  EANGLE_INTERNAL_TO_USER. For example, if you want to use degrees in your
  code but your math functions use turns:

    #define EANGLE_USER_TO_INTERNAL(a) ((a)*EDegToTurn)
    #define EANGLE_INTERNAL_TO_USER(a) ((a)*ETurnToDeg)

  =============================================================================

  LICENSE

  This software is in the public domain. Where that dedication is not
  recognized, you are granted a perpetual, irrevocable license to copy,
  distribute, and modify this file as you see fit.

  =============================================================================

  CREDITS

  Originally written by Zakary Strange.

  Functionality:
   Zakary Strange (strangezak@protonmail.com && @strangezak)
   Matt Mascarenhas (@miblo_)
   Aleph
   FieryDrake (@fierydrake)
   Gingerbill (@TheGingerBill)
   Ben Visness (@bvisness)
   Trinton Bullard (@Peliex_Dev)
   @AntonDan
   Logan Forman (@dev_dwarf)

  Fixes:
   Jeroen van Rijn (@J_vanRijn)
   Kiljacken (@Kiljacken)
   Insofaras (@insofaras)
   Daniel Gibson (@DanielGibson)
*/

#ifndef HANDMADE_MATH_H
#define HANDMADE_MATH_H

#include <cstring>

// Dummy macros for when test framework is not present.
#ifndef COVERAGE
#define COVERAGE(a, b)
#endif

#ifndef ASSERT_COVERED
#define ASSERT_COVERED(a)
#endif

#ifdef HANDMADE_MATH_NO_SSE
#warning "HANDMADE_MATH_NO_SSE is deprecated, use HANDMADE_MATH_NO_SIMD instead"
#define HANDMADE_MATH_NO_SIMD
#endif

/* let's figure out if SSE is really available (unless disabled anyway)
   (it isn't on non-x86/x86_64 platforms or even x86 without explicit SSE support)
   => only use "#ifdef HANDMADE_MATH__USE_SSE" to check for SSE support below this block! */
#ifndef HANDMADE_MATH_NO_SIMD
#ifdef _MSC_VER /* MSVC supports SSE in amd64 mode or _M_IX86_FP >= 1 (2 means SSE2) */
#if defined(_M_AMD64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 1)
#define HANDMADE_MATH__USE_SSE 1
#endif
#else          /* not MSVC, probably GCC, clang, icc or something that doesn't support SSE anyway */
#ifdef __SSE__ /* they #define __SSE__ if it's supported */
#define HANDMADE_MATH__USE_SSE 1
#endif /*  __SSE__ */
#endif /* not _MSC_VER */
#ifdef __ARM_NEON
#define HANDMADE_MATH__USE_NEON 1
#endif /* NEON Supported */
#endif /* #ifndef HANDMADE_MATH_NO_SIMD */

#if (!defined(__cplusplus) && defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L)
#define HANDMADE_MATH__USE_C11_GENERICS 1
#endif

#ifdef HANDMADE_MATH__USE_SSE
#include <xmmintrin.h>
#endif

#ifdef HANDMADE_MATH__USE_NEON
#include <arm_neon.h>
#endif

#ifdef _MSC_VER
#pragma warning(disable : 4201)
#endif

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#if (defined(__GNUC__) && (__GNUC__ == 4 && __GNUC_MINOR__ < 8)) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-braces"
#endif
#ifdef __clang__
#pragma GCC diagnostic ignored "-Wgnu-anonymous-struct"
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif
#endif

#if defined(__GNUC__) || defined(__clang__)
#define EDEPRECATED(msg) __attribute__((deprecated(msg)))
#elif defined(_MSC_VER)
#define EDEPRECATED(msg) __declspec(deprecated(msg))
#else
#define EDEPRECATED(msg)
#endif

#if !defined(HANDMADE_MATH_USE_DEGREES) && !defined(HANDMADE_MATH_USE_TURNS) && !defined(HANDMADE_MATH_USE_RADIANS)
#define HANDMADE_MATH_USE_RADIANS
#endif

#define EPI 3.14159265358979323846
#define EPI32 3.14159265359f
#define EDEG180 180.0
#define EDEG18032 180.0f
#define ETURNHALF 0.5
#define ETURNHALF32 0.5f
#define ERadToDeg ((float)(EDEG180 / EPI))
#define ERadToTurn ((float)(ETURNHALF / EPI))
#define EDegToRad ((float)(EPI / EDEG180))
#define EDegToTurn ((float)(ETURNHALF / EDEG180))
#define ETurnToRad ((float)(EPI / ETURNHALF))
#define ETurnToDeg ((float)(EDEG180 / ETURNHALF))

#if defined(HANDMADE_MATH_USE_RADIANS)
#define EAngleRad(a) (a)
#define EAngleDeg(a) ((a) * EDegToRad)
#define EAngleTurn(a) ((a) * ETurnToRad)
#elif defined(HANDMADE_MATH_USE_DEGREES)
#define EAngleRad(a) ((a) * ERadToDeg)
#define EAngleDeg(a) (a)
#define EAngleTurn(a) ((a) * ETurnToDeg)
#elif defined(HANDMADE_MATH_USE_TURNS)
#define EAngleRad(a) ((a) * ERadToTurn)
#define EAngleDeg(a) ((a) * EDegToTurn)
#define EAngleTurn(a) (a)
#endif

#if !defined(HANDMADE_MATH_PROVIDE_MATH_FUNCTIONS)
#include <math.h>
#define ESINF sinf
#define ECOSF cosf
#define ETANF tanf
#define ESQRTF sqrtf
#define EASINF asinf
#define EACOSF acosf
#define EATAN2F atan2f
#endif

#if !defined(EANGLE_USER_TO_INTERNAL)
#define EANGLE_USER_TO_INTERNAL(a) (EToRad(a))
#endif

#if !defined(EANGLE_INTERNAL_TO_USER)
#if defined(HANDMADE_MATH_USE_RADIANS)
#define EANGLE_INTERNAL_TO_USER(a) (a)
#elif defined(HANDMADE_MATH_USE_DEGREES)
#define EANGLE_INTERNAL_TO_USER(a) ((a) * ERadToDeg)
#elif defined(HANDMADE_MATH_USE_TURNS)
#define EANGLE_INTERNAL_TO_USER(a) ((a) * ERadToTurn)
#endif
#endif

#define EMIN(a, b) ((a) > (b) ? (b) : (a))
#define EMAX(a, b) ((a) < (b) ? (b) : (a))
#define EABS(a) ((a) > 0 ? (a) : -(a))
#define EMOD(a, m) (((a) % (m)) >= 0 ? ((a) % (m)) : (((a) % (m)) + (m)))
#define ESQUARE(x) ((x) * (x))

namespace Ers
{
    struct Vector2
    {
        union
        {
            struct
            {
                float X, Y;
            };

            struct
            {
                float U, V;
            };

            struct
            {
                float Left, Right;
            };

            struct
            {
                float Width, Height;
            };

            float Elements[2];
        };

    #ifdef __cplusplus
            // Note: No constructors - use Vec2(x, y) helper function or Vector2{x, y} for initialization
            inline float& operator[](int Index) { return Elements[Index]; }
            inline const float& operator[](int Index) const { return Elements[Index]; }
    #endif
    };

    struct Vector3
    {
        union
        {
            struct
            {
                float X, Y, Z;
            };

            struct
            {
                float U, V, W;
            };

            struct
            {
                float R, G, B;
            };

            struct
            {
                Vector2 XY;
                float _Ignored0;
            };

            struct
            {
                float _Ignored1;
                Vector2 YZ;
            };

            struct
            {
                Vector2 UV;
                float _Ignored2;
            };

            struct
            {
                float _Ignored3;
                Vector2 VW;
            };

            float Elements[3];
        };

    #ifdef __cplusplus
            // Note: No constructors - use Vec3(x, y, z) helper function or Vector3{x, y, z} for initialization
            inline float& operator[](int Index) { return Elements[Index]; }
            inline const float& operator[](int Index) const { return Elements[Index]; }
    #endif
    };

    struct Vector4
    {
        union
        {
            struct
            {
                union
                {
                    Vector3 XYZ;
                    struct
                    {
                        float X, Y, Z;
                    };
                };

                float W;
            };
            struct
            {
                union
                {
                    Vector3 RGB;
                    struct
                    {
                        float R, G, B;
                    };
                };

                float A;
            };

            struct
            {
                Vector2 XY;
                float _Ignored0;
                float _Ignored1;
            };

            struct
            {
                float _Ignored2;
                Vector2 YZ;
                float _Ignored3;
            };

            struct
            {
                float _Ignored4;
                float _Ignored5;
                Vector2 ZW;
            };

            float Elements[4];

#ifdef HANDMADE_MATH__USE_SSE
            __m128 SSE;
#endif

#ifdef HANDMADE_MATH__USE_NEON
            float32x4_t NEON;
#endif
        };

    #ifdef __cplusplus
            // Note: No constructors - use Vec4(x, y, z, w) helper function or Vector4{x, y, z, w} for initialization
            inline float& operator[](int Index) { return Elements[Index]; }
            inline const float& operator[](int Index) const { return Elements[Index]; }
    #endif
    };

    typedef union Matrix2
    {
        float Elements[2][2];
        Vector2 Columns[2];

    #ifdef __cplusplus
            // Note: No constructors - use Matrix2{} for zero-initialization
            inline Vector2& operator[](int Index) { return Columns[Index]; }
            inline const Vector2& operator[](int Index) const { return Columns[Index]; }
    #endif
    } Matrix2;

    typedef union Matrix3
    {
        float Elements[3][3];
        Vector3 Columns[3];

    #ifdef __cplusplus
            // Note: No constructors - use Matrix3{} for zero-initialization
            inline Vector3& operator[](int Index) { return Columns[Index]; }
            inline const Vector3& operator[](int Index) const { return Columns[Index]; }
    #endif
    } Matrix3;

    typedef union Matrix4
    {
        float Elements[4][4];
        Vector4 Columns[4];

    #ifdef __cplusplus
            // Note: No constructors - use Matrix4{} for zero-initialization
            inline Vector4& operator[](int Index) { return Columns[Index]; }
            inline const Vector4& operator[](int Index) const { return Columns[Index]; }
    #endif
    } Matrix4;

    typedef union Quaternion
    {
        struct
        {
            union
            {
                Vector3 XYZ;
                struct
                {
                    float X, Y, Z;
                };
            };

            float W;
        };

        float Elements[4];

#ifdef HANDMADE_MATH__USE_SSE
        __m128 SSE;
#endif
#ifdef HANDMADE_MATH__USE_NEON
        float32x4_t NEON;
#endif

    #ifdef __cplusplus
            // Note: No constructors - use EQuaternion(x, y, z, w) helper function or Quaternion{x, y, z, w} for initialization
    #endif
        } Quaternion;

    typedef signed int EBool;

    /*
     * Global helper functions for convenient initialization without constructors
     */
#ifdef __cplusplus
    inline constexpr Vector2 Vec2(float x = 0.0f, float y = 0.0f) {
        return {x, y};
    }

    inline constexpr Vector3 Vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f) {
        return {x, y, z};
    }

    inline constexpr Vector4 Vec4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f) {
        return {x, y, z, w};
    }

    inline constexpr Quaternion EQuaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f) {
        return {x, y, z, w};
    }
#endif

    /*
     * Angle unit conversion functions
     */
    inline static float EToRad(float Angle)
    {
#if defined(HANDMADE_MATH_USE_RADIANS)
        float Result = Angle;
#elif defined(HANDMADE_MATH_USE_DEGREES)
    float Result = Angle * EDegToRad;
#elif defined(HANDMADE_MATH_USE_TURNS)
    float Result = Angle * ETurnToRad;
#endif

        return Result;
    }

    inline static float EToDeg(float Angle)
    {
#if defined(HANDMADE_MATH_USE_RADIANS)
        float Result = Angle * ERadToDeg;
#elif defined(HANDMADE_MATH_USE_DEGREES)
    float Result = Angle;
#elif defined(HANDMADE_MATH_USE_TURNS)
    float Result = Angle * ETurnToDeg;
#endif

        return Result;
    }

    inline static float EToTurn(float Angle)
    {
#if defined(HANDMADE_MATH_USE_RADIANS)
        float Result = Angle * ERadToTurn;
#elif defined(HANDMADE_MATH_USE_DEGREES)
    float Result = Angle * EDegToTurn;
#elif defined(HANDMADE_MATH_USE_TURNS)
    float Result = Angle;
#endif

        return Result;
    }

    /*
     * Floating-point math functions
     */

    COVERAGE(ESinF, 1)
    inline static float ESinF(float Angle)
    {
        ASSERT_COVERED(ESinF);
        return ESINF(EANGLE_USER_TO_INTERNAL(Angle));
    }

    COVERAGE(ECosF, 1)
    inline static float ECosF(float Angle)
    {
        ASSERT_COVERED(ECosF);
        return ECOSF(EANGLE_USER_TO_INTERNAL(Angle));
    }

    COVERAGE(ETanF, 1)
    inline static float ETanF(float Angle)
    {
        ASSERT_COVERED(ETanF);
        return ETANF(EANGLE_USER_TO_INTERNAL(Angle));
    }

    COVERAGE(EASinF, 1)
    inline static float EASinF(float Arg)
    {
        ASSERT_COVERED(EASinF);
        return EANGLE_INTERNAL_TO_USER(EASINF(Arg));
    }

    COVERAGE(EACosF, 1)
    inline static float EACosF(float Arg)
    {
        ASSERT_COVERED(EACosF);
        return EANGLE_INTERNAL_TO_USER(EACOSF(Arg));
    }

    COVERAGE(EATan2F, 1)
    inline static float EATan2F(float x, float y)
    {
        ASSERT_COVERED(EATan2F);
        return EANGLE_INTERNAL_TO_USER(EATAN2F(x, y));
    }

    COVERAGE(ESqrtF, 1)
    inline static float ESqrtF(float Float)
    {
        ASSERT_COVERED(ESqrtF);

        float Result;

#ifdef HANDMADE_MATH__USE_SSE
        __m128 In  = _mm_set_ss(Float);
        __m128 Out = _mm_sqrt_ss(In);
        Result     = _mm_cvtss_f32(Out);
#elif defined(HANDMADE_MATH__USE_NEON)
    float32x4_t In  = vdupq_n_f32(Float);
    float32x4_t Out = vsqrtq_f32(In);
    Result          = vgetq_lane_f32(Out, 0);
#else
    Result = ESQRTF(Float);
#endif

        return Result;
    }

    COVERAGE(EInvSqrtF, 1)
    inline static float EInvSqrtF(float Float)
    {
        ASSERT_COVERED(EInvSqrtF);

        float Result;

        Result = 1.0f / ESqrtF(Float);

        return Result;
    }

    /*
     * Utility functions
     */

    COVERAGE(ELerp, 1)
    inline static float ELerp(float A, float Time, float B)
    {
        ASSERT_COVERED(ELerp);
        return (1.0f - Time) * A + Time * B;
    }

    COVERAGE(EClamp, 1)
    inline static float EClamp(float Min, float Value, float Max)
    {
        ASSERT_COVERED(EClamp);

        float Result = Value;

        if (Result < Min)
        {
            Result = Min;
        }

        if (Result > Max)
        {
            Result = Max;
        }

        return Result;
    }

    /*
     * Vector initialization
     */

    COVERAGE(EV2, 1)
    inline static Vector2 EV2(float X, float Y)
    {
        ASSERT_COVERED(EV2);

        Vector2 Result{};
        Result.X = X;
        Result.Y = Y;

        return Result;
    }

    COVERAGE(EV3, 1)
    inline static Vector3 EV3(float X, float Y, float Z)
    {
        ASSERT_COVERED(EV3);

        Vector3 Result{};
        Result.X = X;
        Result.Y = Y;
        Result.Z = Z;

        return Result;
    }

    COVERAGE(EV4, 1)
    inline static Vector4 EV4(float X, float Y, float Z, float W)
    {
        ASSERT_COVERED(EV4);

        Vector4 Result{};

#ifdef HANDMADE_MATH__USE_SSE
        Result.SSE = _mm_setr_ps(X, Y, Z, W);
#elif defined(HANDMADE_MATH__USE_NEON)
    float32x4_t v = {X, Y, Z, W};
    Result.NEON   = v;
#else
    Result.X = X;
    Result.Y = Y;
    Result.Z = Z;
    Result.W = W;
#endif

        return Result;
    }

    COVERAGE(EV4V, 1)
    inline static Vector4 EV4V(Vector3 Vector, float W)
    {
        ASSERT_COVERED(EV4V);

        Vector4 Result{};

#ifdef HANDMADE_MATH__USE_SSE
        Result.SSE = _mm_setr_ps(Vector.X, Vector.Y, Vector.Z, W);
#elif defined(HANDMADE_MATH__USE_NEON)
    float32x4_t v = {Vector.X, Vector.Y, Vector.Z, W};
    Result.NEON   = v;
#else
    Result.XYZ = Vector;
    Result.W   = W;
#endif

        return Result;
    }

    /*
     * Binary vector operations
     */

    COVERAGE(EAddV2, 1)
    inline static Vector2 EAddV2(Vector2 Left, Vector2 Right)
    {
        ASSERT_COVERED(EAddV2);

        Vector2 Result{};
        Result.X = Left.X + Right.X;
        Result.Y = Left.Y + Right.Y;

        return Result;
    }

    COVERAGE(EAddV3, 1)
    inline static Vector3 EAddV3(Vector3 Left, Vector3 Right)
    {
        ASSERT_COVERED(EAddV3);

        Vector3 Result{};
        Result.X = Left.X + Right.X;
        Result.Y = Left.Y + Right.Y;
        Result.Z = Left.Z + Right.Z;

        return Result;
    }

    COVERAGE(EAddV4, 1)
    inline static Vector4 EAddV4(Vector4 Left, Vector4 Right)
    {
        ASSERT_COVERED(EAddV4);

        Vector4 Result{};

#ifdef HANDMADE_MATH__USE_SSE
        Result.SSE = _mm_add_ps(Left.SSE, Right.SSE);
#elif defined(HANDMADE_MATH__USE_NEON)
    Result.NEON = vaddq_f32(Left.NEON, Right.NEON);
#else
    Result.X = Left.X + Right.X;
    Result.Y = Left.Y + Right.Y;
    Result.Z = Left.Z + Right.Z;
    Result.W = Left.W + Right.W;
#endif

        return Result;
    }

    COVERAGE(ESubV2, 1)
    inline static Vector2 ESubV2(Vector2 Left, Vector2 Right)
    {
        ASSERT_COVERED(ESubV2);

        Vector2 Result{};
        Result.X = Left.X - Right.X;
        Result.Y = Left.Y - Right.Y;

        return Result;
    }

    COVERAGE(ESubV3, 1)
    inline static Vector3 ESubV3(Vector3 Left, Vector3 Right)
    {
        ASSERT_COVERED(ESubV3);

        Vector3 Result{};
        Result.X = Left.X - Right.X;
        Result.Y = Left.Y - Right.Y;
        Result.Z = Left.Z - Right.Z;

        return Result;
    }

    COVERAGE(ESubV4, 1)
    inline static Vector4 ESubV4(Vector4 Left, Vector4 Right)
    {
        ASSERT_COVERED(ESubV4);

        Vector4 Result{};

#ifdef HANDMADE_MATH__USE_SSE
        Result.SSE = _mm_sub_ps(Left.SSE, Right.SSE);
#elif defined(HANDMADE_MATH__USE_NEON)
    Result.NEON = vsubq_f32(Left.NEON, Right.NEON);
#else
    Result.X = Left.X - Right.X;
    Result.Y = Left.Y - Right.Y;
    Result.Z = Left.Z - Right.Z;
    Result.W = Left.W - Right.W;
#endif

        return Result;
    }

    COVERAGE(EMulV2, 1)
    inline static Vector2 EMulV2(Vector2 Left, Vector2 Right)
    {
        ASSERT_COVERED(EMulV2);

        Vector2 Result{};
        Result.X = Left.X * Right.X;
        Result.Y = Left.Y * Right.Y;

        return Result;
    }

    COVERAGE(EMulV2F, 1)
    inline static Vector2 EMulV2F(Vector2 Left, float Right)
    {
        ASSERT_COVERED(EMulV2F);

        Vector2 Result{};
        Result.X = Left.X * Right;
        Result.Y = Left.Y * Right;

        return Result;
    }

    COVERAGE(EMulV3, 1)
    inline static Vector3 EMulV3(Vector3 Left, Vector3 Right)
    {
        ASSERT_COVERED(EMulV3);

        Vector3 Result{};
        Result.X = Left.X * Right.X;
        Result.Y = Left.Y * Right.Y;
        Result.Z = Left.Z * Right.Z;

        return Result;
    }

    COVERAGE(EMulV3F, 1)
    inline static Vector3 EMulV3F(Vector3 Left, float Right)
    {
        ASSERT_COVERED(EMulV3F);

        Vector3 Result{};
        Result.X = Left.X * Right;
        Result.Y = Left.Y * Right;
        Result.Z = Left.Z * Right;

        return Result;
    }

    COVERAGE(EMulV4, 1)
    inline static Vector4 EMulV4(Vector4 Left, Vector4 Right)
    {
        ASSERT_COVERED(EMulV4);

        Vector4 Result{};

#ifdef HANDMADE_MATH__USE_SSE
        Result.SSE = _mm_mul_ps(Left.SSE, Right.SSE);
#elif defined(HANDMADE_MATH__USE_NEON)
    Result.NEON = vmulq_f32(Left.NEON, Right.NEON);
#else
    Result.X = Left.X * Right.X;
    Result.Y = Left.Y * Right.Y;
    Result.Z = Left.Z * Right.Z;
    Result.W = Left.W * Right.W;
#endif

        return Result;
    }

    COVERAGE(EMulV4F, 1)
    inline static Vector4 EMulV4F(Vector4 Left, float Right)
    {
        ASSERT_COVERED(EMulV4F);

        Vector4 Result{};

#ifdef HANDMADE_MATH__USE_SSE
        __m128 Scalar = _mm_set1_ps(Right);
        Result.SSE    = _mm_mul_ps(Left.SSE, Scalar);
#elif defined(HANDMADE_MATH__USE_NEON)
    Result.NEON = vmulq_n_f32(Left.NEON, Right);
#else
    Result.X = Left.X * Right;
    Result.Y = Left.Y * Right;
    Result.Z = Left.Z * Right;
    Result.W = Left.W * Right;
#endif

        return Result;
    }

    COVERAGE(EDivV2, 1)
    inline static Vector2 EDivV2(Vector2 Left, Vector2 Right)
    {
        ASSERT_COVERED(EDivV2);

        Vector2 Result{};
        Result.X = Left.X / Right.X;
        Result.Y = Left.Y / Right.Y;

        return Result;
    }

    COVERAGE(EDivV2F, 1)
    inline static Vector2 EDivV2F(Vector2 Left, float Right)
    {
        ASSERT_COVERED(EDivV2F);

        Vector2 Result{};
        Result.X = Left.X / Right;
        Result.Y = Left.Y / Right;

        return Result;
    }

    COVERAGE(EDivV3, 1)
    inline static Vector3 EDivV3(Vector3 Left, Vector3 Right)
    {
        ASSERT_COVERED(EDivV3);

        Vector3 Result{};
        Result.X = Left.X / Right.X;
        Result.Y = Left.Y / Right.Y;
        Result.Z = Left.Z / Right.Z;

        return Result;
    }

    COVERAGE(EDivV3F, 1)
    inline static Vector3 EDivV3F(Vector3 Left, float Right)
    {
        ASSERT_COVERED(EDivV3F);

        Vector3 Result{};
        Result.X = Left.X / Right;
        Result.Y = Left.Y / Right;
        Result.Z = Left.Z / Right;

        return Result;
    }

    COVERAGE(EDivV4, 1)
    inline static Vector4 EDivV4(Vector4 Left, Vector4 Right)
    {
        ASSERT_COVERED(EDivV4);

        Vector4 Result{};

#ifdef HANDMADE_MATH__USE_SSE
        Result.SSE = _mm_div_ps(Left.SSE, Right.SSE);
#elif defined(HANDMADE_MATH__USE_NEON)
    Result.NEON = vdivq_f32(Left.NEON, Right.NEON);
#else
    Result.X = Left.X / Right.X;
    Result.Y = Left.Y / Right.Y;
    Result.Z = Left.Z / Right.Z;
    Result.W = Left.W / Right.W;
#endif

        return Result;
    }

    COVERAGE(EDivV4F, 1)
    inline static Vector4 EDivV4F(Vector4 Left, float Right)
    {
        ASSERT_COVERED(EDivV4F);

        Vector4 Result{};

#ifdef HANDMADE_MATH__USE_SSE
        __m128 Scalar = _mm_set1_ps(Right);
        Result.SSE    = _mm_div_ps(Left.SSE, Scalar);
#elif defined(HANDMADE_MATH__USE_NEON)
    float32x4_t Scalar = vdupq_n_f32(Right);
    Result.NEON        = vdivq_f32(Left.NEON, Scalar);
#else
    Result.X = Left.X / Right;
    Result.Y = Left.Y / Right;
    Result.Z = Left.Z / Right;
    Result.W = Left.W / Right;
#endif

        return Result;
    }

    COVERAGE(EEqV2, 1)
    inline static EBool EEqV2(Vector2 Left, Vector2 Right)
    {
        ASSERT_COVERED(EEqV2);
        return Left.X == Right.X && Left.Y == Right.Y;
    }

    COVERAGE(EEqV3, 1)
    inline static EBool EEqV3(Vector3 Left, Vector3 Right)
    {
        ASSERT_COVERED(EEqV3);
        return Left.X == Right.X && Left.Y == Right.Y && Left.Z == Right.Z;
    }

    COVERAGE(EEqV4, 1)
    inline static EBool EEqV4(Vector4 Left, Vector4 Right)
    {
        ASSERT_COVERED(EEqV4);
        return Left.X == Right.X && Left.Y == Right.Y && Left.Z == Right.Z && Left.W == Right.W;
    }

    COVERAGE(EDotV2, 1)
    inline static float EDotV2(Vector2 Left, Vector2 Right)
    {
        ASSERT_COVERED(EDotV2);
        return (Left.X * Right.X) + (Left.Y * Right.Y);
    }

    COVERAGE(EDotV3, 1)
    inline static float EDotV3(Vector3 Left, Vector3 Right)
    {
        ASSERT_COVERED(EDotV3);
        return (Left.X * Right.X) + (Left.Y * Right.Y) + (Left.Z * Right.Z);
    }

    COVERAGE(EDotV4, 1)
    inline static float EDotV4(Vector4 Left, Vector4 Right)
    {
        ASSERT_COVERED(EDotV4);

        float Result;

        // NOTE(zak): IN the future if we wanna check what version SSE is support
        // we can use _mm_dp_ps (4.3) but for now we will use the old way.
        // Or a r = _mm_mul_ps(v1, v2), r = _mm_hadd_ps(r, r), r = _mm_hadd_ps(r, r) for SSE3
#ifdef HANDMADE_MATH__USE_SSE
        __m128 SSEResultOne = _mm_mul_ps(Left.SSE, Right.SSE);
        __m128 SSEResultTwo = _mm_shuffle_ps(SSEResultOne, SSEResultOne, _MM_SHUFFLE(2, 3, 0, 1));
        SSEResultOne        = _mm_add_ps(SSEResultOne, SSEResultTwo);
        SSEResultTwo        = _mm_shuffle_ps(SSEResultOne, SSEResultOne, _MM_SHUFFLE(0, 1, 2, 3));
        SSEResultOne        = _mm_add_ps(SSEResultOne, SSEResultTwo);
        _mm_store_ss(&Result, SSEResultOne);
#elif defined(HANDMADE_MATH__USE_NEON)
    float32x4_t NEONMultiplyResult = vmulq_f32(Left.NEON, Right.NEON);
    float32x4_t NEONHalfAdd        = vpaddq_f32(NEONMultiplyResult, NEONMultiplyResult);
    float32x4_t NEONFullAdd        = vpaddq_f32(NEONHalfAdd, NEONHalfAdd);
    Result                         = vgetq_lane_f32(NEONFullAdd, 0);
#else
    Result = ((Left.X * Right.X) + (Left.Z * Right.Z)) + ((Left.Y * Right.Y) + (Left.W * Right.W));
#endif

        return Result;
    }

    COVERAGE(ECross, 1)
    inline static Vector3 ECross(Vector3 Left, Vector3 Right)
    {
        ASSERT_COVERED(ECross);

        Vector3 Result{};
        Result.X = (Left.Y * Right.Z) - (Left.Z * Right.Y);
        Result.Y = (Left.Z * Right.X) - (Left.X * Right.Z);
        Result.Z = (Left.X * Right.Y) - (Left.Y * Right.X);

        return Result;
    }

    /*
     * Unary vector operations
     */

    COVERAGE(ELenSqrV2, 1)
    inline static float ELenSqrV2(Vector2 A)
    {
        ASSERT_COVERED(ELenSqrV2);
        return EDotV2(A, A);
    }

    COVERAGE(ELenSqrV3, 1)
    inline static float ELenSqrV3(Vector3 A)
    {
        ASSERT_COVERED(ELenSqrV3);
        return EDotV3(A, A);
    }

    COVERAGE(ELenSqrV4, 1)
    inline static float ELenSqrV4(Vector4 A)
    {
        ASSERT_COVERED(ELenSqrV4);
        return EDotV4(A, A);
    }

    COVERAGE(ELenV2, 1)
    inline static float ELenV2(Vector2 A)
    {
        ASSERT_COVERED(ELenV2);
        return ESqrtF(ELenSqrV2(A));
    }

    COVERAGE(ELenV3, 1)
    inline static float ELenV3(Vector3 A)
    {
        ASSERT_COVERED(ELenV3);
        return ESqrtF(ELenSqrV3(A));
    }

    COVERAGE(ELenV4, 1)
    inline static float ELenV4(Vector4 A)
    {
        ASSERT_COVERED(ELenV4);
        return ESqrtF(ELenSqrV4(A));
    }

    COVERAGE(ENormV2, 1)
    inline static Vector2 ENormV2(Vector2 A)
    {
        ASSERT_COVERED(ENormV2);
        return EMulV2F(A, EInvSqrtF(EDotV2(A, A)));
    }

    COVERAGE(ENormV3, 1)
    inline static Vector3 ENormV3(Vector3 A)
    {
        ASSERT_COVERED(ENormV3);
        return EMulV3F(A, EInvSqrtF(EDotV3(A, A)));
    }

    COVERAGE(ENormV4, 1)
    inline static Vector4 ENormV4(Vector4 A)
    {
        ASSERT_COVERED(ENormV4);
        return EMulV4F(A, EInvSqrtF(EDotV4(A, A)));
    }

    COVERAGE(EFloorV2, 1)
    inline static Vector2 EFloorV2(Vector2 A)
    {
        ASSERT_COVERED(EFloorV2);
        return EV2(floorf(A.X), floorf(A.Y));
    }

	COVERAGE(EFloorV3, 1)
    inline static Vector3 EFloorV3(Vector3 A)
    {
        ASSERT_COVERED(EFloorV3);
        return EV3(floorf(A.X), floorf(A.Y), floorf(A.Z));
    }

	COVERAGE(EFloorV4, 1)
    inline static Vector4 EFloorV4(Vector4 A)
    {
        ASSERT_COVERED(EFloorV3);
        return EV4(floorf(A.X), floorf(A.Y), floorf(A.Z), floorf(A.W));
    }

    /*
     * Utility vector functions
     */

    COVERAGE(ELerpV2, 1)
    inline static Vector2 ELerpV2(Vector2 A, float Time, Vector2 B)
    {
        ASSERT_COVERED(ELerpV2);
        return EAddV2(EMulV2F(A, 1.0f - Time), EMulV2F(B, Time));
    }

    COVERAGE(ELerpV3, 1)
    inline static Vector3 ELerpV3(Vector3 A, float Time, Vector3 B)
    {
        ASSERT_COVERED(ELerpV3);
        return EAddV3(EMulV3F(A, 1.0f - Time), EMulV3F(B, Time));
    }

    COVERAGE(ELerpV4, 1)
    inline static Vector4 ELerpV4(Vector4 A, float Time, Vector4 B)
    {
        ASSERT_COVERED(ELerpV4);
        return EAddV4(EMulV4F(A, 1.0f - Time), EMulV4F(B, Time));
    }

    inline static Vector2 ESignV2(Vector2 A)
    {
        return EV2((A.X > 0.0f) - (A.X < 0.0f), (A.Y > 0.0f) - (A.Y < 0.0f));
    }

    inline static Vector3 ESignV3(Vector3 A)
    {
        return EV3(
            (A.X > 0.0f) - (A.X < 0.0f),
            (A.Y > 0.0f) - (A.Y < 0.0f),
            (A.Z > 0.0f) - (A.Z < 0.0f));
    }

    /*
     * SSE stuff
     */

    COVERAGE(ELinearCombineV4M4, 1)
    inline static Vector4 ELinearCombineV4M4(Vector4 Left, Matrix4 Right)
    {
        ASSERT_COVERED(ELinearCombineV4M4);

        Vector4 Result{};
#ifdef HANDMADE_MATH__USE_SSE
        Result.SSE = _mm_mul_ps(_mm_shuffle_ps(Left.SSE, Left.SSE, 0x00), Right.Columns[0].SSE);
        Result.SSE = _mm_add_ps(Result.SSE, _mm_mul_ps(_mm_shuffle_ps(Left.SSE, Left.SSE, 0x55), Right.Columns[1].SSE));
        Result.SSE = _mm_add_ps(Result.SSE, _mm_mul_ps(_mm_shuffle_ps(Left.SSE, Left.SSE, 0xaa), Right.Columns[2].SSE));
        Result.SSE = _mm_add_ps(Result.SSE, _mm_mul_ps(_mm_shuffle_ps(Left.SSE, Left.SSE, 0xff), Right.Columns[3].SSE));
#elif defined(HANDMADE_MATH__USE_NEON)
    Result.NEON = vmulq_laneq_f32(Right.Columns[0].NEON, Left.NEON, 0);
    Result.NEON = vfmaq_laneq_f32(Result.NEON, Right.Columns[1].NEON, Left.NEON, 1);
    Result.NEON = vfmaq_laneq_f32(Result.NEON, Right.Columns[2].NEON, Left.NEON, 2);
    Result.NEON = vfmaq_laneq_f32(Result.NEON, Right.Columns[3].NEON, Left.NEON, 3);
#else
    Result.X = Left.Elements[0] * Right.Columns[0].X;
    Result.Y = Left.Elements[0] * Right.Columns[0].Y;
    Result.Z = Left.Elements[0] * Right.Columns[0].Z;
    Result.W = Left.Elements[0] * Right.Columns[0].W;

    Result.X += Left.Elements[1] * Right.Columns[1].X;
    Result.Y += Left.Elements[1] * Right.Columns[1].Y;
    Result.Z += Left.Elements[1] * Right.Columns[1].Z;
    Result.W += Left.Elements[1] * Right.Columns[1].W;

    Result.X += Left.Elements[2] * Right.Columns[2].X;
    Result.Y += Left.Elements[2] * Right.Columns[2].Y;
    Result.Z += Left.Elements[2] * Right.Columns[2].Z;
    Result.W += Left.Elements[2] * Right.Columns[2].W;

    Result.X += Left.Elements[3] * Right.Columns[3].X;
    Result.Y += Left.Elements[3] * Right.Columns[3].Y;
    Result.Z += Left.Elements[3] * Right.Columns[3].Z;
    Result.W += Left.Elements[3] * Right.Columns[3].W;
#endif

        return Result;
    }

    /*
     * 2x2 Matrices
     */

    COVERAGE(EM2, 1)
    inline static Matrix2 EM2(void)
    {
        ASSERT_COVERED(EM2);
        Matrix2 Result{};
        return Result;
    }

    COVERAGE(EM2D, 1)
    inline static Matrix2 EM2D(float Diagonal)
    {
        ASSERT_COVERED(EM2D);

        Matrix2 Result       {};
        Result.Elements[0][0] = Diagonal;
        Result.Elements[1][1] = Diagonal;

        return Result;
    }

    COVERAGE(ETransposeM2, 1)
    inline static Matrix2 ETransposeM2(Matrix2 Matrix)
    {
        ASSERT_COVERED(ETransposeM2);

        Matrix2 Result = Matrix;

        Result.Elements[0][1] = Matrix.Elements[1][0];
        Result.Elements[1][0] = Matrix.Elements[0][1];

        return Result;
    }

    COVERAGE(EAddM2, 1)
    inline static Matrix2 EAddM2(Matrix2 Left, Matrix2 Right)
    {
        ASSERT_COVERED(EAddM2);

        Matrix2 Result;

        Result.Elements[0][0] = Left.Elements[0][0] + Right.Elements[0][0];
        Result.Elements[0][1] = Left.Elements[0][1] + Right.Elements[0][1];
        Result.Elements[1][0] = Left.Elements[1][0] + Right.Elements[1][0];
        Result.Elements[1][1] = Left.Elements[1][1] + Right.Elements[1][1];

        return Result;
    }

    COVERAGE(ESubM2, 1)
    inline static Matrix2 ESubM2(Matrix2 Left, Matrix2 Right)
    {
        ASSERT_COVERED(ESubM2);

        Matrix2 Result;

        Result.Elements[0][0] = Left.Elements[0][0] - Right.Elements[0][0];
        Result.Elements[0][1] = Left.Elements[0][1] - Right.Elements[0][1];
        Result.Elements[1][0] = Left.Elements[1][0] - Right.Elements[1][0];
        Result.Elements[1][1] = Left.Elements[1][1] - Right.Elements[1][1];

        return Result;
    }

    COVERAGE(EMulM2V2, 1)
    inline static Vector2 EMulM2V2(Matrix2 Matrix, Vector2 Vector)
    {
        ASSERT_COVERED(EMulM2V2);

        Vector2 Result{};

        Result.X = Vector.Elements[0] * Matrix.Columns[0].X;
        Result.Y = Vector.Elements[0] * Matrix.Columns[0].Y;

        Result.X += Vector.Elements[1] * Matrix.Columns[1].X;
        Result.Y += Vector.Elements[1] * Matrix.Columns[1].Y;

        return Result;
    }

    COVERAGE(EMulM2, 1)
    inline static Matrix2 EMulM2(Matrix2 Left, Matrix2 Right)
    {
        ASSERT_COVERED(EMulM2);

        Matrix2 Result;
        Result.Columns[0] = EMulM2V2(Left, Right.Columns[0]);
        Result.Columns[1] = EMulM2V2(Left, Right.Columns[1]);

        return Result;
    }

    COVERAGE(EMulM2F, 1)
    inline static Matrix2 EMulM2F(Matrix2 Matrix, float Scalar)
    {
        ASSERT_COVERED(EMulM2F);

        Matrix2 Result;

        Result.Elements[0][0] = Matrix.Elements[0][0] * Scalar;
        Result.Elements[0][1] = Matrix.Elements[0][1] * Scalar;
        Result.Elements[1][0] = Matrix.Elements[1][0] * Scalar;
        Result.Elements[1][1] = Matrix.Elements[1][1] * Scalar;

        return Result;
    }

    COVERAGE(EDivM2F, 1)
    inline static Matrix2 EDivM2F(Matrix2 Matrix, float Scalar)
    {
        ASSERT_COVERED(EDivM2F);

        Matrix2 Result;

        Result.Elements[0][0] = Matrix.Elements[0][0] / Scalar;
        Result.Elements[0][1] = Matrix.Elements[0][1] / Scalar;
        Result.Elements[1][0] = Matrix.Elements[1][0] / Scalar;
        Result.Elements[1][1] = Matrix.Elements[1][1] / Scalar;

        return Result;
    }

    COVERAGE(EDeterminantM2, 1)
    inline static float EDeterminantM2(Matrix2 Matrix)
    {
        ASSERT_COVERED(EDeterminantM2);
        return Matrix.Elements[0][0] * Matrix.Elements[1][1] - Matrix.Elements[0][1] * Matrix.Elements[1][0];
    }

    COVERAGE(EInvGeneralM2, 1)
    inline static Matrix2 EInvGeneralM2(Matrix2 Matrix)
    {
        ASSERT_COVERED(EInvGeneralM2);

        Matrix2 Result;
        float InvDeterminant  = 1.0f / EDeterminantM2(Matrix);
        Result.Elements[0][0] = InvDeterminant * +Matrix.Elements[1][1];
        Result.Elements[1][1] = InvDeterminant * +Matrix.Elements[0][0];
        Result.Elements[0][1] = InvDeterminant * -Matrix.Elements[0][1];
        Result.Elements[1][0] = InvDeterminant * -Matrix.Elements[1][0];

        return Result;
    }

    /*
     * 3x3 Matrices
     */

    COVERAGE(EM3, 1)
    inline static Matrix3 EM3(void)
    {
        ASSERT_COVERED(EM3);
        Matrix3 Result{};
        return Result;
    }

    COVERAGE(EM3D, 1)
    inline static Matrix3 EM3D(float Diagonal)
    {
        ASSERT_COVERED(EM3D);

        Matrix3 Result       {};
        Result.Elements[0][0] = Diagonal;
        Result.Elements[1][1] = Diagonal;
        Result.Elements[2][2] = Diagonal;

        return Result;
    }

    COVERAGE(ETransposeM3, 1)
    inline static Matrix3 ETransposeM3(Matrix3 Matrix)
    {
        ASSERT_COVERED(ETransposeM3);

        Matrix3 Result = Matrix;

        Result.Elements[0][1] = Matrix.Elements[1][0];
        Result.Elements[0][2] = Matrix.Elements[2][0];
        Result.Elements[1][0] = Matrix.Elements[0][1];
        Result.Elements[1][2] = Matrix.Elements[2][1];
        Result.Elements[2][1] = Matrix.Elements[1][2];
        Result.Elements[2][0] = Matrix.Elements[0][2];

        return Result;
    }

    COVERAGE(EAddM3, 1)
    inline static Matrix3 EAddM3(Matrix3 Left, Matrix3 Right)
    {
        ASSERT_COVERED(EAddM3);

        Matrix3 Result;

        Result.Elements[0][0] = Left.Elements[0][0] + Right.Elements[0][0];
        Result.Elements[0][1] = Left.Elements[0][1] + Right.Elements[0][1];
        Result.Elements[0][2] = Left.Elements[0][2] + Right.Elements[0][2];
        Result.Elements[1][0] = Left.Elements[1][0] + Right.Elements[1][0];
        Result.Elements[1][1] = Left.Elements[1][1] + Right.Elements[1][1];
        Result.Elements[1][2] = Left.Elements[1][2] + Right.Elements[1][2];
        Result.Elements[2][0] = Left.Elements[2][0] + Right.Elements[2][0];
        Result.Elements[2][1] = Left.Elements[2][1] + Right.Elements[2][1];
        Result.Elements[2][2] = Left.Elements[2][2] + Right.Elements[2][2];

        return Result;
    }

    COVERAGE(ESubM3, 1)
    inline static Matrix3 ESubM3(Matrix3 Left, Matrix3 Right)
    {
        ASSERT_COVERED(ESubM3);

        Matrix3 Result;

        Result.Elements[0][0] = Left.Elements[0][0] - Right.Elements[0][0];
        Result.Elements[0][1] = Left.Elements[0][1] - Right.Elements[0][1];
        Result.Elements[0][2] = Left.Elements[0][2] - Right.Elements[0][2];
        Result.Elements[1][0] = Left.Elements[1][0] - Right.Elements[1][0];
        Result.Elements[1][1] = Left.Elements[1][1] - Right.Elements[1][1];
        Result.Elements[1][2] = Left.Elements[1][2] - Right.Elements[1][2];
        Result.Elements[2][0] = Left.Elements[2][0] - Right.Elements[2][0];
        Result.Elements[2][1] = Left.Elements[2][1] - Right.Elements[2][1];
        Result.Elements[2][2] = Left.Elements[2][2] - Right.Elements[2][2];

        return Result;
    }

    COVERAGE(EMulM3V3, 1)
    inline static Vector3 EMulM3V3(Matrix3 Matrix, Vector3 Vector)
    {
        ASSERT_COVERED(EMulM3V3);

        Vector3 Result{};

        Result.X = Vector.Elements[0] * Matrix.Columns[0].X;
        Result.Y = Vector.Elements[0] * Matrix.Columns[0].Y;
        Result.Z = Vector.Elements[0] * Matrix.Columns[0].Z;

        Result.X += Vector.Elements[1] * Matrix.Columns[1].X;
        Result.Y += Vector.Elements[1] * Matrix.Columns[1].Y;
        Result.Z += Vector.Elements[1] * Matrix.Columns[1].Z;

        Result.X += Vector.Elements[2] * Matrix.Columns[2].X;
        Result.Y += Vector.Elements[2] * Matrix.Columns[2].Y;
        Result.Z += Vector.Elements[2] * Matrix.Columns[2].Z;

        return Result;
    }

    COVERAGE(EMulM3, 1)
    inline static Matrix3 EMulM3(Matrix3 Left, Matrix3 Right)
    {
        ASSERT_COVERED(EMulM3);

        Matrix3 Result;
        Result.Columns[0] = EMulM3V3(Left, Right.Columns[0]);
        Result.Columns[1] = EMulM3V3(Left, Right.Columns[1]);
        Result.Columns[2] = EMulM3V3(Left, Right.Columns[2]);

        return Result;
    }

    COVERAGE(EMulM3F, 1)
    inline static Matrix3 EMulM3F(Matrix3 Matrix, float Scalar)
    {
        ASSERT_COVERED(EMulM3F);

        Matrix3 Result;

        Result.Elements[0][0] = Matrix.Elements[0][0] * Scalar;
        Result.Elements[0][1] = Matrix.Elements[0][1] * Scalar;
        Result.Elements[0][2] = Matrix.Elements[0][2] * Scalar;
        Result.Elements[1][0] = Matrix.Elements[1][0] * Scalar;
        Result.Elements[1][1] = Matrix.Elements[1][1] * Scalar;
        Result.Elements[1][2] = Matrix.Elements[1][2] * Scalar;
        Result.Elements[2][0] = Matrix.Elements[2][0] * Scalar;
        Result.Elements[2][1] = Matrix.Elements[2][1] * Scalar;
        Result.Elements[2][2] = Matrix.Elements[2][2] * Scalar;

        return Result;
    }

    COVERAGE(EDivM3, 1)
    inline static Matrix3 EDivM3F(Matrix3 Matrix, float Scalar)
    {
        ASSERT_COVERED(EDivM3);

        Matrix3 Result;

        Result.Elements[0][0] = Matrix.Elements[0][0] / Scalar;
        Result.Elements[0][1] = Matrix.Elements[0][1] / Scalar;
        Result.Elements[0][2] = Matrix.Elements[0][2] / Scalar;
        Result.Elements[1][0] = Matrix.Elements[1][0] / Scalar;
        Result.Elements[1][1] = Matrix.Elements[1][1] / Scalar;
        Result.Elements[1][2] = Matrix.Elements[1][2] / Scalar;
        Result.Elements[2][0] = Matrix.Elements[2][0] / Scalar;
        Result.Elements[2][1] = Matrix.Elements[2][1] / Scalar;
        Result.Elements[2][2] = Matrix.Elements[2][2] / Scalar;

        return Result;
    }

    COVERAGE(EDeterminantM3, 1)
    inline static float EDeterminantM3(Matrix3 Matrix)
    {
        ASSERT_COVERED(EDeterminantM3);

        Matrix3 Cross;
        Cross.Columns[0] = ECross(Matrix.Columns[1], Matrix.Columns[2]);
        Cross.Columns[1] = ECross(Matrix.Columns[2], Matrix.Columns[0]);
        Cross.Columns[2] = ECross(Matrix.Columns[0], Matrix.Columns[1]);

        return EDotV3(Cross.Columns[2], Matrix.Columns[2]);
    }

    COVERAGE(EInvGeneralM3, 1)
    inline static Matrix3 EInvGeneralM3(Matrix3 Matrix)
    {
        ASSERT_COVERED(EInvGeneralM3);

        Matrix3 Cross;
        Cross.Columns[0] = ECross(Matrix.Columns[1], Matrix.Columns[2]);
        Cross.Columns[1] = ECross(Matrix.Columns[2], Matrix.Columns[0]);
        Cross.Columns[2] = ECross(Matrix.Columns[0], Matrix.Columns[1]);

        float InvDeterminant = 1.0f / EDotV3(Cross.Columns[2], Matrix.Columns[2]);

        Matrix3 Result;
        Result.Columns[0] = EMulV3F(Cross.Columns[0], InvDeterminant);
        Result.Columns[1] = EMulV3F(Cross.Columns[1], InvDeterminant);
        Result.Columns[2] = EMulV3F(Cross.Columns[2], InvDeterminant);

        return ETransposeM3(Result);
    }

	COVERAGE(EEqM3, 1)
    inline static EBool EEqM3(Matrix3 Left, Matrix3 Right)
    {
        ASSERT_COVERED(EEqM3);
        return EEqV3(Left.Columns[0], Right.Columns[0])
            && EEqV3(Left.Columns[1], Right.Columns[1])
            && EEqV3(Left.Columns[2], Right.Columns[2]);
    }

    /*
     * 4x4 Matrices
     */

    COVERAGE(EM4, 1)
    inline static Matrix4 EM4(void)
    {
        ASSERT_COVERED(EM4);
        Matrix4 Result{};
        return Result;
    }

    // Copy a 1D array to a Matrix4
    inline static Matrix4 ECopyArray(const float* array)
    {
        Matrix4 result = EM4();
        memcpy(&result, array, sizeof(float) * 16);
        return result;
    }

    COVERAGE(EM4D, 1)
    inline static Matrix4 EM4D(float Diagonal)
    {
        ASSERT_COVERED(EM4D);

        Matrix4 Result       {};
        Result.Elements[0][0] = Diagonal;
        Result.Elements[1][1] = Diagonal;
        Result.Elements[2][2] = Diagonal;
        Result.Elements[3][3] = Diagonal;

        return Result;
    }

    COVERAGE(ETransposeM4, 1)
    inline static Matrix4 ETransposeM4(Matrix4 Matrix)
    {
        ASSERT_COVERED(ETransposeM4);

        Matrix4 Result;
#ifdef HANDMADE_MATH__USE_SSE
        Result = Matrix;
        _MM_TRANSPOSE4_PS(Result.Columns[0].SSE, Result.Columns[1].SSE, Result.Columns[2].SSE, Result.Columns[3].SSE);
#elif defined(HANDMADE_MATH__USE_NEON)
    float32x4x4_t Transposed = vld4q_f32((float*)Matrix.Columns);
    Result.Columns[0].NEON   = Transposed.val[0];
    Result.Columns[1].NEON   = Transposed.val[1];
    Result.Columns[2].NEON   = Transposed.val[2];
    Result.Columns[3].NEON   = Transposed.val[3];
#else
    Result.Elements[0][0] = Matrix.Elements[0][0];
    Result.Elements[0][1] = Matrix.Elements[1][0];
    Result.Elements[0][2] = Matrix.Elements[2][0];
    Result.Elements[0][3] = Matrix.Elements[3][0];
    Result.Elements[1][0] = Matrix.Elements[0][1];
    Result.Elements[1][1] = Matrix.Elements[1][1];
    Result.Elements[1][2] = Matrix.Elements[2][1];
    Result.Elements[1][3] = Matrix.Elements[3][1];
    Result.Elements[2][0] = Matrix.Elements[0][2];
    Result.Elements[2][1] = Matrix.Elements[1][2];
    Result.Elements[2][2] = Matrix.Elements[2][2];
    Result.Elements[2][3] = Matrix.Elements[3][2];
    Result.Elements[3][0] = Matrix.Elements[0][3];
    Result.Elements[3][1] = Matrix.Elements[1][3];
    Result.Elements[3][2] = Matrix.Elements[2][3];
    Result.Elements[3][3] = Matrix.Elements[3][3];
#endif

        return Result;
    }

    COVERAGE(EAddM4, 1)
    inline static Matrix4 EAddM4(Matrix4 Left, Matrix4 Right)
    {
        ASSERT_COVERED(EAddM4);

        Matrix4 Result;

        Result.Columns[0] = EAddV4(Left.Columns[0], Right.Columns[0]);
        Result.Columns[1] = EAddV4(Left.Columns[1], Right.Columns[1]);
        Result.Columns[2] = EAddV4(Left.Columns[2], Right.Columns[2]);
        Result.Columns[3] = EAddV4(Left.Columns[3], Right.Columns[3]);

        return Result;
    }

    COVERAGE(ESubM4, 1)
    inline static Matrix4 ESubM4(Matrix4 Left, Matrix4 Right)
    {
        ASSERT_COVERED(ESubM4);

        Matrix4 Result;

        Result.Columns[0] = ESubV4(Left.Columns[0], Right.Columns[0]);
        Result.Columns[1] = ESubV4(Left.Columns[1], Right.Columns[1]);
        Result.Columns[2] = ESubV4(Left.Columns[2], Right.Columns[2]);
        Result.Columns[3] = ESubV4(Left.Columns[3], Right.Columns[3]);

        return Result;
    }

    COVERAGE(EMulM4, 1)
    inline static Matrix4 EMulM4(Matrix4 Left, Matrix4 Right)
    {
        ASSERT_COVERED(EMulM4);

        Matrix4 Result;
        Result.Columns[0] = ELinearCombineV4M4(Right.Columns[0], Left);
        Result.Columns[1] = ELinearCombineV4M4(Right.Columns[1], Left);
        Result.Columns[2] = ELinearCombineV4M4(Right.Columns[2], Left);
        Result.Columns[3] = ELinearCombineV4M4(Right.Columns[3], Left);

        return Result;
    }

    COVERAGE(EMulM4F, 1)
    inline static Matrix4 EMulM4F(Matrix4 Matrix, float Scalar)
    {
        ASSERT_COVERED(EMulM4F);

        Matrix4 Result;

#ifdef HANDMADE_MATH__USE_SSE
        __m128 SSEScalar      = _mm_set1_ps(Scalar);
        Result.Columns[0].SSE = _mm_mul_ps(Matrix.Columns[0].SSE, SSEScalar);
        Result.Columns[1].SSE = _mm_mul_ps(Matrix.Columns[1].SSE, SSEScalar);
        Result.Columns[2].SSE = _mm_mul_ps(Matrix.Columns[2].SSE, SSEScalar);
        Result.Columns[3].SSE = _mm_mul_ps(Matrix.Columns[3].SSE, SSEScalar);
#elif defined(HANDMADE_MATH__USE_NEON)
    Result.Columns[0].NEON = vmulq_n_f32(Matrix.Columns[0].NEON, Scalar);
    Result.Columns[1].NEON = vmulq_n_f32(Matrix.Columns[1].NEON, Scalar);
    Result.Columns[2].NEON = vmulq_n_f32(Matrix.Columns[2].NEON, Scalar);
    Result.Columns[3].NEON = vmulq_n_f32(Matrix.Columns[3].NEON, Scalar);
#else
    Result.Elements[0][0] = Matrix.Elements[0][0] * Scalar;
    Result.Elements[0][1] = Matrix.Elements[0][1] * Scalar;
    Result.Elements[0][2] = Matrix.Elements[0][2] * Scalar;
    Result.Elements[0][3] = Matrix.Elements[0][3] * Scalar;
    Result.Elements[1][0] = Matrix.Elements[1][0] * Scalar;
    Result.Elements[1][1] = Matrix.Elements[1][1] * Scalar;
    Result.Elements[1][2] = Matrix.Elements[1][2] * Scalar;
    Result.Elements[1][3] = Matrix.Elements[1][3] * Scalar;
    Result.Elements[2][0] = Matrix.Elements[2][0] * Scalar;
    Result.Elements[2][1] = Matrix.Elements[2][1] * Scalar;
    Result.Elements[2][2] = Matrix.Elements[2][2] * Scalar;
    Result.Elements[2][3] = Matrix.Elements[2][3] * Scalar;
    Result.Elements[3][0] = Matrix.Elements[3][0] * Scalar;
    Result.Elements[3][1] = Matrix.Elements[3][1] * Scalar;
    Result.Elements[3][2] = Matrix.Elements[3][2] * Scalar;
    Result.Elements[3][3] = Matrix.Elements[3][3] * Scalar;
#endif

        return Result;
    }

    COVERAGE(EMulM4V4, 1)
    inline static Vector4 EMulM4V4(Matrix4 Matrix, Vector4 Vector)
    {
        ASSERT_COVERED(EMulM4V4);
        return ELinearCombineV4M4(Vector, Matrix);
    }

    COVERAGE(EDivM4F, 1)
    inline static Matrix4 EDivM4F(Matrix4 Matrix, float Scalar)
    {
        ASSERT_COVERED(EDivM4F);

        Matrix4 Result;

#ifdef HANDMADE_MATH__USE_SSE
        __m128 SSEScalar      = _mm_set1_ps(Scalar);
        Result.Columns[0].SSE = _mm_div_ps(Matrix.Columns[0].SSE, SSEScalar);
        Result.Columns[1].SSE = _mm_div_ps(Matrix.Columns[1].SSE, SSEScalar);
        Result.Columns[2].SSE = _mm_div_ps(Matrix.Columns[2].SSE, SSEScalar);
        Result.Columns[3].SSE = _mm_div_ps(Matrix.Columns[3].SSE, SSEScalar);
#elif defined(HANDMADE_MATH__USE_NEON)
    float32x4_t NEONScalar = vdupq_n_f32(Scalar);
    Result.Columns[0].NEON = vdivq_f32(Matrix.Columns[0].NEON, NEONScalar);
    Result.Columns[1].NEON = vdivq_f32(Matrix.Columns[1].NEON, NEONScalar);
    Result.Columns[2].NEON = vdivq_f32(Matrix.Columns[2].NEON, NEONScalar);
    Result.Columns[3].NEON = vdivq_f32(Matrix.Columns[3].NEON, NEONScalar);
#else
    Result.Elements[0][0] = Matrix.Elements[0][0] / Scalar;
    Result.Elements[0][1] = Matrix.Elements[0][1] / Scalar;
    Result.Elements[0][2] = Matrix.Elements[0][2] / Scalar;
    Result.Elements[0][3] = Matrix.Elements[0][3] / Scalar;
    Result.Elements[1][0] = Matrix.Elements[1][0] / Scalar;
    Result.Elements[1][1] = Matrix.Elements[1][1] / Scalar;
    Result.Elements[1][2] = Matrix.Elements[1][2] / Scalar;
    Result.Elements[1][3] = Matrix.Elements[1][3] / Scalar;
    Result.Elements[2][0] = Matrix.Elements[2][0] / Scalar;
    Result.Elements[2][1] = Matrix.Elements[2][1] / Scalar;
    Result.Elements[2][2] = Matrix.Elements[2][2] / Scalar;
    Result.Elements[2][3] = Matrix.Elements[2][3] / Scalar;
    Result.Elements[3][0] = Matrix.Elements[3][0] / Scalar;
    Result.Elements[3][1] = Matrix.Elements[3][1] / Scalar;
    Result.Elements[3][2] = Matrix.Elements[3][2] / Scalar;
    Result.Elements[3][3] = Matrix.Elements[3][3] / Scalar;
#endif

        return Result;
    }

    COVERAGE(EDeterminantM4, 1)
    inline static float EDeterminantM4(Matrix4 Matrix)
    {
        ASSERT_COVERED(EDeterminantM4);

        Vector3 C01 = ECross(Matrix.Columns[0].XYZ, Matrix.Columns[1].XYZ);
        Vector3 C23 = ECross(Matrix.Columns[2].XYZ, Matrix.Columns[3].XYZ);
        Vector3 B10 = ESubV3(EMulV3F(Matrix.Columns[0].XYZ, Matrix.Columns[1].W), EMulV3F(Matrix.Columns[1].XYZ, Matrix.Columns[0].W));
        Vector3 B32 = ESubV3(EMulV3F(Matrix.Columns[2].XYZ, Matrix.Columns[3].W), EMulV3F(Matrix.Columns[3].XYZ, Matrix.Columns[2].W));

        return EDotV3(C01, B32) + EDotV3(C23, B10);
    }

    COVERAGE(EInvGeneralM4, 1)
    // Returns a general-purpose inverse of an Matrix4. Note that special-purpose inverses of many transformations
    // are available and will be more efficient.
    inline static Matrix4 EInvGeneralM4(Matrix4 Matrix)
    {
        ASSERT_COVERED(EInvGeneralM4);

        Vector3 C01 = ECross(Matrix.Columns[0].XYZ, Matrix.Columns[1].XYZ);
        Vector3 C23 = ECross(Matrix.Columns[2].XYZ, Matrix.Columns[3].XYZ);
        Vector3 B10 = ESubV3(EMulV3F(Matrix.Columns[0].XYZ, Matrix.Columns[1].W), EMulV3F(Matrix.Columns[1].XYZ, Matrix.Columns[0].W));
        Vector3 B32 = ESubV3(EMulV3F(Matrix.Columns[2].XYZ, Matrix.Columns[3].W), EMulV3F(Matrix.Columns[3].XYZ, Matrix.Columns[2].W));

        float InvDeterminant = 1.0f / (EDotV3(C01, B32) + EDotV3(C23, B10));
        C01                  = EMulV3F(C01, InvDeterminant);
        C23                  = EMulV3F(C23, InvDeterminant);
        B10                  = EMulV3F(B10, InvDeterminant);
        B32                  = EMulV3F(B32, InvDeterminant);

        Matrix4 Result;
        Result.Columns[0] =
            EV4V(EAddV3(ECross(Matrix.Columns[1].XYZ, B32), EMulV3F(C23, Matrix.Columns[1].W)), -EDotV3(Matrix.Columns[1].XYZ, C23));
        Result.Columns[1] =
            EV4V(ESubV3(ECross(B32, Matrix.Columns[0].XYZ), EMulV3F(C23, Matrix.Columns[0].W)), +EDotV3(Matrix.Columns[0].XYZ, C23));
        Result.Columns[2] =
            EV4V(EAddV3(ECross(Matrix.Columns[3].XYZ, B10), EMulV3F(C01, Matrix.Columns[3].W)), -EDotV3(Matrix.Columns[3].XYZ, C01));
        Result.Columns[3] =
            EV4V(ESubV3(ECross(B10, Matrix.Columns[2].XYZ), EMulV3F(C01, Matrix.Columns[2].W)), +EDotV3(Matrix.Columns[2].XYZ, C01));

        return ETransposeM4(Result);
    }

	COVERAGE(EEqM4, 1)
    inline static EBool EEqM4(Matrix4 Left, Matrix4 Right)
    {
        ASSERT_COVERED(EEqM4);
        return EEqV4(Left.Columns[0], Right.Columns[0])
            && EEqV4(Left.Columns[1], Right.Columns[1])
            && EEqV4(Left.Columns[2], Right.Columns[2])
            && EEqV4(Left.Columns[3], Right.Columns[3]);
    }

    /*
     * Common graphics transformations
     */

    COVERAGE(EOrthographic_RH_NO, 1)
    // Produces a right-handed orthographic projection matrix with Z ranging from -1 to 1 (the GL convention).
    // Left, Right, Bottom, and Top specify the coordinates of their respective clipping planes.
    // Near and Far specify the distances to the near and far clipping planes.
    inline static Matrix4 EOrthographic_RH_NO(float Left, float Right, float Bottom, float Top, float Near, float Far)
    {
        ASSERT_COVERED(EOrthographic_RH_NO);

        Matrix4 Result{};

        Result.Elements[0][0] = 2.0f / (Right - Left);
        Result.Elements[1][1] = 2.0f / (Top - Bottom);
        Result.Elements[2][2] = 2.0f / (Near - Far);
        Result.Elements[3][3] = 1.0f;

        Result.Elements[3][0] = (Left + Right) / (Left - Right);
        Result.Elements[3][1] = (Bottom + Top) / (Bottom - Top);
        Result.Elements[3][2] = (Near + Far) / (Near - Far);

        return Result;
    }

    COVERAGE(EOrthographic_RH_ZO, 1)
    // Produces a right-handed orthographic projection matrix with Z ranging from 0 to 1 (the DirectX convention).
    // Left, Right, Bottom, and Top specify the coordinates of their respective clipping planes.
    // Near and Far specify the distances to the near and far clipping planes.
    inline static Matrix4 EOrthographic_RH_ZO(float Left, float Right, float Bottom, float Top, float Near, float Far)
    {
        ASSERT_COVERED(EOrthographic_RH_ZO);

        Matrix4 Result{};

        Result.Elements[0][0] = 2.0f / (Right - Left);
        Result.Elements[1][1] = 2.0f / (Top - Bottom);
        Result.Elements[2][2] = 1.0f / (Near - Far);
        Result.Elements[3][3] = 1.0f;

        Result.Elements[3][0] = (Left + Right) / (Left - Right);
        Result.Elements[3][1] = (Bottom + Top) / (Bottom - Top);
        Result.Elements[3][2] = (Near) / (Near - Far);

        return Result;
    }

    COVERAGE(EOrthographic_LH_NO, 1)
    // Produces a left-handed orthographic projection matrix with Z ranging from -1 to 1 (the GL convention).
    // Left, Right, Bottom, and Top specify the coordinates of their respective clipping planes.
    // Near and Far specify the distances to the near and far clipping planes.
    inline static Matrix4 EOrthographic_LH_NO(float Left, float Right, float Bottom, float Top, float Near, float Far)
    {
        ASSERT_COVERED(EOrthographic_LH_NO);

        Matrix4 Result        = EOrthographic_RH_NO(Left, Right, Bottom, Top, Near, Far);
        Result.Elements[2][2] = -Result.Elements[2][2];

        return Result;
    }

    COVERAGE(EOrthographic_LH_ZO, 1)
    // Produces a left-handed orthographic projection matrix with Z ranging from 0 to 1 (the DirectX convention).
    // Left, Right, Bottom, and Top specify the coordinates of their respective clipping planes.
    // Near and Far specify the distances to the near and far clipping planes.
    inline static Matrix4 EOrthographic_LH_ZO(float Left, float Right, float Bottom, float Top, float Near, float Far)
    {
        ASSERT_COVERED(EOrthographic_LH_ZO);

        Matrix4 Result        = EOrthographic_RH_ZO(Left, Right, Bottom, Top, Near, Far);
        Result.Elements[2][2] = -Result.Elements[2][2];

        return Result;
    }

    COVERAGE(EInvOrthographic, 1)
    // Returns an inverse for the given orthographic projection matrix. Works for all orthographic
    // projection matrices, regardless of handedness or NDC convention.
    inline static Matrix4 EInvOrthographic(Matrix4 OrthoMatrix)
    {
        ASSERT_COVERED(EInvOrthographic);

        Matrix4 Result       {};
        Result.Elements[0][0] = 1.0f / OrthoMatrix.Elements[0][0];
        Result.Elements[1][1] = 1.0f / OrthoMatrix.Elements[1][1];
        Result.Elements[2][2] = 1.0f / OrthoMatrix.Elements[2][2];
        Result.Elements[3][3] = 1.0f;

        Result.Elements[3][0] = -OrthoMatrix.Elements[3][0] * Result.Elements[0][0];
        Result.Elements[3][1] = -OrthoMatrix.Elements[3][1] * Result.Elements[1][1];
        Result.Elements[3][2] = -OrthoMatrix.Elements[3][2] * Result.Elements[2][2];

        return Result;
    }

    COVERAGE(EPerspective_RH_NO, 1)
    inline static Matrix4 EPerspective_RH_NO(float FOV, float AspectRatio, float Near, float Far)
    {
        ASSERT_COVERED(EPerspective_RH_NO);

        Matrix4 Result{};

        // See https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluPerspective.xml

        float Cotangent       = 1.0f / ETanF(FOV / 2.0f);
        Result.Elements[0][0] = Cotangent / AspectRatio;
        Result.Elements[1][1] = Cotangent;
        Result.Elements[2][3] = -1.0f;

        Result.Elements[2][2] = (Near + Far) / (Near - Far);
        Result.Elements[3][2] = (2.0f * Near * Far) / (Near - Far);

        return Result;
    }

    COVERAGE(EPerspective_RH_ZO, 1)
    inline static Matrix4 EPerspective_RH_ZO(float FOV, float AspectRatio, float Near, float Far)
    {
        ASSERT_COVERED(EPerspective_RH_ZO);

        Matrix4 Result{};

        // See https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluPerspective.xml

        float Cotangent       = 1.0f / ETanF(FOV / 2.0f);
        Result.Elements[0][0] = Cotangent / AspectRatio;
        Result.Elements[1][1] = Cotangent;
        Result.Elements[2][3] = -1.0f;

        Result.Elements[2][2] = (Far) / (Near - Far);
        Result.Elements[3][2] = (Near * Far) / (Near - Far);

        return Result;
    }

    COVERAGE(EPerspective_LH_NO, 1)
    inline static Matrix4 EPerspective_LH_NO(float FOV, float AspectRatio, float Near, float Far)
    {
        ASSERT_COVERED(EPerspective_LH_NO);

        Matrix4 Result        = EPerspective_RH_NO(FOV, AspectRatio, Near, Far);
        Result.Elements[2][2] = -Result.Elements[2][2];
        Result.Elements[2][3] = -Result.Elements[2][3];

        return Result;
    }

    COVERAGE(EPerspective_LH_ZO, 1)
    inline static Matrix4 EPerspective_LH_ZO(float FOV, float AspectRatio, float Near, float Far)
    {
        ASSERT_COVERED(EPerspective_LH_ZO);

        Matrix4 Result        = EPerspective_RH_ZO(FOV, AspectRatio, Near, Far);
        Result.Elements[2][2] = -Result.Elements[2][2];
        Result.Elements[2][3] = -Result.Elements[2][3];

        return Result;
    }

    COVERAGE(EInvPerspective_RH, 1)
    inline static Matrix4 EInvPerspective_RH(Matrix4 PerspectiveMatrix)
    {
        ASSERT_COVERED(EInvPerspective_RH);

        Matrix4 Result       {};
        Result.Elements[0][0] = 1.0f / PerspectiveMatrix.Elements[0][0];
        Result.Elements[1][1] = 1.0f / PerspectiveMatrix.Elements[1][1];
        Result.Elements[2][2] = 0.0f;

        Result.Elements[2][3] = 1.0f / PerspectiveMatrix.Elements[3][2];
        Result.Elements[3][3] = PerspectiveMatrix.Elements[2][2] * Result.Elements[2][3];
        Result.Elements[3][2] = PerspectiveMatrix.Elements[2][3];

        return Result;
    }

    COVERAGE(EInvPerspective_LH, 1)
    inline static Matrix4 EInvPerspective_LH(Matrix4 PerspectiveMatrix)
    {
        ASSERT_COVERED(EInvPerspective_LH);

        Matrix4 Result       {};
        Result.Elements[0][0] = 1.0f / PerspectiveMatrix.Elements[0][0];
        Result.Elements[1][1] = 1.0f / PerspectiveMatrix.Elements[1][1];
        Result.Elements[2][2] = 0.0f;

        Result.Elements[2][3] = 1.0f / PerspectiveMatrix.Elements[3][2];
        Result.Elements[3][3] = PerspectiveMatrix.Elements[2][2] * -Result.Elements[2][3];
        Result.Elements[3][2] = PerspectiveMatrix.Elements[2][3];

        return Result;
    }

    COVERAGE(ETranslate, 1)
    inline static Matrix4 ETranslate(Vector3 Translation)
    {
        ASSERT_COVERED(ETranslate);

        Matrix4 Result        = EM4D(1.0f);
        Result.Elements[3][0] = Translation.X;
        Result.Elements[3][1] = Translation.Y;
        Result.Elements[3][2] = Translation.Z;

        return Result;
    }

    COVERAGE(EInvTranslate, 1)
    inline static Matrix4 EInvTranslate(Matrix4 TranslationMatrix)
    {
        ASSERT_COVERED(EInvTranslate);

        Matrix4 Result        = TranslationMatrix;
        Result.Elements[3][0] = -Result.Elements[3][0];
        Result.Elements[3][1] = -Result.Elements[3][1];
        Result.Elements[3][2] = -Result.Elements[3][2];

        return Result;
    }

    COVERAGE(ERotate_RH, 1)
    inline static Matrix4 ERotate_RH(float Angle, Vector3 Axis)
    {
        ASSERT_COVERED(ERotate_RH);

        Matrix4 Result = EM4D(1.0f);

        Axis = ENormV3(Axis);

        float SinTheta = ESinF(Angle);
        float CosTheta = ECosF(Angle);
        float CosValue = 1.0f - CosTheta;

        Result.Elements[0][0] = (Axis.X * Axis.X * CosValue) + CosTheta;
        Result.Elements[0][1] = (Axis.X * Axis.Y * CosValue) + (Axis.Z * SinTheta);
        Result.Elements[0][2] = (Axis.X * Axis.Z * CosValue) - (Axis.Y * SinTheta);

        Result.Elements[1][0] = (Axis.Y * Axis.X * CosValue) - (Axis.Z * SinTheta);
        Result.Elements[1][1] = (Axis.Y * Axis.Y * CosValue) + CosTheta;
        Result.Elements[1][2] = (Axis.Y * Axis.Z * CosValue) + (Axis.X * SinTheta);

        Result.Elements[2][0] = (Axis.Z * Axis.X * CosValue) + (Axis.Y * SinTheta);
        Result.Elements[2][1] = (Axis.Z * Axis.Y * CosValue) - (Axis.X * SinTheta);
        Result.Elements[2][2] = (Axis.Z * Axis.Z * CosValue) + CosTheta;

        return Result;
    }

    COVERAGE(ERotate_LH, 1)
    inline static Matrix4 ERotate_LH(float Angle, Vector3 Axis)
    {
        ASSERT_COVERED(ERotate_LH);
        /* NOTE(lcf): Matrix will be inverse/transpose of RH. */
        return ERotate_RH(-Angle, Axis);
    }

    COVERAGE(EInvRotate, 1)
    inline static Matrix4 EInvRotate(Matrix4 RotationMatrix)
    {
        ASSERT_COVERED(EInvRotate);
        return ETransposeM4(RotationMatrix);
    }

    COVERAGE(EScale, 1)
    inline static Matrix4 EScale(Vector3 Scale)
    {
        ASSERT_COVERED(EScale);

        Matrix4 Result        = EM4D(1.0f);
        Result.Elements[0][0] = Scale.X;
        Result.Elements[1][1] = Scale.Y;
        Result.Elements[2][2] = Scale.Z;

        return Result;
    }

    COVERAGE(EInvScale, 1)
    inline static Matrix4 EInvScale(Matrix4 ScaleMatrix)
    {
        ASSERT_COVERED(EInvScale);

        Matrix4 Result        = ScaleMatrix;
        Result.Elements[0][0] = 1.0f / Result.Elements[0][0];
        Result.Elements[1][1] = 1.0f / Result.Elements[1][1];
        Result.Elements[2][2] = 1.0f / Result.Elements[2][2];

        return Result;
    }

    inline static Matrix4 _ELookAt(Vector3 F, Vector3 S, Vector3 U, Vector3 Eye)
    {
        Matrix4 Result;

        Result.Elements[0][0] = S.X;
        Result.Elements[0][1] = U.X;
        Result.Elements[0][2] = -F.X;
        Result.Elements[0][3] = 0.0f;

        Result.Elements[1][0] = S.Y;
        Result.Elements[1][1] = U.Y;
        Result.Elements[1][2] = -F.Y;
        Result.Elements[1][3] = 0.0f;

        Result.Elements[2][0] = S.Z;
        Result.Elements[2][1] = U.Z;
        Result.Elements[2][2] = -F.Z;
        Result.Elements[2][3] = 0.0f;

        Result.Elements[3][0] = -EDotV3(S, Eye);
        Result.Elements[3][1] = -EDotV3(U, Eye);
        Result.Elements[3][2] = EDotV3(F, Eye);
        Result.Elements[3][3] = 1.0f;

        return Result;
    }

    COVERAGE(ELookAt_RH, 1)
    inline static Matrix4 ELookAt_RH(Vector3 Eye, Vector3 Center, Vector3 Up)
    {
        ASSERT_COVERED(ELookAt_RH);

        Vector3 F = ENormV3(ESubV3(Center, Eye));
        Vector3 S = ENormV3(ECross(F, Up));
        Vector3 U = ECross(S, F);

        return _ELookAt(F, S, U, Eye);
    }

    COVERAGE(ELookAt_LH, 1)
    inline static Matrix4 ELookAt_LH(Vector3 Eye, Vector3 Center, Vector3 Up)
    {
        ASSERT_COVERED(ELookAt_LH);

        Vector3 F = ENormV3(ESubV3(Eye, Center));
        Vector3 S = ENormV3(ECross(F, Up));
        Vector3 U = ECross(S, F);

        return _ELookAt(F, S, U, Eye);
    }

    COVERAGE(EInvLookAt, 1)
    inline static Matrix4 EInvLookAt(Matrix4 Matrix)
    {
        ASSERT_COVERED(EInvLookAt);
        Matrix4 Result;

        Matrix3 Rotation   {};
        Rotation.Columns[0] = Matrix.Columns[0].XYZ;
        Rotation.Columns[1] = Matrix.Columns[1].XYZ;
        Rotation.Columns[2] = Matrix.Columns[2].XYZ;
        Rotation            = ETransposeM3(Rotation);

        Result.Columns[0] = EV4V(Rotation.Columns[0], 0.0f);
        Result.Columns[1] = EV4V(Rotation.Columns[1], 0.0f);
        Result.Columns[2] = EV4V(Rotation.Columns[2], 0.0f);
        Result.Columns[3] = EMulV4F(Matrix.Columns[3], -1.0f);
        Result.Elements[3][0] =
            -1.0f * Matrix.Elements[3][0] / (Rotation.Elements[0][0] + Rotation.Elements[0][1] + Rotation.Elements[0][2]);
        Result.Elements[3][1] =
            -1.0f * Matrix.Elements[3][1] / (Rotation.Elements[1][0] + Rotation.Elements[1][1] + Rotation.Elements[1][2]);
        Result.Elements[3][2] =
            -1.0f * Matrix.Elements[3][2] / (Rotation.Elements[2][0] + Rotation.Elements[2][1] + Rotation.Elements[2][2]);
        Result.Elements[3][3] = 1.0f;

        return Result;
    }

    /*
     * Quaternion operations
     */

    COVERAGE(EQ, 1)
    inline static Quaternion EQ(float X, float Y, float Z, float W)
    {
        ASSERT_COVERED(EQ);

        Quaternion Result;

#ifdef HANDMADE_MATH__USE_SSE
        Result.SSE = _mm_setr_ps(X, Y, Z, W);
#elif defined(HANDMADE_MATH__USE_NEON)
    float32x4_t v = {X, Y, Z, W};
    Result.NEON   = v;
#else
    Result.X = X;
    Result.Y = Y;
    Result.Z = Z;
    Result.W = W;
#endif

        return Result;
    }

    COVERAGE(EQV4, 1)
    inline static Quaternion EQV4(Vector4 Vector)
    {
        ASSERT_COVERED(EQV4);

        Quaternion Result;

#ifdef HANDMADE_MATH__USE_SSE
        Result.SSE = Vector.SSE;
#elif defined(HANDMADE_MATH__USE_NEON)
    Result.NEON = Vector.NEON;
#else
    Result.X = Vector.X;
    Result.Y = Vector.Y;
    Result.Z = Vector.Z;
    Result.W = Vector.W;
#endif

        return Result;
    }

    COVERAGE(EAddQ, 1)
    inline static Quaternion EAddQ(Quaternion Left, Quaternion Right)
    {
        ASSERT_COVERED(EAddQ);

        Quaternion Result;

#ifdef HANDMADE_MATH__USE_SSE
        Result.SSE = _mm_add_ps(Left.SSE, Right.SSE);
#elif defined(HANDMADE_MATH__USE_NEON)
    Result.NEON = vaddq_f32(Left.NEON, Right.NEON);
#else

    Result.X = Left.X + Right.X;
    Result.Y = Left.Y + Right.Y;
    Result.Z = Left.Z + Right.Z;
    Result.W = Left.W + Right.W;
#endif

        return Result;
    }

    COVERAGE(ESubQ, 1)
    inline static Quaternion ESubQ(Quaternion Left, Quaternion Right)
    {
        ASSERT_COVERED(ESubQ);

        Quaternion Result;

#ifdef HANDMADE_MATH__USE_SSE
        Result.SSE = _mm_sub_ps(Left.SSE, Right.SSE);
#elif defined(HANDMADE_MATH__USE_NEON)
    Result.NEON = vsubq_f32(Left.NEON, Right.NEON);
#else
    Result.X = Left.X - Right.X;
    Result.Y = Left.Y - Right.Y;
    Result.Z = Left.Z - Right.Z;
    Result.W = Left.W - Right.W;
#endif

        return Result;
    }

    COVERAGE(EMulQ, 1)
    inline static Quaternion EMulQ(Quaternion Left, Quaternion Right)
    {
        ASSERT_COVERED(EMulQ);

        Quaternion Result;

#ifdef HANDMADE_MATH__USE_SSE
        __m128 SSEResultOne   = _mm_xor_ps(_mm_shuffle_ps(Left.SSE, Left.SSE, _MM_SHUFFLE(0, 0, 0, 0)), _mm_setr_ps(0.f, -0.f, 0.f, -0.f));
        __m128 SSEResultTwo   = _mm_shuffle_ps(Right.SSE, Right.SSE, _MM_SHUFFLE(0, 1, 2, 3));
        __m128 SSEResultThree = _mm_mul_ps(SSEResultTwo, SSEResultOne);

        SSEResultOne   = _mm_xor_ps(_mm_shuffle_ps(Left.SSE, Left.SSE, _MM_SHUFFLE(1, 1, 1, 1)), _mm_setr_ps(0.f, 0.f, -0.f, -0.f));
        SSEResultTwo   = _mm_shuffle_ps(Right.SSE, Right.SSE, _MM_SHUFFLE(1, 0, 3, 2));
        SSEResultThree = _mm_add_ps(SSEResultThree, _mm_mul_ps(SSEResultTwo, SSEResultOne));

        SSEResultOne   = _mm_xor_ps(_mm_shuffle_ps(Left.SSE, Left.SSE, _MM_SHUFFLE(2, 2, 2, 2)), _mm_setr_ps(-0.f, 0.f, 0.f, -0.f));
        SSEResultTwo   = _mm_shuffle_ps(Right.SSE, Right.SSE, _MM_SHUFFLE(2, 3, 0, 1));
        SSEResultThree = _mm_add_ps(SSEResultThree, _mm_mul_ps(SSEResultTwo, SSEResultOne));

        SSEResultOne = _mm_shuffle_ps(Left.SSE, Left.SSE, _MM_SHUFFLE(3, 3, 3, 3));
        SSEResultTwo = _mm_shuffle_ps(Right.SSE, Right.SSE, _MM_SHUFFLE(3, 2, 1, 0));
        Result.SSE   = _mm_add_ps(SSEResultThree, _mm_mul_ps(SSEResultTwo, SSEResultOne));
#elif defined(HANDMADE_MATH__USE_NEON)
    float32x4_t Right1032 = vrev64q_f32(Right.NEON);
    float32x4_t Right3210 = vcombine_f32(vget_high_f32(Right1032), vget_low_f32(Right1032));
    float32x4_t Right2301 = vrev64q_f32(Right3210);

    float32x4_t FirstSign  = {1.0f, -1.0f, 1.0f, -1.0f};
    Result.NEON            = vmulq_f32(Right3210, vmulq_f32(vdupq_laneq_f32(Left.NEON, 0), FirstSign));
    float32x4_t SecondSign = {1.0f, 1.0f, -1.0f, -1.0f};
    Result.NEON            = vfmaq_f32(Result.NEON, Right2301, vmulq_f32(vdupq_laneq_f32(Left.NEON, 1), SecondSign));
    float32x4_t ThirdSign  = {-1.0f, 1.0f, 1.0f, -1.0f};
    Result.NEON            = vfmaq_f32(Result.NEON, Right1032, vmulq_f32(vdupq_laneq_f32(Left.NEON, 2), ThirdSign));
    Result.NEON            = vfmaq_laneq_f32(Result.NEON, Right.NEON, Left.NEON, 3);

#else
    Result.X = Right.Elements[3] * +Left.Elements[0];
    Result.Y = Right.Elements[2] * -Left.Elements[0];
    Result.Z = Right.Elements[1] * +Left.Elements[0];
    Result.W = Right.Elements[0] * -Left.Elements[0];

    Result.X += Right.Elements[2] * +Left.Elements[1];
    Result.Y += Right.Elements[3] * +Left.Elements[1];
    Result.Z += Right.Elements[0] * -Left.Elements[1];
    Result.W += Right.Elements[1] * -Left.Elements[1];

    Result.X += Right.Elements[1] * -Left.Elements[2];
    Result.Y += Right.Elements[0] * +Left.Elements[2];
    Result.Z += Right.Elements[3] * +Left.Elements[2];
    Result.W += Right.Elements[2] * -Left.Elements[2];

    Result.X += Right.Elements[0] * +Left.Elements[3];
    Result.Y += Right.Elements[1] * +Left.Elements[3];
    Result.Z += Right.Elements[2] * +Left.Elements[3];
    Result.W += Right.Elements[3] * +Left.Elements[3];
#endif

        return Result;
    }

    COVERAGE(EMulQF, 1)
    inline static Quaternion EMulQF(Quaternion Left, float Multiplicative)
    {
        ASSERT_COVERED(EMulQF);

        Quaternion Result;

#ifdef HANDMADE_MATH__USE_SSE
        __m128 Scalar = _mm_set1_ps(Multiplicative);
        Result.SSE    = _mm_mul_ps(Left.SSE, Scalar);
#elif defined(HANDMADE_MATH__USE_NEON)
    Result.NEON = vmulq_n_f32(Left.NEON, Multiplicative);
#else
    Result.X = Left.X * Multiplicative;
    Result.Y = Left.Y * Multiplicative;
    Result.Z = Left.Z * Multiplicative;
    Result.W = Left.W * Multiplicative;
#endif

        return Result;
    }

    COVERAGE(EDivQF, 1)
    inline static Quaternion EDivQF(Quaternion Left, float Divnd)
    {
        ASSERT_COVERED(EDivQF);

        Quaternion Result;

#ifdef HANDMADE_MATH__USE_SSE
        __m128 Scalar = _mm_set1_ps(Divnd);
        Result.SSE    = _mm_div_ps(Left.SSE, Scalar);
#elif defined(HANDMADE_MATH__USE_NEON)
    float32x4_t Scalar = vdupq_n_f32(Divnd);
    Result.NEON        = vdivq_f32(Left.NEON, Scalar);
#else
    Result.X = Left.X / Divnd;
    Result.Y = Left.Y / Divnd;
    Result.Z = Left.Z / Divnd;
    Result.W = Left.W / Divnd;
#endif

        return Result;
    }

    COVERAGE(EDotQ, 1)
    inline static float EDotQ(Quaternion Left, Quaternion Right)
    {
        ASSERT_COVERED(EDotQ);

        float Result;

#ifdef HANDMADE_MATH__USE_SSE
        __m128 SSEResultOne = _mm_mul_ps(Left.SSE, Right.SSE);
        __m128 SSEResultTwo = _mm_shuffle_ps(SSEResultOne, SSEResultOne, _MM_SHUFFLE(2, 3, 0, 1));
        SSEResultOne        = _mm_add_ps(SSEResultOne, SSEResultTwo);
        SSEResultTwo        = _mm_shuffle_ps(SSEResultOne, SSEResultOne, _MM_SHUFFLE(0, 1, 2, 3));
        SSEResultOne        = _mm_add_ps(SSEResultOne, SSEResultTwo);
        _mm_store_ss(&Result, SSEResultOne);
#elif defined(HANDMADE_MATH__USE_NEON)
    float32x4_t NEONMultiplyResult = vmulq_f32(Left.NEON, Right.NEON);
    float32x4_t NEONHalfAdd        = vpaddq_f32(NEONMultiplyResult, NEONMultiplyResult);
    float32x4_t NEONFullAdd        = vpaddq_f32(NEONHalfAdd, NEONHalfAdd);
    Result                         = vgetq_lane_f32(NEONFullAdd, 0);
#else
    Result = ((Left.X * Right.X) + (Left.Z * Right.Z)) + ((Left.Y * Right.Y) + (Left.W * Right.W));
#endif

        return Result;
    }

    COVERAGE(EInvQ, 1)
    inline static Quaternion EInvQ(Quaternion Left)
    {
        ASSERT_COVERED(EInvQ);

        Quaternion Result;
        Result.X = -Left.X;
        Result.Y = -Left.Y;
        Result.Z = -Left.Z;
        Result.W = Left.W;

        return EDivQF(Result, (EDotQ(Left, Left)));
    }

    COVERAGE(ENormQ, 1)
    inline static Quaternion ENormQ(Quaternion Quat)
    {
        ASSERT_COVERED(ENormQ);

        /* NOTE(lcf): Take advantage of SSE implementation in ENormV4 */
        Vector4 Vec       = Vec4(Quat.X, Quat.Y, Quat.Z, Quat.W);
        Vec               = ENormV4(Vec);
        Quaternion Result;
        Result.X = Vec.X;
        Result.Y = Vec.Y;
        Result.Z = Vec.Z;
        Result.W = Vec.W;

        return Result;
    }

    inline static Quaternion _EMixQ(Quaternion Left, float MixLeft, Quaternion Right, float MixRight)
    {
        Quaternion Result;

#ifdef HANDMADE_MATH__USE_SSE
        __m128 ScalarLeft   = _mm_set1_ps(MixLeft);
        __m128 ScalarRight  = _mm_set1_ps(MixRight);
        __m128 SSEResultOne = _mm_mul_ps(Left.SSE, ScalarLeft);
        __m128 SSEResultTwo = _mm_mul_ps(Right.SSE, ScalarRight);
        Result.SSE          = _mm_add_ps(SSEResultOne, SSEResultTwo);
#elif defined(HANDMADE_MATH__USE_NEON)
    float32x4_t ScaledLeft  = vmulq_n_f32(Left.NEON, MixLeft);
    float32x4_t ScaledRight = vmulq_n_f32(Right.NEON, MixRight);
    Result.NEON             = vaddq_f32(ScaledLeft, ScaledRight);
#else
    Result.X = Left.X * MixLeft + Right.X * MixRight;
    Result.Y = Left.Y * MixLeft + Right.Y * MixRight;
    Result.Z = Left.Z * MixLeft + Right.Z * MixRight;
    Result.W = Left.W * MixLeft + Right.W * MixRight;
#endif

        return Result;
    }

    COVERAGE(ENLerp, 1)
    inline static Quaternion ENLerp(Quaternion Left, float Time, Quaternion Right)
    {
        ASSERT_COVERED(ENLerp);

        Quaternion Result = _EMixQ(Left, 1.0f - Time, Right, Time);
        Result            = ENormQ(Result);

        return Result;
    }

    COVERAGE(ESLerp, 1)
    inline static Quaternion ESLerp(Quaternion Left, float Time, Quaternion Right)
    {
        ASSERT_COVERED(ESLerp);

        Quaternion Result;

        float Cos_Theta = EDotQ(Left, Right);

        if (Cos_Theta < 0.0f)
        { /* NOTE(lcf): Take shortest path on Hyper-sphere */
            Cos_Theta = -Cos_Theta;
            Right     = EQ(-Right.X, -Right.Y, -Right.Z, -Right.W);
        }

        /* NOTE(lcf): Use Normalized Linear interpolation when vectors are roughly not L.I. */
        if (Cos_Theta > 0.9995f)
        {
            Result = ENLerp(Left, Time, Right);
        }
        else
        {
            float Angle    = EACosF(Cos_Theta);
            float MixLeft  = ESinF((1.0f - Time) * Angle);
            float MixRight = ESinF(Time * Angle);

            Result = _EMixQ(Left, MixLeft, Right, MixRight);
            Result = ENormQ(Result);
        }

        return Result;
    }

    COVERAGE(EQToM4, 1)
    inline static Matrix4 EQToM4(Quaternion Left)
    {
        ASSERT_COVERED(EQToM4);

        Matrix4 Result;

        Quaternion NormalizedQ = ENormQ(Left);

        float XX, YY, ZZ, XY, XZ, YZ, WX, WY, WZ;

        XX = NormalizedQ.X * NormalizedQ.X;
        YY = NormalizedQ.Y * NormalizedQ.Y;
        ZZ = NormalizedQ.Z * NormalizedQ.Z;
        XY = NormalizedQ.X * NormalizedQ.Y;
        XZ = NormalizedQ.X * NormalizedQ.Z;
        YZ = NormalizedQ.Y * NormalizedQ.Z;
        WX = NormalizedQ.W * NormalizedQ.X;
        WY = NormalizedQ.W * NormalizedQ.Y;
        WZ = NormalizedQ.W * NormalizedQ.Z;

        Result.Elements[0][0] = 1.0f - 2.0f * (YY + ZZ);
        Result.Elements[0][1] = 2.0f * (XY + WZ);
        Result.Elements[0][2] = 2.0f * (XZ - WY);
        Result.Elements[0][3] = 0.0f;

        Result.Elements[1][0] = 2.0f * (XY - WZ);
        Result.Elements[1][1] = 1.0f - 2.0f * (XX + ZZ);
        Result.Elements[1][2] = 2.0f * (YZ + WX);
        Result.Elements[1][3] = 0.0f;

        Result.Elements[2][0] = 2.0f * (XZ + WY);
        Result.Elements[2][1] = 2.0f * (YZ - WX);
        Result.Elements[2][2] = 1.0f - 2.0f * (XX + YY);
        Result.Elements[2][3] = 0.0f;

        Result.Elements[3][0] = 0.0f;
        Result.Elements[3][1] = 0.0f;
        Result.Elements[3][2] = 0.0f;
        Result.Elements[3][3] = 1.0f;

        return Result;
    }

    // This method taken from Mike Day at Insomniac Games.
    // https://d3cw3dd2w32x2b.cloudfront.net/wp-content/uploads/2015/01/matrix-to-quat.pdf
    //
    // Note that as mentioned at the top of the paper, the paper assumes the matrix
    // would be *post*-multiplied to a vector to rotate it, meaning the matrix is
    // the transpose of what we're dealing with. But, because our matrices are
    // stored in column-major order, the indices *appear* to match the paper.
    //
    // For example, m12 in the paper is row 1, column 2. We need to transpose it to
    // row 2, column 1. But, because the column comes first when referencing
    // elements, it looks like M.Elements[1][2].
    //
    // Don't be confused! Or if you must be confused, at least trust this
    // comment. :)
    COVERAGE(EM4ToQ_RH, 4)
    inline static Quaternion EM4ToQ_RH(Matrix4 M)
    {
        float T;
        Quaternion Q;

        if (M.Elements[2][2] < 0.0f)
        {
            if (M.Elements[0][0] > M.Elements[1][1])
            {
                ASSERT_COVERED(EM4ToQ_RH);

                T = 1 + M.Elements[0][0] - M.Elements[1][1] - M.Elements[2][2];
                Q = EQ(T, M.Elements[0][1] + M.Elements[1][0], M.Elements[2][0] + M.Elements[0][2], M.Elements[1][2] - M.Elements[2][1]);
            }
            else
            {
                ASSERT_COVERED(EM4ToQ_RH);

                T = 1 - M.Elements[0][0] + M.Elements[1][1] - M.Elements[2][2];
                Q = EQ(M.Elements[0][1] + M.Elements[1][0], T, M.Elements[1][2] + M.Elements[2][1], M.Elements[2][0] - M.Elements[0][2]);
            }
        }
        else
        {
            if (M.Elements[0][0] < -M.Elements[1][1])
            {
                ASSERT_COVERED(EM4ToQ_RH);

                T = 1 - M.Elements[0][0] - M.Elements[1][1] + M.Elements[2][2];
                Q = EQ(M.Elements[2][0] + M.Elements[0][2], M.Elements[1][2] + M.Elements[2][1], T, M.Elements[0][1] - M.Elements[1][0]);
            }
            else
            {
                ASSERT_COVERED(EM4ToQ_RH);

                T = 1 + M.Elements[0][0] + M.Elements[1][1] + M.Elements[2][2];
                Q = EQ(M.Elements[1][2] - M.Elements[2][1], M.Elements[2][0] - M.Elements[0][2], M.Elements[0][1] - M.Elements[1][0], T);
            }
        }

        Q = EMulQF(Q, 0.5f / ESqrtF(T));

        return Q;
    }

    COVERAGE(EM4ToQ_LH, 4)
    inline static Quaternion EM4ToQ_LH(Matrix4 M)
    {
        float T;
        Quaternion Q;

        if (M.Elements[2][2] < 0.0f)
        {
            if (M.Elements[0][0] > M.Elements[1][1])
            {
                ASSERT_COVERED(EM4ToQ_LH);

                T = 1 + M.Elements[0][0] - M.Elements[1][1] - M.Elements[2][2];
                Q = EQ(T, M.Elements[0][1] + M.Elements[1][0], M.Elements[2][0] + M.Elements[0][2], M.Elements[2][1] - M.Elements[1][2]);
            }
            else
            {
                ASSERT_COVERED(EM4ToQ_LH);

                T = 1 - M.Elements[0][0] + M.Elements[1][1] - M.Elements[2][2];
                Q = EQ(M.Elements[0][1] + M.Elements[1][0], T, M.Elements[1][2] + M.Elements[2][1], M.Elements[0][2] - M.Elements[2][0]);
            }
        }
        else
        {
            if (M.Elements[0][0] < -M.Elements[1][1])
            {
                ASSERT_COVERED(EM4ToQ_LH);

                T = 1 - M.Elements[0][0] - M.Elements[1][1] + M.Elements[2][2];
                Q = EQ(M.Elements[2][0] + M.Elements[0][2], M.Elements[1][2] + M.Elements[2][1], T, M.Elements[1][0] - M.Elements[0][1]);
            }
            else
            {
                ASSERT_COVERED(EM4ToQ_LH);

                T = 1 + M.Elements[0][0] + M.Elements[1][1] + M.Elements[2][2];
                Q = EQ(M.Elements[2][1] - M.Elements[1][2], M.Elements[0][2] - M.Elements[2][0], M.Elements[1][0] - M.Elements[0][2], T);
            }
        }

        Q = EMulQF(Q, 0.5f / ESqrtF(T));

        return Q;
    }

    COVERAGE(EQFromAxisAngle_RH, 1)
    inline static Quaternion EQFromAxisAngle_RH(Vector3 Axis, float Angle)
    {
        ASSERT_COVERED(EQFromAxisAngle_RH);

        Quaternion Result;

        Vector3 AxisNormalized = ENormV3(Axis);
        float SineOfRotation   = ESinF(Angle / 2.0f);

        Result.XYZ = EMulV3F(AxisNormalized, SineOfRotation);
        Result.W   = ECosF(Angle / 2.0f);

        return Result;
    }

    COVERAGE(EQFromAxisAngle_LH, 1)
    inline static Quaternion EQFromAxisAngle_LH(Vector3 Axis, float Angle)
    {
        ASSERT_COVERED(EQFromAxisAngle_LH);

        return EQFromAxisAngle_RH(Axis, -Angle);
    }

    COVERAGE(ERotateV2, 1)
    inline static Vector2 ERotateV2(Vector2 V, float Angle)
    {
        ASSERT_COVERED(ERotateV2)

        float sinA = ESinF(Angle);
        float cosA = ECosF(Angle);

        return EV2(V.X * cosA - V.Y * sinA, V.X * sinA + V.Y * cosA);
    }

    // implementation from
    // https://blog.molecular-matters.com/2013/05/24/a-faster-quaternion-vector-multiplication/
    COVERAGE(ERotateV3Q, 1)
    inline static Vector3 ERotateV3Q(Vector3 V, Quaternion Q)
    {
        ASSERT_COVERED(ERotateV3Q);

        Vector3 t = EMulV3F(ECross(Q.XYZ, V), 2);
        return EAddV3(V, EAddV3(EMulV3F(t, Q.W), ECross(Q.XYZ, t)));
    }

    COVERAGE(ERotateV3AxisAngle_LH, 1)
    inline static Vector3 ERotateV3AxisAngle_LH(Vector3 V, Vector3 Axis, float Angle)
    {
        ASSERT_COVERED(ERotateV3AxisAngle_LH);

        return ERotateV3Q(V, EQFromAxisAngle_LH(Axis, Angle));
    }

    COVERAGE(ERotateV3AxisAngle_RH, 1)
    inline static Vector3 ERotateV3AxisAngle_RH(Vector3 V, Vector3 Axis, float Angle)
    {
        ASSERT_COVERED(ERotateV3AxisAngle_RH);

        return ERotateV3Q(V, EQFromAxisAngle_RH(Axis, Angle));
    }

} // namespace Ers

#ifdef __cplusplus

using namespace Ers;

COVERAGE(ELenV2CPP, 1)
inline static float ELen(Vector2 A)
{
    ASSERT_COVERED(ELenV2CPP);
    return ELenV2(A);
}

COVERAGE(ELenV3CPP, 1)
inline static float ELen(Vector3 A)
{
    ASSERT_COVERED(ELenV3CPP);
    return ELenV3(A);
}

COVERAGE(ELenV4CPP, 1)
inline static float ELen(Vector4 A)
{
    ASSERT_COVERED(ELenV4CPP);
    return ELenV4(A);
}

COVERAGE(ELenSqrV2CPP, 1)
inline static float ELenSqr(Vector2 A)
{
    ASSERT_COVERED(ELenSqrV2CPP);
    return ELenSqrV2(A);
}

COVERAGE(ELenSqrV3CPP, 1)
inline static float ELenSqr(Vector3 A)
{
    ASSERT_COVERED(ELenSqrV3CPP);
    return ELenSqrV3(A);
}

COVERAGE(ELenSqrV4CPP, 1)
inline static float ELenSqr(Vector4 A)
{
    ASSERT_COVERED(ELenSqrV4CPP);
    return ELenSqrV4(A);
}

COVERAGE(ENormV2CPP, 1)
inline static Vector2 ENorm(Vector2 A)
{
    ASSERT_COVERED(ENormV2CPP);
    return ENormV2(A);
}

COVERAGE(ENormV3CPP, 1)
inline static Vector3 ENorm(Vector3 A)
{
    ASSERT_COVERED(ENormV3CPP);
    return ENormV3(A);
}

COVERAGE(ENormV4CPP, 1)
inline static Vector4 ENorm(Vector4 A)
{
    ASSERT_COVERED(ENormV4CPP);
    return ENormV4(A);
}

COVERAGE(ENormQCPP, 1)
inline static Quaternion ENorm(Quaternion A)
{
    ASSERT_COVERED(ENormQCPP);
    return ENormQ(A);
}

COVERAGE(EDotV2CPP, 1)
inline static float EDot(Vector2 Left, Vector2 VecTwo)
{
    ASSERT_COVERED(EDotV2CPP);
    return EDotV2(Left, VecTwo);
}

COVERAGE(EDotV3CPP, 1)
inline static float EDot(Vector3 Left, Vector3 VecTwo)
{
    ASSERT_COVERED(EDotV3CPP);
    return EDotV3(Left, VecTwo);
}

COVERAGE(EDotV4CPP, 1)
inline static float EDot(Vector4 Left, Vector4 VecTwo)
{
    ASSERT_COVERED(EDotV4CPP);
    return EDotV4(Left, VecTwo);
}

COVERAGE(ELerpV2CPP, 1)
inline static Vector2 ELerp(Vector2 Left, float Time, Vector2 Right)
{
    ASSERT_COVERED(ELerpV2CPP);
    return ELerpV2(Left, Time, Right);
}

COVERAGE(ELerpV3CPP, 1)
inline static Vector3 ELerp(Vector3 Left, float Time, Vector3 Right)
{
    ASSERT_COVERED(ELerpV3CPP);
    return ELerpV3(Left, Time, Right);
}

COVERAGE(ELerpV4CPP, 1)
inline static Vector4 ELerp(Vector4 Left, float Time, Vector4 Right)
{
    ASSERT_COVERED(ELerpV4CPP);
    return ELerpV4(Left, Time, Right);
}

inline static Vector2 ESign(Vector2 Vector)
{
    return ESignV2(Vector);
}

inline static Vector3 ESign(Vector3 Vector)
{
    return ESignV3(Vector);
}

COVERAGE(ETransposeM2CPP, 1)
inline static Matrix2 ETranspose(Matrix2 Matrix)
{
    ASSERT_COVERED(ETransposeM2CPP);
    return ETransposeM2(Matrix);
}

COVERAGE(ETransposeM3CPP, 1)
inline static Matrix3 ETranspose(Matrix3 Matrix)
{
    ASSERT_COVERED(ETransposeM3CPP);
    return ETransposeM3(Matrix);
}

COVERAGE(ETransposeM4CPP, 1)
inline static Matrix4 ETranspose(Matrix4 Matrix)
{
    ASSERT_COVERED(ETransposeM4CPP);
    return ETransposeM4(Matrix);
}

COVERAGE(EDeterminantM2CPP, 1)
inline static float EDeterminant(Matrix2 Matrix)
{
    ASSERT_COVERED(EDeterminantM2CPP);
    return EDeterminantM2(Matrix);
}

COVERAGE(EDeterminantM3CPP, 1)
inline static float EDeterminant(Matrix3 Matrix)
{
    ASSERT_COVERED(EDeterminantM3CPP);
    return EDeterminantM3(Matrix);
}

COVERAGE(EDeterminantM4CPP, 1)
inline static float EDeterminant(Matrix4 Matrix)
{
    ASSERT_COVERED(EDeterminantM4CPP);
    return EDeterminantM4(Matrix);
}

COVERAGE(EInvGeneralM2CPP, 1)
inline static Matrix2 EInvGeneral(Matrix2 Matrix)
{
    ASSERT_COVERED(EInvGeneralM2CPP);
    return EInvGeneralM2(Matrix);
}

COVERAGE(EInvGeneralM3CPP, 1)
inline static Matrix3 EInvGeneral(Matrix3 Matrix)
{
    ASSERT_COVERED(EInvGeneralM3CPP);
    return EInvGeneralM3(Matrix);
}

COVERAGE(EInvGeneralM4CPP, 1)
inline static Matrix4 EInvGeneral(Matrix4 Matrix)
{
    ASSERT_COVERED(EInvGeneralM4CPP);
    return EInvGeneralM4(Matrix);
}

COVERAGE(EDotQCPP, 1)
inline static float EDot(Quaternion QuatOne, Quaternion QuatTwo)
{
    ASSERT_COVERED(EDotQCPP);
    return EDotQ(QuatOne, QuatTwo);
}

COVERAGE(EAddV2CPP, 1)
inline static Vector2 EAdd(Vector2 Left, Vector2 Right)
{
    ASSERT_COVERED(EAddV2CPP);
    return EAddV2(Left, Right);
}

COVERAGE(EAddV3CPP, 1)
inline static Vector3 EAdd(Vector3 Left, Vector3 Right)
{
    ASSERT_COVERED(EAddV3CPP);
    return EAddV3(Left, Right);
}

COVERAGE(EAddV4CPP, 1)
inline static Vector4 EAdd(Vector4 Left, Vector4 Right)
{
    ASSERT_COVERED(EAddV4CPP);
    return EAddV4(Left, Right);
}

COVERAGE(EAddM2CPP, 1)
inline static Matrix2 EAdd(Matrix2 Left, Matrix2 Right)
{
    ASSERT_COVERED(EAddM2CPP);
    return EAddM2(Left, Right);
}

COVERAGE(EAddM3CPP, 1)
inline static Matrix3 EAdd(Matrix3 Left, Matrix3 Right)
{
    ASSERT_COVERED(EAddM3CPP);
    return EAddM3(Left, Right);
}

COVERAGE(EAddM4CPP, 1)
inline static Matrix4 EAdd(Matrix4 Left, Matrix4 Right)
{
    ASSERT_COVERED(EAddM4CPP);
    return EAddM4(Left, Right);
}

COVERAGE(EAddQCPP, 1)
inline static Quaternion EAdd(Quaternion Left, Quaternion Right)
{
    ASSERT_COVERED(EAddQCPP);
    return EAddQ(Left, Right);
}

COVERAGE(ESubV2CPP, 1)
inline static Vector2 ESub(Vector2 Left, Vector2 Right)
{
    ASSERT_COVERED(ESubV2CPP);
    return ESubV2(Left, Right);
}

COVERAGE(ESubV3CPP, 1)
inline static Vector3 ESub(Vector3 Left, Vector3 Right)
{
    ASSERT_COVERED(ESubV3CPP);
    return ESubV3(Left, Right);
}

COVERAGE(ESubV4CPP, 1)
inline static Vector4 ESub(Vector4 Left, Vector4 Right)
{
    ASSERT_COVERED(ESubV4CPP);
    return ESubV4(Left, Right);
}

COVERAGE(ESubM2CPP, 1)
inline static Matrix2 ESub(Matrix2 Left, Matrix2 Right)
{
    ASSERT_COVERED(ESubM2CPP);
    return ESubM2(Left, Right);
}

COVERAGE(ESubM3CPP, 1)
inline static Matrix3 ESub(Matrix3 Left, Matrix3 Right)
{
    ASSERT_COVERED(ESubM3CPP);
    return ESubM3(Left, Right);
}

COVERAGE(ESubM4CPP, 1)
inline static Matrix4 ESub(Matrix4 Left, Matrix4 Right)
{
    ASSERT_COVERED(ESubM4CPP);
    return ESubM4(Left, Right);
}

COVERAGE(ESubQCPP, 1)
inline static Quaternion ESub(Quaternion Left, Quaternion Right)
{
    ASSERT_COVERED(ESubQCPP);
    return ESubQ(Left, Right);
}

COVERAGE(EMulV2CPP, 1)
inline static Vector2 EMul(Vector2 Left, Vector2 Right)
{
    ASSERT_COVERED(EMulV2CPP);
    return EMulV2(Left, Right);
}

COVERAGE(EMulV2FCPP, 1)
inline static Vector2 EMul(Vector2 Left, float Right)
{
    ASSERT_COVERED(EMulV2FCPP);
    return EMulV2F(Left, Right);
}

COVERAGE(EMulV3CPP, 1)
inline static Vector3 EMul(Vector3 Left, Vector3 Right)
{
    ASSERT_COVERED(EMulV3CPP);
    return EMulV3(Left, Right);
}

COVERAGE(EMulV3FCPP, 1)
inline static Vector3 EMul(Vector3 Left, float Right)
{
    ASSERT_COVERED(EMulV3FCPP);
    return EMulV3F(Left, Right);
}

COVERAGE(EMulV4CPP, 1)
inline static Vector4 EMul(Vector4 Left, Vector4 Right)
{
    ASSERT_COVERED(EMulV4CPP);
    return EMulV4(Left, Right);
}

COVERAGE(EMulV4FCPP, 1)
inline static Vector4 EMul(Vector4 Left, float Right)
{
    ASSERT_COVERED(EMulV4FCPP);
    return EMulV4F(Left, Right);
}

COVERAGE(EMulM2CPP, 1)
inline static Matrix2 EMul(Matrix2 Left, Matrix2 Right)
{
    ASSERT_COVERED(EMulM2CPP);
    return EMulM2(Left, Right);
}

COVERAGE(EMulM3CPP, 1)
inline static Matrix3 EMul(Matrix3 Left, Matrix3 Right)
{
    ASSERT_COVERED(EMulM3CPP);
    return EMulM3(Left, Right);
}

COVERAGE(EMulM4CPP, 1)
inline static Matrix4 EMul(Matrix4 Left, Matrix4 Right)
{
    ASSERT_COVERED(EMulM4CPP);
    return EMulM4(Left, Right);
}

COVERAGE(EMulM2FCPP, 1)
inline static Matrix2 EMul(Matrix2 Left, float Right)
{
    ASSERT_COVERED(EMulM2FCPP);
    return EMulM2F(Left, Right);
}

COVERAGE(EMulM3FCPP, 1)
inline static Matrix3 EMul(Matrix3 Left, float Right)
{
    ASSERT_COVERED(EMulM3FCPP);
    return EMulM3F(Left, Right);
}

COVERAGE(EMulM4FCPP, 1)
inline static Matrix4 EMul(Matrix4 Left, float Right)
{
    ASSERT_COVERED(EMulM4FCPP);
    return EMulM4F(Left, Right);
}

COVERAGE(EMulM2V2CPP, 1)
inline static Vector2 EMul(Matrix2 Matrix, Vector2 Vector)
{
    ASSERT_COVERED(EMulM2V2CPP);
    return EMulM2V2(Matrix, Vector);
}

COVERAGE(EMulM3V3CPP, 1)
inline static Vector3 EMul(Matrix3 Matrix, Vector3 Vector)
{
    ASSERT_COVERED(EMulM3V3CPP);
    return EMulM3V3(Matrix, Vector);
}

COVERAGE(EMulM4V4CPP, 1)
inline static Vector4 EMul(Matrix4 Matrix, Vector4 Vector)
{
    ASSERT_COVERED(EMulM4V4CPP);
    return EMulM4V4(Matrix, Vector);
}

COVERAGE(EMulQCPP, 1)
inline static Quaternion EMul(Quaternion Left, Quaternion Right)
{
    ASSERT_COVERED(EMulQCPP);
    return EMulQ(Left, Right);
}

COVERAGE(EMulQFCPP, 1)
inline static Quaternion EMul(Quaternion Left, float Right)
{
    ASSERT_COVERED(EMulQFCPP);
    return EMulQF(Left, Right);
}

COVERAGE(EDivV2CPP, 1)
inline static Vector2 EDiv(Vector2 Left, Vector2 Right)
{
    ASSERT_COVERED(EDivV2CPP);
    return EDivV2(Left, Right);
}

COVERAGE(EDivV2FCPP, 1)
inline static Vector2 EDiv(Vector2 Left, float Right)
{
    ASSERT_COVERED(EDivV2FCPP);
    return EDivV2F(Left, Right);
}

COVERAGE(EDivV3CPP, 1)
inline static Vector3 EDiv(Vector3 Left, Vector3 Right)
{
    ASSERT_COVERED(EDivV3CPP);
    return EDivV3(Left, Right);
}

COVERAGE(EDivV3FCPP, 1)
inline static Vector3 EDiv(Vector3 Left, float Right)
{
    ASSERT_COVERED(EDivV3FCPP);
    return EDivV3F(Left, Right);
}

COVERAGE(EDivV4CPP, 1)
inline static Vector4 EDiv(Vector4 Left, Vector4 Right)
{
    ASSERT_COVERED(EDivV4CPP);
    return EDivV4(Left, Right);
}

COVERAGE(EDivV4FCPP, 1)
inline static Vector4 EDiv(Vector4 Left, float Right)
{
    ASSERT_COVERED(EDivV4FCPP);
    return EDivV4F(Left, Right);
}

COVERAGE(EDivM2FCPP, 1)
inline static Matrix2 EDiv(Matrix2 Left, float Right)
{
    ASSERT_COVERED(EDivM2FCPP);
    return EDivM2F(Left, Right);
}

COVERAGE(EDivM3FCPP, 1)
inline static Matrix3 EDiv(Matrix3 Left, float Right)
{
    ASSERT_COVERED(EDivM3FCPP);
    return EDivM3F(Left, Right);
}

COVERAGE(EDivM4FCPP, 1)
inline static Matrix4 EDiv(Matrix4 Left, float Right)
{
    ASSERT_COVERED(EDivM4FCPP);
    return EDivM4F(Left, Right);
}

COVERAGE(EDivQFCPP, 1)
inline static Quaternion EDiv(Quaternion Left, float Right)
{
    ASSERT_COVERED(EDivQFCPP);
    return EDivQF(Left, Right);
}

COVERAGE(EEqV2CPP, 1)
inline static EBool EEq(Vector2 Left, Vector2 Right)
{
    ASSERT_COVERED(EEqV2CPP);
    return EEqV2(Left, Right);
}

COVERAGE(EEqV3CPP, 1)
inline static EBool EEq(Vector3 Left, Vector3 Right)
{
    ASSERT_COVERED(EEqV3CPP);
    return EEqV3(Left, Right);
}

COVERAGE(EEqV4CPP, 1)
inline static EBool EEq(Vector4 Left, Vector4 Right)
{
    ASSERT_COVERED(EEqV4CPP);
    return EEqV4(Left, Right);
}

COVERAGE(EAddV2Op, 1)
inline static Vector2 operator+(Vector2 Left, Vector2 Right)
{
    ASSERT_COVERED(EAddV2Op);
    return EAddV2(Left, Right);
}

COVERAGE(EAddV3Op, 1)
inline static Vector3 operator+(Vector3 Left, Vector3 Right)
{
    ASSERT_COVERED(EAddV3Op);
    return EAddV3(Left, Right);
}

COVERAGE(EAddV4Op, 1)
inline static Vector4 operator+(Vector4 Left, Vector4 Right)
{
    ASSERT_COVERED(EAddV4Op);
    return EAddV4(Left, Right);
}

COVERAGE(EAddM2Op, 1)
inline static Matrix2 operator+(Matrix2 Left, Matrix2 Right)
{
    ASSERT_COVERED(EAddM2Op);
    return EAddM2(Left, Right);
}

COVERAGE(EAddM3Op, 1)
inline static Matrix3 operator+(Matrix3 Left, Matrix3 Right)
{
    ASSERT_COVERED(EAddM3Op);
    return EAddM3(Left, Right);
}

COVERAGE(EAddM4Op, 1)
inline static Matrix4 operator+(Matrix4 Left, Matrix4 Right)
{
    ASSERT_COVERED(EAddM4Op);
    return EAddM4(Left, Right);
}

COVERAGE(EAddQOp, 1)
inline static Quaternion operator+(Quaternion Left, Quaternion Right)
{
    ASSERT_COVERED(EAddQOp);
    return EAddQ(Left, Right);
}

COVERAGE(ESubV2Op, 1)
inline static Vector2 operator-(Vector2 Left, Vector2 Right)
{
    ASSERT_COVERED(ESubV2Op);
    return ESubV2(Left, Right);
}

COVERAGE(ESubV3Op, 1)
inline static Vector3 operator-(Vector3 Left, Vector3 Right)
{
    ASSERT_COVERED(ESubV3Op);
    return ESubV3(Left, Right);
}

COVERAGE(ESubV4Op, 1)
inline static Vector4 operator-(Vector4 Left, Vector4 Right)
{
    ASSERT_COVERED(ESubV4Op);
    return ESubV4(Left, Right);
}

COVERAGE(ESubM2Op, 1)
inline static Matrix2 operator-(Matrix2 Left, Matrix2 Right)
{
    ASSERT_COVERED(ESubM2Op);
    return ESubM2(Left, Right);
}

COVERAGE(ESubM3Op, 1)
inline static Matrix3 operator-(Matrix3 Left, Matrix3 Right)
{
    ASSERT_COVERED(ESubM3Op);
    return ESubM3(Left, Right);
}

COVERAGE(ESubM4Op, 1)
inline static Matrix4 operator-(Matrix4 Left, Matrix4 Right)
{
    ASSERT_COVERED(ESubM4Op);
    return ESubM4(Left, Right);
}

COVERAGE(ESubQOp, 1)
inline static Quaternion operator-(Quaternion Left, Quaternion Right)
{
    ASSERT_COVERED(ESubQOp);
    return ESubQ(Left, Right);
}

COVERAGE(EMulV2Op, 1)
inline static Vector2 operator*(Vector2 Left, Vector2 Right)
{
    ASSERT_COVERED(EMulV2Op);
    return EMulV2(Left, Right);
}

COVERAGE(EMulV3Op, 1)
inline static Vector3 operator*(Vector3 Left, Vector3 Right)
{
    ASSERT_COVERED(EMulV3Op);
    return EMulV3(Left, Right);
}

COVERAGE(EMulV4Op, 1)
inline static Vector4 operator*(Vector4 Left, Vector4 Right)
{
    ASSERT_COVERED(EMulV4Op);
    return EMulV4(Left, Right);
}

COVERAGE(EMulM2Op, 1)
inline static Matrix2 operator*(Matrix2 Left, Matrix2 Right)
{
    ASSERT_COVERED(EMulM2Op);
    return EMulM2(Left, Right);
}

COVERAGE(EMulM3Op, 1)
inline static Matrix3 operator*(Matrix3 Left, Matrix3 Right)
{
    ASSERT_COVERED(EMulM3Op);
    return EMulM3(Left, Right);
}

COVERAGE(EMulM4Op, 1)
inline static Matrix4 operator*(Matrix4 Left, Matrix4 Right)
{
    ASSERT_COVERED(EMulM4Op);
    return EMulM4(Left, Right);
}

COVERAGE(EMulQOp, 1)
inline static Quaternion operator*(Quaternion Left, Quaternion Right)
{
    ASSERT_COVERED(EMulQOp);
    return EMulQ(Left, Right);
}

COVERAGE(EMulV2FOp, 1)
inline static Vector2 operator*(Vector2 Left, float Right)
{
    ASSERT_COVERED(EMulV2FOp);
    return EMulV2F(Left, Right);
}

COVERAGE(EMulV3FOp, 1)
inline static Vector3 operator*(Vector3 Left, float Right)
{
    ASSERT_COVERED(EMulV3FOp);
    return EMulV3F(Left, Right);
}

COVERAGE(EMulV4FOp, 1)
inline static Vector4 operator*(Vector4 Left, float Right)
{
    ASSERT_COVERED(EMulV4FOp);
    return EMulV4F(Left, Right);
}

COVERAGE(EMulM2FOp, 1)
inline static Matrix2 operator*(Matrix2 Left, float Right)
{
    ASSERT_COVERED(EMulM2FOp);
    return EMulM2F(Left, Right);
}

COVERAGE(EMulM3FOp, 1)
inline static Matrix3 operator*(Matrix3 Left, float Right)
{
    ASSERT_COVERED(EMulM3FOp);
    return EMulM3F(Left, Right);
}

COVERAGE(EMulM4FOp, 1)
inline static Matrix4 operator*(Matrix4 Left, float Right)
{
    ASSERT_COVERED(EMulM4FOp);
    return EMulM4F(Left, Right);
}

COVERAGE(EMulQFOp, 1)
inline static Quaternion operator*(Quaternion Left, float Right)
{
    ASSERT_COVERED(EMulQFOp);
    return EMulQF(Left, Right);
}

COVERAGE(EMulV2FOpLeft, 1)
inline static Vector2 operator*(float Left, Vector2 Right)
{
    ASSERT_COVERED(EMulV2FOpLeft);
    return EMulV2F(Right, Left);
}

COVERAGE(EMulV3FOpLeft, 1)
inline static Vector3 operator*(float Left, Vector3 Right)
{
    ASSERT_COVERED(EMulV3FOpLeft);
    return EMulV3F(Right, Left);
}

COVERAGE(EMulV4FOpLeft, 1)
inline static Vector4 operator*(float Left, Vector4 Right)
{
    ASSERT_COVERED(EMulV4FOpLeft);
    return EMulV4F(Right, Left);
}

COVERAGE(EMulM2FOpLeft, 1)
inline static Matrix2 operator*(float Left, Matrix2 Right)
{
    ASSERT_COVERED(EMulM2FOpLeft);
    return EMulM2F(Right, Left);
}

COVERAGE(EMulM3FOpLeft, 1)
inline static Matrix3 operator*(float Left, Matrix3 Right)
{
    ASSERT_COVERED(EMulM3FOpLeft);
    return EMulM3F(Right, Left);
}

COVERAGE(EMulM4FOpLeft, 1)
inline static Matrix4 operator*(float Left, Matrix4 Right)
{
    ASSERT_COVERED(EMulM4FOpLeft);
    return EMulM4F(Right, Left);
}

COVERAGE(EMulQFOpLeft, 1)
inline static Quaternion operator*(float Left, Quaternion Right)
{
    ASSERT_COVERED(EMulQFOpLeft);
    return EMulQF(Right, Left);
}

COVERAGE(EMulM2V2Op, 1)
inline static Vector2 operator*(Matrix2 Matrix, Vector2 Vector)
{
    ASSERT_COVERED(EMulM2V2Op);
    return EMulM2V2(Matrix, Vector);
}

COVERAGE(EMulM3V3Op, 1)
inline static Vector3 operator*(Matrix3 Matrix, Vector3 Vector)
{
    ASSERT_COVERED(EMulM3V3Op);
    return EMulM3V3(Matrix, Vector);
}

COVERAGE(EMulM4V4Op, 1)
inline static Vector4 operator*(Matrix4 Matrix, Vector4 Vector)
{
    ASSERT_COVERED(EMulM4V4Op);
    return EMulM4V4(Matrix, Vector);
}

COVERAGE(EDivV2Op, 1)
inline static Vector2 operator/(Vector2 Left, Vector2 Right)
{
    ASSERT_COVERED(EDivV2Op);
    return EDivV2(Left, Right);
}

COVERAGE(EDivV3Op, 1)
inline static Vector3 operator/(Vector3 Left, Vector3 Right)
{
    ASSERT_COVERED(EDivV3Op);
    return EDivV3(Left, Right);
}

COVERAGE(EDivV4Op, 1)
inline static Vector4 operator/(Vector4 Left, Vector4 Right)
{
    ASSERT_COVERED(EDivV4Op);
    return EDivV4(Left, Right);
}

COVERAGE(EDivV2FOp, 1)
inline static Vector2 operator/(Vector2 Left, float Right)
{
    ASSERT_COVERED(EDivV2FOp);
    return EDivV2F(Left, Right);
}

COVERAGE(EDivV3FOp, 1)
inline static Vector3 operator/(Vector3 Left, float Right)
{
    ASSERT_COVERED(EDivV3FOp);
    return EDivV3F(Left, Right);
}

COVERAGE(EDivV4FOp, 1)
inline static Vector4 operator/(Vector4 Left, float Right)
{
    ASSERT_COVERED(EDivV4FOp);
    return EDivV4F(Left, Right);
}

COVERAGE(EDivM4FOp, 1)
inline static Matrix4 operator/(Matrix4 Left, float Right)
{
    ASSERT_COVERED(EDivM4FOp);
    return EDivM4F(Left, Right);
}

COVERAGE(EDivM3FOp, 1)
inline static Matrix3 operator/(Matrix3 Left, float Right)
{
    ASSERT_COVERED(EDivM3FOp);
    return EDivM3F(Left, Right);
}

COVERAGE(EDivM2FOp, 1)
inline static Matrix2 operator/(Matrix2 Left, float Right)
{
    ASSERT_COVERED(EDivM2FOp);
    return EDivM2F(Left, Right);
}

COVERAGE(EDivQFOp, 1)
inline static Quaternion operator/(Quaternion Left, float Right)
{
    ASSERT_COVERED(EDivQFOp);
    return EDivQF(Left, Right);
}

COVERAGE(EAddV2Assign, 1)
inline static Vector2& operator+=(Vector2& Left, Vector2 Right)
{
    ASSERT_COVERED(EAddV2Assign);
    return Left = Left + Right;
}

COVERAGE(EAddV3Assign, 1)
inline static Vector3& operator+=(Vector3& Left, Vector3 Right)
{
    ASSERT_COVERED(EAddV3Assign);
    return Left = Left + Right;
}

COVERAGE(EAddV4Assign, 1)
inline static Vector4& operator+=(Vector4& Left, Vector4 Right)
{
    ASSERT_COVERED(EAddV4Assign);
    return Left = Left + Right;
}

COVERAGE(EAddM2Assign, 1)
inline static Matrix2& operator+=(Matrix2& Left, Matrix2 Right)
{
    ASSERT_COVERED(EAddM2Assign);
    return Left = Left + Right;
}

COVERAGE(EAddM3Assign, 1)
inline static Matrix3& operator+=(Matrix3& Left, Matrix3 Right)
{
    ASSERT_COVERED(EAddM3Assign);
    return Left = Left + Right;
}

COVERAGE(EAddM4Assign, 1)
inline static Matrix4& operator+=(Matrix4& Left, Matrix4 Right)
{
    ASSERT_COVERED(EAddM4Assign);
    return Left = Left + Right;
}

COVERAGE(EAddQAssign, 1)
inline static Quaternion& operator+=(Quaternion& Left, Quaternion Right)
{
    ASSERT_COVERED(EAddQAssign);
    return Left = Left + Right;
}

COVERAGE(ESubV2Assign, 1)
inline static Vector2& operator-=(Vector2& Left, Vector2 Right)
{
    ASSERT_COVERED(ESubV2Assign);
    return Left = Left - Right;
}

COVERAGE(ESubV3Assign, 1)
inline static Vector3& operator-=(Vector3& Left, Vector3 Right)
{
    ASSERT_COVERED(ESubV3Assign);
    return Left = Left - Right;
}

COVERAGE(ESubV4Assign, 1)
inline static Vector4& operator-=(Vector4& Left, Vector4 Right)
{
    ASSERT_COVERED(ESubV4Assign);
    return Left = Left - Right;
}

COVERAGE(ESubM2Assign, 1)
inline static Matrix2& operator-=(Matrix2& Left, Matrix2 Right)
{
    ASSERT_COVERED(ESubM2Assign);
    return Left = Left - Right;
}

COVERAGE(ESubM3Assign, 1)
inline static Matrix3& operator-=(Matrix3& Left, Matrix3 Right)
{
    ASSERT_COVERED(ESubM3Assign);
    return Left = Left - Right;
}

COVERAGE(ESubM4Assign, 1)
inline static Matrix4& operator-=(Matrix4& Left, Matrix4 Right)
{
    ASSERT_COVERED(ESubM4Assign);
    return Left = Left - Right;
}

COVERAGE(ESubQAssign, 1)
inline static Quaternion& operator-=(Quaternion& Left, Quaternion Right)
{
    ASSERT_COVERED(ESubQAssign);
    return Left = Left - Right;
}

COVERAGE(EMulV2Assign, 1)
inline static Vector2& operator*=(Vector2& Left, Vector2 Right)
{
    ASSERT_COVERED(EMulV2Assign);
    return Left = Left * Right;
}

COVERAGE(EMulV3Assign, 1)
inline static Vector3& operator*=(Vector3& Left, Vector3 Right)
{
    ASSERT_COVERED(EMulV3Assign);
    return Left = Left * Right;
}

COVERAGE(EMulV4Assign, 1)
inline static Vector4& operator*=(Vector4& Left, Vector4 Right)
{
    ASSERT_COVERED(EMulV4Assign);
    return Left = Left * Right;
}

COVERAGE(EMulV2FAssign, 1)
inline static Vector2& operator*=(Vector2& Left, float Right)
{
    ASSERT_COVERED(EMulV2FAssign);
    return Left = Left * Right;
}

COVERAGE(EMulV3FAssign, 1)
inline static Vector3& operator*=(Vector3& Left, float Right)
{
    ASSERT_COVERED(EMulV3FAssign);
    return Left = Left * Right;
}

COVERAGE(EMulV4FAssign, 1)
inline static Vector4& operator*=(Vector4& Left, float Right)
{
    ASSERT_COVERED(EMulV4FAssign);
    return Left = Left * Right;
}

COVERAGE(EMulM2FAssign, 1)
inline static Matrix2& operator*=(Matrix2& Left, float Right)
{
    ASSERT_COVERED(EMulM2FAssign);
    return Left = Left * Right;
}

COVERAGE(EMulM3FAssign, 1)
inline static Matrix3& operator*=(Matrix3& Left, float Right)
{
    ASSERT_COVERED(EMulM3FAssign);
    return Left = Left * Right;
}

COVERAGE(EMulM4FAssign, 1)
inline static Matrix4& operator*=(Matrix4& Left, float Right)
{
    ASSERT_COVERED(EMulM4FAssign);
    return Left = Left * Right;
}

COVERAGE(EMulQFAssign, 1)
inline static Quaternion& operator*=(Quaternion& Left, float Right)
{
    ASSERT_COVERED(EMulQFAssign);
    return Left = Left * Right;
}

COVERAGE(EDivV2Assign, 1)
inline static Vector2& operator/=(Vector2& Left, Vector2 Right)
{
    ASSERT_COVERED(EDivV2Assign);
    return Left = Left / Right;
}

COVERAGE(EDivV3Assign, 1)
inline static Vector3& operator/=(Vector3& Left, Vector3 Right)
{
    ASSERT_COVERED(EDivV3Assign);
    return Left = Left / Right;
}

COVERAGE(EDivV4Assign, 1)
inline static Vector4& operator/=(Vector4& Left, Vector4 Right)
{
    ASSERT_COVERED(EDivV4Assign);
    return Left = Left / Right;
}

COVERAGE(EDivV2FAssign, 1)
inline static Vector2& operator/=(Vector2& Left, float Right)
{
    ASSERT_COVERED(EDivV2FAssign);
    return Left = Left / Right;
}

COVERAGE(EDivV3FAssign, 1)
inline static Vector3& operator/=(Vector3& Left, float Right)
{
    ASSERT_COVERED(EDivV3FAssign);
    return Left = Left / Right;
}

COVERAGE(EDivV4FAssign, 1)
inline static Vector4& operator/=(Vector4& Left, float Right)
{
    ASSERT_COVERED(EDivV4FAssign);
    return Left = Left / Right;
}

COVERAGE(EDivM4FAssign, 1)
inline static Matrix4& operator/=(Matrix4& Left, float Right)
{
    ASSERT_COVERED(EDivM4FAssign);
    return Left = Left / Right;
}

COVERAGE(EDivQFAssign, 1)
inline static Quaternion& operator/=(Quaternion& Left, float Right)
{
    ASSERT_COVERED(EDivQFAssign);
    return Left = Left / Right;
}

COVERAGE(EEqV2Op, 1)
inline static EBool operator==(Vector2 Left, Vector2 Right)
{
    ASSERT_COVERED(EEqV2Op);
    return EEqV2(Left, Right);
}

COVERAGE(EEqV3Op, 1)
inline static EBool operator==(Vector3 Left, Vector3 Right)
{
    ASSERT_COVERED(EEqV3Op);
    return EEqV3(Left, Right);
}

COVERAGE(EEqV4Op, 1)
inline static EBool operator==(Vector4 Left, Vector4 Right)
{
    ASSERT_COVERED(EEqV4Op);
    return EEqV4(Left, Right);
}

COVERAGE(EEqM3Op, 1)
inline static EBool operator==(Matrix3 Left, Matrix3 Right)
{
    ASSERT_COVERED(EEqM3Op);
    return EEqM3(Left, Right);
}

COVERAGE(EEqM4Op, 1)
inline static EBool operator==(Matrix4 Left, Matrix4 Right)
{
    ASSERT_COVERED(EEqM4Op);
    return EEqM4(Left, Right);
}

COVERAGE(EEqV2OpNot, 1)
inline static EBool operator!=(Vector2 Left, Vector2 Right)
{
    ASSERT_COVERED(EEqV2OpNot);
    return !EEqV2(Left, Right);
}

COVERAGE(EEqV3OpNot, 1)
inline static EBool operator!=(Vector3 Left, Vector3 Right)
{
    ASSERT_COVERED(EEqV3OpNot);
    return !EEqV3(Left, Right);
}

COVERAGE(EEqV4OpNot, 1)
inline static EBool operator!=(Vector4 Left, Vector4 Right)
{
    ASSERT_COVERED(EEqV4OpNot);
    return !EEqV4(Left, Right);
}

COVERAGE(EEqM3OpNot, 1)
inline static EBool operator!=(Matrix3 Left, Matrix3 Right)
{
    ASSERT_COVERED(EEqM3OpNot);
    return !EEqM3(Left, Right);
}

COVERAGE(EEqM4OpNot, 1)
inline static EBool operator!=(Matrix4 Left, Matrix4 Right)
{
    ASSERT_COVERED(EEqM4OpNot);
    return !EEqM4(Left, Right);
}

COVERAGE(EUnaryMinusV2, 1)
inline static Vector2 operator-(Vector2 In)
{
    ASSERT_COVERED(EUnaryMinusV2);

    Vector2 Result;
    Result.X = -In.X;
    Result.Y = -In.Y;

    return Result;
}

COVERAGE(EUnaryMinusV3, 1)
inline static Vector3 operator-(Vector3 In)
{
    ASSERT_COVERED(EUnaryMinusV3);

    Vector3 Result;
    Result.X = -In.X;
    Result.Y = -In.Y;
    Result.Z = -In.Z;

    return Result;
}

COVERAGE(EUnaryMinusV4, 1)
inline static Vector4 operator-(Vector4 In)
{
    ASSERT_COVERED(EUnaryMinusV4);

    Vector4 Result;
#if HANDMADE_MATH__USE_SSE
    Result.SSE = _mm_xor_ps(In.SSE, _mm_set1_ps(-0.0f));
#elif defined(HANDMADE_MATH__USE_NEON)
    float32x4_t Zero = vdupq_n_f32(0.0f);
    Result.NEON      = vsubq_f32(Zero, In.NEON);
#else
    Result.X = -In.X;
    Result.Y = -In.Y;
    Result.Z = -In.Z;
    Result.W = -In.W;
#endif

    return Result;
}

#endif /* __cplusplus*/

#ifdef HANDMADE_MATH__USE_C11_GENERICS
#define EAdd(A, B)                                                                                                                     \
    _Generic(                                                                                                                          \
        (A), Vector2: EAddV2, Vector3: EAddV3, Vector4: EAddV4, Matrix2: EAddM2, Matrix3: EAddM3, Matrix4: EAddM4, Quaternion: EAddQ)( \
        A, B)

#define ESub(A, B)                                                                                                                     \
    _Generic(                                                                                                                          \
        (A), Vector2: ESubV2, Vector3: ESubV3, Vector4: ESubV4, Matrix2: ESubM2, Matrix3: ESubM3, Matrix4: ESubM4, Quaternion: ESubQ)( \
        A, B)

#define EMul(A, B)               \
    _Generic(                    \
        (B),                     \
        float: _Generic(         \
            (A),                 \
            Vector2: EMulV2F,    \
            Vector3: EMulV3F,    \
            Vector4: EMulV4F,    \
            Matrix2: EMulM2F,    \
            Matrix3: EMulM3F,    \
            Matrix4: EMulM4F,    \
            Quaternion: EMulQF), \
        Matrix2: EMulM2,         \
        Matrix3: EMulM3,         \
        Matrix4: EMulM4,         \
        Quaternion: EMulQ,       \
        default: _Generic(       \
            (A), Vector2: EMulV2, Vector3: EMulV3, Vector4: EMulV4, Matrix2: EMulM2V2, Matrix3: EMulM3V3, Matrix4: EMulM4V4))(A, B)

#define EDiv(A, B)               \
    _Generic(                    \
        (B),                     \
        float: _Generic(         \
            (A),                 \
            Matrix2: EDivM2F,    \
            Matrix3: EDivM3F,    \
            Matrix4: EDivM4F,    \
            Vector2: EDivV2F,    \
            Vector3: EDivV3F,    \
            Vector4: EDivV4F,    \
            Quaternion: EDivQF), \
        Matrix2: EDivM2,         \
        Matrix3: EDivM3,         \
        Matrix4: EDivM4,         \
        Quaternion: EDivQ,       \
        default: _Generic((A), Vector2: EDivV2, Vector3: EDivV3, Vector4: EDivV4))(A, B)

#define ELen(A) _Generic((A), Vector2: ELenV2, Vector3: ELenV3, Vector4: ELenV4)(A)

#define ELenSqr(A) _Generic((A), Vector2: ELenSqrV2, Vector3: ELenSqrV3, Vector4: ELenSqrV4)(A)

#define ENorm(A) _Generic((A), Vector2: ENormV2, Vector3: ENormV3, Vector4: ENormV4)(A)

#define EDot(A, B) _Generic((A), Vector2: EDotV2, Vector3: EDotV3, Vector4: EDotV4)(A, B)

#define ELerp(A, T, B) _Generic((A), float: ELerp, Vector2: ELerpV2, Vector3: ELerpV3, Vector4: ELerpV4)(A, T, B)

#define EEq(A, B) _Generic((A), Vector2: EEqV2, Vector3: EEqV3, Vector4: EEqV4)(A, B)

#define ETranspose(M) _Generic((M), Matrix2: ETransposeM2, Matrix3: ETransposeM3, Matrix4: ETransposeM4)(M)

#define EDeterminant(M) _Generic((M), Matrix2: EDeterminantM2, Matrix3: EDeterminantM3, Matrix4: EDeterminantM4)(M)

#define EInvGeneral(M) _Generic((M), Matrix2: EInvGeneralM2, Matrix3: EInvGeneralM3, Matrix4: EInvGeneralM4)(M)

#endif

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif

#endif /* HANDMADE_MATH_H */

// clang-format on
