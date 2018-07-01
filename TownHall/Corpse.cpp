#include "Corpse.h"
#include "Defines.h"
#include "Globals.h"
#include "UpdateBlock.h"
#include "Player.h"
#include "Item.h"
#include "Packets.h"

CCorpse::CCorpse(void):CWoWObject(OBJ_CORPSE), CUpdateObject(CORPSE_END)
{

}

CCorpse::~CCorpse(void)
{
	Delete();
}

void CCorpse::Clear()
{
	CWoWObject::Clear();
	memset(&Data,0,sizeof(CorpseData));
	memset(Items,0,120*sizeof(CItem*));
}

void CCorpse::Delete()
{
	CPacket pkg(SMSG_DESTROY_OBJECT);
	pkg << guid;
	pkg << CORPSEGUID_HIGH;
	SendRegion(&pkg);

	RegionManager.ObjectRemove(*this);
	CWoWObject::Delete();
}

void CCorpse::New()
{
	Clear();
	CWoWObject::New();
	EventsEligible=true;
}

unsigned long CCorpse::GetCorpseInfoData(char *buffer, bool Create)
{
#define Add(datatype,data) *(datatype*)&buffer[c]=data;c+=sizeof(datatype);
#define Skip(n) c+=n;
#define Fill(size,value) memset(&buffer[c],value,size);c+=size;
	unsigned long c=0;
	// HEADER
	Skip(Packets::PackGuidBuffer(buffer,guid,CORPSEGUID_HIGH));
	Add(unsigned char, ID_CORPSE);
	if(Create)
	{
		Add(unsigned char, 0x52);
		Add(_Location, Data.Loc);
		Add(float, Data.Facing);
		Add(unsigned long, 0x6297848C);
		Add(unsigned long, 0xBD38BA14);
	}

#undef Fill
#undef Add
#undef Skip

	CUpdateBlock block(&buffer[c], CORPSE_END);

	block.Add(OBJECT_FIELD_GUID, guid, CORPSEGUID_HIGH);
	block.Add(OBJECT_FIELD_TYPE, HIER_TYPE_CORPSE);
	block.Add(OBJECT_FIELD_SCALE_X, 1.0f);
	block.Add(CORPSE_FIELD_OWNER, Data.Owner, PLAYERGUID_HIGH);
	block.Add(CORPSE_FIELD_FACING,Data.Facing);
	block.Add(CORPSE_FIELD_POS_X,Data.Loc.X);
	block.Add(CORPSE_FIELD_POS_Y,Data.Loc.Y);
	block.Add(CORPSE_FIELD_POS_Z,Data.Loc.Z);
	block.Add(CORPSE_FIELD_DISPLAY_ID, Data.Model);

	// add visible items
	for(short i = 0; i < 19; i++)
	{
		if (CItem *pItem = Items[i])
		{
			/*
			iDisplayID = m_items[i]->GetProto()->DisplayInfoID;
			iIventoryType = (uint16)m_items[i]->GetProto()->InventoryType;

			_cfi =  (uint16(iDisplayID)) | (iIventoryType)<< 24;
			pCorpse->SetUInt32Value(CORPSE_FIELD_ITEM + i,_cfi);
			*/
			block.Add(CORPSE_FIELD_ITEM + i,(pItem->Data.nItemTemplate) | (i) << 24);
		}
	}

	block.Add(CORPSE_FIELD_BYTES_1, (0x00) | (Data.Race << 8) | (Data.Gender << 16) | (Data.Appearance[0] << 24));
	block.Add(CORPSE_FIELD_BYTES_2, (Data.Appearance[1]) | (Data.Appearance[2] << 8) | (Data.Appearance[3] << 16) | (Data.Appearance[4] << 24));
	block.Add(CORPSE_FIELD_FLAGS,4);
	return block.GetSize() + c;
}

void CCorpse::SpawnBones()
{
	AddUpdateVal(CORPSE_FIELD_FLAGS,5);

	// Remove all items
	for(int i = 0; i < 19; i++)
	{
		if (Items[i])
		{
			AddUpdateVal(CORPSE_FIELD_ITEM + i,0);
		}
	}

	UpdateObject();

	// Leave the bones ingame for 10 minutes
	EventManager.AddEvent(*this,600000,EVENT_CORPSE_DESTROY,0,0);
}

void CCorpse::ProcessEvent(WoWEvent &Event)
{
	switch(Event.EventType)
	{
	case EVENT_CORPSE_DESTROY:
		{
			Delete();
		}
	}
}

void CCorpse::SendRegion(IPacket *pkg)
{
	CRegion *pCorpseRegion=RegionManager.ObjectRegions[guid];
	if (!pCorpseRegion)
		return;

	for (int i = 0 ; i < 3 ; i++)
		for (int j = 0 ; j < 3 ; j++)
		{
			if (CRegion *pRegion=pCorpseRegion->Adjacent[i][j])
			{
				RegionObjectNode *pNode=pRegion->pList;
				while(pNode)
				{
					if(pNode->pObject->type == OBJ_PLAYER && ((CPlayer*)pNode->pObject)->pClient)
						((CPlayer*)pNode->pObject)->pClient->Send(pkg);
					pNode=pNode->pNext;
				}
			}
		}
}
