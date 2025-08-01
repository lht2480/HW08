// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PracticeProject : ModuleRules
{
	public PracticeProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { //�� ������Ʈ���� �ʼ������� ����ϴ� ���/������
			"Core",				//�ھ���� ���
			"CoreUObject",		//���÷��� �ý���, ������ �÷���
			"Engine",			//���ӿ����� �ֿ���
			"InputCore",		//�Է½ý���
			"EnhancedInput",	//EnhancedInputSystem�� ����
			"UMG"				//���� �������Ʈ�� ����
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		
	}
}
