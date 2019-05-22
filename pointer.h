#pragma once
int p_base = 0x0114A860;
int o_health = 0xF8;
int o_amour = 0xFC;
int o_speed = 0x80; // 1 = Normal - 10 = fastest
int o_crouch = 0x5C; //3.375 = Crouch - 4.5 = Stand
int o_height = 0xC;
int o_jump = 0x3C;
int o_name = 0x225; //String

//Ammo Offsets
int o_ar = 0x150;
int o_ar_extra_mag = 0x128;
int o_pistol_ammo = 0x13C;
int o_pistol_extra_mag = 0x114;
int o_grenade = 0x158;
int o_akimbo_enable = 0x10C; // 0 = Disabled - 1 = Enabled
int o_akimbo_ammo = 0x15C;
int o_akimbo_extra_mag = 0x134;