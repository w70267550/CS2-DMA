#pragma once
#include <iostream>
#include <DMALibrary/Memory/Memory.h>
#include <kmbox/Decryption.hpp>
#include "kmbox/KmboxNet.hpp"
#include "kmbox/KmboxB.h"
#include <thread>
#include "a2x/Offsets.h"
#include "Player.h"
#include "imgui/imgui.h"

uintptr_t Client_BASE = 0x0;

float calculateDistance(float targetX, float targetY, float screenWidth, float screenHeight) {
	float screenCenterX = screenWidth / 2;
	float screenCenterY = screenHeight / 2;

	float distanceX = targetX - screenCenterX;
	float distanceY = targetY - screenCenterY;

	float distance = std::sqrt(distanceX * distanceX + distanceY * distanceY);
	return distance;
}


struct Matrix
{
	float matrix[16];
};


bool WorldToScreen(Vector from, float* m_vMatrix, int targetWidth, int targetHeight, Vector& to)
{
	float w = m_vMatrix[12] * from.x + m_vMatrix[13] * from.y + m_vMatrix[14] * from.z + m_vMatrix[15];

	if (w < 0.01f)
	{
		to.x = 0;
		to.y = 0;
		to.z = 0;
		return false;
	}

	to.x = m_vMatrix[0] * from.x + m_vMatrix[1] * from.y + m_vMatrix[2] * from.z + m_vMatrix[3];
	to.y = m_vMatrix[4] * from.x + m_vMatrix[5] * from.y + m_vMatrix[6] * from.z + m_vMatrix[7];

	float invw = 1.0f / w;
	to.x *= invw;
	to.y *= invw;

	float x = targetWidth / 2;
	float y = targetHeight / 2;

	x += 0.5 * to.x * targetWidth + 0.5;
	y -= 0.5 * to.y * targetHeight + 0.5;

	to.x = x;
	to.y = y;
	to.z = 0;
	return true;
}


enum BONEINDEX : DWORD
{
	head = 6,
	neck_0 = 5,
	spine_1 = 4,
	spine_2 = 2,
	pelvis = 0,
	arm_upper_L = 8,
	arm_lower_L = 9,
	hand_L = 10,
	arm_upper_R = 13,
	arm_lower_R = 14,
	hand_R = 15,
	leg_upper_L = 22,
	leg_lower_L = 23,
	ankle_L = 24,
	leg_upper_R = 25,
	leg_lower_R = 26,
	ankle_R = 27,
};

struct c_utl_vector
{
	uint64_t count;
	uint64_t data;
};

class Settings {
public:
	float width = 1920;
	float height = 1080;

	std::string last_map_name = "";

	bool webradar = false;
	int KmBoxTypeSelected = 0;
	std::string KmboxType = "Net";
	char KmboxIP[24] = "192.168.2.188";
	char KmboxPort[10] = "69";
	char KmboxUUID[32] = "96";
	int KmboxComPort = 0;
	int BPro_Porter = 115200;
	bool connect = false;
	bool auto_connect = false;


	int aimbone = 6;


	bool RCS;
	int shotsFired;

	int aimbotstopshotsFired = 10;

	float m_pitch = 0.022;
	float m_yaw = 0.022;


	Vector2D aimPunch;

	c_utl_vector aimPunchCache;

	QAngle aimPunchCachetest;


	Vector2D oldAngle;
	uint64_t sensPointer;
	float sensitivity = 1;

	float aim_tick = 0.005;
	float shoot_delay = 0.005;

	int aim_button1 = 0;
	int aim_button2 = 0;

	int trigger_button1 = 0;

	int vischeckdelay = 10;

	//int radarupdatedelay = 100;

	float max_fov = 200;
	float Smoothing = 5;
	float speed_X = 5;
	float speed_Y = 5;

	bool keyboardstate;

	bool EnableVSync;

	bool VisibleCheck = true;

	bool BlackScreen = true;

	//bool autobhop;

	bool ShowMenu = true;

	bool showradar = true;

	bool fontoutline = false;

	bool AimbotAimToggle;
	bool showbox;
	bool showskeleton = true;
	bool showhealth = true;
	bool showname = true;
	bool showweaponname = true;
	bool showfov = true;
	bool teamcheck;
	bool aimbotteamcheck = true;
	//bool showhead = true;

	bool TriggerAimToggle;

	float bonevizcolor[4]{ 0, 255,0 ,255 };
	float boneinvizcolor[4]{ 255, 255,255 ,255 };
	float boxvizcolor[4]{ 0, 255,0 ,255 };
	float boxinvizcolor[4]{ 255, 255,255 ,255 };
	float textinfo_colorr[4]{ 255,255,255 ,255 };
	float fovcolor[4]{ 0, 255, 255,255 };

	float skeletonthickness = 1.0f;

	float healthbarthickness = 2.0f;

	float boxthickness = 1.0f;

	//float boxpadding = 7.f;

	float textoffset = 3.3f;

	//float healthboxoffset = 0.0f;


	void saveSettings(const std::string& fileName) const {
		std::ofstream file(fileName);
		if (file.is_open()) {
			file << "width=" << width << std::endl;
			file << "height=" << height << std::endl;
			//////////////////////////////////////////////////////////绘制
			file << "showbox=" << (showbox ? "true" : "false") << std::endl;
			file << "showskeleton=" << (showskeleton ? "true" : "false") << std::endl;
			file << "showhealth=" << (showhealth ? "true" : "false") << std::endl;
			file << "showname=" << (showname ? "true" : "false") << std::endl;
			file << "showweaponname=" << (showweaponname ? "true" : "false") << std::endl;
			file << "teamcheck=" << (teamcheck ? "true" : "false") << std::endl;
			file << "skeletonthickness=" << skeletonthickness << std::endl;
			file << "boxthickness=" << boxthickness << std::endl;
			file << "healthbarthickness=" << healthbarthickness << std::endl;
			//file << "boxpadding=" << boxpadding << std::endl;
			file << "textoffset=" << textoffset << std::endl;
			//file << "healthboxoffset=" << healthboxoffset << std::endl;
			////////////////////////////////////////////////////////// text offset color
			//file << "textinfo_colorr[0]=" << textinfo_colorr[0] << std::endl;
			//file << "textinfo_colorr[1]=" << textinfo_colorr[1] << std::endl;
			//file << "textinfo_colorr[2]=" << textinfo_colorr[2] << std::endl;
			//file << "textinfo_colorr[3]=" << textinfo_colorr[3] << std::endl;
			//////////////////////////////////////////////////////////方框颜色
			//file << "boxvizcolor[0]=" << boxvizcolor[0] << std::endl;
			//file << "boxvizcolor[1]=" << boxvizcolor[1] << std::endl;
			//file << "boxvizcolor[2]=" << boxvizcolor[2] << std::endl;
			//file << "boxvizcolor[3]=" << boxvizcolor[3] << std::endl;

			//file << "boxinvizcolor[0]=" << boxinvizcolor[0] << std::endl;
			//file << "boxinvizcolor[1]=" << boxinvizcolor[1] << std::endl;
			//file << "boxinvizcolor[2]=" << boxinvizcolor[2] << std::endl;
			//file << "boxinvizcolor[3]=" << boxinvizcolor[3] << std::endl;
			//////////////////////////////////////////////////////////骨骼颜色
			//file << "bonevizcolor[0]=" << bonevizcolor[0] << std::endl;
			//file << "bonevizcolor[1]=" << bonevizcolor[1] << std::endl;
			//file << "bonevizcolor[2]=" << bonevizcolor[2] << std::endl;
			//file << "bonevizcolor[3]=" << bonevizcolor[3] << std::endl;

			//file << "boneinvizcolor[0]=" << boneinvizcolor[0] << std::endl;
			//file << "boneinvizcolor[1]=" << boneinvizcolor[1] << std::endl;
			//file << "boneinvizcolor[2]=" << boneinvizcolor[2] << std::endl;
			//file << "boneinvizcolor[3]=" << boneinvizcolor[3] << std::endl;
			//////////////////////////////////////////////////////////FOV颜色
			//file << "fovcolor[0]=" << fovcolor[0] << std::endl;
			//file << "fovcolor[1]=" << fovcolor[1] << std::endl;
			//file << "fovcolor[2]=" << fovcolor[2] << std::endl;
			//file << "fovcolor[3]=" << fovcolor[3] << std::endl;
			//////////////////////////////////////////////////////////盒子
			file << "KmBoxTypeSelected=" << KmBoxTypeSelected << std::endl;
			file << "KmboxType=" << KmboxType << std::endl;
			file << "KmboxIP=" << KmboxIP << std::endl;
			file << "KmboxPort=" << KmboxPort << std::endl;
			file << "KmboxUUID=" << KmboxUUID << std::endl;
			file << "KmboxComPort=" << KmboxComPort << std::endl;
			file << "BPro_Porter=" << BPro_Porter << std::endl;
			file << "auto_connect=" << (auto_connect ? "true" : "false") << std::endl;
			//////////////////////////////////////////////////////////自瞄
			file << "AimbotAimToggle=" << (AimbotAimToggle ? "true" : "false") << std::endl;
			file << "aimbone=" << aimbone << std::endl;
			file << "aim_tick=" << aim_tick << std::endl;
			file << "aim_button1=" << aim_button1 << std::endl;
			file << "aim_button2=" << aim_button2 << std::endl;
			file << "max_fov=" << max_fov << std::endl;
			file << "Smoothing=" << Smoothing << std::endl;
			file << "speed_X=" << speed_X << std::endl;
			file << "speed_Y=" << speed_Y << std::endl;
			file << "aimbotteamcheck=" << (aimbotteamcheck ? "true" : "false") << std::endl;
			file << "showfov=" << (showfov ? "true" : "false") << std::endl;
			file << "aimbotstopshotsFired=" << aimbotstopshotsFired << std::endl;
			///////////////////////////////////////////////////////////////// triggerbot
			//file << "TriggerAimToggle=" << (TriggerAimToggle ? "true" : "false") << std::endl;
			//file << "trigger_button1=" << trigger_button1 << std::endl;
			///////////////////////////////////////////////////////////////
			file << "VisibleCheck=" << (VisibleCheck ? "true" : "false") << std::endl;
			file << "EnableVSync=" << (EnableVSync ? "true" : "false") << std::endl;
			//file << "radarupdatedelay=" << radarupdatedelay << std::endl;
			//file << "autobhop=" << (autobhop ? "true" : "false") << std::endl;
			file << "fontoutline=" << (fontoutline ? "true" : "false") << std::endl;
			file.close();
			std::cout << " [ > ] Config Saved..." << std::endl;
		}
		else {
			std::cout << " [ > ] Failed to Save Config..." << std::endl;
		}
	}

	void loadSettings(const std::string& fileName) {
		std::ifstream file(fileName);
		if (file.is_open()) {
			std::string line;
			while (std::getline(file, line)) {
				std::istringstream iss(line);
				std::string key;
				std::string value;
				if (std::getline(iss, key, '=') && std::getline(iss, value)) {
					//////////////////////////////////////////////////////////绘制
					if (key == "width") {
						width = std::stof(value);
					}
					else if (key == "height") {
						height = std::stof(value);
					}
					else if (key == "showbox") {
						showbox = (value == "true");
					}
					else if (key == "showskeleton") {
						showskeleton = (value == "true");
					}
					else if (key == "showhealth") {
						showhealth = (value == "true");
					}
					else if (key == "showname") {
						showname = (value == "true");
					}
					else if (key == "showweaponname") {
						showweaponname = (value == "true");
					}
					else if (key == "teamcheck") {
						teamcheck = (value == "true");
					}
					else if (key == "skeletonthickness") {
						skeletonthickness = std::stof(value);
					}
					else if (key == "boxthickness") {
						boxthickness = std::stof(value);
					}
					else if (key == "healthbarthickness") {
						healthbarthickness = std::stof(value);
					}
					//else if (key == "boxpadding") {
					//	boxpadding = std::stof(value);
					//}
					else if (key == "textoffset") {
						textoffset = std::stof(value);
					}
					//else if (key == "healthboxoffset") {
					//	healthboxoffset = std::stof(value);
					//}
					//////////////////////////////////////////////////////////方框颜色
					/*else if (key == "textinfo_colorr[0]") {
						textinfo_colorr[0] = std::stoi(value);
					}
					else if (key == "textinfo_colorr[1]") {
						textinfo_colorr[1] = std::stoi(value);
					}
					else if (key == "textinfo_colorr[2]") {
						textinfo_colorr[2] = std::stoi(value);
					}
					else if (key == "textinfo_colorr[3]") {
						textinfo_colorr[3] = std::stoi(value);
					}*/

					/*else if (key == "boxvizcolor[0]") {
						boxvizcolor[0] = std::stoi(value);
					}
					else if (key == "boxvizcolor[1]") {
						boxvizcolor[1] = std::stoi(value);
					}
					else if (key == "boxvizcolor[2]") {
						boxvizcolor[2] = std::stoi(value);
					}
					else if (key == "boxvizcolor[3]") {
						boxvizcolor[3] = std::stoi(value);
					}*/
					
					/*else if (key == "boxinvizcolor[0]") {
						boxinvizcolor[0] = std::stoi(value);
					}
					else if (key == "boxinvizcolor[1]") {
						boxinvizcolor[1] = std::stoi(value);
					}
					else if (key == "boxinvizcolor[2]") {
						boxinvizcolor[2] = std::stoi(value);
					}
					else if (key == "boxinvizcolor[3]") {
						boxinvizcolor[3] = std::stoi(value);
					}*/
					//////////////////////////////////////////////////////////骨骼颜色
					/*else if (key == "bonevizcolor[0]") {
						bonevizcolor[0] = std::stoi(value);
					}
					else if (key == "bonevizcolor[1]") {
						bonevizcolor[1] = std::stoi(value);
					}
					else if (key == "bonevizcolor[2]") {
						bonevizcolor[2] = std::stoi(value);
					}
					else if (key == "bonevizcolor[3]") {
						bonevizcolor[3] = std::stoi(value);
					}

					else if (key == "boneinvizcolor[0]") {
						boneinvizcolor[0] = std::stoi(value);
					}
					else if (key == "boneinvizcolor[1]") {
						boneinvizcolor[1] = std::stoi(value);
					}
					else if (key == "boneinvizcolor[2]") {
						boneinvizcolor[2] = std::stoi(value);
					}
					else if (key == "boneinvizcolor[3]") {
						boneinvizcolor[3] = std::stoi(value);
					}*/
					//////////////////////////////////////////////////////////FOV颜色
					/*else if (key == "fovcolor[0]") {
						fovcolor[0] = std::stoi(value);
					}
					else if (key == "fovcolor[1]") {
						fovcolor[1] = std::stoi(value);
					}
					else if (key == "fovcolor[2]") {
						fovcolor[2] = std::stoi(value);
					}
					else if (key == "fovcolor[3]") {
						fovcolor[3] = std::stoi(value);
					}*/
					//////////////////////////////////////////////////////////盒子
					else if (key == "KmBoxTypeSelected") {
						KmBoxTypeSelected = std::stoi(value);
					}
					else if (key == "KmboxType") {
						KmboxType = value;
					}
					else if (key == "KmboxIP") {
						std::strncpy(KmboxIP, value.c_str(), sizeof(KmboxIP));
						KmboxIP[sizeof(KmboxIP) - 1] = '\0';
					}
					else if (key == "KmboxPort") {
						std::strncpy(KmboxPort, value.c_str(), sizeof(KmboxPort));
						KmboxPort[sizeof(KmboxPort) - 1] = '\0';
					}
					else if (key == "KmboxUUID") {
						std::strncpy(KmboxUUID, value.c_str(), sizeof(KmboxUUID));
						KmboxUUID[sizeof(KmboxUUID) - 1] = '\0';
					}
					else if (key == "KmboxComPort") {
						KmboxComPort = std::stoi(value);
					}
					else if (key == "BPro_Porter") {
						BPro_Porter = std::stoi(value);
					}
					else if (key == "auto_connect") {
						auto_connect = (value == "true");
					}
					//////////////////////////////////////////////////////////自瞄
					else if (key == "AimbotAimToggle") {
						AimbotAimToggle = (value == "true");
					}
					else if (key == "aimbone") {
						aimbone = std::stof(value);
					}
					else if (key == "aim_tick") {
						aim_tick = std::stof(value);
					}
					else if (key == "aim_button1") {
						aim_button1 = std::stoi(value);
					}
					else if (key == "aim_button2") {
						aim_button2 = std::stoi(value);
					}
					else if (key == "max_fov") {
						max_fov = std::stof(value);
					}
					else if (key == "Smoothing") {
						Smoothing = std::stof(value);
					}
					else if (key == "speed_X") {
						speed_X = std::stof(value);
					}
					else if (key == "speed_Y") {
						speed_Y = std::stof(value);
					}
					else if (key == "aimbotteamcheck") {
						aimbotteamcheck = (value == "true");
						}
					else if (key == "showfov") {
							showfov = (value == "true");
					}
					else if (key == "aimbotstopshotsFired") {
						aimbotstopshotsFired = std::stoi(value);
					}
					//////////////////////////////trigger bot
					//else if (key == "TriggerAimToggle") {
					//	TriggerAimToggle = (value == "true");
					//}
					//else if (key == "trigger_button1") {
					//	trigger_button1 = std::stof(value);
					//}
					else if (key == "VisibleCheck") {
						VisibleCheck = (value == "true");
					}
					else if (key == "EnableVSync") {
						EnableVSync = (value == "true");
					}
					//else if (key == "autobhop") {
					//	autobhop = (value == "true");
					//	}
					//else if (key == "radarupdatedelay") {
					//	radarupdatedelay = std::stoi(value);
					//}
					else if (key == "fontoutline") {
						fontoutline = (value == "true");
					}
				}
			}
			file.close();
			//std::cout << " [ > ] Config Loaded... " << fileName << std::endl;
			std::cout << " [ > ] Config Loaded... " << std::endl;
		}
		else {
			std::cout << " [ ! ] Failed to Load Config..." << std::endl;
		}
	}

};
Settings set;


class Aimbot
{
public:

	float width = 1920;
	float height = 1080;

	int MinimumDelay = 1;
	bool connect = false;


	std::chrono::steady_clock::time_point Aim_old_time = std::chrono::steady_clock::now();

	std::string KmboxType = "Net";
	char KmboxIP[24] = "192.168.2.188";
	char KmboxPort[10] = "6969";
	char KmboxUUID[32] = "6969";
	int KmboxComPort = 0;
	int BPro_Porter = 115200;

	float aim_tick=0.005;
	float Smoothing=5;
	float speed_X=5;
	float speed_Y=5;

	_com comPort;

	bool Initialize() {
		if (KmboxType == "Net") {
			std::cout << " [ > ] Initialize KMBOX Net..." << std::endl;
			MinimumDelay = 1;

			int result = kmNet_init(KmboxIP, KmboxPort, KmboxUUID);

			if (result != 0) {
				std::cout << " [ > ] Kmbox Net Failed to connect..." << std::endl;
				return false;
			}
			else {
				std::cout << " [ > ] KMBOX Net Connected..." << std::endl;
				return true;
			}
		}
		else if (KmboxType == "BPro") {
			std::cout << " [ > ] Initialize KMBOX B+ PRO..." << std::endl;
			MinimumDelay = 3;

			if (comPort.open(KmboxComPort, BPro_Porter)) {
				std::cout << " [ > ] Kmbox B+ Pro Connected..." << std::endl;
				return true;
			}
			else {
				std::cout << " [ > ] Kmbox B+ Pro Failed to connect..." << std::endl;
				return false;
			}

		}

	}

	void keyClick(int key) {
		if (KmboxType == "Net") {
			kmNet_keydown(key);
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			kmNet_keyup(key);
		}
		else if (KmboxType == "BPro") {
			char cmd[1024] = { 0 };
			sprintf_s(cmd, "km.down(%d)\r\n", key);
			comPort.write(cmd);
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			cmd[1024] = { 0 };
			sprintf_s(cmd, "km.up(%d)\r\n", key);
			comPort.write(cmd);
		}
	}

	void LeftClick(int delay) {
		if (KmboxType == "Net") {
			kmNet_mouse_left(1);
			std::this_thread::sleep_for(std::chrono::milliseconds(delay));
			kmNet_mouse_left(0);
		}
		else if (KmboxType == "BPro") {
			char cmd[1024] = { 0 };
			sprintf_s(cmd, "km.click(0)\r\n");
			comPort.write(cmd);
		}
	}

	void Move(int x, int y) {
		if (KmboxType == "Net") {
			kmNet_mouse_move(x, y);
		}
		else if (KmboxType == "BPro") {
			char cmd[1024] = { 0 };
			sprintf_s(cmd, "km.move(%d, %d, 10)\r\n", x, y);
			comPort.write(cmd);
		}
	}

	void starAimbot(DWORD num_shots, Vector2D vec_punch, float sensitivity, Player Target)
	{
		Vector2D RelativePosition = { Target.Bone_2D[set.aimbone].x - width / 2, Target.Bone_2D[set.aimbone].y - height / 2};

		float Smoothing_tmp = Smoothing;
		float speed_X_tmp = speed_X;
		float speed_Y_tmp = speed_Y;


		Vector2D step = {
				(RelativePosition.x / Smoothing_tmp),
				(RelativePosition.y / Smoothing_tmp)
		};

		if (std::abs(step.x) > speed_X_tmp)
		{
			if (step.x > 0)
			{
				step.x = speed_X_tmp;
			}
			else
			{
				step.x = -speed_X_tmp;
			}
		}

		if (std::abs(step.y) > speed_Y_tmp)
		{
			if (step.y > 0)
			{
				step.y = speed_Y_tmp;
			}
			else
			{
				step.y = -speed_Y_tmp;
			}
		}
		if (std::abs(step.x) < 1.0f && std::abs(RelativePosition.x) > 1.0f)
		{
			if (step.x > 0)
			{
				step.x = 1.0f;
			}
			else
			{
				step.x = -1.0f;
			}
		}
		if (std::abs(step.y) < 1.0f && std::abs(RelativePosition.y) > 1.0f)
		{
			if (step.y > 0)
			{
				step.y = 1.0f;
			}
			else
			{
				step.y = -1.0f;
			}
		}

		std::chrono::steady_clock::time_point Aim_new_time = std::chrono::steady_clock::now();
		std::chrono::duration<double> Date_time = Aim_new_time - Aim_old_time;

		if (connect)
		{
			if (Date_time.count() < aim_tick)
			{
				return;
			}

			if (set.RCS)
			{
				if (num_shots > 1)
				{
					float x = (vec_punch.x - set.oldAngle.x) * -1.0f;
					float y = (vec_punch.y - set.oldAngle.y) * -1.0f;

					int mouse_angle_x = (int)(((y * 2.0f) / sensitivity) / -0.022f);
					int mouse_angle_y = (int)(((x * 2.0f) / sensitivity) / 0.022f);

					Move(mouse_angle_x + step.x, mouse_angle_y + step.y);

				}
				set.oldAngle = vec_punch;
			}
			else
			{
				Move(step.x, step.y);
			}
		}
		Aim_new_time = std::chrono::steady_clock::now();
		Aim_old_time = Aim_new_time;
	}

};