#pragma once

#include "kmbox/Math.hpp"
#include <cstdint>

struct BoneJointData
{
	Vector Pos;
	float Scale;
	char pad[0x10];
};




enum class e_weapon_type : int
{
	knife,
	pistol,
	submachine_gun,
	rifle,
	shotgun,
	sniper_rifle,
	machine_gun,
	c4,
	taser,
	grenade,
	equipment = 10
};

struct WeaponData
{
	int idx;
	uint64_t entity_list;
	int handle;
	uint64_t weapon_data;
	uint64_t weapon_name_ptr;
	char weapon_name[32];
	std::string weapon_name_Radar;
	int weapon_id;
	int weapon_id_Radar;
	uint64_t my_weapons;
};

class Player
{
public:
	uint64_t Controller_ptr;
	uint32_t Pawn;
	uint64_t EntityPawnListEntry;
	uint64_t Pawn_ptr;

	Vector r_start;
	Vector r_end;

	bool Radar_Draw;
	int TeamID;
	int TeamID_Radar;
	bool IsAlive;
	bool IsAlive_Radar;
	char PlayerName[64];
	char PlayerName_tmp[64];

	// new steamid
	uint64_t steamID_tmp;

	uint64_t steamID_Radar;

	int Health;
	int Health_tmp;
	uint64_t fFlags;
	Vector Pos;
	Vector Pos_Radar;
	Vector Pos_2D;
	bool isDraw;
	uint64_t GameSceneNode;
	uint64_t BoneArray_ptr;
	BoneJointData BoneArray[30];
	Vector Bone_2D[30];
	float dist;
	QAngle ViewAngle;
	QAngle ViewAngle_Radar;
	uint64_t bSpottedByMask;
	bool isVisible;

	int iShotsFired_tmp;

	//int iShotsFired;

	//DWORD aimPunchCache_tmp;
	QAngle aimPunchCache;

	uint64_t WeaponServices;
	int handle;
	uint64_t entry_list;
	uint64_t active_weapon;
	uint64_t weapon_data;
	uint64_t weapon_name_ptr;
	char weapon_name[32];
	std::string weapon_name_Radar;


	int Weapon_num;
	int Weapon_num_Radar;
	uint64_t AllWeapon_ptr;
	WeaponData AllWeapon[20];

	int armor;
	int armor_tmp;

	uint64_t in_game_money_services;
	int money;
	int money_Radar;

	uint64_t item_services;
	bool helmet;
	bool helmet_Radar;
	bool defuser;
	bool defuser_Radar;

	uint64_t model_name_ptr;
	char model_name[64];
	std::string model_path;


	uint64_t iIDEntIndex;


};


class Map
{
public:

	uint64_t global_vars;
	uint64_t map_name_ptr;
	char map_name_tmp[32];
	std::string map_name;

	bool EnableWebRadar;
};
