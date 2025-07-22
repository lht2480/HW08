// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PracticeProject : ModuleRules
{
	public PracticeProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { //이 프로젝트에서 필수적으로 사용하는 기능/엔진들
			"Core",				//코어엔진의 기능
			"CoreUObject",		//리플렉션 시스템, 가비지 컬렉션
			"Engine",			//게임엔진의 주요기능
			"InputCore",		//입력시스템
			"EnhancedInput",	//EnhancedInputSystem과 관련
			"UMG"				//위젯 블루프린트와 관련
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		
	}
}
