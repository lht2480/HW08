// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "HWGameInstance.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef HW08_HWGameInstance_generated_h
#error "HWGameInstance.generated.h already included, missing '#pragma once' in HWGameInstance.h"
#endif
#define HW08_HWGameInstance_generated_h

#define FID_GitClone_HW08_HW08_Source_HW08_Public_HWGameInstance_h_11_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execAddToScore);


#define FID_GitClone_HW08_HW08_Source_HW08_Public_HWGameInstance_h_11_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUHWGameInstance(); \
	friend struct Z_Construct_UClass_UHWGameInstance_Statics; \
public: \
	DECLARE_CLASS(UHWGameInstance, UGameInstance, COMPILED_IN_FLAGS(0 | CLASS_Transient), CASTCLASS_None, TEXT("/Script/HW08"), NO_API) \
	DECLARE_SERIALIZER(UHWGameInstance)


#define FID_GitClone_HW08_HW08_Source_HW08_Public_HWGameInstance_h_11_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UHWGameInstance(UHWGameInstance&&); \
	UHWGameInstance(const UHWGameInstance&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UHWGameInstance); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UHWGameInstance); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UHWGameInstance) \
	NO_API virtual ~UHWGameInstance();


#define FID_GitClone_HW08_HW08_Source_HW08_Public_HWGameInstance_h_8_PROLOG
#define FID_GitClone_HW08_HW08_Source_HW08_Public_HWGameInstance_h_11_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_GitClone_HW08_HW08_Source_HW08_Public_HWGameInstance_h_11_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_GitClone_HW08_HW08_Source_HW08_Public_HWGameInstance_h_11_INCLASS_NO_PURE_DECLS \
	FID_GitClone_HW08_HW08_Source_HW08_Public_HWGameInstance_h_11_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> HW08_API UClass* StaticClass<class UHWGameInstance>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_GitClone_HW08_HW08_Source_HW08_Public_HWGameInstance_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
