#pragma once

const int ped_cs_bones_index_len = 125;
const int ped_cs_bones_index[125] = {
	0, //SKEL_ROOT
	11816, //SKEL_Pelvis
	58271, //SKEL_L_Thigh
	63931, //SKEL_L_Calf
	14201, //SKEL_L_Foot
	2108, //SKEL_L_Toe0
	//65245, //IK_L_Foot
	//57717, //PH_L_Foot
	46078, //MH_L_Knee
	51826, //SKEL_R_Thigh
	36864, //SKEL_R_Calf
	52301, //SKEL_R_Foot
	20781, //SKEL_R_Toe0
	//35502, //IK_R_Foot
	//24806, //PH_R_Foot
	16335, //MH_R_Knee
	23639, //RB_L_ThighRoll
	6442, //RB_R_ThighRoll
	57597, //SKEL_Spine_Root
	23553, //SKEL_Spine0
	24816, //SKEL_Spine1
	24817, //SKEL_Spine2
	24818, //SKEL_Spine3
	64729, //SKEL_L_Clavicle
	45509, //SKEL_L_UpperArm
	61163, //SKEL_L_Forearm
	18905, //SKEL_L_Hand
	26610, //SKEL_L_Finger00
	4089, //SKEL_L_Finger01
	4090, //SKEL_L_Finger02
	26611, //SKEL_L_Finger10
	4169, //SKEL_L_Finger11
	4170, //SKEL_L_Finger12
	26612, //SKEL_L_Finger20
	4185, //SKEL_L_Finger21
	4186, //SKEL_L_Finger22
	26613, //SKEL_L_Finger30
	4137, //SKEL_L_Finger31
	4138, //SKEL_L_Finger32
	26614, //SKEL_L_Finger40
	4153, //SKEL_L_Finger41
	4154, //SKEL_L_Finger42
	60309, //PH_L_Hand
	36029, //IK_L_Hand
	61007, //RB_L_ForeArmRoll
	5232, //RB_L_ArmRoll
	22711, //MH_L_Elbow
	10706, //SKEL_R_Clavicle
	40269, //SKEL_R_UpperArm
	28252, //SKEL_R_Forearm
	57005, //SKEL_R_Hand
	58866, //SKEL_R_Finger00
	64016, //SKEL_R_Finger01
	64017, //SKEL_R_Finger02
	58867, //SKEL_R_Finger10
	64096, //SKEL_R_Finger11
	64097, //SKEL_R_Finger12
	58868, //SKEL_R_Finger20
	64112, //SKEL_R_Finger21
	64113, //SKEL_R_Finger22
	58869, //SKEL_R_Finger30
	64064, //SKEL_R_Finger31
	64065, //SKEL_R_Finger32
	58870, //SKEL_R_Finger40
	64080, //SKEL_R_Finger41
	64081, //SKEL_R_Finger42
	28422, //PH_R_Hand
	6286, //IK_R_Hand
	43810, //RB_R_ForeArmRoll
	37119, //RB_R_ArmRoll
	2992, //MH_R_Elbow
	39317, //SKEL_Neck_1
	31086, //SKEL_Head
	//12844, //IK_Head
	65068, //FACIAL_facialRoot
	2849, //FACIAL_jaw
	46456, //FACIAL_chin
	19068, //FACIAL_tongueA
	19069, //FACIAL_tongueB
	29317, //FACIAL_lipLowerSDK
	55675, //FACIAL_lipLowerAnalog
	47585, //FACIAL_L_lipLowerSDK
	9290, //FACIAL_L_lipLowerAnalog
	41012, //FACIAL_R_lipLowerSDK
	49881, //FACIAL_R_lipLowerAnalog
	57434, //FACIAL_noseLower
	29474, //FACIAL_L_nostril
	31010, //FACIAL_R_nostril
	26887, //FACIAL_L_cheekLower
	62311, //FACIAL_R_cheekLower
	59307, //FACIAL_L_cheekInner
	29564, //FACIAL_R_cheekInner
	33121, //FACIAL_L_cheekOuter
	3378, //FACIAL_R_cheekOuter
	39308, //FACIAL_L_eyelidLower
	32735, //FACIAL_R_eyelidLower
	5956, //FACIAL_L_eyeball
	6468, //FACIAL_R_eyeball
	38849, //FACIAL_L_eyelidUpper
	32276, //FACIAL_R_eyelidUpper
	37761, //FACIAL_L_eyesackUpperOuter
	37857, //FACIAL_R_eyesackUpperOuter
	37400, //FACIAL_forehead
	2115, //FACIAL_L_foreheadInner
	3651, //FACIAL_R_foreheadInner
	16987, //FACIAL_L_foreheadMid
	10414, //FACIAL_R_foreheadMid
	36299, //FACIAL_L_foreheadOuter
	36811, //FACIAL_R_foreheadOuter
	6621, //FACIAL_L_ear
	4407, //FACIAL_R_ear
	2844, //FACIAL_L_lipCornerSDK
	58728, //FACIAL_L_lipCornerAnalog
	2876, //FACIAL_R_lipCornerSDK
	60942, //FACIAL_R_lipCornerAnalog
	6004, //FACIAL_lipUpperSDK
	57444, //FACIAL_lipUpperAnalog
	36656, //FACIAL_L_lipUpperSDK
	45519, //FACIAL_L_lipUpperAnalog
	30083, //FACIAL_R_lipUpperSDK
	20943, //FACIAL_R_lipUpperAnalog
	35731, //RB_Neck_1
	64654, //SPR_L_Breast
	34911, //SPR_R_Breast
	//56604, //IK_Root
};

//int ped_cs_bones_index_len = 317;
//int ped_cs_bones_index[317] = {
//	0x0000,
//	0x01BD,
//	0x01E1,
//	0x0684,
//	0x07BC,
//	0x0810,
//	0x083C,
//	0x0843,
//	0x08D6,
//	0x0937,
//	0x0991,
//	0x0AA6,
//	0x0B1C,
//	0x0B21,
//	0x0B3C,
//	0x0BB0,
//	0x0D32,
//	0x0E0A,
//	0x0E13,
//	0x0E43,
//	0x0FF9,
//	0x0FFA,
//	0x1013,
//	0x1029,
//	0x102A,
//	0x1039,
//	0x103A,
//	0x1049,
//	0x104A,
//	0x1059,
//	0x105A,
//	0x10A6,
//	0x1137,
//	0x140F,
//	0x1470,
//	0x14A5,
//	0x1675,
//	0x1704,
//	0x1744,
//	0x1774,
//	0x188E,
//	0x192A,
//	0x1944,
//	0x19DD,
//	0x1AF9,
//	0x1CD6,
//	0x1FB8,
//	0x20F1,
//	0x2127,
//	0x234E,
//	0x244A,
//	0x2659,
//	0x27B7,
//	0x2810,
//	0x2962,
//	0x29D2,
//	0x2A02,
//	0x2BBA,
//	0x2BF4,
//	0x2C53,
//	0x2C63,
//	0x2CAA,
//	0x2E28,
//	0x2F2A,
//	0x2FEE,
//	0x2FEF,
//	0x2FF0,
//	0x2FF1,
//	0x2FF2,
//	0x322C,
//	0x3322,
//	0x35EE,
//	0x35EF,
//	0x35F0,
//	0x35F1,
//	0x35F2,
//	0x35FF,
//	0x365F,
//	0x36FF,
//	0x3779,
//	0x37CE,
//	0x382E,
//	0x385C,
//	0x38BC,
//	0x3988,
//	0x3E48,
//	0x3E73,
//	0x3E8F,
//	0x3EB3,
//	0x3FCF,
//	0x4141,
//	0x414E,
//	0x414F,
//	0x4150,
//	0x4151,
//	0x4221,
//	0x4293,
//	0x4427,
//	0x457B,
//	0x4800,
//	0x49D9,
//	0x4A5E,
//	0x4A7C,
//	0x4A7D,
//	0x4A7E,
//	0x4A7F,
//	0x4A80,
//	0x4B41,
//	0x4CCF,
//	0x4D11,
//	0x5038,
//	0x507B,
//	0x509B,
//	0x512D,
//	0x51A3,
//	0x51CF,
//	0x51EA,
//	0x52A7,
//	0x54C3,
//	0x566A,
//	0x575F,
//	0x58B7,
//	0x593D,
//	0x593E,
//	0x593F,
//	0x5940,
//	0x599B,
//	0x599C,
//	0x5A90,
//	0x5ACA,
//	0x5C01,
//	0x5C57,
//	0x5DF0,
//	0x5FB8,
//	0x6005,
//	0x600D,
//	0x6031,
//	0x60E6,
//	0x60F0,
//	0x60F1,
//	0x60F2,
//	0x67F2,
//	0x67F3,
//	0x67F4,
//	0x67F5,
//	0x67F6,
//	0x67FA,
//	0x68FB,
//	0x6907,
//	0x69B8,
//	0x6A60,
//	0x6E5C,
//	0x6F06,
//	0x7226,
//	0x7285,
//	0x7322,
//	0x737C,
//	0x7583,
//	0x767C,
//	0x769C,
//	0x7704,
//	0x771B,
//	0x777B,
//	0x78A7,
//	0x78A8,
//	0x78A9,
//	0x7922,
//	0x796E,
//	0x7975,
//	0x7981,
//	0x7993,
//	0x79D5,
//	0x7BD0,
//	0x7C63,
//	0x7E14,
//	0x7FDF,
//	0x8031,
//	0x8161,
//	0x8172,
//	0x8242,
//	0x8959,
//	0x899A,
//	0x8A95,
//	0x8AAE,
//	0x8C53,
//	0x8C63,
//	0x8CBD,
//	0x8DCB,
//	0x8F30,
//	0x8FCB,
//	0x9000,
//	0x9035,
//	0x90FF,
//	0x9218,
//	0x92DC,
//	0x933C,
//	0x93D4,
//	0x9420,
//	0x95DD,
//	0x97C1,
//	0x98BC,
//	0x998C,
//	0x9995,
//	0x9ADA,
//	0x9B1F,
//	0x9BA3,
//	0x9C7A,
//	0x9D4D,
//	0x9E8F,
//	0x9FAE,
//	0xA034,
//	0xA04F,
//	0xA0CE,
//	0xA1C2,
//	0xA244,
//	0xA359,
//	0xA4DA,
//	0xA559,
//	0xAA5E,
//	0xAB22,
//	0xAB6D,
//	0xAD09,
//	0xAE1F,
//	0xAF15,
//	0xAF19,
//	0xAF79,
//	0xB013,
//	0xB115,
//	0xB1C5,
//	0xB1CF,
//	0xB334,
//	0xB3FE,
//	0xB578,
//	0xB836,
//	0xB9AA,
//	0xB9E1,
//	0xBBD4,
//	0xBBD5,
//	0xBBD6,
//	0xBE49,
//	0xC15F,
//	0xC2D9,
//	0xC597,
//	0xC5BB,
//	0xC5ED,
//	0xC664,
//	0xC67B,
//	0xC6DB,
//	0xC6E9,
//	0xC749,
//	0xC78A,
//	0xCA72,
//	0xCC4D,
//	0xCD78,
//	0xCEF3,
//	0xCF13,
//	0xD21F,
//	0xD341,
//	0xD541,
//	0xD61E,
//	0xD7F6,
//	0xD97B,
//	0xDA2D,
//	0xDD1C,
//	0xDD42,
//	0xDDF3,
//	0xDEAD,
//	0xE05A,
//	0xE064,
//	0xE0FD,
//	0xE175,
//	0xE18E,
//	0xE38F,
//	0xE39F,
//	0xE3FB,
//	0xE3FC,
//	0xE568,
//	0xE5F2,
//	0xE5F3,
//	0xE5F4,
//	0xE5F5,
//	0xE5F6,
//	0xE699,
//	0xE7AB,
//	0xE98F,
//	0xEB95,
//	0xEE0E,
//	0xEE4F,
//	0xEEEB,
//	0xEF4B,
//	0xF035,
//	0xF03B,
//	0xF092,
//	0xF151,
//	0xF25A,
//	0xF351,
//	0xF367,
//	0xF41B,
//	0xF5AF,
//	0xF7D6,
//	0xF9BB,
//	0xFA10,
//	0xFA11,
//	0xFA40,
//	0xFA41,
//	0xFA50,
//	0xFA51,
//	0xFA60,
//	0xFA61,
//	0xFA70,
//	0xFA71,
//	0xFB13,
//	0xFB26,
//	0xFCD9,
//	0xFE2C,
//	0xFE4C,
//	0xFEDD
//};