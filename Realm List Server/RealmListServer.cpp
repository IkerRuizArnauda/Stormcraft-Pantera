#include "stdafx.h"   
#include "RealmListServer.h"   
#include <vector>   

#include <sstream>
#include <algorithm>   
#include "BigNumber.h"   
#include "Sha1.h"   
#include "Debug.h"   
#include "Accounts.h"   
#include "antidebuggers.h"   
using namespace std;
#define AUTO_ACCOUNT   
#ifdef WIN32   
#include "Realm List Server.h"   
#include "Realm List ServerDlg.h"   
#endif   

typedef unsigned long        uint32;
typedef unsigned short       uint16;
typedef unsigned char        uint8;
extern CAccount *LoadAccount(const char *name, bool createflag = true);

struct RealmListClient
{
	SOCKET sock;
	time_t lastActive;
	//authentication stuff   
	bool authed;
	BigNumber N, s, g, v, b, B, rs, K;
	std::string login;
};
#pragma pack(push, 1) //align on 1-byte boundaries to make packets read properly   
typedef struct {
	uint8   cmd;
	uint8   error;          // 0x00   
	uint16  size;           // 0x0026   
	uint8   gamename[4];    // 'WoW'   
	uint8   version1;       // 0x00   
	uint8   version2;       // 0x08 (0.8.0)   
	uint8   version3;       // 0x00   
	uint16  build;          // 3734   
	uint8   platform[4];    // 'x86'   
	uint8   os[4];          // 'Win'   
	uint8   country[4];     // 'enUS'   
	uint32  timezone_bias;  // -419   
	uint32  ip;             // client ip   
	uint8   I_len;          // length of account name   
	uint8   I[1];           // account name   
} sAuthLogonChallenge_C;

typedef sAuthLogonChallenge_C sAuthReconnectChallenge_C;

typedef struct {
	uint8   cmd;            // 0x00 CMD_AUTH_LOGON_CHALLENGE   
	uint8   error;          // 0 - ok   
	uint8   unk2;           // 0x00   
	uint8   B[32];
	uint8   g_len;          // 0x01   
	uint8   g[1];
	uint8   N_len;          // 0x20   
	uint8   N[32];
	uint8   s[32];
	uint8   unk3[16];
} sAuthLogonChallenge_S;

typedef struct {
	uint8   cmd; // 0x01   
	uint8   A[32];
	uint8   M1[20];
	uint8   crc_hash[20];
	uint8   number_of_keys;
	uint8   unk;
} sAuthLogonProof_C;

typedef struct {
	uint16  unk1;
	uint32  unk2;
	uint8   unk3[4];
	uint16  unk4[20];       // sha1(A,g,?)   
}  sAuthLogonProofKey_C;

typedef struct {
	uint8   cmd;            // 0x01 CMD_AUTH_LOGON_PROOF   
	uint8   error;
	uint8   M2[20];
	uint32  unk2;
	uint16  unk3;
} sAuthLogonProof_S;
#pragma pack(pop) //reset alignment   

THREAD WINAPI RealmListServerThreadFunction(LPVOID pParam)
{
	CThread *pThread = (CThread*)pParam;
	CLock L(&pThread->Threading, true);
	pThread->bThreading = true;
	pThread->ThreadReady = true;
	CRealmListServer *pServer = (CRealmListServer*)pThread->Info;

	//TCPSocket nextclient;   
	char pkg0[5] = { 0x03, 0x00, 0x00, 0x00, 0x00 };
	char pkg2[34] = { 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	char pkg3[2] = { 0x03, 0x00 };

	char buffer[2048];
	char FullList[20480];
	Addr From;
	time_t LastCleanup = time(0);
	vector<RealmListClient> clients;
	TCPSocket aSock;
	RealmListClient aClient;
	int UpdateCounter = 0;

	CDebug logfile;
	logfile.Initialize("RLPktLog.txt");

	while (!pThread->CloseThread)
	{
		DETECT_DEBUG
			if (clients.size() < 100)
			{
				int N = 0;
				// try to get a few new clients   
				aSock.m_hSocket = INVALID_SOCKET;
				if (pServer->ListListener.Accept(aSock))
				{
					do
					{
						aClient.lastActive = time(0);
						aClient.sock = aSock.m_hSocket;
						clients.push_back(aClient);
						aSock.m_hSocket = INVALID_SOCKET;
						N++;
					} while (N < 5 && pServer->ListListener.Accept(aSock));
				}
			}

		unsigned char TotalSent;
		unsigned long Pos;
		unsigned short alen;
		unsigned long Temp;
		unsigned long len_send = 0;

		TotalSent = 0;
		Pos = 8;
		memset(FullList, 0, 20480);

		for (unsigned long i = 0; i < pServer->Realms.Size; i++)
		{
			if (RealmInfo *pRealm = pServer->Realms[i])
			{
				if (pRealm->Active)
				{
					Temp = pServer->ShowRealm(*pRealm, TotalSent + 1, &FullList[Pos]);
					TotalSent++;
					if (TotalSent >= 250)
						break;
					Pos += Temp;
				}
			}
		}

		//#if defined(WIN32) && defined(NDEBUG)   
		UpdateCounter++;
		if (UpdateCounter >= 80 && dlg)
		{
			UpdateCounter = 0;
			char temp[100];
			sprintf(temp, "Connected to %i Townhall%c", TotalSent, (TotalSent == 1) ? '\x00' : 's');
			dlg->m_Connected.SetWindowText(temp);
		}
		//#endif   

		FullList[Pos++] = 0x01;
		FullList[Pos++] = 0x00;

		FullList[0] = 0x10; // REALMLIST opcode   
		alen = (unsigned short)(Pos - 3);
		*(unsigned short*)&FullList[1] = alen;
		// request code   
		unsigned long request = 0;
		*(unsigned char*)&FullList[3] = 0;

		FullList[4] = 0x01;
		FullList[5] = 0x00;
		FullList[6] = 0x00;

		FullList[7] = TotalSent;

		vector<RealmListClient> tmplist = clients;
		clients.clear();
		// process current clients   
		for (vector<RealmListClient>::iterator iter = tmplist.begin(); iter != tmplist.end(); iter++)
		{
			aSock.m_hSocket = iter->sock;
			long dataLen;
			if (dataLen = aSock.isData())
			{
				if (dataLen > 2048 || aSock.Receive(&buffer[0], dataLen) != dataLen) {
					OutputDebugString("Removing client...\n");
					aSock.Close();
					logfile.Log("Error");
					iter->sock = INVALID_SOCKET;
					//  clients.erase(iter);   
					continue;
				}
				// handle packets   
				switch (buffer[0]) // pkgID   
				{
				case 0: //AUTH_LOGON_CHALLENGE   
					iter->lastActive = time(0);
					if (1) {
						sAuthLogonChallenge_C *ch = (sAuthLogonChallenge_C*)buffer;
						logfile.LogBuffer(buffer, sizeof(sAuthLogonChallenge_C) + ch->I_len - 1, "sAuthLogonChallenge_C Buffer");
						buffer[sizeof(sAuthLogonChallenge_C) + ch->I_len - 1] = 0; //null-terminate user string   

						char pkt[2048]; //packet   
						int c = 0;

						iter->login = (const char*)ch->I; //get login name   

						enum _errors {
							CE_SUCCESS = 0,
							CE_IPBAN = 1,
							CE_ACCOUNT_CLOSED = 3,
							CE_NO_ACCOUNT = 4,
							CE_ACCOUNT_IN_USE = 6,
							CE_PREORDER_TIME_LIMIT = 7,
							CE_SERVER_FULL = 8,
							CE_WRONG_BUILDNUMBER = 9,
							CE_UPDATE_CLIENT = 10,
							CE_ACCOUNT_FREEZED = 12
						} res;

						std::string password;

						// check for an accepted client version   
						int minbuild = 0;
						int maxbuild = 10000;
						if (ch->build<minbuild || ch->build>maxbuild) res = CE_WRONG_BUILDNUMBER;
						else
						{
							CAccount *pAccount;
							pAccount = LoadAccount(iter->login.data());
							if (pAccount)
							{
								password = pAccount->Data.Password;
								delete pAccount;
								res = CE_SUCCESS;
							}
							else
							{

#ifdef AUTO_ACCOUNT				
								pAccount = LoadAccount(iter->login.data(), true);
								if (pAccount) delete pAccount;
								password = "nopass";
								res = CE_SUCCESS;
#else   
								res = CE_NO_ACCOUNT; //specified account doesn't exist   
#endif   
							}
							pkt[c++] = (char)0x00;//AUTH_LOGON_CHALLENGE;   

							if (res == CE_SUCCESS)
							{
								OutputDebugString("Computing Hashes...\n");
								logfile.Log("Computing Hashes...");
								std::transform(password.begin(), password.end(), password.begin(), toupper);

								iter->N.SetHexStr("894B645E89E1535BBDAD5B8B290650530801B18EBFBF5E8FAB3C82872A3E9BB7");
								iter->g.SetDword(7);
								iter->s.SetRand(32 * 8);
								Sha1Hash I;
								std::string sI = iter->login + ":" + password;
								I.UpdateData(sI);
								I.Finalize();

								Sha1Hash sha;
								sha.UpdateData(iter->s.AsByteArray(), iter->s.GetNumBytes());
								sha.UpdateData(I.GetDigest(), 20);
								sha.Finalize();

								BigNumber x;
								x.SetBinary(sha.GetDigest(), sha.GetLength());

								iter->v = iter->g.ModExp(x, iter->N);
								iter->b.SetRand(19 * 8);

								BigNumber gmod = iter->g.ModExp(iter->b, iter->N);
								iter->B = ((iter->v * 3) + gmod) % iter->N;
								//ASSERT(gmod.GetNumBytes() <= 32);   

								BigNumber unk3;
								unk3.SetRand(16 * 8);

								pkt[c++] = (char)0; // no error   
								pkt[c++] = (char)0; // res   
								uint8 *BArray, *NArray, *sArray;
								BArray = iter->B.AsByteArray();
								for (int i = 0; i < 32; i++) pkt[c++] = (char)BArray[i];
								// g_len, g   
								pkt[c++] = (char)1;
								pkt[c++] = iter->g.AsByteArray()[0];
								// N_len, N   
								pkt[c++] = (char)32;
								NArray = iter->N.AsByteArray();
								for (int i = 0; i < 32; i++) pkt[c++] = (char)NArray[i];
								sArray = iter->s.AsByteArray();
								for (int i = 0; i < iter->s.GetNumBytes(); i++) pkt[c++] = (char)sArray[i];
								sArray = unk3.AsByteArray();
								for (int i = 0; i < 16; i++) pkt[c++] = (char)sArray[i];
								pkt[c++] = (char)0x00;
							}
							else
							{
								pkt[c++] = (char)0x00;
								pkt[c++] = (char)res;
							}
							}
						logfile.LogBuffer(pkt, c, "Challenge Packet to Send Back");
						aSock.Send((char *)pkt, c);
						}
					break;
				case 1: // AUTH_LOGON_PROOF   
					iter->lastActive = time(0);
					if (1) {
						if (dataLen < sizeof(sAuthLogonProof_C))
							break; // wrong size...   
						sAuthLogonProof_C *lp = (sAuthLogonProof_C*)&buffer[0];
						logfile.LogBuffer(buffer, sizeof(sAuthLogonProof_C), "sAuthLogonProof_C Buffer");

						BigNumber A;
						A.SetBinary(lp->A, 32);

						Sha1Hash sha;
						sha.UpdateBigNumbers(&A, &iter->B, NULL);
						sha.Finalize();
						BigNumber u;
						u.SetBinary(sha.GetDigest(), 20);
						BigNumber S = (A * (iter->v.ModExp(u, iter->N))).ModExp(iter->b, iter->N);

						uint8 t[32];
						uint8 t1[16];
						uint8 vK[40];
						memcpy(t, S.AsByteArray(), 32);
						for (int i = 0; i < 16; i++)
						{
							t1[i] = t[i * 2];
						}
						sha.Initialize();
						sha.UpdateData(t1, 16);
						sha.Finalize();
						for (int i = 0; i < 20; i++)
						{
							vK[i * 2] = sha.GetDigest()[i];
						}
						for (int i = 0; i < 16; i++)
						{
							t1[i] = t[i * 2 + 1];
						}
						sha.Initialize();
						sha.UpdateData(t1, 16);
						sha.Finalize();
						for (int i = 0; i < 20; i++)
						{
							vK[i * 2 + 1] = sha.GetDigest()[i];
						}
						iter->K.SetBinary(vK, 40);

						uint8 hash[20];

						sha.Initialize();
						sha.UpdateBigNumbers(&iter->N, NULL);
						sha.Finalize();
						memcpy(hash, sha.GetDigest(), 20);
						sha.Initialize();
						sha.UpdateBigNumbers(&iter->g, NULL);
						sha.Finalize();
						for (int i = 0; i < 20; i++)
						{
							hash[i] ^= sha.GetDigest()[i];
						}
						BigNumber t3;
						t3.SetBinary(hash, 20);

						sha.Initialize();
						sha.UpdateData(iter->login);
						sha.Finalize();
						BigNumber t4;
						t4.SetBinary(sha.GetDigest(), 20);

						sha.Initialize();
						sha.UpdateBigNumbers(&t3, &t4, &iter->s, &A, &iter->B, &iter->K, NULL);
						sha.Finalize();
						BigNumber M;
						M.SetBinary(sha.GetDigest(), 20);

						if (!memcmp(M.AsByteArray(), lp->M1, 20))
						{
							//user successfully authed   
							if (CAccount *pAccount = LoadAccount(iter->login.data())) //check to see if account exists   
							{
								OutputDebugString("Auth success...\n");
								memcpy(pAccount->Data.SessionKey, iter->K.AsByteArray(), 40);
								pAccount->Data.LastLogin = time(0);
								pAccount->Save();
								delete pAccount; // mem leak otherwise!!   
							}
							else //somehow, we can't get your account. Something is wrong.   
							{
								OutputDebugString("Invalid Account...\n");
								aSock.Close();
								iter->sock = INVALID_SOCKET;
								break;
							}
							sha.Initialize();
							sha.UpdateBigNumbers(&A, &M, &iter->K, NULL);
							sha.Finalize();

							sAuthLogonProof_S proof;
							memcpy(proof.M2, sha.GetDigest(), 20);
							proof.cmd = 0x01; //AUTH_LOGON_PROOF;   
							proof.error = 0;
							proof.unk2 = 0;
							proof.unk3 = 0; //?? Enabled for 1.12.x?
							logfile.LogBuffer((char *)iter->K.AsByteArray(), iter->K.GetNumBytes(), "SessionKey");
							logfile.LogBuffer((char *)&proof, sizeof(sAuthLogonProof_S), "Proof Packet to Send Back");
							aSock.Send((char *)&proof, sizeof(proof));

							iter->authed = true;
						}
						else
						{
							OutputDebugString("Bad Password!\n");
							char pkt[2048];
							int c = 0;
							pkt[c++] = (char)0x01; //AUTH_LOGON_PROOF   
							pkt[c++] = (char)4; // bad password   
							logfile.Log("Bad Password.");
							logfile.LogBuffer(pkt, c, "Proof Packet to Send Back");
							aSock.Send((char *)pkt, c);
						}
					}
					break;
				case 2: // reconnect challenge   
					OutputDebugString("Reconnect Challenge Ignored...\n");
					logfile.LogBuffer(buffer, dataLen, "Type 2 Buffer");
					iter->lastActive = time(0);
					//aSock.Send(pkg2, 34);   
					break;
				case 3: // reconnect proof   
					OutputDebugString("Reconnect Proof Ignored...\n");
					logfile.LogBuffer(buffer, dataLen, "Type 3 Buffer");
					iter->lastActive = time(0);
					//aSock.Send(pkg3, 2);   
					break;
				case 0x10: // realm list request   
					OutputDebugString("Realmlist Request...\n");
					logfile.LogBuffer(buffer, dataLen, "RealmList Buffer");
					logfile.LogBuffer(&FullList[0], (TotalSent ? Pos : 8), "RealmList Information");
					aSock.Send(&FullList[0], Pos);
					//if (!TotalSent)
					//	aSock.Send(&FullList[0], 8);
					//else
						
					break;
				default:
					//logfile.LogBuffer(buffer,128,"Unknown Buffer");   
					break;
					}
				}
			else if (difftime(time(0), iter->lastActive) > 30.0f)
			{
				// client timed out   
				OutputDebugString("Client Timeout...\n");
				aSock.Close();
				iter->sock = INVALID_SOCKET;
				//clients.erase(iter);   
			}
			}
		for (vector<RealmListClient>::iterator iter = tmplist.begin(); iter != tmplist.end(); iter++)
		{
			if (iter->sock != INVALID_SOCKET)
				clients.push_back(*iter);
		}
		tmplist.clear();

		if (pServer->MasterListener.isData())
		{
			int len = pServer->MasterListener.RecvFrom(buffer, 2048, From);
			if (len == sizeof(RealmPacket))
			{
				OutputDebugString("RealmPacket...\n");
				pServer->AddRealm((RealmPacket*)&buffer[0], From);
			}
			else
			{
				if (buffer[0] == 0x22)
				{
					//we got a sessionkey request   
					char *acctname = &buffer[1];
					//load acctname   
					CAccount *pAccount = LoadAccount(acctname);
					time_t now = time(0);
					Addr RetAddr;
					memset(&RetAddr, 0, sizeof(Addr));
					RetAddr.sa_family = 2;
					RetAddr.IP = From.IP;
					RetAddr.Port = htons(31416);
					Sleep(1);
					if (pAccount == NULL)
					{
						char empty[40];
						memset(empty, 0, 40);
						pServer->MasterListener.SendTo(empty, 40, RetAddr);
					}
					else
					{
						pServer->MasterListener.SendTo((char *)pAccount->Data.SessionKey, 40, RetAddr);
						delete pAccount;
					}
				}
			}
		}
		if (difftime(time(0), LastCleanup) > 30.0f)
		{
			pServer->CleanupExpired();
			LastCleanup = time(0);
		}
		Sleep(10); // 50 per second   
		}

	pThread->bThreading = false;
	return 0;
	}

CRealmListServer::CRealmListServer(void)
{
	unsigned long i;
	for (i = 0; i < VERIFY_THREADS; i++)
		pRealmVerifiers[i] = 0;

	if (Initialize())
	{
		RealmThread.BeginThread(RealmListServerThreadFunction, this);
		for (i = 0; i < VERIFY_THREADS; i++)
		{
			pRealmVerifiers[i] = new CRealmVerifier(this);
			pRealmVerifiers[i]->Go();
		}
	}
	else
	{
#if WIN32   
		MessageBox(NULL, "Critical Error: Initialization Failed: Ports not available!", "Fatal Error", MB_ICONERROR | MB_OK);
#else   
		puts("Critical Error: Initialization Failed: Ports not available!");
#endif   
		exit(1); // failure code   
				 // memleaks shmemleaks. we're quitting now anyway   
	}
}

CRealmListServer::~CRealmListServer(void)
{
	for (unsigned long i = 0; i < VERIFY_THREADS; i++)
	{
		if (pRealmVerifiers[i])
			delete pRealmVerifiers[i];
	}
	RealmThread.EndThread();
	Realms.Cleanup();
}

bool CRealmListServer::Initialize()
{
	if (!ListListener.Create(3724))
		return false;
	if (!ListListener.Listen())
		return false;
	if (!MasterListener.Create(9111))
		return false;
	return true;
}

unsigned long CRealmListServer::ShowRealm(RealmInfo &Info, char Total, char *buffer)
{
	//OutputDebugString("Show Realm...\n");

	char sPort[12] = { 0 };
	char c = 0;

	*(unsigned char *)&buffer[c] = 0;
	buffer[c++] = Info.Icon;
	c += 4;
	buffer[c++] = Info.Color;

	strcpy(&buffer[c], Info.Name);  // server full name   
	c += strlen(Info.Name) + 1;         // string length; null-terminated   

	strcpy(&buffer[c], Info.IPAddr); // server address   
	c += strlen(Info.IPAddr);         // string length; port follows   
	buffer[c++] = ':';              // port separator   
	sprintf(sPort, "%i", Info.Port);  // port number   
	strcpy(&buffer[c], sPort);
	c += strlen(sPort) + 1;             // string length; null-terminated   

	*(float*)&buffer[c] = 1; // Population   
	c += 4;

	buffer[c++] = 1; // "Characters" // name becomes yellow if this is 0   
	buffer[c++] = Info.Language;
	buffer[c++] = Total; //order? for putting all realms in order perhaps   

	return c;
}

void CRealmListServer::AddRealm(RealmPacket *realm, Addr &From)
{
	OutputDebugString("AddRealm\n");
	realm->Name[63] = 0;
	// lets block all ports other than 9090.   
	//if (realm->Port!=9090)   
	//  return;   

	char IPAddr[16];
	if (realm->IPAddr[0])
		strcpy(IPAddr, realm->IPAddr);
	else
		strcpy(IPAddr, inet_ntoa(*(in_addr*)&From.IP));

	int N = FindRealm(IPAddr, realm->Port);
	if (N >= 0)
	{
		RealmInfo *pInfo = Realms[N];
		// update existing   
		if (!pInfo->Active)
		{
			if (difftime(time(0), pInfo->LastVerified) > 60.0f)
				pInfo->LastVerified = 0;// accelerate check   
		}

		strcpy(pInfo->Name, realm->Name);
		pInfo->nPlayers = realm->nPlayers;
		pInfo->Icon = realm->Icon;
		pInfo->Color = 0;
		pInfo->LastUpdate = time(0);
	}
	else// if (nRealms<250)   
	{
		// add new   
		RealmInfo *pRealm = new RealmInfo;
		pRealm->nIP = From.IP;
		pRealm->Port = realm->Port;
		strcpy(pRealm->Name, realm->Name);
		pRealm->LastUpdate = time(0);
		pRealm->LastVerified = 0;
		pRealm->Active = false;
		pRealm->Color = 0;
		pRealm->Icon = realm->Icon;
		pRealm->Language = (unsigned char)realm->Language;
		strcpy(pRealm->IPAddr, IPAddr);
		pRealm->nPlayers = realm->nPlayers;
		unsigned long N = Realms.GetUnused();
		Realms[N] = pRealm;
		MapInsert(IPAddr, realm->Port, N);
	}
}

int CRealmListServer::FindRealm(const char *IPAddr, unsigned short Port)
{
	char TestBuffer[25];
	sprintf(TestBuffer, "%s:%u", IPAddr, Port);
	return RealmMap[TestBuffer] - 1;
}

void CRealmListServer::MapInsert(const char *IPAddr, unsigned short Port, unsigned long nRealm)
{
	char TestBuffer[25];
	sprintf(TestBuffer, "%s:%u", IPAddr, Port);
	RealmMap[TestBuffer] = nRealm + 1;
}

void CRealmListServer::CleanupExpired()
{
	time_t now = time(0);
	for (unsigned long i = 0; i < Realms.Size; i++)
	{
		if (RealmInfo *pRealm = Realms[i])
		{
			// 2.5 mins recycle time   
			if (difftime(now, pRealm->LastUpdate) > 150.0f)
			{
				pRealm->Active = false;
			}
		}
	}
}

RealmInfo *CRealmListServer::GetNextVerify()
{
	CLock L(&Verifying, 1);
	time_t now = time(0);
	for (unsigned long i = 0; i < Realms.Size; i++)
	{
		if (RealmInfo *pRealm = Realms[i])
		{
			if (difftime(now, pRealm->LastUpdate) < 150.0f && difftime(now, pRealm->LastVerified) > 600.0f)
			{
				pRealm->LastVerified = now;
				return pRealm;
			}
		}
	}
	return 0;
}

