// --- Author : Moreau Cyril - Spl3en
#pragma once

// ---------- Includes ------------
#include "Utils/Utils.h"
#include "./HudChat/HudChat.h"

// ---------- Defines -------------


// ------ Structure declaration -------

#pragma pack(push, 1)
typedef struct _PlayerHUD
{
	int field_0;
	char gap_4[108];
	int field_1;
	int field_3;
	char gap_78[12];
	__int16 field_5;
	char gap_86[2];
	int field_6;
	int field_7;
	int field_8;
	int field_9;
	int field_10;
	int field_11;
	int field_12;
	int field_13;
	int field_14;
	int field_15;
	int field_16;
	int field_17;
	int field_18;
	int field_19;
	int field_20;
	int field_21;
	int field_22;
	int field_23;
	int field_24;
	int field_25;
	int field_26;
	int field_27;
	int field_28;
	int field_29;
	int field_30;
	int field_31;
	int field_32;
	__int16 field_33;
	char gap_F6[2];
	int field_34;
	int field_35;
	int field_36;
	int field_37;
	int field_38;
	int field_39;
	HudChat *hudChat;
	int field_41;
	int field_42;
	int field_43;
	int field_44;
	int field_45;
	int field_46;
	int field_47;
	int field_48;
	int field_49;
	int field_50;
	int field_51;
	char gap_140[4];
	int field_52;
	int field_53;
	int field_54;
	int field_55;
	int field_56;
	int field_57;
	int field_58;
	char gap_160[32];
	int field_59;
	int field_60;
	int field_61;
	int field_62;
	int field_63;
	int field_64;
	int field_65;
	int field_66;
	int field_67;
	int field_68;
	int field_69;
	int field_70;
	char field_71;
	char gap_1B1[3];
	int field_72;
	int field_73;
	int field_74;
	int field_75;
	int field_76;
	char gap_1C8[4];
	char field_77;
	char gap_1CD[15];
	int field_78;
	int field_79;
	char gap_1E4[4];
	__int16 field_80;
	char gap_1EA[1];
	char field_81;
	char gap_1EC[4];
	int field_82;
	int field_83;
	int field_84;
	int field_85;
	int field_86;
	int field_87;
	int field_88;
	int field_89;
	int field_90;
	int field_91;
	char field_92;
	char gap_219[3];
	int field_93;
	char gap_220[8];
	int field_94;
	int field_95;
	char gap_230[4];
	int field_96;
	int field_97;
	char field_98;
	char gap_23D[3];
	char field_99;
	char gap_241[15];
	int field_100;
	int field_101;
	int field_102;
	int field_103;
	int field_104;
	__int16 field_105;
	char gap_266[2];
	int field_106;
	int field_107;
	int field_109;

	DWORD pThis;

} 	PlayerHUD;
#pragma pack(pop)



// --------- Allocators ---------
/*
 * Description 	: Allocate a new PlayerHUD structure.
 * DWORD baseAddress : Base address of the module
 * DWORD sizeOfModule : Size of the module
 * Return		: A pointer to an allocated PlayerHUD.
 */
PlayerHUD *
PlayerHUD_new (
	DWORD baseAddress,
	DWORD sizeOfModule
);

// ----------- Functions ------------

/*
 * Description : Initialize an allocated PlayerHUD structure.
 * PlayerHUD *this : An allocated PlayerHUD to initialize.
 * DWORD baseAddress : Base address of the module
 * DWORD sizeOfModule : Size of the module
 */
bool
PlayerHUD_init (
	PlayerHUD *this,
	DWORD baseAddress,
	DWORD sizeOfModule
);

/*
 * Description : Unit tests checking if a PlayerHUD is coherent
 * PlayerHUD *this : The instance to test
 * Return : true on success, false on failure
 */
bool
PlayerHUD_test (
	PlayerHUD *this
);

// --------- Destructors ----------

/*
 * Description : Free an allocated PlayerHUD structure.
 * PlayerHUD *this : An allocated PlayerHUD to free.
 */
void
PlayerHUD_free (
	PlayerHUD *this
);


