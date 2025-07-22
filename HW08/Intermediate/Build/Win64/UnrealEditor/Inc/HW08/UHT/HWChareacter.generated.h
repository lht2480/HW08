// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "HWChareacter.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FInputActionValue;
#ifdef HW08_HWChareacter_generated_h
#error "HWChareacter.generated.h already included, missing '#pragma once' in HWChareacter.h"
#endif
#define HW08_HWChareacter_generated_h

#define FID_GitClone_HW08_HW08_Source_HW08_Public_HWChareacter_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execStopSprint); \
	DECLARE_FUNCTION(execStartSprint); \
	DECLARE_FUNCTION(execLook); \
	DECLARE_FUNCTION(execStopJump); \
	DECLARE_FUNCTION(execStartJump); \
	DECLARE_FUNCTION(execMove); \
	DECLARE_FUNCTION(execAddHealth); \
	DECLARE_FUNCTION(execGetHealth);


#define FID_GitClone_HW08_HW08_Source_HW08_Public_HWChareacter_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAHWChareacter(); \
	friend struct Z_Construct_UClass_AHWChareacter_Statics; \
public: \
	DECLARE_CLASS(AHWChareacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/HW08"), NO_API) \
	DECLARE_SERIALIZER(AHWChareacter)


#define FID_GitClone_HW08_HW08_Source_HW08_Public_HWChareacter_h_16_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	AHWChareacter(AHWChareacter&&); \
	AHWChareacter(const AHWChareacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AHWChareacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AHWChareacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AHWChareacter) \
	NO_API virtual ~AHWChareacter();


#define FID_GitClone_HW08_HW08_Source_HW08_Public_HWChareacter_h_13_PROLOG
#define FID_GitClone_HW08_HW08_Source_HW08_Public_HWChareacter_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_GitClone_HW08_HW08_Source_HW08_Public_HWChareacter_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_GitClone_HW08_HW08_Source_HW08_Public_HWChareacter_h_16_INCLASS_NO_PURE_DECLS \
	FID_GitClone_HW08_HW08_Source_HW08_Public_HWChareacter_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> HW08_API UClass* StaticClass<class AHWChareacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_GitClone_HW08_HW08_Source_HW08_Public_HWChareacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
