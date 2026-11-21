#pragma once

#define EMPTY

#define CONCATENATE(x,y) x##y
#define CONCATENATE3(x,y,z) x##y##z
#define EXPAND(x) x

#define VA_LENGTH_(_16, _15, _14, _13, _12, _11, _10, _09, _08, _07, _06, _05, _04, _03, _02, _01, N, ...) N
#define VA_LENGTH(...) EXPAND(VA_LENGTH_(__VA_ARGS__, 16, 15, 14, 13, 12, 11, 10, 09, 08, 07, 06, 05, 04, 03, 02, 01, 00))
#define VA_LENGTH_MINUS_1(...) EXPAND(VA_LENGTH_(__VA_ARGS__, 15, 14, 13, 12, 11, 10, 09, 08, 07, 06, 05, 04, 03, 02, 01, 00))
#define VA_LENGTH_MINUS_2(...) EXPAND(VA_LENGTH_(__VA_ARGS__, 14, 13, 12, 11, 10, 09, 08, 07, 06, 05, 04, 03, 02, 01, 00))


#define SEMICOLON ;