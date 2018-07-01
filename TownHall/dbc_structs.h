#ifndef DBC_STRUCTS_H
#define DBC_STRUCTS_H

struct MapRec {
	int ID;
	char* Directory;
	int PVP;
	int IsInMap;
	char* MapName_lang[8];
	int MapName_flag;
};

struct SoundCharacterMacroLinesRec {
	int ID;
	int Category;
	int Sex;
	int Race;
	int SoundID;
};

struct ChrRacesRec {
	int ID;
	int flags;
	int factionID;
	int MaleDisplayId;
	int FemaleDisplayId;
	char* ClientPrefix;
	float MountScale;
	int BaseLanguage;
	int creatureType;
	int LoginEffectSpellID;
	int CombatStunSpellID;
	int ResSicknessSpellID;
	int SplashSoundID;
	int startingTaxiNodes;
	char* clientFileString;
	int cinematicSequenceID;
	char* name_lang[8];
	int name_flag;
};

struct AreaMIDIAmbiencesRec {
	int ID;
	char* DaySequence;
	char* NightSequence;
	char* DLSFile;
	float volume;
};

struct SoundWaterTypeRec {
	int ID;
	int soundType;
	int soundSubtype;
	int SoundID;
};

struct SoundEntriesRec {
	int ID;
	int soundType;
	char* name;
	char* File[10];
	int Freq[10];
	char* DirectoryBase;
	float volumeFloat;
	float pitch;
	float pitchVariation;
	int priority;
	int channel;
	int flags;
	float minDistance;
	float maxDistance;
	float distanceCutoff;
	int EAXDef;
};

struct ZoneMusicRec {
	int ID;
	float VolumeFloat;
	char* MusicFile[2];
	int SilenceIntervalMin[2];
	int SilenceIntervalMax[2];
	int SegmentLength[2];
	int SegmentPlayMin[2];
	int SegmentPlayMax[2];
	int Sounds[2];
};

struct SheatheSoundLookupsRec {
	int ID;
	int classID;
	int subclassID;
	int material;
	int checkMaterial;
	int sheatheSound;
	int unsheatheSound;
};

struct SoundSamplePreferencesRec {
	int ID;
	float EAX1EffectLevel;
	int EAX2SampleDirect;
	int EAX2SampleDirectHF;
	int EAX2SampleRoom;
	int EAX2SampleRoomHF;
	float EAX2SampleObstruction;
	float EAX2SampleObstructionLFRatio;
	float EAX2SampleOcclusion;
	float EAX2SampleOcclusionLFRatio;
	float EAX2SampleOcclusionRoomRatio;
	float EAX2SampleRoomRolloff;
	float EAX2SampleAirAbsorption;
	int EAX2SampleOutsideVolumeHF;
	float EAX3SampleOcclusionDirectRatio;
	float EAX3SampleExclusion;
	float EAX3SampleExclusionLFRatio;
	float EAX3SampleDopplerFactor;
	float Fast2DPredelayTime;
	float Fast2DDamping;
	float Fast2DReverbTime;
};

struct WeaponSwingSounds2Rec {
	int ID;
	int SwingType;
	int Crit;
	int SoundID;
};

struct WeaponImpactSoundsRec {
	int ID;
	int WeaponSubClassID;
	int ParrySoundType;
	int impactSoundID[10];
	int critImpactSoundID[10];
};

struct MaterialRec {
	int materialID;
	int flags;
	int foleySoundID;
};


struct SoundProviderPreferencesRec {
	int ID;
	char* Description;
	int Flags;
	int EAXEnvironmentSelection;
	float EAXEffectVolume;
	float EAXDecayTime;
	float EAXDamping;
	float EAX2EnvironmentSize;
	float EAX2EnvironmentDiffusion;
	int EAX2Room;
	int EAX2RoomHF;
	float EAX2DecayHFRatio;
	int EAX2Reflections;
	float EAX2ReflectionsDelay;
	int EAX2Reverb;
	float EAX2ReverbDelay;
	float EAX2RoomRolloff;
	float EAX2AirAbsorption;
	int EAX3RoomLF;
	float EAX3DecayLFRatio;
	float EAX3EchoTime;
	float EAX3EchoDepth;
	float EAX3ModulationTime;
	float EAX3ModulationDepth;
	float EAX3HFReference;
	float EAX3LFReference;
};

struct VocalUISoundsRec {
	int ID;
	int vocalUIEnum;
	int raceID;
	int NormalSoundID[2];
	int PissedSoundID[2];
};

struct SpellRec
{
	unsigned long Id; // 1
	unsigned long School; // 2
	unsigned long Category; // 3
	unsigned long field4; // 4
	unsigned long DispelType; // 5
	unsigned long MechanicsType; // 6
	unsigned long Attributes; // 7
	unsigned long AttributesEx; // 8
	unsigned long Flags3; // 9
	unsigned long field10; // 10
	unsigned long field11; // 11
	unsigned long field12; // 12
	unsigned long field13; // 13
	unsigned long Targets; // 14
	unsigned long TargetCreatureType; // 15
	unsigned long RequiresSpellFocus; // 16
	unsigned long CasterAuraState; // 17
	unsigned long TargetAuraState; // 18

	// From here, TBC field numbers are 2 greater than stated
	unsigned long CastingTimeIndex; // 19
	unsigned long RecoveryTime; // 20
	unsigned long CategoryRecoveryTime; // 21
	unsigned long InterruptFlags; // 22
	unsigned long AuraInterruptFlags; // 23
	unsigned long ChannelInterruptFlags; // 24
	unsigned long procFlags; // 25
	unsigned long procChance; // 26
	unsigned long procCharges; // 27
	unsigned long maxLevel; // 28
	unsigned long baseLevel; // 29
	unsigned long spellLevel; // 30
	unsigned long DurationIndex; // 31
	unsigned long powerType; // 32
	unsigned long manaCost; // 33
	unsigned long manaCostPerlevel; // 34
	unsigned long manaPerSecond; // 35
	unsigned long manaPerSecondPerLevel; // 36
	unsigned long rangeIndex; // 37
	float speed; // 38
	unsigned long modalNextSpell; // 39
	unsigned long maxstack; // 40
	unsigned long Totem[2]; // 41-42
	unsigned long Reagent[8]; // 43-50
	unsigned long ReagentCount[8]; // 51-58
	unsigned long EquippedItemClass; // 59
	unsigned long EquippedItemSubClass; // 60
	unsigned long field61; // 61
	unsigned long Effect[3]; // 62-64
	unsigned long EffectDieSides[3]; // 65-67
	unsigned long EffectBaseDice[3]; // 68-70
	float EffectDicePerLevel[3]; // 71-73
	float EffectRealPointsPerLevel[3]; // 74-76
	unsigned long EffectBasePoints[3]; // 77-79
	unsigned long Effectunk190[3]; // 80-82
	unsigned long EffectImplicitTargetA[3]; // 83-85
	unsigned long EffectImplicitTargetB[3]; // 86-88
	unsigned long EffectRadiusIndex[3]; // 89-91
	unsigned long EffectApplyAuraName[3]; // 92-94
	unsigned long EffectAmplitude[3]; // 95-97
	float Effectunknown[3]; // 98-100
	unsigned long EffectChainTarget[3]; // 101-103
	unsigned long EffectSpellGroupRelation[3]; // 104-106 // not sure maybe we should rename it. its the relation to field: SpellGroupType
	unsigned long EffectMiscValue[3]; // 107-109
	unsigned long EffectTriggerSpell[3]; // 110-112
	float EffectPointsPerComboPoint[3]; // 113-115
	unsigned long SpellVisual; // 116
	unsigned long field117; // 117 // 0 for all spells but Sire's Suicide [ID 18184], where it is 749
	unsigned long SpellIconID; // 118
	unsigned long CoSpell; // 119 //             activeIconID;
	unsigned long spellPriority; // 120
	unsigned long Name; // 121
	unsigned long NameAlt1; // 122
	unsigned long NameAlt2; // 123
	unsigned long NameAlt3; // 124
	unsigned long NameAlt4; // 125
	unsigned long NameAlt5; // 126
	unsigned long NameAlt6; // 127
	unsigned long NameAlt7; // 128
	unsigned long NameFlags; // 129
	unsigned long Rank; // 130
	unsigned long RankAlt1; // 131
	unsigned long RankAlt2; // 132
	unsigned long RankAlt3; // 133
	unsigned long RankAlt4; // 134
	unsigned long RankAlt5; // 135
	unsigned long RankAlt6; // 136
	unsigned long RankAlt7; // 137
	unsigned long RankFlags; // 138
	unsigned long Description; // 139
	unsigned long DescriptionAlt1; // 140
	unsigned long DescriptionAlt2; // 141
	unsigned long DescriptionAlt3; // 142
	unsigned long DescriptionAlt4; // 143
	unsigned long DescriptionAlt5; // 144
	unsigned long DescriptionAlt6; // 145
	unsigned long DescriptionAlt7; // 146
	unsigned long DescriptionFlags; // 147
	unsigned long BuffDescription; // 148
	unsigned long BuffDescriptionAlt1; // 149
	unsigned long BuffDescriptionAlt2; // 150
	unsigned long BuffDescriptionAlt3; // 151
	unsigned long BuffDescriptionAlt4; // 152
	unsigned long BuffDescriptionAlt5; // 153
	unsigned long BuffDescriptionAlt6; // 154
	unsigned long BuffDescriptionAlt7; // 155
	unsigned long BuffDescriptionFlags; // 156
	unsigned long ManaCostPercentage; // 157
	unsigned long field158; // 158 // 0x0,0x4,0x3F,0x85,0x1FF; only 4 spells have values 0x4,0x3F, or 0x1FF
	unsigned long StartRecoveryTime; // 159
	unsigned long StartRecoveryCategory; // 160
	unsigned long SpellFamilyName; // 161
	unsigned long SpellGroupType; // 162 // flags
	unsigned long field163; // 163 // values 0,1,2,4,8
	unsigned long MaxTargets; // 164 // values 0,1,2,3,4,5,10,15,20; is this really Max Targets?
	unsigned long field165; // 165 // values 0,1,2,3
	unsigned long field166; // 166 // values 0,1,2
	unsigned long field167; // 167 // values -1,0,1,2,3,4,5,6,7; majority of spells have value -1 or 0
	float field168; // 168 // multiple float values; majority of spells (>99%) have value 1.0
	float field169; // 169 // 0.0, 1.0 or 10.0; only Super Shrink Ray, ID 22742, has value 10.0
	float field170; // 170 // 0.0 or 1.0
	unsigned long field171; // 171 // 0 for all spells except zzOLDFeinting Strike, ID 6994, where it is 369
	unsigned long field172; // 172 // 0 for all spells except zzOLDFeinting Strike, ID 6994, where it is 4
	unsigned long field173; // 173 // 0 for all spells except Amorous, ID 26869, where it is 1
};

struct ResistancesRec {
	int ID;
	int Flags;
	int FizzleSoundID;
	char* name_lang[8];
	int name_flag;
};

struct ItemDisplayInfoRec {
	int ID;
	char* modelName[2];
	char* modelTexture[2];
	char* inventoryIcon;
	char* groundModel;
	int geosetGroup[4];
	int flags;
	int spellVisualID;
	int groupSoundIndex;
	int itemSize;
	int helmetGeosetVisID;
	char* texture[8];
	int itemVisual;
};

struct TerrainTypeRec {
	int TerrainID;
	char* TerrainDesc;
	int FootstepSprayRun;
	int FootstepSprayWalk;
	int SoundID;
	int Flags;
	int generatedID;
};

struct TerrainTypeSoundsRec {
	int ID;
};

struct ItemGroupSoundsRec {
	int ID;
	int sound[4];
};

struct FootstepTerrainLookupRec {
	int ID;
	int CreatureFootstepID;
	int TerrainSoundID;
	int SoundID;
	int SoundIDSplash;
};

struct ChrClassesRec {
	int ID;
	int PlayerClass;
	int DamageBonusStat;
	int DisplayPower;
	char* petNameToken;
	char* name_lang[8];
	int name_flag;
};

struct AreaTableRec {
	int ID;
	int AreaNumber;
	int ContinentID;
	int ParentAreaNum;
	int AreaBit;
	int flags;
	int SoundProviderPref;
	int SoundProviderPrefUnderwater;
	int MIDIAmbience;
	int MIDIAmbienceUnderwater;
	int ZoneMusic;
	int IntroSound;
	int IntroPriority;
	char* AreaName_lang[8];
	int AreaName_flag;
};

struct CreatureDisplayInfoRec {
	int ID;
	int modelID;
	int soundID;
	int extendedDisplayInfoID;
	float creatureModelScale;
	int creatureModelAlpha;
	char* textureVariation[3];
	int bloodID;
};

struct CreatureModelDataRec {
	int ID;
	int flags;
	char* ModelName;
	int sizeClass;
	float modelScale;
	int bloodID;
	int footprintTextureID;
	float footprintTextureLength;
	float footprintTextureWidth;
	float footprintParticleScale;
	int foleyMaterialID;
	int footstepShakeSize;
	int deathThudShakeSize;
	int soundID;
};

struct CharacterCreateCamerasRec {
	int Race;
	int Sex;
	int Camera;
	float Height;
	float Radius;
	float Target;
	int generatedID;
};

struct FactionGroupRec {
	int ID;
	int maskID;
	char* internalName;
	char* name_lang[8];
	int name_flag;
};
struct FactionEntry
{
	int ID;
	int	reputationListID;
	int unk1;
	int unk2;
	int unk3;
	int unk4;
	int unk5;
	int unk6;
	int unk7;
	int something1;
	int something2;
	int something3;
	int something4;
	int something5;
	int something6;
	int something7;
	int something8;
	int something9;
	int faction;
	int name;
	int unk8;
	int unk9;
	int unk10;
	int unk11;
	int unk12;
	int unk13;
	int unk14;
	int unk15;
	int unk16;
	int unk17;
	int unk18;
	int unk19;
	int unk20;
	int unk21;
	int unk22;
	int unk23;
	int unk24;
};
struct FactionTemplateRec {
	int ID;
	int faction;
	int unk1;
	int fightsupport;
	int friendly;
	int hostile;
	int enemies1;
	int enemies2;
	int enemies3;
	int enemies4;
	int friends1;
	int friends2;
	int friends3;
	int friends4;
};

struct CharBaseInfoRec {
	unsigned char raceID;
	unsigned char classID;
	int proficiency;
	int generatedID;
};

struct CharStartOutfitRec {
	int ID;
	unsigned char raceID;
	unsigned char classID;
	unsigned char sexID;
	unsigned char outfitID;
	int ItemID[12];
	int DisplayItemID[12];
	int InventoryType[12];
};

struct ItemVisualEffectsRec {
	int ID;
	char* Model;
};

struct HelmetGeosetVisDataRec {
	int ID;
	int DefaultFlags[32];
	int PreferredFlags[32];
	int HideFlags[32];
};

struct ItemVisualsRec {
	int ID;
	int Slot[5];
};

struct CharVariationsRec {
	int RaceID;
	int SexID;
	int TextureHoldLayer[4];
	int generatedID;
};

struct CharacterFacialHairStylesRec {
	int RaceID;
	int SexID;
	int VariationID;
	int BeardGeoset;
	int MoustacheGeoset;
	int SideburnGeoset;
	int generatedID;
};

struct CharTextureVariationsV2Rec {
	int ID;
	int RaceID;
	int SexID;
	int SectionID;
	int VariationID;
	int ColorID;
	int IsNPC;
	char* TextureName;
};

struct CharHairGeosetsRec {
	int ID;
	int RaceID;
	int SexID;
	int VariationID;
	int GeosetID;
	int Showscalp;
};

struct SpellRadiusRec {
	int ID;
	float Radius;
	float unk1;
	float Radius2;
};

struct SpellDurationRec {
	int ID;
	int Duration1;
	int Duration2;
	int Duration3;
};

struct SpellRangeRec {
	int ID;
	float minRange;
	float Range;
	int unks[18];
};

struct PageTextMaterialRec {
	int ID;
	char* name;
};

struct SkillLineRec {
	int ID;
	int raceMask;
	int classMask;
	int excludeRace;
	int excludeClass;
	int categoryID;
	int skillType;
	int minCharLevel;
	int maxRank;
	int abandonable;
	char* displayName_lang[8];
	int displayName_flag;
};

struct ItemClassRec {
	int classID;
	int subclassMapID;
	int flags;
	char* className_lang[8];
	int className_flag;
	int generatedID;
};

struct ItemSubClassRec {
	int classID;
	int subClassID;
	int prerequisiteProficiency;
	int postrequisiteProficiency;
	int flags;
	int displayFlags;
	int weaponParrySeq;
	int weaponReadySeq;
	int weaponAttackSeq;
	int WeaponSwingSize;
	char* displayName_lang[8];
	int displayName_flag;
	char* verboseName_lang[8];
	int verboseName_flag;
	int generatedID;
};

struct SpellFocusObjectRec {
	int ID;
	char* name_lang[8];
	int name_flag;
};

struct BankBagSlotPricesRec {
	int ID;
	int Cost;
};

struct SpellIconRec {
	int ID;
	char* textureFilename;
};

struct FactionRec {
	int ID;
	int reputationIndex;
	int reputationRaceMask[4];
	int reputationClassMask[4];
	int reputationBase[4];
	char* name_lang[8];
	int name_flag;
};

struct ChrProficiencyRec {
	int ID;
	int proficiency_minLevel[16];
	int proficiency_acquireMethod[16];
	int proficiency_itemClass[16];
	int proficiency_itemSubClassMask[16];
};

struct PaperDollItemFrameRec {
	char* ItemButtonName;
	char* SlotIcon;
	int SlotNumber;
	int generatedID;
};

struct SpellShapeshiftFormRec {
	int ID;
	int bonusActionBar;
	char* name_lang[8];
	int name_flag;
	int flags;
};

struct TaxiNodesRec {
	long ID;
	long ContinentID;
	float X;
	float Y;
	float Z;
	char* Name_Lang[4];
	long unk1; // 1-7 are empty
	long unk2;
	long unk3;
	long unk4;
	long unk5;
	long unk6;
	long unk7;
	long unk8;
	long unk9;
	long unk10;
};

struct QuestSortRec {
	int ID;
	char* SortName_lang[8];
	int SortName_flag;
};

struct QuestInfoRec {
	int ID;
	char* InfoName_lang[8];
	int InfoName_flag;
};

struct SpellCastTimesRec {
	int ID;
	int base;
	int perLevel;
	int minimum;
};

struct SpellItemEnchantmentRec {
	int ID;
	int effect[3];
	int effectPointsMin[3];
	int effectPointsMax[3];
	int effectArg[3];
	char* name_lang[8];
	int name_flag;
	int itemVisual;
};

struct AreaPOIRec {
	int ID;
	int importance;
	int icon;
	int factionID;
	float x;
	float y;
	float z;
	int continentID;
	int flags;
	char* name_lang[8];
	int name_flag;
};

struct WorldMapAreaRec {
	int ID;
	int mapID;
	int areaID;
	int leftBoundary;
	int rightBoundary;
	int topBoundary;
	int bottomBoundary;
	char* areaName;
};

struct WorldMapContinentRec {
	int ID;
	int mapID;
	int leftBoundary;
	int rightBoundary;
	int topBoundary;
	int bottomBoundary;
	float continentOffsetX;
	float continentOffsetY;
};

struct WorldSafeLocsRec {
	int ID;
	int continent;
	float locX;
	float locY;
	float locZ;
	char* AreaName_lang[8];
	int AreaName_flag;
};

struct LanguagesRec {
	int ID;
	char* name_lang[8];
	int name_flag;
};

struct LanguageWordsRec {
	int ID;
	int languageID;
	char* word;
};

struct EmotesTextRec {
	int ID;
	char* name;
	int emoteID;
	int emoteText[16];
};

struct EmotesTextDataRec {
	int ID;
	char* text_lang[8];
	int text_flag;
};

struct CinematicCameraRec {
	int ID;
	char* model;
	int soundID;
	float originX;
	float originY;
	float originZ;
	float originFacing;
};

struct CinematicSequencesRec {
	int ID;
	int soundID;
	int camera[8];
};

struct CameraShakesRec {
	int ID;
	int shakeType;
	int direction;
	float amplitude;
	float frequency;
	float duration;
	float phase;
	float coefficient;
};

struct SpellEffectNamesRec {
	int EnumID;
	char* name_lang[8];
	int name_flag;
	int generatedID;
};

struct SpellAuraNamesRec {
	int EnumID;
	int specialMiscValue;
	char* globalstrings_tag;
	char* name_lang[8];
	int name_flag;
	int generatedID;
};

struct SpellDispelTypeRec {
	int ID;
	char* name_lang[8];
	int name_flag;
};

struct CreatureTypeRec {
	int ID;
	char* name_lang[8];
	int name_flag;
};

struct LockRec {
	int ID;
	int Type[4];
	int Index[4];
	int Skill[4];
	int Action[4];
};

struct LockTypeRec {
	int ID;
	char* name_lang[8];
	int name_flag;
	char* resourceName_lang[8];
	int resourceName_flag;
	char* verb_lang[8];
	int verb_flag;
};

struct WMOAreaTableRec {
	int ID;
	int WMOID;
	int NameSetID;
	int WMOGroupID;
	int DayAmbienceSoundID;
	int NightAmbienceSoundID;
	int SoundProviderPref;
	int SoundProviderPrefUnderwater;
	int MIDIAmbience;
	int MIDIAmbienceUnderwater;
	int ZoneMusic;
	int IntroSound;
	int IntroPriority;
	int Flags;
	char* AreaName_lang[8];
	int AreaName_flag;
};

struct NPCSoundsRec {
	int ID;
	int SoundID[4];
};

struct StringLookupsRec {
	int ID;
	char* String;
};

struct SkillLineAbilityRec {
	int ID;
	int skillLine;
	int spell;
	int raceMask;
	int classMask;
	int excludeRace;
	int excludeClass;
	int minSkillLineRank;
	int supercedhedBySpell;
	int trivialSkillLineRankHigh;
	int trivialSkillLineRankLow;
	int abandonable;
};

struct SpellChainEffectsRec {
	int ID;
	float AvgSegLen;
	float Width;
	float NoiseScale;
	float TexCoordScale;
	int SegDuration;
	int SegDelay;
	char* Texture;
};

struct GameObjectDisplayInfoRec {
	int ID;
	char* modelName;
	int Sound[10];
};

struct GroundEffectTextureRec {
	int ID;
	int datestamp;
	int continentId;
	int zoneId;
	int textureId;
	char* textureName;
	int doodadId[4];
	int density;
	int sound;
};

struct EmotesRec {
	int ID;
	int EmoteAnimID;
	int EmoteFlags;
	int EmoteSpecProc;
	int EmoteSpecProcParam;
};

struct UnitBloodRec {
	int ID;
	int CombatBloodSpurtFront[2];
	int CombatBloodSpurtBack[2];
	char* GroundBlood[5];
};

struct UISoundLookupsRec {
	int ID;
	int SoundID;
	char* SoundName;
};

struct GroundEffectDoodadRec {
	int ID;
	int doodadIdTag;
	char* doodadpath;
};

struct UnitBloodLevelsRec {
	int ID;
	int Violencelevel[3];
};

struct NamesProfanityRec {
	int ID;
	char* Name;
};

struct NamesReservedRec {
	int ID;
	char* Name;
};

struct AreaTriggerRec {
	int ID;
	int ContinentID;
	float x;
	float y;
	float z;
	float radius;
};

struct EmoteAnimsRec {
	int ID;
	int ProcessedAnimIndex;
	char* AnimName;
};

struct CreatureDisplayInfoExtraRec {
	int ID;
	int DisplayRaceID;
	int DisplaySexID;
	int SkinID;
	int FaceID;
	int HairStyleID;
	int HairColorID;
	int FacialHairID;
	int NPCItemDisplay[10];
	char* BakeName;
};

struct SpellVisualAnimNameRec {
	int AnimID;
	char* name;
	int generatedID;
};

struct CreatureFamilyRec {
	int ID;
	float minScale;
	int minScaleLevel;
	float maxScale;
	int maxScaleLevel;
	int skillLine[2];
};

struct SpellVisualRec {
	int ID;
	int precastKit;
	int castKit;
	int impactKit;
	int stateKit;
	int channelKit;
	int hasMissile;
	int missileModel;
	int missilePathType;
	int missileDestinationAttachment;
	int missileSound;
	int hasAreaEffect;
	int areaModel;
	int areaKit;
	int animEventSoundID;
	unsigned char weaponTrailRed;
	unsigned char weaponTrailGreen;
	unsigned char weaponTrailBlue;
	unsigned char weaponTrailAlpha;
	unsigned char weaponTrailFadeoutRate;
	int weaponTrailDuration;
};

struct SpellVisualPrecastTransitionsRec {
	int ID;
	char* PrecastLoadAnimName;
	char* PrecastHoldAnimName;
};

struct TaxiPathRec {
	int ID;
	int FromTaxiNode;
	int ToTaxiNode;
	int Cost;
};

struct SpellVisualEffectNameRec {
	int ID;
	char* fileName;
	int specialID;
	int specialAttachPoint;
	float areaEffectSize;
	int VisualEffectNameFlags;
};

struct TransportAnimationRec {
	int ID;
	int TransportID;
	int TimeIndex;
	float PosX;
	float PosY;
	float PosZ;
};

struct TabardBackgroundTexturesRec {
	int ID;
	char* TorsoTexture[2];
};

struct FootprintTexturesRec {
	int ID;
	char* FootstepFilename;
};

struct TaxiPathNodeRec {
	long id;
	long path;
	long seq;
	long mapid;
	float x;
	float y;
	float z;
	long unk1;
	long waittime;
};

struct CreatureSoundDataRec {
	int ID;
	int soundExertionID;
	int soundExertionCriticalID;
	int soundInjuryID;
	int soundInjuryCriticalID;
	int soundInjuryCrushingBlowID;
	int soundDeathID;
	int soundStunID;
	int soundStandID;
	int soundFootstepID;
	int soundAggroID;
	int soundWingFlapID;
	int soundWingGlideID;
	int soundAlertID;
	int soundFidget[4];
	int customAttack[4];
	int NPCSoundID;
	int loopSoundID;
	int creatureImpactType;
	int soundJumpStartID;
	int soundJumpEndID;
};

struct SpellVisualKitRec {
	int ID;
	int kitType;
	int anim;
	int headEffect;
	int chestEffect;
	int baseEffect;
	int leftHandEffect;
	int rightHandEffect;
	int breathEffect;
	int specialEffect[3];
	int characterProcedure;
	float characterParam[4];
	int soundID;
	int shakeID;
};

struct TabardEmblemTexturesRec {
	int ID;
	char* TorsoTexture[2];
};

struct AttackAnimTypesRec {
	int AnimID;
	char* AnimName;
};

struct DeathThudLookupsRec {
	int ID;
	int SizeClass;
	int TerrainTypeSoundID;
	int SoundEntryID;
	int SoundEntryIDWater;
};

struct SpellEffectCameraShakesRec {
	int ID;
	int CameraShake[3];
};

struct AttackAnimKitsRec {
	int ID;
	int ItemSubclassID;
	int AnimTypeID;
	int AnimFrequency;
	int WhichHand;
};

struct VideoHardwareRec {
	int vendorID;
	int deviceID;
	int farclipIdx;
	int terrainLODDistIdx;
	int terrainShadowLOD;
	int detailDoodadDensityIdx;
	int detailDoodadAlpha;
	int animatingDoodadIdx;
	int trilinear;
	int numLights;
	int specularity;
	int waterLODIdx;
	int particleDensityIdx;
	int unitDrawDistIdx;
	int smallCullDistIdx;
	int resolutionIdx;
	int baseMipLevel;
	int oglPixelShader;
	int d3dPixelShader;
	int generatedID;
};

struct TalentRec
{
	int TalentID;
	int TalentTree;
	int unk1;
	int unk2;
	int RankID[5];
	int unk[12];
};

struct WorldMapArea
{
	unsigned long ID;
	unsigned long mapId;
	unsigned long zoneId;
	unsigned long zoneName;
	float	y1;
	float	y2;
	float	x1;
	float	x2;
};

struct AreaTableEntry
{
	unsigned long ID;
	unsigned long map;
	unsigned long zone;
	unsigned long exploreFlag;
	unsigned long zone_type;
    long area_level;
	unsigned long unk3;
	unsigned long unk4;
	unsigned long unk5;
	unsigned long unk6;
	unsigned long unk7;
	unsigned long name;
	unsigned long unk8;
	unsigned long unk9;
	unsigned long unk10;
	unsigned long unk11;
	unsigned long unk12;
	unsigned long unk13;
	unsigned long unk14;
	unsigned long unk15;
	unsigned long unk16;
};

struct WorldMapOverlayEntry
{
	unsigned long ID;
	unsigned long worldMapAreaID;
	unsigned long areaTableID;
	unsigned long unk1;
	unsigned long unk2;
	unsigned long unk3;
	unsigned long unk4;
	unsigned long unk5;
	unsigned long name;
	unsigned long areaW; //in pixels 2x
	unsigned long areaH; //in pixels 2x
	unsigned long unk6;  //I think columns #12, #13, #14 and #15
	unsigned long unk7;  //are some kind of positions, but i did not
	unsigned long unk8;  //discover what exactly.
	unsigned long unk9;
	unsigned long drawX; //in pixels
	unsigned long drawY; //in pixels
};

#endif // DBC_STRUCTS_H
