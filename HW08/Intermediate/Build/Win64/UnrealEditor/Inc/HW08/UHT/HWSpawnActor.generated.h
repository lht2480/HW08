// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "HWSpawnActor.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
#ifdef HW08_HWSpawnActor_generated_h
#error "HWSpawnActor.generated.h already included, missing '#pragma once' in HWSpawnActor.h"
#endif
#define HW08_HWSpawnActor_generated_h

#define FID_GitClone_HW08_HW08_Source_HW08_Public_HWSpawnActor_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execSpawnRandomItem);


#define FID_GitClone_HW08_HW08_Source_HW08_Public_HWSpawnActor_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAHWSpawnActor(); \
	friend struct Z_Construct_UClass_AHWSpawnActor_Statics; \
public: \
	DECLARE_CLASS(AHWSpawnActor, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/HW08"), NO_API) \
	DECLARE_SERIALIZER(AHWSpawnActor)


#define FID_GitClone_HW08_HW08_Source_HW08_Public_HWSpawnActor_h_13_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	AHWSpawnActor(AHWSpawnActor&&); \
	AHWSpawnActor(const AHWSpawnActor&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AHWSpawnActor); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AHWSpawnActor); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AHWSpawnActor) \
	NO_API virtual ~AHWSpawnActor();


#define FID_GitClone_HW08_HW08_Source_HW08_Public_HWSpawnActor_h_10_PROLOG
#define FID_GitClone_HW08_HW08_Source_HW08_Public_HWSpawnActor_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_GitClone_HW08_HW08_Source_HW08_Public_HWSpawnActor_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_GitClone_HW08_HW08_Source_HW08_Public_HWSpawnActor_h_13_INCLASS_NO_PURE_DECLS \
	FID_GitClone_HW08_HW08_Source_HW08_Public_HWSpawnActor_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> HW08_API UClass* StaticClass<class AHWSpawnActor>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_GitClone_HW08_HW08_Source_HW08_Public_HWSpawnActor_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
