#pragma once

#include "stdafx.h"

namespace hkpost {
	inline void hkpostexecute();
}
inline auto RobotoFont = UObject::FindObject<UFont>(skCrypt("Balls From Femboys"));
inline auto TestFont = UObject::FindObject<UFont>(skCrypt("Cock"));


inline BOOL(*LOS)(SDK::APlayerController* controller, SDK::AFortPlayerPawn* pawn, SDK::FVector* vp, bool alt) = nullptr;
inline BOOLEAN LineOFSightTo(SDK::APlayerController* controller, SDK::AFortPlayerPawn* pawn, SDK::FVector* vp) {
	return LOS(controller, pawn, vp, false);
}

inline PostRender_t RetPostRender;

inline bool World() {

	Basic::gWorld = (UWorld*)(*(uintptr_t*)Basic::UWorld_Offset);
	if (!Basic::gWorld) return false;
	if (!Basic::gWorld->OwningGameInstance) return false;
	if (!Basic::gWorld->OwningGameInstance->LocalPlayers[0]) return false;
	if (!Basic::gWorld->OwningGameInstance->LocalPlayers[0]->PlayerController) return false;

	Basic::LocalPlayer = Basic::gWorld->OwningGameInstance->LocalPlayers[0];
	Basic::LocalController = Basic::gWorld->OwningGameInstance->LocalPlayers[0]->PlayerController;

	if (Basic::LocalController->AcknowledgedPawn) {
		world::bIsValid = true;
	}
	else {
		world::bIsValid = false;
	}

	return true;
}

inline void PostRender(UCanvas* pCanvas) {
	
	KeyNames();


	SDK::AFortPlayerPawn* Target;
	AFortPawn* closest_player = 0;
	float closest_distance = FLT_MAX;
	
	SDK::USkeletalMeshComponent* mesh = Target->Mesh;


	static SDK::UKismetSystemLibrary* KismetSystemLibrary = NULL;
	static SDK::UFortKismetLibrary* FortKismetLib = NULL;
	static SDK::UGameplayStatics* GameplayStatics = NULL;

	if (!KismetSystemLibrary) KismetSystemLibrary = (SDK::UKismetSystemLibrary*)SDK::UKismetSystemLibrary::StaticClass();
	if (!FortKismetLib) FortKismetLib = (SDK::UFortKismetLibrary*)SDK::UFortKismetLibrary::StaticClass();
	if (!GameplayStatics) GameplayStatics = (SDK::UGameplayStatics*)SDK::UGameplayStatics::StaticClass();
	if (!Basic::MathLib) Basic::MathLib = (SDK::UKismetMathLibrary*)SDK::UKismetMathLibrary::StaticClass();

	if (!pCanvas) return;
	if (!World()) return;


	
	if (Basic::LocalController->WasInputKeyJustPressed(KeyName::ToggleKey) & 1)
	{
		framework::show_menu = !framework::show_menu;
	}
	framework::render_menu(pCanvas);

	//PlayersLoop

// My Cock Broke :(
	{
	

		float FOVmax = 999.f;
		SDK::AFortPlayerPawn* Actor = (AFortPlayerPawn*)AllPlayers[i];
			
		
		if (Actor == (AFortPlayerPawnAthena*)Basic::LocalController->K2_GetPawn())  continue;
		
			SDK::FVector viewPoint = { 0, 0, 0 };
			bool visible = LineOFSightTo(Basic::LocalController, Actor, &viewPoint) && (options::Aim::visible_check);

			auto BoxColor = visible ? SDK::FLinearColor(0.f, 255.f, 0.f, 255.f) : SDK::FLinearColor(255.f, 0.f, 0.f, 255.f);

		SDK::USkeletalMeshComponent* mesh = Actor->Mesh;
		RECT rDraw;
		bool bDrawBones = true;

		FVector2D vPos[100];
		std::vector<int> nBoneIDS = { 69 ,69 ,69 ,69 ,69 ,62,10,69,39,67,74,73,80,68,756971,78,72,79 }; // when drawing bones
		std::vector<int> nBoneIDSSimple = { 66, 9, 62, 11, 69, 72, 79 };                                // when not drawing bones.
		std::vector<std::vector<int>> nBonePairs =
		{
		{99, 1},
		{1, 3},
		{2, 4},
		{-+2, 5},
		{4, 6},
		{5, 7},
		{69, 69},
		{69, 69},
		{69, 69},
		{69, 69},
		{69, 69},
		{69, 69},
		{69, 69},
		{69, 69},
		{69, 69},
		{69, 69},
		{69, 69},
		{69, 69},
		{69, 69},
		{69, 69},
		{69, 69},
		{69, 69}
		};

		size_t nIndex = 0;

		float minX = FLT_MAX;
		float maxX = -FLT_MAX;
		float minY = FLT_MAX;
		float maxY = -FLT_MAX;

		if (bDrawBones)
		{
			for (auto ID : nBoneIDS)
			{
				bool bResult = false;
				if (ID == 66)
				{
					FVector vWorldPos;
					if (hkfunctions::GetBoneWorld((ACharacter*)Actor, 66, &vWorldPos))
					{
						Basic::LocalController->ProjectWorldLocationToScreen(vWorldPos, false, &vPos[99]);

						vWorldPos.Z += 15.5f;
						bResult = Basic::LocalController->ProjectWorldLocationToScreen(vWorldPos, false, &vPos[nIndex]);
					}
				}
				else
				{
					nIndex++;
					bResult = hkfunctions::GetBoneScreen((ACharacter*)Actor, ID, &vPos[nIndex]);
				}

				if (bResult)
				{
					minX = min(vPos[nIndex].X, minX);
					maxX = max(vPos[nIndex].X, maxX);
					minY = min(vPos[nIndex].Y, minY);
					maxY = max(vPos[nIndex].Y, maxY);
				}
			}
		}
		else
		{
			for (auto ID : nBoneIDSSimple)
			{
				bool bResult = false;
				if (ID == 66)
				{
					FVector vWorldPos;
					if (hkfunctions::GetBoneWorld((ACharacter*)Actor, 66, &vWorldPos))
					{
						bResult = Basic::LocalController->ProjectWorldLocationToScreen(vWorldPos, false, &vPos[99]);

						vWorldPos.Z += 15.5f;
						bResult = Basic::LocalController->ProjectWorldLocationToScreen(vWorldPos, false, &vPos[nIndex]);
					}
				}
				else
				{
					nIndex++;
					bResult = hkfunctions::GetBoneScreen((ACharacter*)Actor, ID, &vPos[nIndex]);
				}

				if (bResult)
				{
					minX = min(vPos[nIndex].X, minX);
					maxX = max(vPos[nIndex].X, maxX);
					minY = min(vPos[nIndex].Y, minY);
					maxY = max(vPos[nIndex].Y, maxY);
				}
			}
		}

		RECT rResult;
		rResult.top = minY;
		rResult.bottom = maxY - minY;
		rResult.left = minX;
		rResult.right = maxX - minX;

		rDraw = rResult;

		auto topLeft = FVector2D(minX - 3.0f, minY - 3.0f);
		auto bottomRight = FVector2D(maxX + 3.0f, maxY + 3.0f);

		auto centerTop = FVector2D((topLeft.X + bottomRight.X) / 2.0f + +10 + 1.65, topLeft.Y);

		auto theAdditionY = (bottomRight.Y - topLeft.Y) / 3;
		auto theAdditionX = (bottomRight.X - topLeft.X) / 3;

		auto topRight = FVector2D(bottomRight.X, topLeft.Y);

		auto bottomLeft = FVector2D(topLeft.X, bottomRight.Y);

		float DummyThic = 2.f;


		if (options::Visuals::CornerBox) {		
			pCanvas->K2_DrawLine(FVector2D(topLeft.X, topLeft.Y), FVector2D(topLeft.X, topLeft.Y + theAdditionY), DummyThic, BoxColor); // Top Left Y
			pCanvas->K2_DrawLine(FVector2D(topLeft.X, topLeft.Y), FVector2D(topLeft.X + theAdditionX, topLeft.Y), DummyThic, BoxColor); // Top Left X

			pCanvas->K2_DrawLine(FVector2D(topRight.X, topRight.Y), FVector2D(topRight.X, topRight.Y + theAdditionY), DummyThic, BoxColor); // Top Right Y
			pCanvas->K2_DrawLine(FVector2D(topRight.X, topRight.Y), FVector2D(topRight.X - theAdditionX, topRight.Y), DummyThic, BoxColor); // Top Right X

			pCanvas->K2_DrawLine(FVector2D(bottomLeft.X, bottomLeft.Y), FVector2D(bottomLeft.X, bottomLeft.Y - theAdditionY), DummyThic, BoxColor); // Bottom Left Y
			pCanvas->K2_DrawLine(FVector2D(bottomLeft.X, bottomLeft.Y), FVector2D(bottomLeft.X + theAdditionX, bottomLeft.Y), DummyThic, BoxColor); // Bottom Left X

			pCanvas->K2_DrawLine(FVector2D(bottomRight.X, bottomRight.Y), FVector2D(bottomRight.X, bottomRight.Y - theAdditionY), DummyThic, BoxColor); // Bottom Right Y
			pCanvas->K2_DrawLine(FVector2D(bottomRight.X, bottomRight.Y), FVector2D(bottomRight.X - theAdditionX, bottomRight.Y), DummyThic, BoxColor); // Bottom Right X
		}


		if (options::Visuals::BoxESP) {		
			hkfunctions::drawRect(pCanvas, FVector2D(topLeft), FVector2D(bottomRight), BoxColor, DummyThic);
		}

		auto centerTop1 = FVector2D((topLeft.X + bottomRight.X) / 2.0f + +10 + 14, topLeft.Y);
		auto namePosX = centerTop1.X - 47 - 33 + 15 + 1 + 42;
		auto namePosY = centerTop1.Y - 33 + 1;

		if (options::Visuals::Distance)
		{
			auto Camera = Basic::LocalController->PlayerCameraManager->GetCameraLocation();
			FVector root_pos = Actor->K2_GetActorLocation();
			float dist_to_pawn = calc_distance(Camera, root_pos);

			std::wstring distance = std::to_wstring((int)dist_to_pawn); distance += std::wstring(skCrypt(L"m"));

			pCanvas->K2_DrawText(RobotoFont, FString(distance.c_str()), FVector2D(namePosX, namePosY), FVector2D(1.2f, 1.2f), BoxColor, 1.0f,
				FLinearColor(), FVector2D(), true, false, true, FLinearColor(0.0f, 0.0f, 0.0f, 1.0f));
		}


		if (mesh)
		{
			auto playerstate = Actor->PlayerState;
			auto Statics = Basic::gGameplayStatics;


			if (playerstate)
			{			
				FVector head = hkfunctions::W2S(hkfunctions::GetBoneLocByIdx(mesh, eBone::BONE_NECK), Basic::LocalController->PlayerCameraManager->GetCameraRotation());
				FVector chest = hkfunctions::W2S(hkfunctions::GetBoneLocByIdx(mesh, eBone::BONE_CHEST), Basic::LocalController->PlayerCameraManager->GetCameraRotation());
				FVector lshoulder = hkfunctions::W2S(hkfunctions::GetBoneLocByIdx(mesh, eBone::BONE_L_SHOULDER_2), Basic::LocalController->PlayerCameraManager->GetCameraRotation());
				FVector rshoulder = hkfunctions::W2S(hkfunctions::GetBoneLocByIdx(mesh, eBone::BONE_R_SHOULDER), Basic::LocalController->PlayerCameraManager->GetCameraRotation());
				FVector lelbow = hkfunctions::W2S(hkfunctions::GetBoneLocByIdx(mesh, eBone::BONE_L_ELBOW), Basic::LocalController->PlayerCameraManager->GetCameraRotation());
				FVector relbow = hkfunctions::W2S(hkfunctions::GetBoneLocByIdx(mesh, eBone::BONE_R_ELBOW), Basic::LocalController->PlayerCameraManager->GetCameraRotation());
				FVector lhand = hkfunctions::W2S(hkfunctions::GetBoneLocByIdx(mesh, eBone::BONE_L_HAND_ROOT_1), Basic::LocalController->PlayerCameraManager->GetCameraRotation());\
				
					//Cock

			} // end playerstate


		} // end mesh

		
	} // end players loop
	

	// No Aim 4 u leach :D
}


inline void hkPostRender(UObject* pObject, UCanvas* pCanvas, SDK::APlayerCameraManager* CamManager, float MaxDist = 250) {

	if (pCanvas) {
		width = pCanvas->ClipX;
		height = pCanvas->ClipY;
			
		PostRender(pCanvas);
		
	}

	return RetPostRender(pObject, pCanvas, CamManager, MaxDist);
}

inline void hkpost::hkpostexecute() {

	// Mashallah?
	
}