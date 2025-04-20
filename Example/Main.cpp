#include "VisCheck/ray_trace.h"
#include <winsock2.h>
#include <windows.h>
#include <Game.h>
#include <thread>
#include "imgui/main.h"
#include <Menu.h>


void web_radar();

Player players[64];
Aimbot aimbot;
//Settings set;
int aim_index;
float fov;
Map G_map;
map_loader map;
float data_up_time;

std::chrono::steady_clock::time_point newTime = std::chrono::steady_clock::now();
//std::chrono::steady_clock::time_point newTime2 = std::chrono::steady_clock::now();
std::chrono::steady_clock::time_point oldTime1 = std::chrono::steady_clock::now();
//std::chrono::steady_clock::time_point oldTime2 = std::chrono::steady_clock::now();
//std::chrono::steady_clock::time_point oldTime3 = std::chrono::steady_clock::now();
//std::chrono::steady_clock::time_point oldTime2 = std::chrono::steady_clock::now();
//std::chrono::steady_clock::time_point oldTime0 = std::chrono::steady_clock::now();

int selectedIndex = 0;
const char* Boneitems[] = { "head", "neck", "chest", "stomach", "cock" };
const int Bonevalues[] = { 6, 5, 4, 2, 0 };

int LocalPlayerControllerIndex = 0;

Vector2D data{};

//Vector aim_punch_cache{};

/// slow mem read no scatter for testing
/*void UpData()
{
    while (Client_BASE)
    {
        // 获取当前时间点
        auto start = std::chrono::high_resolution_clock::now();

        // 获取当前时间
        newTime = std::chrono::steady_clock::now();

        // 检查时间间隔
        std::chrono::duration<double> elapsed_second0 = newTime - oldTime0;

        std::chrono::duration<double> elapsed_second1 = newTime - oldTime1;



        {
            //Matrix m = mem.Read<Matrix>(Client_BASE + Offset::Matrix);

            //Vector2D ViewAngle = mem.Read<Vector2D>(Client_BASE + Offset::ViewAngle);

            uint64_t LocalController_ptr = mem.Read<uint64_t>(Client_BASE + Offset::LocalPlayerController);
            uint64_t LocalPawn_ptr = mem.Read<uint64_t>(Client_BASE + Offset::LocalPlayerPawn);

            set.shotsFired = mem.Read<int32_t>(LocalPawn_ptr + Offset::Pawn.iShotsFired);

            //set.shotsFired = mem.Read<int32_t>(LocalPawn_ptr + Offset::Pawn.iShotsFired);
            //aim_punch_cache[0] = mem.Read<DWORD>(LocalPawn_ptr + Offset::Pawn.aimPunchCache);
            //aim_punch_cache[1] = mem.Read<DWORD>(LocalPawn_ptr + Offset::Pawn.aimPunchCache);
            //DWORD aimpunch_size = ((DWORD*)&aim_punch_cache[0])[0];

            std::cout << "shotsFired: " << set.shotsFired << std::endl;
            //std::cout << "aimPunch: " << set.aimPunch.x << "||" << set.aimPunch.y << std::endl;
            //std::cout << "sensitivity: " << set.sensitivity << std::endl;

            //for (int i = 0; i < 64; i++)
            //{
            //    players[i].Controller_ptr = mem.Read<uint64_t>(NewEntityListEntry + (i + 1) * 0x78);
            //    if (players[i].Controller_ptr == LocalController_ptr)
            //    {
            //        LocalPlayerControllerIndex = i;
            //    }
            //    if (!players[i].Controller_ptr)
            //    {
            //        players[i].isDraw = false;
            //        continue;
            //    }
            //    players[i].IsAlive = mem.Read<bool>(players[i].Controller_ptr + Offset::Entity.IsAlive);
            //    players[i].TeamID = mem.Read<int>(players[i].Controller_ptr + Offset::Pawn.iTeamNum);
            //    mem.Read(players[i].Controller_ptr + Offset::Entity.iszPlayerName, players[i].PlayerName, 32);

            //    players[i].Pawn = mem.Read<uint32_t>(players[i].Controller_ptr + Offset::Entity.PlayerPawn);
            //    players[i].EntityPawnListEntry = mem.Read<uint64_t>(EntityListEntry + 0x10 + 8 * ((players[i].Pawn & 0x7FFF) >> 9));
            //    players[i].Pawn_ptr = mem.Read<uint64_t>(players[i].EntityPawnListEntry + 0x78 * (players[i].Pawn & 0x1FF));

            //    players[i].Health = mem.Read<int>(players[i].Pawn_ptr + Offset::Pawn.CurrentHealth);
            //    players[i].Pos = mem.Read<Vector>(players[i].Pawn_ptr + Offset::Pawn.Pos);



            //    players[i].GameSceneNode = mem.Read<uint64_t>(players[i].Pawn_ptr + Offset::Pawn.GameSceneNode);
            //    players[i].BoneArray_ptr = mem.Read<uint64_t>(players[i].GameSceneNode + Offset::Pawn.BoneArray);
            //    mem.Read(players[i].BoneArray_ptr, players[i].BoneArray, 30 * sizeof(BoneJointData));

            //    if (!WorldToScreen(players[i].Pos, m.matrix, set.width, set.height, players[i].Pos_2D))
            //    {
            //        players[i].isDraw = false;
            //        continue;
            //    }
            //    for (int k = 0; k < 30; k++)
            //    {
            //        //std::cout<< k<<"] " << players[i].BoneArray[k].Pos.x << " " << players[i].BoneArray[k].Pos.y << " " << players[i].BoneArray[k].Pos.z << std::endl;
            //        if (WorldToScreen(players[i].BoneArray[k].Pos, m.matrix, set.width, set.height, players[i].Bone_2D[k]))
            //        {
            //            players[i].isDraw = false;
            //            continue;
            //        }
            //    }

            //    if (players[i].IsAlive && LocalPlayerControllerIndex != i && players[i].Health > 0)
            //    {
            //        players[i].isDraw = true;
            //    }
            //    else
            //    {
            //        players[i].isDraw = false;
            //    }
            //}
            //std::cout << LocalPlayerControllerIndex << std::endl;

        }

        if (elapsed_second1.count() >= 90)
        {
            // VMMDLL_ConfigSet(mem.vHandle, VMMDLL_OPT_REFRESH_FREQ_MEM_PARTIAL, 1);
            // VMMDLL_ConfigSet(mem.vHandle, VMMDLL_OPT_REFRESH_FREQ_TLB_PARTIAL, 1);
            //VMMDLL_ConfigSet(mem.vHandle, VMMDLL_OPT_REFRESH_FREQ_MEM, 1);
            //VMMDLL_ConfigSet(mem.vHandle, VMMDLL_OPT_REFRESH_FREQ_TLB, 1);
            oldTime1 = newTime;
        }

        // 再次获取当前时间点
        auto end = std::chrono::high_resolution_clock::now();

        // 计算时间差
        std::chrono::duration<double> elapsed = end - start;

        // 输出运行时间，单位为秒
       // std::cout << "data_up_time: " << elapsed.count() << " s" << std::endl;
    }
}*/




Matrix m;
QAngle ViewAngle;
uint64_t EntityListEntry;
uint64_t NewEntityListEntry;
uint64_t LocalController_ptr;
uint64_t LocalPawn_ptr;
//int planted_c4;

//uint32_t iShotsFired;


Vector* DeathPos=NULL;
void UpData2()
{
    while (1)
    {
        try
        {
            while (Client_BASE)
            {
                //auto start = std::chrono::high_resolution_clock::now();

                newTime = std::chrono::steady_clock::now();
                //newTime2 = std::chrono::steady_clock::now();
                //std::chrono::duration<double> elapsed_second0 = newTime - oldTime0;

                std::chrono::duration<double> elapsed_second1 = newTime - oldTime1;

                //std::chrono::duration<double> elapsed_second2 = newTime2 - oldTime2;


                Vector CameraPos;
                fov = 99999;
                {
                    auto handle = mem.CreateScatterHandle();

                    if (NewEntityListEntry)
                    {
                        for (int i = 0; i < 64; i++)
                        {
                            // Controller
                            if (players[i].Controller_ptr)
                            {
                                // Local Controller
                                if (players[i].Controller_ptr == LocalController_ptr)
                                {
                                    LocalPlayerControllerIndex = i;
                                }
                                // 
                                if (players[i].IsAlive)
                                {
                                    // 
                                    if (players[i].Pawn_ptr)
                                    {

                                        // BONE ARRAY
                                        if (players[i].BoneArray_ptr)
                                        {
                                            mem.AddScatterReadRequest(handle, players[i].BoneArray_ptr, &players[i].BoneArray, 30 * sizeof(BoneJointData));
                                        }
                                        // MODEL NAME
                                        if (players[i].model_name_ptr)
                                        {
                                            mem.AddScatterReadRequest(handle, players[i].model_name_ptr, &players[i].model_name, 64);
                                        }
                                        // BONE ARRAY GAME SCENE NODE
                                        if (players[i].GameSceneNode)
                                        {
                                            mem.AddScatterReadRequest(handle, players[i].GameSceneNode + Offset::Pawn.BoneArray, &players[i].BoneArray_ptr, sizeof(uint64_t));

                                            mem.AddScatterReadRequest(handle, players[i].GameSceneNode + 0x218, &players[i].model_name_ptr, sizeof(uint64_t));
                                        }
                                        // weapon stuff
                                        if (players[i].WeaponServices)
                                        {
                                            if (players[i].weapon_name_ptr)
                                            {
                                                mem.AddScatterReadRequest(handle, players[i].weapon_name_ptr, &players[i].weapon_name, 32);
                                            }
                                            if (players[i].weapon_data)
                                            {
                                                mem.AddScatterReadRequest(handle, players[i].weapon_data + Offset::WeaponBaseData.szName, &players[i].weapon_name_ptr, sizeof(uint64_t));
                                            }
                                            if (players[i].active_weapon)
                                            {
                                                mem.AddScatterReadRequest(handle, players[i].active_weapon + Offset::WeaponBaseData.WeaponDataPTR, &players[i].weapon_data, sizeof(uint64_t));
                                            }
                                            //entry_list
                                            if (players[i].entry_list)
                                            {
                                                mem.AddScatterReadRequest(handle, players[i].entry_list + 120 * ((players[i].handle & 0x7fff) & 0x1ff), &players[i].active_weapon, sizeof(uint64_t));
                                            }
                                            if (players[i].handle != -1)
                                            {
                                                mem.AddScatterReadRequest(handle, EntityListEntry + 8 * ((players[i].handle & 0x7fff) >> 9) + 16, &players[i].entry_list, sizeof(uint64_t));
                                            }
                                            if (players[i].Weapon_num < 20)
                                            {
                                                for (int k = 0; k < players[i].Weapon_num; k++)
                                                {
                                                    if (players[i].AllWeapon[k].weapon_name_ptr)
                                                    {
                                                        mem.AddScatterReadRequest(handle, players[i].AllWeapon[k].weapon_name_ptr, &players[i].AllWeapon[k].weapon_name, 32);
                                                    }
                                                    if (players[i].AllWeapon[k].weapon_data)
                                                    {
                                                        mem.AddScatterReadRequest(handle, players[i].AllWeapon[k].weapon_data + Offset::WeaponBaseData.WeaponType, &players[i].AllWeapon[k].weapon_id, sizeof(int));

                                                        mem.AddScatterReadRequest(handle, players[i].AllWeapon[k].weapon_data + Offset::WeaponBaseData.szName, &players[i].AllWeapon[k].weapon_name_ptr, sizeof(uint64_t));
                                                    }
                                                    if (players[i].AllWeapon[k].my_weapons)
                                                    {
                                                        mem.AddScatterReadRequest(handle, players[i].AllWeapon[k].my_weapons + Offset::WeaponBaseData.WeaponDataPTR, &players[i].AllWeapon[k].weapon_data, sizeof(uint64_t));
                                                    }
                                                    if (players[i].AllWeapon[k].entity_list)
                                                    {
                                                        mem.AddScatterReadRequest(handle, players[i].AllWeapon[k].entity_list + 120 * ((players[i].AllWeapon[k].handle & 0x7fff) & 0x1ff), &players[i].AllWeapon[k].my_weapons, sizeof(uint64_t));
                                                    }
                                                    if (players[i].AllWeapon[k].handle != -1)
                                                    {
                                                        mem.AddScatterReadRequest(handle, EntityListEntry + 8 * ((players[i].AllWeapon[k].handle & 0x7fff) >> 9) + 16, &players[i].AllWeapon[k].entity_list, sizeof(uint64_t));
                                                    }
                                                    mem.AddScatterReadRequest(handle, players[i].AllWeapon_ptr + k * 0x4, &players[i].AllWeapon[k].handle, sizeof(int));
                                                }
                                            }
                                            // all weapon ptr
                                            mem.AddScatterReadRequest(handle, players[i].WeaponServices + Offset::WeaponBaseData.AllWeapon + 0x08, &players[i].AllWeapon_ptr, sizeof(uint64_t));
                                            // weapon num
                                            mem.AddScatterReadRequest(handle, players[i].WeaponServices + Offset::WeaponBaseData.AllWeapon, &players[i].Weapon_num, sizeof(int));

                                            mem.AddScatterReadRequest(handle, players[i].WeaponServices + Offset::WeaponBaseData.ActiveWeapon, &players[i].handle, sizeof(int));

                                        }
                                        // helmet and defuser
                                        if (players[i].item_services)
                                        {
                                            mem.AddScatterReadRequest(handle, players[i].item_services + Offset::Pawn.HasHelmet, &players[i].helmet, sizeof(bool));
                                            mem.AddScatterReadRequest(handle, players[i].item_services + Offset::Pawn.HasDefuser, &players[i].defuser, sizeof(bool));
                                        }


                                        mem.AddScatterReadRequest(handle, players[i].Pawn_ptr + Offset::Pawn.ItemServices, &players[i].item_services, sizeof(uint64_t));

                                        mem.AddScatterReadRequest(handle, players[i].Pawn_ptr + Offset::Pawn.WeaponServices, &players[i].WeaponServices, sizeof(uint64_t));

                                        mem.AddScatterReadRequest(handle, players[i].Pawn_ptr + Offset::Pawn.GameSceneNode, &players[i].GameSceneNode, sizeof(uint64_t));

                                        mem.AddScatterReadRequest(handle, players[i].Pawn_ptr + Offset::Pawn.angEyeAngles, &players[i].ViewAngle, sizeof(QAngle));
                                        // pawn pos
                                        mem.AddScatterReadRequest(handle, players[i].Pawn_ptr + Offset::Pawn.Pos, &players[i].Pos, sizeof(Vector));
                                        // health
                                        mem.AddScatterReadRequest(handle, players[i].Pawn_ptr + Offset::Pawn.CurrentHealth, &players[i].Health_tmp, sizeof(int));
                                        // armor
                                        mem.AddScatterReadRequest(handle, players[i].Pawn_ptr + Offset::Pawn.CurrentArmor, &players[i].armor_tmp, sizeof(int));


                                        // shots fired
                                        mem.AddScatterReadRequest(handle, players[i].Pawn_ptr + Offset::Pawn.iShotsFired, &players[i].iShotsFired_tmp, sizeof(int));


                                    }

                                    if (players[i].EntityPawnListEntry)
                                    {
                                        mem.AddScatterReadRequest(handle, players[i].EntityPawnListEntry + 0x78 * (players[i].Pawn & 0x1FF), &players[i].Pawn_ptr, sizeof(uint64_t));
                                    }

                                    if (EntityListEntry)
                                    {
                                        mem.AddScatterReadRequest(handle, EntityListEntry + 0x10 + 8 * ((players[i].Pawn & 0x7FFF) >> 9), &players[i].EntityPawnListEntry, sizeof(uint64_t));
                                    }

                                    if (players[i].in_game_money_services)
                                    {
                                        mem.AddScatterReadRequest(handle, players[i].in_game_money_services + Offset::InGameMoneyServices.Account, &players[i].money, sizeof(int));
                                    }
                                    mem.AddScatterReadRequest(handle, players[i].Controller_ptr + Offset::InGameMoneyServices.MoneyServices, &players[i].in_game_money_services, sizeof(uint64_t));
                                    
                                    mem.AddScatterReadRequest(handle, players[i].Controller_ptr + Offset::Entity.PlayerPawn, &players[i].Pawn, sizeof(uint32_t));
                                    
                                    mem.AddScatterReadRequest(handle, players[i].Controller_ptr + Offset::Entity.iszPlayerName, &players[i].PlayerName_tmp, 64);

                                    // test read steam ids (working)
                                    mem.AddScatterReadRequest(handle, players[i].Controller_ptr + Offset::Entity.steamID, &players[i].steamID_tmp, sizeof(uint64_t));

                                    
                                }
                                mem.AddScatterReadRequest(handle, players[i].Controller_ptr + Offset::Entity.IsAlive, &players[i].IsAlive, sizeof(bool));
                                
                                mem.AddScatterReadRequest(handle, players[i].Controller_ptr + Offset::Pawn.iTeamNum, &players[i].TeamID, sizeof(int));

                            }

                            mem.AddScatterReadRequest(handle, NewEntityListEntry + (i + 1) * 0x78, &players[i].Controller_ptr, sizeof(uint64_t));
                        }
                    }


                    if (EntityListEntry)
                    {
                        mem.AddScatterReadRequest(handle, EntityListEntry + 0x10, &NewEntityListEntry, sizeof(uint64_t));
                    }
                    else
                    {
                        NewEntityListEntry = 0;
                    }

                    // map read
                    if (G_map.global_vars)
                    {
                        if (G_map.map_name_ptr)
                        {
                            mem.AddScatterReadRequest(handle, G_map.map_name_ptr, &G_map.map_name_tmp, 32);
                        }
                        mem.AddScatterReadRequest(handle, G_map.global_vars + 0x180, &G_map.map_name_ptr, sizeof(uint64_t));
                    }

                        
                    


                    mem.AddScatterReadRequest(handle, Client_BASE + Offset::Matrix, &m, sizeof(Matrix));

                    mem.AddScatterReadRequest(handle, Client_BASE + Offset::ViewAngle, &ViewAngle, sizeof(QAngle));

                    mem.AddScatterReadRequest(handle, Client_BASE + Offset::EntityList, &EntityListEntry, sizeof(uint64_t));

                    mem.AddScatterReadRequest(handle, Client_BASE + Offset::LocalPlayerController, &LocalController_ptr, sizeof(uint64_t));

                    //mem.AddScatterReadRequest(handle, Client_BASE + Offset::LocalPlayerPawn, &LocalPawn_ptr, sizeof(uint64_t));

                    mem.AddScatterReadRequest(handle, Client_BASE + Offset::GlobalVars, &G_map.global_vars, sizeof(uint64_t));

                    //mem.AddScatterReadRequest(handle, Client_BASE + Offset::PlantedC4, &planted_c4, sizeof(int));

                    //std::cout << planted_c4 << std::endl;

                    // Execute the scatter read
                    mem.ExecuteReadScatter(handle);

                    // Close the scatter handle
                    mem.CloseScatterHandle(handle);
                }

                // if map not null or empty
                if (G_map.map_name_tmp[0] != '\0')
                {
                    std::string nowmap = G_map.map_name_tmp;
                    if (G_map.map_name != G_map.map_name_tmp && nowmap != "<empty>" && nowmap != "client" && nowmap != "SNDLVL_40dB")
                    {
                        map.unload();


                        map.load_map(G_map.map_name_tmp);
                    }
                    G_map.map_name = G_map.map_name_tmp;
                }
                //  std::cout << G_map.map_name << std::endl;
                  // check local play is alive
                if (!players[LocalPlayerControllerIndex].IsAlive)
                {
                    for (int i = 0; i < 64; i++)
                    {
                        if (ViewAngle == players[i].ViewAngle)
                        {
                            DeathPos = &players[i].Pos;
                        }
                    }
                    if (DeathPos)
                    {
                        CameraPos = *DeathPos;
                    }
                }
                // std::cout << players[LocalPlayerControllerIndex].helmet << std::endl;
                 // radar draw stuff and weapons
                for (int i = 0; i < 64; i++)
                {
                    if (players[i].Controller_ptr)
                    {
                        players[i].Radar_Draw = true;
                    }
                    else
                    {
                        players[i].Radar_Draw = false;
                    }

                    if (players[i].Weapon_num < 20)
                    {
                        try
                        {
                            // std::cout << players[i].model_name << std::endl;
                            for (int k = 0; k < players[i].Weapon_num; k++)
                            {
                                //std::cout << "K  " << k << std::endl;
                                players[i].AllWeapon[k].weapon_id_Radar = players[i].AllWeapon[k].weapon_id;
                                std::string str = players[i].AllWeapon[k].weapon_name;

                                if (str.size() > 7 && str.find("weapon_") != std::string::npos)
                                {
                                    players[i].AllWeapon[k].weapon_name_Radar = str.substr(7);
                                }
                            }
                        }
                        catch (...)
                        {

                        }
                    }
                    std::string str = players[i].weapon_name;

                    if (str.size() > 7 && str.find("weapon_") != std::string::npos)
                    {
                        players[i].weapon_name_Radar = str.substr(7);
                    }
                    players[i].model_path = players[i].model_name;
                    if (players[i].Weapon_num < 20) {
                        players[i].Weapon_num_Radar = players[i].Weapon_num;
                    }
                    players[i].Weapon_num_Radar = players[i].Weapon_num;
                    players[i].helmet_Radar = players[i].helmet;
                    players[i].defuser_Radar = players[i].defuser;
                    players[i].money_Radar = players[i].money;
                    players[i].Health = players[i].Health_tmp;
                    players[i].armor = players[i].armor_tmp;
                    players[i].TeamID_Radar = players[i].TeamID;
                    players[i].IsAlive_Radar = players[i].IsAlive;
                    players[i].Pos_Radar = players[i].Pos;
                    players[i].ViewAngle_Radar = players[i].ViewAngle;
                    // testing steam id (working)
                    players[i].steamID_Radar = players[i].steamID_tmp;


                    set.shotsFired = players[LocalPlayerControllerIndex].iShotsFired_tmp;


                    // need rcs
                    //set.aimPunch.x = players[LocalPlayerControllerIndex].aimPunchCache.x;
                    //set.aimPunch.y = players[LocalPlayerControllerIndex].aimPunchCache.y;

                    //set.aimPunchCachetest = players[LocalPlayerControllerIndex].aimPunchCache_tmp;
                    //DWORD aimpunch_size = ((DWORD*)&players[LocalPlayerControllerIndex].aimPunchCache_tmp[0])[0];


                    strcpy(players[i].PlayerName, players[i].PlayerName_tmp);


                    if (!players[LocalPlayerControllerIndex].IsAlive)
                    {
                        players[i].dist = (players[i].Pos - CameraPos).Length() / 40.f;
                    }
                    else
                    {
                        players[i].dist = (players[i].Pos - players[LocalPlayerControllerIndex].Pos).Length() / 40.f;
                    }

                    if (!players[i].Controller_ptr || !players[i].Pawn_ptr)
                    {
                        players[i].isDraw = false;
                        continue;
                    }
                    //if (!players[i].IsAlive || players[i].TeamID == players[LocalPlayerControllerIndex].TeamID)
                    if (!players[i].IsAlive || players[i].TeamID == players[LocalPlayerControllerIndex].TeamID && !set.teamcheck)
                    {
                        players[i].isDraw = false;
                        continue;
                    }
                    if (!WorldToScreen(players[i].Pos, m.matrix, set.width, set.height, players[i].Pos_2D))
                    {
                        players[i].isDraw = false;
                        continue;
                    }


                    // new ray trace selected bone index pos 6 = HEAD CURRENTLY (set.aimbone)


                    players[i].r_end = players[i].BoneArray[set.aimbone].Pos;
                    //players[i].r_end.z += 73; // old r trace

                    players[i].r_start = players[LocalPlayerControllerIndex].BoneArray[6].Pos;
                    //players[i].r_start.z += 73; // old r trace


                    if (map.is_visible(players[i].r_start, players[i].r_end))
                    {
                        players[i].isVisible = true;
                    }
                    else
                    {
                        players[i].isVisible = false;
                    }


                    if (players[i].BoneArray[head].Pos.z < players[i].Pos.z || players[i].BoneArray[head].Pos.z - players[i].Pos.z>65.f)
                    {
                        players[i].BoneArray[head].Pos = players[i].Pos;
                        players[i].BoneArray[head].Pos.z += 60.f;
                    }
                    for (int k = 0; k < 30; k++)
                    {
                        //std::cout<< k<<"] " << players[i].BoneArray[k].Pos.x << " " << players[i].BoneArray[k].Pos.y << " " << players[i].BoneArray[k].Pos.z << std::endl;
                        if ((players[i].Pos - players[i].BoneArray[k].Pos).Length() / 40.f > 5.f)
                        {
                            players[i].isDraw = false;
                        }
                        if (!WorldToScreen(players[i].BoneArray[k].Pos, m.matrix, set.width, set.height, players[i].Bone_2D[k]))
                        {
                            players[i].isDraw = false;
                        }
                    }
                    if (players[i].IsAlive && LocalPlayerControllerIndex != i && players[i].Health > 0)
                    {
                        players[i].isDraw = true;
                    }
                    else
                    {
                        players[i].isDraw = false;
                    }

                    if (players[i].isDraw)
                    {
                        if (calculateDistance(players[i].Bone_2D[head].x, players[i].Bone_2D[head].y, set.width, set.height) < fov)
                        {
                            fov = calculateDistance(players[i].Bone_2D[head].x, players[i].Bone_2D[head].y, set.width, set.height);
                            aim_index = i;
                        }
                    }
                }


                


                

                // new ray trace selected bone index pos 6 = HEAD CURRENTLY

                //players[i].r_end = players[i].BoneArray[6].Pos;
                //players[i].r_end.z += 73;

                //players[i].r_start = players[LocalPlayerControllerIndex].BoneArray[6].Pos;
                //players[i].r_start.z += 73;


                


                // aimbot here if holding key
                bool aiming = false;
                if (mem.GetKeyboard()->IsKeyDown(set.aim_button1) || mem.GetKeyboard()->IsKeyDown(set.aim_button2))
                {
                    aiming = true;
                }
                if (aim_index < 64 && aim_index > 0 && aiming && players[aim_index].isDraw && fov < set.max_fov && (players[aim_index].isVisible || !set.VisibleCheck) && ((players[aim_index].TeamID_Radar != players[LocalPlayerControllerIndex].TeamID) || !set.aimbotteamcheck) && set.AimbotAimToggle && set.shotsFired < set.aimbotstopshotsFired)
                {
                    aimbot.starAimbot(set.shotsFired, set.aimPunch, set.sensitivity, players[aim_index]);
                }


                // refresh dma cache every 1 second
                if (elapsed_second1.count() >= 1)
                {
                    // VMMDLL_ConfigSet(mem.vHandle, VMMDLL_OPT_REFRESH_FREQ_MEM_PARTIAL, 1);
                    // VMMDLL_ConfigSet(mem.vHandle, VMMDLL_OPT_REFRESH_FREQ_TLB_PARTIAL, 1);
                    VMMDLL_ConfigSet(mem.vHandle, VMMDLL_OPT_REFRESH_FREQ_MEM, 1);
                    VMMDLL_ConfigSet(mem.vHandle, VMMDLL_OPT_REFRESH_FREQ_TLB, 1);

                    //std::cout << " [#] CACHE CLEARED: " << elapsed_second1.count() << "s" << std::endl;

                    oldTime1 = newTime;
                }


                //std::this_thread::sleep_for(std::chrono::milliseconds(1));

                // 再次获取当前时间点
                //auto end = std::chrono::high_resolution_clock::now();

                // 计算时间差
                //std::chrono::duration<double> elapsed = end - start;
                //data_up_time = elapsed.count();
                // 输出运行时间，单位为秒
                //std::cout << "data_up_time: " << elapsed.count() << " s" << std::endl;
            }
        }
        catch (...)
        {

        }
    }
}


void DrawFontStroke(const ImFont* font, float size, ImVec2 pos, ImVec4 color, const char* str)
{
    auto draw = ImGui::GetForegroundDrawList();

    if (set.fontoutline) {
        draw->AddText(font, size, ImVec2(pos.x + 1, pos.y), ImColor(15, 15, 20, 255), str);
        draw->AddText(font, size, ImVec2(pos.x - 1, pos.y), ImColor(15, 15, 20, 255), str);
        draw->AddText(font, size, ImVec2(pos.x, pos.y + 1), ImColor(15, 15, 20, 255), str);
        draw->AddText(font, size, ImVec2(pos.x, pos.y - 1), ImColor(15, 15, 20, 255), str);
        
    }
    draw->AddText(font, size, ImVec2(pos.x, pos.y), ImColor(color), str);
}

static ID3D11Device * g_pd3dDevice = nullptr;
static ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
static IDXGISwapChain* g_pSwapChain = nullptr;
static UINT g_ResizeWidth = 0, g_ResizeHeight = 0;
static ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;

bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Shader Resource View
bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
{
    
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return false;

    
    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Width = image_width;
    desc.Height = image_height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags = 0;

    ID3D11Texture2D* pTexture = NULL;
    D3D11_SUBRESOURCE_DATA subResource;
    subResource.pSysMem = image_data;
    subResource.SysMemPitch = desc.Width * 4;
    subResource.SysMemSlicePitch = 0;
    g_pd3dDevice->CreateTexture2D(&desc, &subResource, &pTexture);

    
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));
    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = desc.MipLevels;
    srvDesc.Texture2D.MostDetailedMip = 0;
    g_pd3dDevice->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
    pTexture->Release();

    *out_width = image_width;
    *out_height = image_height;
    stbi_image_free(image_data);

    return true;
}

bool CreateDeviceD3D(HWND hWnd)
{
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));

    
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 144;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;

    D3D_FEATURE_LEVEL featureLevel;
    // 定义所需的 D3D 特性级别数组
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };

    // 创建 D3D 设备和交换链
    HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    // 如果硬件驱动不支持所需的特性级别，则使用 WARP 软件驱动创建 D3D 设备和交换链
    if (res == DXGI_ERROR_UNSUPPORTED)
        res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    // 判断设备和交换链是否创建成功
    if (res != S_OK)
        return false;

    CreateRenderTarget(); // 创建渲染目标视图
    return true;
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget(); // 清理渲染目标视图
    // 释放设备和交换链的资源
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = nullptr; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = nullptr; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
}

void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    // 获取交换链的后台缓冲区
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    // 使用后台缓冲区创建渲染目标视图
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget()
{
    // 释放渲染目标视图的资源
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = nullptr; }
}

#ifndef WM_DPICHANGED
#define WM_DPICHANGED 0x02E0 // 来自 Windows SDK 8.1+ 头文件
#endif


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    // 调用 ImGui_ImplWin32_WndProcHandler 处理 ImGui 的窗口消息
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        // 当窗口被最小化时，返回 0 (消息已处理)
        if (wParam == SIZE_MINIMIZED)
            return 0;
        // 将窗口大小信息保存在全局变量 g_ResizeWidth 和 g_ResizeHeight 中，以便后续使用
        g_ResizeWidth = (UINT)LOWORD(lParam); // 队列中的大小改变
        g_ResizeHeight = (UINT)HIWORD(lParam);
        return 0;
    case WM_SYSCOMMAND:
        // 如果 wParam 是 SC_KEYMENU (ALT 键按下)，则返回 0 (消息已处理)，以禁用应用程序菜单
        if ((wParam & 0xfff0) == SC_KEYMENU)
            return 0;
        break;
    case WM_DESTROY:
        // 发送一个退出消息给主消息循环，以便退出程序
        ::PostQuitMessage(0);
        return 0;
    //case WM_DPICHANGED:
    //    // 如果启用了 ImGuiConfigFlags_DpiEnableScaleViewports 配置标志，处理 DPI 改变消息
    //    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DpiEnableScaleViewports)
    //    {
    //        // 获取建议的窗口矩形，并根据该矩形设置窗口的位置和大小
    //        const RECT* suggested_rect = (RECT*)lParam;
    //        ::SetWindowPos(hWnd, nullptr, suggested_rect->left, suggested_rect->top, suggested_rect->right - suggested_rect->left, suggested_rect->bottom - suggested_rect->top, SWP_NOZORDER | SWP_NOACTIVATE);
    //    }
    //    break;
    }
    // 使用默认的窗口过程处理未处理的消息
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}


// line and box coord
//static ImVec2 line_coord1{ 200,200 };
//static ImVec2 box_coord1{ 200,300 };
//static ImVec2 box_coord2{ 350,550 };

float GetDistance(const ImVec2& p1, const ImVec2& p2)
{
    return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}



ImColor box_color = { set.boxvizcolor[0], set.boxvizcolor[1], set.boxvizcolor[2] , set.boxvizcolor[3] }; 

ImColor line_color1 = { set.bonevizcolor[0], set.bonevizcolor[1], set.bonevizcolor[2] ,set.bonevizcolor[3] }; 
ImColor line_color2 = { set.boneinvizcolor[0], set.boneinvizcolor[1], set.boneinvizcolor[2] ,set.boneinvizcolor[3] };
//ImColor box_color = { set.boxvizcolor[0], set.boxvizcolor[1], set.boxvizcolor[2] ,set.boxvizcolor[3] }; 
ImColor box_color1 = { set.boxinvizcolor[0], set.boxinvizcolor[1], set.boxinvizcolor[2] ,set.boxinvizcolor[3] };
ImColor textinfo_color = { set.textinfo_colorr[0], set.textinfo_colorr[1], set.textinfo_colorr[2] ,set.textinfo_colorr[3] };


void imgui_Star()
{
    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"ImGui Example", nullptr };
    ::RegisterClassExW(&wc);

    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L" ESP OVERLAY", WS_POPUP, 0, 0, 1920, 1080, nullptr, nullptr, wc.hInstance, nullptr);
    
    // HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"imgui", WS_OVERLAPPEDWINDOW, 100,100, 800, 600, nullptr, nullptr, wc.hInstance, nullptr);

    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
    }

    ::ShowWindow(hwnd, 10);
    ::UpdateWindow(hwnd);

    ImGui_ImplWin32_EnableAlphaCompositing(hwnd); // 窗口透明
    //LONG exStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
    //exStyle |= WS_EX_TRANSPARENT | WS_EX_LAYERED;
    //SetWindowLong(hwnd, GWL_EXSTYLE, exStyle); // 鼠标穿透

    // ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    //ImGuiStyle& style = ImGui::GetStyle();
    //if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    //{
    //    style.WindowRounding = 0.0f;
    //    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    //}

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    io.IniFilename = nullptr;
    ImFontConfig Font_cfg;
    Font_cfg.FontDataOwnedByAtlas = false;

    //ImFont* Font = io.Fonts->AddFontFromMemoryTTF((void*)Font_data, Font_size, 18.0f, &Font_cfg, io.Fonts->GetGlyphRangesChineseFull());
    ImFont* Font = io.Fonts->AddFontFromMemoryTTF((void*)ttf_data, ttf_data_len, 13.0f, &Font_cfg, io.Fonts->GetGlyphRangesChineseFull());

    std::string KmboxComPortStr = std::to_string(set.KmboxComPort);
    std::string BPro_PorterStr = std::to_string(set.BPro_Porter);

    char KmboxComPortBuf[64];
    char BPro_PorterBuf[64];

    strncpy(KmboxComPortBuf, KmboxComPortStr.c_str(), sizeof(KmboxComPortBuf));
    strncpy(BPro_PorterBuf, BPro_PorterStr.c_str(), sizeof(BPro_PorterBuf));


    chinesefont = io.Fonts->AddFontFromMemoryTTF(&ttf_data, ttf_data_len, 12 * dpi_scale, NULL, io.Fonts->GetGlyphRangesCyrillic());
    tab_text1 = io.Fonts->AddFontFromMemoryTTF(&ttf_data, ttf_data_len, 12 * dpi_scale, NULL, io.Fonts->GetGlyphRangesCyrillic());
    tab_text2 = io.Fonts->AddFontFromMemoryTTF(&ttf_data, ttf_data_len, 24 * dpi_scale, NULL, io.Fonts->GetGlyphRangesCyrillic());
    tab_text3 = io.Fonts->AddFontFromMemoryTTF(&ttf_data, ttf_data_len, 40 * dpi_scale, NULL, io.Fonts->GetGlyphRangesCyrillic());
    ico = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 25 * dpi_scale, NULL, io.Fonts->GetGlyphRangesCyrillic());
    ico_2 = io.Fonts->AddFontFromMemoryTTF(&Menuicon, sizeof Menuicon, 20 * dpi_scale, NULL, io.Fonts->GetGlyphRangesCyrillic());
    ico_subtab = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 35 * dpi_scale, NULL, io.Fonts->GetGlyphRangesCyrillic());
    ico_logo = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 31 * dpi_scale, NULL, io.Fonts->GetGlyphRangesCyrillic());
    tab_textA = io.Fonts->AddFontFromMemoryTTF(&ttf_data, ttf_data_len, 19 * dpi_scale, NULL, io.Fonts->GetGlyphRangesCyrillic());
    ico_minimize = io.Fonts->AddFontFromMemoryTTF(&icon, sizeof icon, 27 * dpi_scale, NULL, io.Fonts->GetGlyphRangesCyrillic());


    //style.FrameRounding = 12;
    ImGui::StyleColorsLight();
    //style.Colors[ImGuiCol_Header] = RGBAtoIV4(36, 54, 74, 79);

    int my_image_width;
    int my_image_height;
    ID3D11ShaderResourceView* my_texture1 = NULL;
    bool ret1 = LoadTextureFromFile("mp_rr_desertlands_hu.jpg", &my_texture1, &my_image_width, &my_image_height);
    IM_ASSERT(ret1);




    ImGui_ImplWin32_EnableDpiAwareness();

    bool done = false;
    while (!done)
    {
        try
        {

            MSG msg;
            while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
            {
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);
                if (msg.message == WM_QUIT)
                    done = true;
            }

            if (done)
                break;

            if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
            {
                CleanupRenderTarget();
                g_pSwapChain->ResizeBuffers(0, g_ResizeWidth, g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0);
                g_ResizeWidth = g_ResizeHeight = 0;
                CreateRenderTarget();
            }

            
            static bool show_demo_window{}; 
            static bool show_another_window{}; 
            static bool show_line{};
            static bool show_Circle{}; 
            static bool show_box{}; 


            // box and skeleton thickness
            static float line_cx = 1; 
            static float Circle_cx = 2; 
            static float box_cx = 1; 

            static float box_yj = 0; 



            static ImColor Circle_color = ImColor{ set.fovcolor[0], set.fovcolor[1], set.fovcolor[2] };
            //static ImColor Circle_color1 = ImColor{ 0, 255, 0 }; 

            ImVec4 clear_color = ImVec4{ 0, 0, 0, 0 };
            if(set.BlackScreen)
            {
                clear_color = ImVec4{ 0, 0, 0, 255 };
            }
            else
            {
                clear_color = ImVec4{ 0, 0, 0, 0 };
            }

            //static ImColor line_color = ImColor{ 255, 0, 0 }; 
            //static ImColor line_2color = ImColor{ 255, 0, 0 }; 

            //ImColor line_color1 = { set.bonevizcolor[0], set.bonevizcolor[1], set.bonevizcolor[2] ,set.bonevizcolor[3] }; 
            //static ImColor line_color1 = ImColor{ 0, 255, 0, 255 };
            //ImColor line_color2 = { set.boneinvizcolor[0], set.boneinvizcolor[1], set.boneinvizcolor[2] ,set.boneinvizcolor[3] }; 
            //static ImColor line_color2 = ImColor{ 255, 255, 255, 255 };

            //ImColor box_color = { set.boxvizcolor[0], set.boxvizcolor[1], set.boxvizcolor[2] ,set.boxvizcolor[3] }; 
            //static ImColor box_color = ImColor{ 0, 255, 0, 255 };
            //ImColor box_color1 = { set.boxinvizcolor[0], set.boxinvizcolor[1], set.boxinvizcolor[2] ,set.boxinvizcolor[3] }; 
            //static ImColor box_color1 = ImColor{ 255, 255, 255, 255 };

            //ImColor textinfo_color = { set.textinfo_colorr[0], set.textinfo_colorr[1], set.textinfo_colorr[2] ,set.textinfo_colorr[3] };

            //static ImColor textinfo_color = ImColor{ 255, 255, 255, 255 };


            static ImGuiStyle ref_saved_style;
            static int style_idx = 0;

            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();
            SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); 

            //FOV
            ImVec2 Circle_coord{ set.width / 2,set.height / 2 }; 
            if (set.showfov && set.AimbotAimToggle)
            {
                ImGui::GetForegroundDrawList()->AddCircle(Circle_coord, set.max_fov, Circle_color, 0, 0.5f);
            }


            // head circle
           /* for (int i = 0; i < 64; i++)
            {
                if (players[i].isDraw && set.showhead)
                {
                    static ImVec2 head_1, head_2;


                    float abs_y = abs((players[i].Bone_2D[6].y + 100) - (players[i].Bone_2D[6].y + 100));
                    head_1 = ImVec2{ players[i].Bone_2D[head].x,players[i].Bone_2D[head].y };
                    //head_2 = { players[i].Pos_2D.x + abs_y / 4,players[i].Bone_2D[6].y };



                    if (abs_y / 2 < set.width / 2)
                    {
                        if (players[i].isVisible && set.VisibleCheck)
                        {
                            // testing head boxes
                            ImGui::GetForegroundDrawList()->AddCircle(head_1, 5, players[i].isVisible ? line_color1 : line_color2, 0, set.skeletonthickness);

                            //ImGui::GetForegroundDrawList()->AddRect(head_1, head_2, box_color, box_yj, NULL, set.boxthickness);
                        }
                        else
                        {
                            ImGui::GetForegroundDrawList()->AddCircle(head_1, 5, players[i].isVisible ? line_color1 : line_color2, 0, set.skeletonthickness);
                        }
                    }

                }
            }*/


                        //TEAM ID TESTING
            /*for (int i = 0; i < 64; i++)
            {
                if (players[i].isDraw)
                {
                    //float font_size = Dummies[i].width*0.7;
                    float font_size = 12;
                    ImVec2 position_2(players[i].Pos_2D.x, players[i].Pos_2D.y);
                    ImColor color = { 0,255,120 };
                    std::string Information5 = std::to_string(players[i].TeamID_Radar);
                    //Information = Information + "  " + players[i].weapon_name_Radar;
                    // Information = Information + "  " + std::to_string((int)players[i].dist) + "m" + players[i].weapon_name_Radar;

                    const char* text_name = Information5.c_str();

                    ImFont* font = ImGui::GetFont();
                    float text_width = font->CalcTextSizeA(font_size, FLT_MAX, 0.0f, text_name).x;

                    ImVec2 text_size(text_width, font_size);
                    ImVec2 center_offset = ImVec2(text_size.x * 0.5f, 0.0f);
                    ImVec2 centered_position = ImVec2(position_2.x - center_offset.x, position_2.y - center_offset.y + 28.f); // +5.f is the area to lower text name



                    DrawFontStroke(NULL, font_size, centered_position, color, text_name);
                }
            }*/

            // render esp stuff loop
            for (int i = 0; i < 64; i++)
            {
                if (players[i].isDraw && set.showweaponname)
                {
                    //float font_size = Dummies[i].width*0.7;
                    float font_size = 14;
                    ImVec2 position_2(players[i].Pos_2D.x, players[i].Pos_2D.y);
                    //ImColor color = { 0,255,120 };
                    std::string Informationstats = players[i].weapon_name_Radar;
                    //Informationstats = Informationstats + "  " + players[i].weapon_name_Radar;
                    // Information = Information + "  " + std::to_string((int)players[i].dist) + "m" + players[i].weapon_name_Radar;

                    const char* text_name = Informationstats.c_str();

                    ImFont* font = ImGui::GetFont();
                    float text_width = font->CalcTextSizeA(font_size, FLT_MAX, 0.0f, text_name).x;

                    ImVec2 text_size(text_width, font_size);
                    ImVec2 center_offset = ImVec2(text_size.x * 0.5f, 0.0f);
                    ImVec2 centered_position = ImVec2(position_2.x - center_offset.x, position_2.y - center_offset.y + set.textoffset + 13.f); // +5.f is the area to lower text name



                    DrawFontStroke(NULL, font_size, centered_position, textinfo_color, text_name);
                }

                if (players[i].isDraw && set.showname)
                {
                    //float font_size = Dummies[i].width*0.7;
                    float font_size = 14;
                    ImVec2 position_2(players[i].Pos_2D.x, players[i].Pos_2D.y);
                    //ImColor color = { 0,255,120 };
                    std::string Information = players[i].PlayerName;
                    //Information = Information + "  " + players[i].weapon_name_Radar;
                    // Information = Information + "  " + std::to_string((int)players[i].dist) + "m" + players[i].weapon_name_Radar;

                    const char* text_name = Information.c_str();

                    ImFont* font = ImGui::GetFont();
                    float text_width = font->CalcTextSizeA(font_size, FLT_MAX, 0.0f, text_name).x;

                    ImVec2 text_size(text_width, font_size);
                    ImVec2 center_offset = ImVec2(text_size.x * 0.5f, 0.0f);
                    ImVec2 centered_position = ImVec2(position_2.x - center_offset.x, position_2.y - center_offset.y + set.textoffset); // +5.f is the area to lower text name



                    DrawFontStroke(NULL, font_size, centered_position, textinfo_color, text_name);
                }

                if (players[i].isDraw && set.showbox)
                {
                    static ImVec2 box_1, box_2;


                    // players width
                    float abs_y = abs(players[i].Bone_2D[6].y - players[i].Pos_2D.y);
                    // box pos
                    box_1 = { players[i].Pos_2D.x - abs_y / 4,players[i].Pos_2D.y };
                    //top box
                    box_2 = { players[i].Pos_2D.x + abs_y / 4,players[i].Bone_2D[6].y };



                    if (abs_y / 2 < set.width / 2)
                    {
                        if (players[i].isVisible && set.VisibleCheck)
                        {
                            ImGui::GetForegroundDrawList()->AddRect(box_1, box_2, box_color, box_yj, NULL, set.boxthickness);
                        }
                        else
                        {
                            ImGui::GetForegroundDrawList()->AddRect(box_1, box_2, box_color1, box_yj, NULL, set.boxthickness);
                        }
                    }

                }

                if (players[i].isDraw && set.showhealth)
                {
                    float abs_y = abs(players[i].Bone_2D[head].y - players[i].Pos_2D.y);
                    ImVec2 box_1 = { players[i].Pos_2D.x - abs_y / 4,players[i].Pos_2D.y };
                    //ImVec2 box_2 = { players[i].Pos_2D.x + abs_y / 4,players[i].Bone_2D[head].y };

                    static ImVec2 line2;
                    line2.x = box_1.x - abs_y / 8; // health bar offset
                    line2.y = box_1.y;
                    static ImVec2 line3;
                    line3.x = box_1.x - abs_y / 8; // health bar offset
                    line3.y = box_1.y - (abs_y)*players[i].Health / 100;


                    //btm
                    //static ImVec2 line2_btm;
                    //line2_btm.x = box_1.x - abs_y / 8;
                    //line2_btm.y = box_1.y;
                    //static ImVec2 line3_btm;
                    //line3_btm.x = box_1.x - abs_y / 8;
                    //line3_btm.y = box_1.y - (abs_y);


                    //ImU32 line_color_btm = IM_COL32(255, 255, 255, 128);
                    //ImGui::GetForegroundDrawList()->AddLine(line2_btm, line3_btm, line_color_btm, line_cx);


                    ImGui::GetForegroundDrawList()->AddLine(line2, line3, ImColor{ 0, 255, 0 }, set.healthbarthickness);
                }

                if (players[i].isDraw && set.showskeleton)
                {

                    bool allConditionsSatisfied = true;

                    if (GetDistance(ImVec2{ players[i].Bone_2D[neck_0].x,players[i].Bone_2D[neck_0].y }, ImVec2{ players[i].Bone_2D[spine_2].x,players[i].Bone_2D[spine_2].y }) >= set.width / 4 ||
                        GetDistance(ImVec2{ players[i].Bone_2D[spine_2].x,players[i].Bone_2D[spine_2].y }, ImVec2{ players[i].Bone_2D[pelvis].x,players[i].Bone_2D[pelvis].y }) >= set.width / 4 ||
                        GetDistance(ImVec2{ players[i].Bone_2D[neck_0].x,players[i].Bone_2D[neck_0].y }, ImVec2{ players[i].Bone_2D[arm_upper_L].x,players[i].Bone_2D[arm_upper_L].y }) >= set.width / 4 ||
                        GetDistance(ImVec2{ players[i].Bone_2D[arm_upper_L].x,players[i].Bone_2D[arm_upper_L].y }, ImVec2{ players[i].Bone_2D[arm_lower_L].x,players[i].Bone_2D[arm_lower_L].y }) >= set.width / 4 ||
                        GetDistance(ImVec2{ players[i].Bone_2D[arm_lower_L].x,players[i].Bone_2D[arm_lower_L].y }, ImVec2{ players[i].Bone_2D[hand_L].x,players[i].Bone_2D[hand_L].y }) >= set.width / 4 ||
                        GetDistance(ImVec2{ players[i].Bone_2D[neck_0].x,players[i].Bone_2D[neck_0].y }, ImVec2{ players[i].Bone_2D[arm_upper_R].x,players[i].Bone_2D[arm_upper_R].y }) >= set.width / 4 ||
                        GetDistance(ImVec2{ players[i].Bone_2D[arm_upper_R].x,players[i].Bone_2D[arm_upper_R].y }, ImVec2{ players[i].Bone_2D[arm_lower_R].x,players[i].Bone_2D[arm_lower_R].y }) >= set.width / 4 ||
                        GetDistance(ImVec2{ players[i].Bone_2D[arm_lower_R].x,players[i].Bone_2D[arm_lower_R].y }, ImVec2{ players[i].Bone_2D[hand_R].x,players[i].Bone_2D[hand_R].y }) >= set.width / 4 ||
                        GetDistance(ImVec2{ players[i].Bone_2D[pelvis].x,players[i].Bone_2D[pelvis].y }, ImVec2{ players[i].Bone_2D[leg_upper_L].x,players[i].Bone_2D[leg_upper_L].y }) >= set.width / 4 ||
                        GetDistance(ImVec2{ players[i].Bone_2D[leg_upper_L].x,players[i].Bone_2D[leg_upper_L].y }, ImVec2{ players[i].Bone_2D[leg_lower_L].x,players[i].Bone_2D[leg_lower_L].y }) >= set.width / 4 ||
                        GetDistance(ImVec2{ players[i].Bone_2D[leg_lower_L].x,players[i].Bone_2D[leg_lower_L].y }, ImVec2{ players[i].Bone_2D[ankle_L].x,players[i].Bone_2D[ankle_L].y }) >= set.width / 4 ||
                        GetDistance(ImVec2{ players[i].Bone_2D[pelvis].x,players[i].Bone_2D[pelvis].y }, ImVec2{ players[i].Bone_2D[leg_upper_R].x,players[i].Bone_2D[leg_upper_R].y }) >= set.width / 4 ||
                        GetDistance(ImVec2{ players[i].Bone_2D[leg_upper_R].x,players[i].Bone_2D[leg_upper_R].y }, ImVec2{ players[i].Bone_2D[leg_lower_R].x,players[i].Bone_2D[leg_lower_R].y }) >= set.width / 4 ||
                        GetDistance(ImVec2{ players[i].Bone_2D[leg_lower_R].x,players[i].Bone_2D[leg_lower_R].y }, ImVec2{ players[i].Bone_2D[ankle_R].x,players[i].Bone_2D[ankle_R].y }) >= set.width / 4)
                    {
                        allConditionsSatisfied = false;
                    }

                    if (allConditionsSatisfied)
                    {
                        ImGui::GetForegroundDrawList()->AddLine(ImVec2{ players[i].Bone_2D[neck_0].x,players[i].Bone_2D[neck_0].y }, ImVec2{ players[i].Bone_2D[spine_2].x,players[i].Bone_2D[spine_2].y }, players[i].isVisible ? line_color1 : line_color2, set.skeletonthickness);
                        ImGui::GetForegroundDrawList()->AddLine(ImVec2{ players[i].Bone_2D[spine_2].x,players[i].Bone_2D[spine_2].y }, ImVec2{ players[i].Bone_2D[pelvis].x,players[i].Bone_2D[pelvis].y }, players[i].isVisible ? line_color1 : line_color2, set.skeletonthickness);

                        ImGui::GetForegroundDrawList()->AddLine(ImVec2{ players[i].Bone_2D[neck_0].x,players[i].Bone_2D[neck_0].y }, ImVec2{ players[i].Bone_2D[arm_upper_L].x,players[i].Bone_2D[arm_upper_L].y }, players[i].isVisible ? line_color1 : line_color2, set.skeletonthickness);
                        ImGui::GetForegroundDrawList()->AddLine(ImVec2{ players[i].Bone_2D[arm_upper_L].x,players[i].Bone_2D[arm_upper_L].y }, ImVec2{ players[i].Bone_2D[arm_lower_L].x,players[i].Bone_2D[arm_lower_L].y }, players[i].isVisible ? line_color1 : line_color2, set.skeletonthickness);
                        ImGui::GetForegroundDrawList()->AddLine(ImVec2{ players[i].Bone_2D[arm_lower_L].x,players[i].Bone_2D[arm_lower_L].y }, ImVec2{ players[i].Bone_2D[hand_L].x,players[i].Bone_2D[hand_L].y }, players[i].isVisible ? line_color1 : line_color2, set.skeletonthickness);

                        ImGui::GetForegroundDrawList()->AddLine(ImVec2{ players[i].Bone_2D[neck_0].x,players[i].Bone_2D[neck_0].y }, ImVec2{ players[i].Bone_2D[arm_upper_R].x,players[i].Bone_2D[arm_upper_R].y }, players[i].isVisible ? line_color1 : line_color2, set.skeletonthickness);
                        ImGui::GetForegroundDrawList()->AddLine(ImVec2{ players[i].Bone_2D[arm_upper_R].x,players[i].Bone_2D[arm_upper_R].y }, ImVec2{ players[i].Bone_2D[arm_lower_R].x,players[i].Bone_2D[arm_lower_R].y }, players[i].isVisible ? line_color1 : line_color2, set.skeletonthickness);
                        ImGui::GetForegroundDrawList()->AddLine(ImVec2{ players[i].Bone_2D[arm_lower_R].x,players[i].Bone_2D[arm_lower_R].y }, ImVec2{ players[i].Bone_2D[hand_R].x,players[i].Bone_2D[hand_R].y }, players[i].isVisible ? line_color1 : line_color2, set.skeletonthickness);

                        ImGui::GetForegroundDrawList()->AddLine(ImVec2{ players[i].Bone_2D[pelvis].x,players[i].Bone_2D[pelvis].y }, ImVec2{ players[i].Bone_2D[leg_upper_L].x,players[i].Bone_2D[leg_upper_L].y }, players[i].isVisible ? line_color1 : line_color2, set.skeletonthickness);
                        ImGui::GetForegroundDrawList()->AddLine(ImVec2{ players[i].Bone_2D[leg_upper_L].x,players[i].Bone_2D[leg_upper_L].y }, ImVec2{ players[i].Bone_2D[leg_lower_L].x,players[i].Bone_2D[leg_lower_L].y }, players[i].isVisible ? line_color1 : line_color2, set.skeletonthickness);
                        ImGui::GetForegroundDrawList()->AddLine(ImVec2{ players[i].Bone_2D[leg_lower_L].x,players[i].Bone_2D[leg_lower_L].y }, ImVec2{ players[i].Bone_2D[ankle_L].x,players[i].Bone_2D[ankle_L].y }, players[i].isVisible ? line_color1 : line_color2, set.skeletonthickness);

                        ImGui::GetForegroundDrawList()->AddLine(ImVec2{ players[i].Bone_2D[pelvis].x,players[i].Bone_2D[pelvis].y }, ImVec2{ players[i].Bone_2D[leg_upper_R].x,players[i].Bone_2D[leg_upper_R].y }, players[i].isVisible ? line_color1 : line_color2, set.skeletonthickness);
                        ImGui::GetForegroundDrawList()->AddLine(ImVec2{ players[i].Bone_2D[leg_upper_R].x,players[i].Bone_2D[leg_upper_R].y }, ImVec2{ players[i].Bone_2D[leg_lower_R].x,players[i].Bone_2D[leg_lower_R].y }, players[i].isVisible ? line_color1 : line_color2, set.skeletonthickness);
                        ImGui::GetForegroundDrawList()->AddLine(ImVec2{ players[i].Bone_2D[leg_lower_R].x,players[i].Bone_2D[leg_lower_R].y }, ImVec2{ players[i].Bone_2D[ankle_R].x,players[i].Bone_2D[ankle_R].y }, players[i].isVisible ? line_color1 : line_color2, set.skeletonthickness);

                    }

                }

            }

            if (show_demo_window)
            {
                ImGui::ShowDemoWindow();
            }

            static std::chrono::time_point LastTimePoint = std::chrono::steady_clock::now();
            auto CurTimePoint = std::chrono::steady_clock::now();

            // HOME  open menu
            if ((mem.GetKeyboard()->IsKeyDown(VK_INSERT) || mem.GetKeyboard()->IsKeyDown(VK_F8)) && CurTimePoint - LastTimePoint >= std::chrono::milliseconds(230)) {
                set.ShowMenu = !set.ShowMenu;
                LastTimePoint = CurTimePoint;
            }

            // MENU  black screen
            //if ((mem.GetKeyboard()->IsKeyDown(VK_F9) || mem.GetKeyboard()->IsKeyDown(VK_HOME)) && CurTimePoint - LastTimePoint >= std::chrono::milliseconds(230)) {
            //    set.BlackScreen = !set.BlackScreen;
            //    LastTimePoint = CurTimePoint;
            //}

            // F5 refresh cache
            if (mem.GetKeyboard()->IsKeyDown(VK_F5) && CurTimePoint - LastTimePoint >= std::chrono::milliseconds(230)) {
                std::cout << " [ > ] CACHE REFRESHED_ALL" << std::endl;
                VMMDLL_ConfigSet(mem.vHandle, VMMDLL_OPT_REFRESH_ALL, 1);
                LastTimePoint = CurTimePoint;
            }

            // F8  re init cs2
            /*if (mem.GetKeyboard()->IsKeyDown(VK_F8) && CurTimePoint - LastTimePoint >= std::chrono::milliseconds(230)) {
                mem.~Memory();
                Sleep(500);
                // Initialize DMA
                if (!mem.Init("cs2.exe", true, false))
                {
                    std::cout << " [ ! ] DMA INIT FAILED OR CS2 NOT FOUND" << std::endl;
                    Sleep(2000);
                    //exit(1);
                }

                std::cout << " [#] CS2 FOUND" << std::endl;
                Client_BASE = mem.GetBaseDaddy("client.dll");

                std::cout << " [#] Fetch Base Address for client.dll at " << Client_BASE << std::endl;

                LastTimePoint = CurTimePoint;
            }*/

            // END shut down
            if (mem.GetKeyboard()->IsKeyDown(VK_END) && CurTimePoint - LastTimePoint >= std::chrono::milliseconds(230)) {
                ImGui_ImplDX11_Shutdown();
                ImGui_ImplWin32_Shutdown();
                ImGui::DestroyContext();
                mem.~Memory();//释放DMA进程
                Sleep(100);
                exit(0);  // 退出程序
                LastTimePoint = CurTimePoint;
            }

            if (set.ShowMenu) {
                // WS_EX_TRANSPARENT
                LONG exStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
                exStyle |= WS_EX_TRANSPARENT | WS_EX_LAYERED;
                SetWindowLong(hwnd, GWL_EXSTYLE, exStyle & ~WS_EX_TRANSPARENT);
            }
            else {
                //WS_EX_TRANSPARENT 
                LONG exStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
                exStyle |= WS_EX_TRANSPARENT | WS_EX_LAYERED;
                SetWindowLong(hwnd, GWL_EXSTYLE, exStyle | WS_EX_TRANSPARENT);
            }


            if (set.ShowMenu)
            {
                ImGui::SetNextWindowSize(ImVec2(855 * dpi_scale, 650 * dpi_scale));
                ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
                {
                    ImGuiStyle& s = ImGui::GetStyle();

                    s.Colors[ImGuiCol_WindowBg] = ImColor(60, 65, 80, 60);
                    s.Colors[ImGuiCol_ChildBg] = ImColor(20, 20, 20, 255);
                    s.Colors[ImGuiCol_PopupBg] = ImColor(26, 26, 26, 255);
                    s.Colors[ImGuiCol_Text] = ImColor(150, 150, 150, 255);
                    s.Colors[ImGuiCol_TextDisabled] = ImColor(125, 125, 125, 255);
                    s.Colors[ImGuiCol_Border] = ImColor(204, 0, 255, 255);
                    s.Colors[ImGuiCol_TextSelectedBg] = ImColor(50, 50, 50, 100);

                    s.Colors[ImGuiCol_ScrollbarGrab] = ImColor(255, 60, 60, 255);
                    s.Colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(60, 255, 60, 255);
                    s.Colors[ImGuiCol_ScrollbarGrabActive] = ImColor(60, 60, 255, 255);

                    s.WindowBorderSize = 0;
                    s.WindowPadding = ImVec2(0, 0);
                    s.WindowRounding = 20.f;
                    s.PopupBorderSize = 0.f;
                    s.PopupRounding = 0.f;
                    s.ChildRounding = 1.f;
                    s.ChildBorderSize = 1.f;
                    s.FrameBorderSize = 1.0f;
                    s.ScrollbarSize = 3.0f;
                    s.FrameRounding = 1.f;
                    s.ItemSpacing = ImVec2(0, 15);
                    s.ItemInnerSpacing = ImVec2(7, 0);

                    const auto& p = ImGui::GetWindowPos();


                    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0));
                    ImGui::BeginChild("G-Tab", ImVec2(173 * dpi_scale, 650 * dpi_scale), false);
                    {
                        DrawFontStroke(tab_text3, 36 * dpi_scale, ImVec2(20 * dpi_scale + p.x, 20 * dpi_scale + p.y), ImColor(204, 0, 255), "CS2-DMA");

                        //tab black box
                        //ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(0 + p.x, 0 + p.y), ImVec2(170 * dpi_scale + p.x, 490 * dpi_scale + p.y), ImGui::GetColorU32(colors::Tab_Child), s.WindowRounding);
                        //user info black box
                        //ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(0 + p.x, 60 + p.y), ImVec2(170 * dpi_scale + p.x, 400 * dpi_scale + p.y), ImGui::GetColorU32(colors::Tab_Child), s.WindowRounding);

                        ImGui::SetCursorPosY(60);

                        ImGui::SetWindowFontScale(dpi_scale);
                        if (ImGui::Tab("H", "AIM-BOT", "AUTO-AIM SETUP", 0 == Gui::tabs, ImVec2(150 * dpi_scale, 42 * dpi_scale))) Gui::tabs = 0;
                        //if (ImGui::Tab("A", "TRIGGER-BOT", "( WIP )", 5 == Gui::tabs, ImVec2(150 * dpi_scale, 42 * dpi_scale))) Gui::tabs = 5;
                        if (ImGui::Tab("F", "VISUALS", "ESP SETTINGS", 1 == Gui::tabs, ImVec2(150 * dpi_scale, 42 * dpi_scale))) Gui::tabs = 1;
                        //if (ImGui::Tab("B", "CONFIG", "SAVE CONFIGS", 2 == Gui::tabs, ImVec2(150 * dpi_scale, 42 * dpi_scale))) Gui::tabs = 2;
                        if (ImGui::Tab("E", "SETTINGS", "KMBOX & DISPLAY", 3 == Gui::tabs, ImVec2(150 * dpi_scale, 42 * dpi_scale))) Gui::tabs = 3;
                        if (ImGui::Tab("X", "QUIT", "CLOSE SOFTWARE", 4 == Gui::tabs, ImVec2(150 * dpi_scale, 42 * dpi_scale))) {
                            
                            ImGui_ImplDX11_Shutdown();
                            ImGui_ImplWin32_Shutdown();
                            ImGui::DestroyContext();
                            mem.~Memory();
                            Sleep(100);
                            exit(0);  
                        }

                    }ImGui::EndChild();


                    ImGui::PopStyleColor();

                    //black background
                    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(0 + p.x, 0 + p.y), ImVec2(765 * dpi_scale + p.x, 490 * dpi_scale + p.y), ImGui::GetColorU32(colors::main_color), s.WindowRounding);

                    //ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(0 + p.x, 755 * dpi_scale + p.y), ImVec2(855 * dpi_scale + p.x, 600 * dpi_scale + p.y), ImGui::GetColorU32(colors::lite_color), s.WindowRounding);

                    //   ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(0 + p.x, 0 + p.y), ImVec2(705 + p.x, 60 + p.y), ImGui::GetColorU32(colors::lite_color), s.WindowRounding);

                    std::stringstream ss;
                    ss << std::fixed << std::setprecision(0) << io.Framerate;
                    std::string framedata = ss.str();
                    std::string countStr = "FPS > " + framedata;


                    // how to use insert
                    DrawFontStroke(tab_text3, 14 * dpi_scale, ImVec2(6 * dpi_scale + p.x, 515 * dpi_scale + p.y), ImColor(200, 200, 200, 255), "[INSERT / F8] OPEN / CLOSE");



                    // keyboard status
                    DrawFontStroke(tab_text3, 14 * dpi_scale, ImVec2(18 * dpi_scale + p.x, 420 * dpi_scale + p.y), ImColor(204, 0, 255, 255), "KB > ");
                    if (set.keyboardstate)
                    {
                        DrawFontStroke(tab_text3, 14 * dpi_scale, ImVec2(46 * dpi_scale + p.x, 420 * dpi_scale + p.y), ImColor(0, 255, 0, 255), "CONNECTED");
                    }
                    else
                    {
                        DrawFontStroke(tab_text3, 14 * dpi_scale, ImVec2(46 * dpi_scale + p.x, 420 * dpi_scale + p.y), ImColor(255, 0, 0, 255), "FAILED");
                    }

                    // KMBOX status
                    DrawFontStroke(tab_text3, 14 * dpi_scale, ImVec2(18 * dpi_scale + p.x, 440 * dpi_scale + p.y), ImColor(204, 0, 255, 255), "KMBOX > ");
                    if (set.connect)
                    {
                        DrawFontStroke(tab_text3, 14 * dpi_scale, ImVec2(73 * dpi_scale + p.x, 440 * dpi_scale + p.y), ImColor(0, 255, 0, 255), "CONNECTED");
                    }
                    else
                    {
                        DrawFontStroke(tab_text3, 14 * dpi_scale, ImVec2(73 * dpi_scale + p.x, 440 * dpi_scale + p.y), ImColor(255, 0, 0, 255), "FAILED");
                    }

                    
                    // fps display
                    DrawFontStroke(tab_text3, 14 * dpi_scale, ImVec2(18 * dpi_scale + p.x, 460 * dpi_scale + p.y), ImColor(204, 0, 255, 255), countStr.c_str());
                    


                    Gui::tab_alpha = ImClamp(Gui::tab_alpha + (7.f * ImGui::GetIO().DeltaTime * (Gui::tabs == Gui::active_tab ? 1.f : -1.f)), 0.f, 1.f);
                    Gui::tab_add = ImClamp(Gui::tab_add + (std::round(50.f) * ImGui::GetIO().DeltaTime * (Gui::tabs == Gui::active_tab ? 1.f : -1.f)), 0.f, 1.f);

                    if (Gui::tab_alpha == 0.f && Gui::tab_add == 0.f) Gui::active_tab = Gui::tabs;

                    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, Gui::tab_alpha * s.Alpha);

                    ImGui::SetCursorPos(ImVec2(180 * dpi_scale, 15 * dpi_scale));

                    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0));
                    ImGui::BeginChild("General", ImVec2(717 * dpi_scale, 610 * dpi_scale), false);
                    {
                        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::GetColorU32(colors::lite_color));
                        switch (Gui::active_tab)
                        {
                            //Aimbot
                        case 0:
                        {
                            //ImGui::SetCursorPosY(0 * dpi_scale);
                            ImGui::BeginChildPos("AIMBOT SETTINGS", ImVec2(280 * dpi_scale, 460 * dpi_scale), true);
                            {
                                ImGui::SetWindowFontScale(dpi_scale);
                                ImGui::Checkbox("Toggle", &set.AimbotAimToggle);
                                ImGui::SameLine(150, 0);
                                ImGui::Checkbox("FOV", &set.showfov);
                                
                                ImGui::Checkbox("Team Check", &set.aimbotteamcheck);
                                ImGui::SameLine(150, 0);
                                ImGui::Checkbox("Vis Check", &set.VisibleCheck);
                                if (ImGui::IsItemHovered()) {
                                    ImGui::BeginTooltip();
                                    ImGui::Text("MAPS NEED UPDATING\nMANY MAPS NOT SUPPORTED");
                                    ImGui::EndTooltip();
                                }

                                //ImGui::Checkbox("RCS", &set.RCS);

                                if (ImGui::Combo("Aim Bone Selection", &selectedIndex, Boneitems, IM_ARRAYSIZE(Boneitems)))
                                {
                                    set.aimbone = Bonevalues[selectedIndex];
                                }
                                ImGui::Keybind("AIMBOT Button [1]", &set.aim_button1, true);
                                ImGui::Keybind("AIMBOT Button [2]", &set.aim_button2, true);
                                ImGui::SliderFloat("In-Game Mouse Sensitivity", &set.sensitivity, 0.1f, 20.f, "%.1f");
                            }

                            ImGui::EndChild();

                            ImGui::SetCursorPos(ImVec2(290 * dpi_scale, NULL));

                            ImGui::BeginChildPos("SLIDERS", ImVec2(280 * dpi_scale, 460 * dpi_scale), true);
                            {

                                ImGui::SetWindowFontScale(dpi_scale);

                                ImGui::SliderFloat("Kmbox Delay Ticks", &set.aim_tick, 0.0f, 0.05f);
                                ImGui::SliderFloat("FOV", &set.max_fov, 1.0f, 500.0f, "%.1f");
                                ImGui::SliderFloat("Smoothing", &set.Smoothing, 1.0f, 50.f, "%.1f");
                                ImGui::SliderFloat("Aim X", &set.speed_X, 1.0f, 400.f, "%.1f");
                                ImGui::SliderFloat("Aim Y", &set.speed_Y, 1.0f, 400.f, "%.1f");
                                ImGui::SliderInt("Stop Aimbot After X Bullets", &set.aimbotstopshotsFired, 1, 30, "%d Bullets");

                            }
                            ImGui::EndChild();
                            aimbot.aim_tick = set.aim_tick;
                            aimbot.Smoothing = set.Smoothing;
                            aimbot.speed_X = set.speed_X;
                            aimbot.speed_Y = set.speed_Y;
                        }
                        break;
                        case 1:
                        {
                            ImGui::BeginChildPos("ESP SETTINGS", ImVec2(280 * dpi_scale, 460 * dpi_scale), true);
                            {
                                ImGui::SetWindowFontScale(dpi_scale);

                                ImGui::Checkbox("Box", &set.showbox);
                                ImGui::SameLine(100, 0);
                                ImGui::Checkbox("Health", &set.showhealth);
                                //ImGui::Checkbox("Head", &set.showhead);
                                ImGui::SameLine(180, 0);
                                ImGui::Checkbox("Bones", &set.showskeleton);
                                ImGui::Checkbox("Name", &set.showname);
                                ImGui::SameLine(100, 0);
                                ImGui::Checkbox("Weapon", &set.showweaponname);
                                ImGui::SameLine(180, 0);
                                ImGui::Checkbox("Team", &set.teamcheck);
                                ImGui::SliderFloat("Skeleton Thickness", &set.skeletonthickness, 0.5f, 3.0f, "%.1f");
                                ImGui::SliderFloat("Box Thickness", &set.boxthickness, 0.5f, 3.0f, "%.1f");
                                //ImGui::SliderFloat("Box Padding", &set.boxpadding, 1.0f, 25.0f);
                                ImGui::SliderFloat("Health Bar Thickness", &set.healthbarthickness, 1.0f, 3.0f, "%.1f");
                                ImGui::SliderFloat("Text Vertical Offset", &set.textoffset, 3.0f, 70.0f, "%.1f");
                                //ImGui::SliderFloat("Health Bar Offset", &set.healthboxoffset, -20.0f, 40.0f, "%.1f");

                                //ImGui::SliderInt("Vischeck Delay MS", &set.vischeckdelay, 1, 100, "%dms");
                            }
                            ImGui::EndChild();
                            /// color picker stuff here
                            ImGui::SetCursorPos(ImVec2(290 * dpi_scale, NULL));
                            ImGui::BeginChildPos("Color Editor", ImVec2(280 * dpi_scale, 460 * dpi_scale), true);
                            {
                                ImGui::SetWindowFontScale(dpi_scale);


                                //if (ImGui::ColorPicker69(reinterpret_cast<float*>(&box_color), false)) {

                                 //   std::cout << box_color.Value.x << " " << box_color.Value.y << " " << box_color.Value.z << " " << box_color.Value.w << std::endl;
                                    //std::cout << set.boxvizcolor[0] << " " << set.boxvizcolor[1] << " " << set.boxvizcolor[2] << " " << set.boxvizcolor[3] << std::endl;
                                    //set.boxvizcolor[0] = box_color.Value.x * 255.f;
                               // }



                                if (ImGui::ColorEdit4("Box Color##box_color", reinterpret_cast<float*>(&box_color), ImGuiColorEditFlags_NoInputs)) {

                                    std::cout << box_color.Value.x << " " << box_color.Value.y << " " << box_color.Value.z << " " << box_color.Value.w << std::endl;
                                    //std::cout << set.boxvizcolor[0] << " " << set.boxvizcolor[1] << " " << set.boxvizcolor[2] << " " << set.boxvizcolor[3] << std::endl;
                                    //set.boxvizcolor[0] = box_color.Value.x * 255.f;
                                    //set.boxvizcolor[1] = box_color.Value.y * 255.f;
                                    //set.boxvizcolor[2] = box_color.Value.z * 255.f;
                                    //set.boxvizcolor[3] = box_color.Value.w;

                                }

                                


                                

                                

                                if (ImGui::ColorEdit4("Box Not Visible##box_color1", reinterpret_cast<float*>(&box_color1), ImGuiColorEditFlags_NoInputs)) {
                                    
                                    //set.boxinvizcolor[0] = box_color1.Value.x * 255.f;
                                    //set.boxinvizcolor[1] = box_color1.Value.y * 255.f;
                                    //set.boxinvizcolor[2] = box_color1.Value.z * 255.f;
                                    //set.boxinvizcolor[3] = box_color.Value.w;
                                }

                                if (ImGui::ColorEdit4("Bone Color##line_color1", reinterpret_cast<float*>(&line_color1), ImGuiColorEditFlags_NoInputs)) {
                                    
                                    //set.bonevizcolor[0] = line_color1.Value.x * 255.f;
                                    //set.bonevizcolor[1] = line_color1.Value.y * 255.f;
                                    //set.bonevizcolor[2] = line_color1.Value.z * 255.f;
                                    //set.boxinvizcolor[3] = box_color.Value.w;
                                }


                                if (ImGui::ColorEdit4("Bone Not Visible##line_color2", reinterpret_cast<float*>(&line_color2), ImGuiColorEditFlags_NoInputs)) {

                                    //set.boneinvizcolor[0] = line_color2.Value.x * 255.f;
                                    //set.boneinvizcolor[1] = line_color2.Value.y * 255.f;
                                    //set.boneinvizcolor[2] = line_color2.Value.z * 255.f;
                                }


                                if (ImGui::ColorEdit4("Text Info##textinfo_color", reinterpret_cast<float*>(&textinfo_color), ImGuiColorEditFlags_NoInputs)) {
                                    
                                    //set.textinfo_colorr[0] = textinfo_color.Value.x * 255.f;
                                    //set.textinfo_colorr[1] = textinfo_color.Value.y * 255.f;
                                    //set.textinfo_colorr[2] = textinfo_color.Value.z * 255.f;

                                }

                                if (ImGui::ColorEdit4("FOV Circle Color##Circle_color", reinterpret_cast<float*>(&Circle_color), ImGuiColorEditFlags_NoInputs)) {

                                    //set.fovcolor[0] = Circle_color.Value.x * 255.f;
                                    //set.fovcolor[1] = Circle_color.Value.y * 255.f;
                                    //set.fovcolor[2] = Circle_color.Value.z * 255.f;


                                }

                                //ImGui::Text("Colors");

                                //ImGui::ColorEdit4("Bone Color##BoneColor", reinterpret_cast<float*>(&Menu::Color::BoneColor), ImGuiColorEditFlags_NoInputs);
                                //ImGui::ColorEdit4("HeadCricle Color##HeadCricleColor", reinterpret_cast<float*>(&Menu::Color::HeadCricleColor), ImGuiColorEditFlags_NoInputs);
                                //ImGui::ColorEdit4("Eye Ray Color##EyeRay", reinterpret_cast<float*>(&Menu::Color::EyeRayColor), ImGuiColorEditFlags_NoInputs);
                                //ImGui::ColorEdit4("Name Color Color##Name", reinterpret_cast<float*>(&Menu::Color::NameColor), ImGuiColorEditFlags_NoInputs);
                                //ImGui::ColorEdit4("Line to enemy Color##LineToEnemyColor", reinterpret_cast<float*>(&Menu::Color::LineColor), ImGuiColorEditFlags_NoInputs);

                                //ImGui::ColorEdit4("Health Color##Health", reinterpret_cast<float*>(&Menu::Color::HealthColor), ImGuiColorEditFlags_NoInputs);

                            }
                            ImGui::EndChild();
                        }
                        break;
                        
                        case 3:
                        {
                            ImGui::BeginChildPos("DISPLAY SETTINGS", ImVec2(280 * dpi_scale, 460 * dpi_scale), true);
                            {
                                ImGui::SetWindowFontScale(dpi_scale);

                                ImGui::InputFloat("Monitor Width", &set.width, .0f, .0f, "%.0f");
                                ImGui::InputFloat("Monitor Height", &set.height, .0f, .0f, "%.0f");
                                ImGui::Checkbox("V-Sync", &set.EnableVSync);//105
                                ImGui::SameLine(120, 0);
                                ImGui::Checkbox("FUSER MODE", &set.BlackScreen);
                                
                                //ImGui::Checkbox("AUTO-BHOP", &set.autobhop);
                                ImGui::Checkbox("Font Outline", &set.fontoutline);
                                //ImGui::Text("CONFIGS");
                                if (ImGui::Button("SAVE CONFIG")) {
                                    set.saveSettings("config.json");
                                }
                                //ImGui::SameLine(120, 0);
                                //if (ImGui::Button("LOAD CONFIG")) {
                                //    set.loadSettings("config.json");
                                //}
                                //ImGui::Text("OTHER");
                                ImGui::Checkbox("Enable WebRadar", &G_map.EnableWebRadar);
                                if (G_map.EnableWebRadar)
                                {
                                    ImGui::SameLine(150, 0);
                                    if (ImGui::Button("OPEN SITE")) {
                                        ShellExecute(0, 0, L"http://localhost:5173", 0, 0, SW_SHOW);
                                    }
                                }
                                
                                

                                



                                //ImGui::SliderInt("Radar Update Delay", &set.radarupdatedelay, 10, 5000, "%dms");
                                /*if (ImGui::Button("EXIT SOFTWARE")) {
                                    ImGui_ImplDX11_Shutdown();
                                    ImGui_ImplWin32_Shutdown();
                                    ImGui::DestroyContext();
                                    mem.~Memory();
                                    Sleep(100);
                                    exit(0);
                                }*/
                                


                            }
                            ImGui::EndChild();
                            ImGui::SetCursorPos(ImVec2(290 * dpi_scale, NULL));
                            ImGui::BeginChildPos("KMBOX SETUP", ImVec2(280 * dpi_scale, 460 * dpi_scale), true);
                            {

                                ImGui::SetWindowFontScale(dpi_scale);

                                const char* KmboxType[] = { "Net", "BPro" };

                                if (ImGui::BeginCombo("KMBOX TYPE", KmboxType[set.KmBoxTypeSelected])) {
                                    for (int i = 0; i < IM_ARRAYSIZE(KmboxType); i++) {
                                        bool isSelected = (set.KmBoxTypeSelected == i);
                                        if (ImGui::Selectable(KmboxType[i], isSelected)) {
                                            set.KmBoxTypeSelected = i;
                                        }
                                        if (isSelected) {
                                            ImGui::SetItemDefaultFocus();
                                        }
                                    }
                                    ImGui::EndCombo();
                                }

                                switch (set.KmBoxTypeSelected)
                                {
                                case 0:
                                    set.KmboxType = "Net";
                                    ImGui::InputText("IP", set.KmboxIP, sizeof(set.KmboxIP));
                                    ImGui::InputText("PORT", set.KmboxPort, sizeof(set.KmboxPort));
                                    ImGui::InputText("UUID", set.KmboxUUID, sizeof(set.KmboxUUID));
                                    break;
                                case 1:
                                    set.KmboxType = "BPro";
                                    if (ImGui::InputText("COM PORT", KmboxComPortBuf, sizeof(KmboxComPortBuf)))
                                    {
                                        set.KmboxComPort = std::stoi(KmboxComPortBuf);
                                    }

                                    if (ImGui::InputText("BUFFER", BPro_PorterBuf, sizeof(BPro_PorterBuf)))
                                    {
                                        set.BPro_Porter = std::stoi(BPro_PorterBuf);
                                    }
                                    break;
                                }

                                if (ImGui::Button("INITIALIZE")) {
                                    set.connect = aimbot.Initialize();
                                }
                                if (ImGui::IsItemHovered()) {
                                    ImGui::BeginTooltip();
                                    if (set.connect)
                                    {
                                        ImGui::TextColored(ImVec4(0, 1, 0, 1), "CONNECTED");
                                    }
                                    else
                                    {
                                        ImGui::TextColored(ImVec4(1, 0.2, 0, 1), "NOT-CONNECTED");
                                    }
                                    ImGui::EndTooltip();
                                }


                                ImGui::SameLine(110, 0);

                                if (ImGui::Button("TEST KMBOX"))
                                {
                                    aimbot.Move(20, 20);
                                }
                                if (ImGui::IsItemHovered()) {
                                    ImGui::BeginTooltip();
                                    ImGui::Text("Moves mouse x:20 y:20");
                                    ImGui::EndTooltip();
                                }
                                ImGui::Checkbox("Auto Connect", &set.auto_connect);

                            }
                            if (set.auto_connect && !set.connect)
                            {


                                set.connect = aimbot.Initialize();



                            }
                            aimbot.KmboxType = set.KmboxType;
                            strcpy(aimbot.KmboxIP, set.KmboxIP);
                            strcpy(aimbot.KmboxUUID, set.KmboxUUID);
                            strcpy(aimbot.KmboxPort, set.KmboxPort);
                            aimbot.KmboxComPort = set.KmboxComPort;
                            aimbot.connect = set.connect;

                            aimbot.width = set.width;
                            aimbot.height = set.height;

                            //aimbot.aim_tick = set.aim_tick;
                            //aimbot.Smoothing = set.Smoothing;
                            //aimbot.speed_X = set.speed_X;
                            //aimbot.speed_Y = set.speed_Y;

                            ImGui::EndChild();
                        }
                        break;
                        case 5:
                        {
                            ImGui::BeginChildPos("TRIGGERBOT SETTINGS", ImVec2(280 * dpi_scale, 460 * dpi_scale), true);
                            {
                                ImGui::SetWindowFontScale(dpi_scale);
                                ImGui::Checkbox("Trigger Toggle", &set.TriggerAimToggle);
                                if (ImGui::IsItemHovered()) {
                                    ImGui::BeginTooltip();
                                    ImGui::Text("THIS IS A WORK IN PROGRESS");
                                    ImGui::EndTooltip();
                                }
                                ImGui::Checkbox("Triggerbot Team Check", &set.aimbotteamcheck);
                                //ImGui::Checkbox("FOV Circle", &set.showfov);
                                //ImGui::Checkbox("Visible Check", &set.VisibleCheck);
                                ImGui::Keybind("TRIGGER Button [1]", &set.trigger_button1, true);
                                //if (ImGui::Combo("Bone Selection", &selectedIndex, Boneitems, IM_ARRAYSIZE(Boneitems)))
                                //{
                                //    set.aimbone = Bonevalues[selectedIndex];
                                //}
                                ImGui::SliderFloat("Shoot Delay", &set.shoot_delay, 0.0f, 0.05f);
                                //ImGui::SliderInt("Shoot Delay", &set.triggerbotovershootshots, 0.0f, 0.05f);
                            }
                            ImGui::EndChild();


                        }
                        break;
                        /*case 2:
                        {
                            ImGui::BeginChildPos("CONFIG SETTINGS", ImVec2(300 * dpi_scale, 550 * dpi_scale));
                            {
                                ImGui::SetWindowFontScale(dpi_scale);

                                if (ImGui::Button("SAVE CONFIG #1")) {
                                    set.saveSettings("config.json");
                                }
                                ImGui::SameLine(0, 35);
                                if (ImGui::Button("SAVE CONFIG #2")) {
                                    set.saveSettings("config2.json");
                                }
                                if (ImGui::Button("LOAD CONFIG #1")) {
                                    set.loadSettings("config.json");
                                }
                                ImGui::SameLine(0, 35);
                                if (ImGui::Button("LOAD CONFIG #2")) {
                                    set.loadSettings("config2.json");
                                }

                            }
                            ImGui::EndChild();
                        }
                        break;*/
                        }
                        ImGui::PopStyleColor(1);

                        ImGui::Spacing();

                        ImGui::EndChild();

                        ImGui::PopStyleColor(1);
                    }
                    //if (animated_background)
                        //Particles();
                    ImGui::PopStyleVar(1);

                }
                ImGui::End();

            }
           
            ImGui::Render(); 

            const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };

            g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);

            g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);

            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

            g_pSwapChain->Present(set.EnableVSync ? 1 : 0, 0);
        }
        catch (const std::exception& e)
        {
            std::cerr << "Exception in imgui_Star loop: " << e.what() << std::endl;
        }
        catch (...)
        {
            std::cerr << "Unknown exception in imgui_Star loop" << std::endl;
        }
    }

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
    mem.~Memory();

    return;
}


int main()
{

    std::cout << "\n [ > ] Looking for CS2.exe..." << std::endl;

    if (!mem.Init("cs2.exe", true, false))
    {
        std::cout << " [ ! ] Failed to find CS2.exe... closing...." << std::endl;
        Sleep(3000);
        exit(1);
    }
    std::cout << " [ > ] CS2.exe Found..." << std::endl;

    Sleep(30);
    Client_BASE = mem.GetBaseDaddy("client.dll");

    if (!mem.GetKeyboard()->InitKeyboard())
    {
        std::cout << " [ ! ] Keyboard not found Restart winlogon.exe on main pc" << std::endl;
        set.keyboardstate = false;
        std::cin.get();
    }
    else
    {
        std::cout << " [ > ] Keyboard Found..." << std::endl;
        set.keyboardstate = true;
    }

    // auto load config on startup
    set.loadSettings("config.json");

    

    std::thread UpData1_thr = std::thread(UpData2); // dma read types
    std::thread imgui_thr = std::thread(imgui_Star);
    std::thread WebRadar_thr = std::thread(web_radar); // radar thread
    

    UpData1_thr.join();

    imgui_thr.join();
    
    WebRadar_thr.join(); // radar thread start




}