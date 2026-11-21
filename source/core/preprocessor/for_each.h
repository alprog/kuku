#pragma once

#include "common.h"

#define FOR_00(Macro, x, ...)
#define FOR_01(Macro, x, ...) Macro(x)
#define FOR_02(Macro, x, ...) Macro(x) EXPAND(FOR_01(Macro, __VA_ARGS__))
#define FOR_03(Macro, x, ...) Macro(x) EXPAND(FOR_02(Macro, __VA_ARGS__))
#define FOR_04(Macro, x, ...) Macro(x) EXPAND(FOR_03(Macro, __VA_ARGS__))
#define FOR_05(Macro, x, ...) Macro(x) EXPAND(FOR_04(Macro, __VA_ARGS__))
#define FOR_06(Macro, x, ...) Macro(x) EXPAND(FOR_05(Macro, __VA_ARGS__))
#define FOR_07(Macro, x, ...) Macro(x) EXPAND(FOR_06(Macro, __VA_ARGS__))
#define FOR_08(Macro, x, ...) Macro(x) EXPAND(FOR_07(Macro, __VA_ARGS__))
#define FOR_09(Macro, x, ...) Macro(x) EXPAND(FOR_08(Macro, __VA_ARGS__))
#define FOR_10(Macro, x, ...) Macro(x) EXPAND(FOR_09(Macro, __VA_ARGS__))
#define FOR_11(Macro, x, ...) Macro(x) EXPAND(FOR_10(Macro, __VA_ARGS__))
#define FOR_12(Macro, x, ...) Macro(x) EXPAND(FOR_11(Macro, __VA_ARGS__))
#define FOR_13(Macro, x, ...) Macro(x) EXPAND(FOR_12(Macro, __VA_ARGS__))
#define FOR_14(Macro, x, ...) Macro(x) EXPAND(FOR_13(Macro, __VA_ARGS__))
#define FOR_15(Macro, x, ...) Macro(x) EXPAND(FOR_14(Macro, __VA_ARGS__))
#define FOR_16(Macro, x, ...) Macro(x) EXPAND(FOR_15(Macro, __VA_ARGS__))

#define FOR_(N, Macro, ...) __VA_OPT__(EXPAND(CONCATENATE(FOR_, N)(Macro, __VA_ARGS__)))
#define FOR_EACH(Macro, ...) FOR_(VA_LENGTH(__VA_ARGS__), Macro, __VA_ARGS__)

//------------------------------------------------------------------------------

#define FOR_WITH_COMMA_00(Macro, x, ...)
#define FOR_WITH_COMMA_01(Macro, x, ...) Macro(x)
#define FOR_WITH_COMMA_02(Macro, x, ...) Macro(x), EXPAND(FOR_WITH_COMMA_01(Macro, __VA_ARGS__))
#define FOR_WITH_COMMA_03(Macro, x, ...) Macro(x), EXPAND(FOR_WITH_COMMA_02(Macro, __VA_ARGS__))
#define FOR_WITH_COMMA_04(Macro, x, ...) Macro(x), EXPAND(FOR_WITH_COMMA_03(Macro, __VA_ARGS__))
#define FOR_WITH_COMMA_05(Macro, x, ...) Macro(x), EXPAND(FOR_WITH_COMMA_04(Macro, __VA_ARGS__))
#define FOR_WITH_COMMA_06(Macro, x, ...) Macro(x), EXPAND(FOR_WITH_COMMA_05(Macro, __VA_ARGS__))
#define FOR_WITH_COMMA_07(Macro, x, ...) Macro(x), EXPAND(FOR_WITH_COMMA_06(Macro, __VA_ARGS__))
#define FOR_WITH_COMMA_08(Macro, x, ...) Macro(x), EXPAND(FOR_WITH_COMMA_07(Macro, __VA_ARGS__))
#define FOR_WITH_COMMA_09(Macro, x, ...) Macro(x), EXPAND(FOR_WITH_COMMA_08(Macro, __VA_ARGS__))
#define FOR_WITH_COMMA_10(Macro, x, ...) Macro(x), EXPAND(FOR_WITH_COMMA_09(Macro, __VA_ARGS__))
#define FOR_WITH_COMMA_11(Macro, x, ...) Macro(x), EXPAND(FOR_WITH_COMMA_10(Macro, __VA_ARGS__))
#define FOR_WITH_COMMA_12(Macro, x, ...) Macro(x), EXPAND(FOR_WITH_COMMA_11(Macro, __VA_ARGS__))
#define FOR_WITH_COMMA_13(Macro, x, ...) Macro(x), EXPAND(FOR_WITH_COMMA_12(Macro, __VA_ARGS__))
#define FOR_WITH_COMMA_14(Macro, x, ...) Macro(x), EXPAND(FOR_WITH_COMMA_13(Macro, __VA_ARGS__))
#define FOR_WITH_COMMA_15(Macro, x, ...) Macro(x), EXPAND(FOR_WITH_COMMA_14(Macro, __VA_ARGS__))
#define FOR_WITH_COMMA_16(Macro, x, ...) Macro(x), EXPAND(FOR_WITH_COMMA_15(Macro, __VA_ARGS__))

#define FOR_WITH_COMMA_(N, Macro, ...) __VA_OPT__(EXPAND(CONCATENATE(FOR_WITH_COMMA_, N)(Macro, __VA_ARGS__)))
#define FOR_EACH_WITH_COMMA(Macro, ...) FOR_WITH_COMMA_(VA_LENGTH(__VA_ARGS__), Macro, __VA_ARGS__)

//------------------------------------------------------------------------------

#define FOR_WITH_SEPARATOR_00(Macro, Separator, x, ...)
#define FOR_WITH_SEPARATOR_01(Macro, Separator, x, ...) Macro(x)
#define FOR_WITH_SEPARATOR_02(Macro, Separator, x, ...) Macro(x) Separator EXPAND(FOR_WITH_SEPARATOR_01(Macro, Separator, __VA_ARGS__))
#define FOR_WITH_SEPARATOR_03(Macro, Separator, x, ...) Macro(x) Separator EXPAND(FOR_WITH_SEPARATOR_02(Macro, Separator, __VA_ARGS__))
#define FOR_WITH_SEPARATOR_04(Macro, Separator, x, ...) Macro(x) Separator EXPAND(FOR_WITH_SEPARATOR_03(Macro, Separator, __VA_ARGS__))
#define FOR_WITH_SEPARATOR_05(Macro, Separator, x, ...) Macro(x) Separator EXPAND(FOR_WITH_SEPARATOR_04(Macro, Separator, __VA_ARGS__))
#define FOR_WITH_SEPARATOR_06(Macro, Separator, x, ...) Macro(x) Separator EXPAND(FOR_WITH_SEPARATOR_05(Macro, Separator, __VA_ARGS__))
#define FOR_WITH_SEPARATOR_07(Macro, Separator, x, ...) Macro(x) Separator EXPAND(FOR_WITH_SEPARATOR_06(Macro, Separator, __VA_ARGS__))
#define FOR_WITH_SEPARATOR_08(Macro, Separator, x, ...) Macro(x) Separator EXPAND(FOR_WITH_SEPARATOR_07(Macro, Separator, __VA_ARGS__))
#define FOR_WITH_SEPARATOR_09(Macro, Separator, x, ...) Macro(x) Separator EXPAND(FOR_WITH_SEPARATOR_08(Macro, Separator, __VA_ARGS__))
#define FOR_WITH_SEPARATOR_10(Macro, Separator, x, ...) Macro(x) Separator EXPAND(FOR_WITH_SEPARATOR_09(Macro, Separator, __VA_ARGS__))
#define FOR_WITH_SEPARATOR_11(Macro, Separator, x, ...) Macro(x) Separator EXPAND(FOR_WITH_SEPARATOR_10(Macro, Separator, __VA_ARGS__))
#define FOR_WITH_SEPARATOR_12(Macro, Separator, x, ...) Macro(x) Separator EXPAND(FOR_WITH_SEPARATOR_11(Macro, Separator, __VA_ARGS__))
#define FOR_WITH_SEPARATOR_13(Macro, Separator, x, ...) Macro(x) Separator EXPAND(FOR_WITH_SEPARATOR_12(Macro, Separator, __VA_ARGS__))
#define FOR_WITH_SEPARATOR_14(Macro, Separator, x, ...) Macro(x) Separator EXPAND(FOR_WITH_SEPARATOR_13(Macro, Separator, __VA_ARGS__))
#define FOR_WITH_SEPARATOR_15(Macro, Separator, x, ...) Macro(x) Separator EXPAND(FOR_WITH_SEPARATOR_14(Macro, Separator, __VA_ARGS__))
#define FOR_WITH_SEPARATOR_16(Macro, Separator, x, ...) Macro(x) Separator EXPAND(FOR_WITH_SEPARATOR_15(Macro, Separator, __VA_ARGS__))

#define FOR_WITH_SEPARATOR_(N, Macro, Separator, ...) __VA_OPT__(EXPAND(CONCATENATE(FOR_WITH_SEPARATOR_, N)(Macro, Separator, __VA_ARGS__)))
#define FOR_EACH_WITH_SEPARATOR(Macro, Separator, ...) FOR_WITH_SEPARATOR_(VA_LENGTH(__VA_ARGS__), Macro, Separator, __VA_ARGS__)

