#pragma once

#include "types.h"
#include "reflectable_enum.h"

#define CODES2(X) X, X##_K
#define CODES4(X) X, X##_KR, X##_RK, X##_KK

reflectable_enum(opcode, byte,
	PRINT,

	VALUE,
	CREATE_OBJECT,
	SET_FIELD,
	VIRTUAL_CALL,
	JUMP,
	IFJUMP,
	INC,

	END,

	//---------

	ADD,
	SUB,
	MULT,
	DIVIDE,
	POWER,
	EQ,
	NEQ,
	L,
	G,
	LEQ,
	GEQ,

	LOADVAR,
	SAVEVAR,
	PUSH_K
);
