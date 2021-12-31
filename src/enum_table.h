/* Copyright © 2008-2022 Pioneer Developers. See AUTHORS.txt for details */
/* Licensed under the terms of the GPL v3. See licenses/GPL-3.txt        */

#ifndef HX_GEN_ENUM_TABLES
#define HX_GEN_ENUM_TABLES

/* THIS FILE IS AUTO-GENERATED, CHANGES WILL BE OVERWRITTEN */
/* enum table generated by scan_enums.py */

struct EnumItem {
	const char *name;
	int value;
};
struct EnumTable {
	const char *name;
	const EnumItem *first;
};

extern const struct EnumItem ENUM_PhysicsObjectType[];
extern const struct EnumItem ENUM_ShipAIError[];
extern const struct EnumItem ENUM_ShipFlightState[];
extern const struct EnumItem ENUM_ShipJumpStatus[];
extern const struct EnumItem ENUM_ShipAlertStatus[];
extern const struct EnumItem ENUM_ShipAICmdName[];
extern const struct EnumItem ENUM_DualLaserOrientation[];
extern const struct EnumItem ENUM_ShipTypeTag[];
extern const struct EnumItem ENUM_DockingRefusedReason[];
extern const struct EnumItem ENUM_ProjectableTypes[];
extern const struct EnumItem ENUM_ProjectableBases[];
extern const struct EnumItem ENUM_SystemViewColorIndex[];
extern const struct EnumItem ENUM_PolitEcon[];
extern const struct EnumItem ENUM_PolitGovType[];
extern const struct EnumItem ENUM_BodyType[];
extern const struct EnumItem ENUM_BodySuperType[];
extern const struct EnumItem ENUM_DetailLevel[];
extern const struct EnumItem ENUM_FileSystemRoot[];
extern const struct EnumItem ENUM_PiGuiFaceFlags[];
extern const struct EnumItem ENUM_ModelDebugFlags[];
extern const struct EnumItem ENUM_ShipTypeThruster[];
extern const struct EnumItem ENUM_PropulsionFuelStatus[];
extern const struct EnumItem ENUM_ShipControllerFlightControlState[];

extern const struct EnumTable ENUM_TABLES[];
extern const struct EnumTable ENUM_TABLES_PUBLIC[];

#endif
