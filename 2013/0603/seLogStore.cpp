////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2005
// Packet Engineering, Inc. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification is not permitted unless authorized in writing by a duly
// appointed officer of Packet Engineering, Inc. or its derivatives
//
// Description:
//	logid = seqno + curOffset	
//	stored = u32 + u64 + u32 + loginfo 
//
// Modification History:
// 06/17/2013 Create by Young Pan
////////////////////////////////////////////////////////////////////////////
#include "SeLogSvr/SeLogStore.h"

#include "alarm_c/alarm.h"
#include "API/AosApi.h"
#include "Alarm/Alarm.h"
#include "IILClient/IILClient.h"
#include "Rundata/Ptrs.h"
#include "ReliableFile/ReliableFile.h"
#include "SearchEngine/DocMgr.h"
#include "SEUtil/SeTypes.h"
#include "SeLogSvr/PhyLogSvr.h"
#include "SeLogUtil/LogNames.h"
#include "Security/SecurityMgr.h"
#include "Util/StrSplit.h"
#include "Util/Buff.h"
#include "Util/File.h"
#include "UtilHash/HashedObj.h"
#include "XmlUtil/XmlDoc.h"
#include "XmlUtil/SeXmlParser.h"
#include "XmlUtil/AccessRcd.h"
#include "StorageMgr/VirtualFileSysMgr.h"
#include "StorageMgr/FileKeys.h"
#include "StorageMgr/SystemId.h"
#include "VirtualFile/VirtualFile.h"
#include "Thread/Mutex.h"


static bool sgGetLogBuffFlag = false;

AosSeLogStore::AosSeLogStore()
:
mFileId(0),
mPreLogLen(0),
mCurOffset(0),
mSeqno(0),
mLock(OmnNew OmnMutex())
{
	// if not have header file , create the header file
	// then put the xml log_doc into the header file
	AosVfsMgrObjPtr vfsMgr = AosVfsMgrObj::getVfsMgr();
	mRdata = OmnNew AosRundata(AosMemoryCheckerArgsBegin);
	mRdata->setSiteid(AOS_SYS_SITEID);

	mVirtualId = 0;
	if (mStrKey == "")
	{
		mStrKey = AOSFILEKEY_SELOG_STORE_FILENAME;
		mStrKey << "_" << mLogName;
	}

	if (!vfsMgr->openFileByStrKey(mVirtualId, mStrKey, mRdata AosMemoryCheckerArgs))
	{
		OmnFilePtr file = vfsMgr->createFileByStrKey(mVirtualId, mStrKey, eDftHeaderFileSize, true, mRdata AosMemoryCheckerArgs);
		u64 logid = 0;
		file->setU64(0, logid, true);
		file->setU64(sizeof(u64), 0, true);
	}

	init();
}


AosSeLogStore::AosSeLogStore(
		const u32 &virtual_id,
		const OmnString &logname,
		const OmnString &strkey,
		const AosXmlTagPtr &log_doc)
:
mFileId(0),
mPreLogLen(0),
mCurOffset(0),
mVirtualId(virtual_id),
mSeqno(0),
mLogName(logname),
mStrKey(strkey),
mLock(OmnNew OmnMutex())
{
	// if not have header file , create the header file
	// then put the xml log_doc into the header file
	AosVfsMgrObjPtr vfsMgr = AosVfsMgrObj::getVfsMgr();
	mRdata = OmnNew AosRundata(AosMemoryCheckerArgsBegin);
	mRdata->setSiteid(AOS_SYS_SITEID);
	if (mStrKey == "")
	{
		mStrKey = AOSFILEKEY_SELOG_STORE_FILENAME;
		mStrKey << "_" << mLogName;
	}

	if (!vfsMgr->openFileByStrKey(mVirtualId, mStrKey, mRdata AosMemoryCheckerArgs))
	{
		OmnFilePtr file = vfsMgr->createFileByStrKey(mVirtualId, mStrKey, eDftHeaderFileSize, true, mRdata AosMemoryCheckerArgs);
		OmnString logdoc = log_doc->toString();
		u64 logid = 0;
		u64 docLen = logdoc.length();
		file->setU64(0, logid, true);
		file->setU64(sizeof(u64), docLen, true);
		file->put(sizeof(u64)*2, logdoc.data(), docLen, true);
	}

	init();
}


AosSeLogStore::~AosSeLogStore()
{
}


bool
AosSeLogStore::init()
{
	mFileIdMap.clear();
	//mRdata = OmnNew AosRundata(AosMemoryCheckerArgsBegin);
	//mRdata->setSiteid(AOS_SYS_SITEID);

	AosVfsMgrObjPtr vfsMgr = AosVfsMgrObj::getVfsMgr();
	aos_assert_r(vfsMgr, false);

	if (mStrKey == "")
	{
		mStrKey = AOSFILEKEY_SELOG_STORE_FILENAME;
		mStrKey << "_" << mLogName;
	}

	OmnFilePtr headerFile = vfsMgr->openFileByStrKey(mVirtualId, mStrKey, mRdata AosMemoryCheckerArgs);
	if (headerFile)
	{
		// get start offset from header file
		u64 docLen = headerFile->readBinaryU32(sizeof(u64), 0);
		u64 startOffset = sizeof(u64) * 2 + docLen;

		u32 fileLength = headerFile->getLength();	
		AosBuffPtr buff = OmnNew AosBuff(fileLength AosMemoryCheckerArgs);

		u32 offset = fileLength - eDftStep; 
		u32 seqno = headerFile->readBinaryU32(offset, 0);
		u64 fileid = headerFile->readBinaryU64(offset+sizeof(u32), 0);

		// 1. get current log file 
		OmnLocalFilePtr tmpFile = vfsMgr->openFile(fileid, mRdata AosMemoryCheckerArgs);
		aos_assert_r(tmpFile, false);
		mCurFile = dynamic_cast<OmnFile*>(tmpFile.getPtr());

		// 2. set the offset
		mCurOffset = mCurFile->getLength();

		// 3. set map 
		u32 tmpSeqno;
		u64 tmpFileid;
		for (u32 i=0; i<(fileLength-startOffset)/eDftStep; i++)
		{
			tmpSeqno = headerFile->readBinaryU32(i * eDftStep + startOffset, 0);
			tmpFileid = headerFile->readBinaryU64(i * eDftStep + sizeof(u32) + startOffset, 0);
			mFileIdMap.insert(std::pair<u32,u64>(tmpSeqno, tmpFileid));
		}

		// 4. next log's seqno
		mSeqno = seqno;

		// 5. set Get buff logid
		tmpSeqno = headerFile->readBinaryU32(0, 0);
		mGetBuffLogid = getNextLogid(tmpSeqno);
	}

	return true;
}


u64
AosSeLogStore::addLog(
				const OmnString &loginfo, 
				u64 &logid)
{
	aos_assert_r(loginfo != "", false);

	mLock->lock();
	// 1.check header file and log file
	checkFile(loginfo);

	// 2.get logid
	logid = mSeqno;
	aos_assert_rl(mSeqno != 0, mLock, 0);
	logid = (logid << 32) + mCurOffset;

	// 3.write log to file
	mCurFile->setU32(mCurOffset, loginfo.length(), false);
	mCurOffset += sizeof(u32); 
	mCurFile->setU64(mCurOffset, logid, false);
	mCurOffset += sizeof(u64); 
	mCurFile->setU32(mCurOffset, mPreLogLen, false);
	mCurOffset += sizeof(u32); 
	mCurFile->put(mCurOffset, loginfo.data(), loginfo.length(), true);
	mCurOffset += loginfo.length(); 

	mPreLogLen = loginfo.length();
	mLock->unlock();
	return logid;
}


OmnString 
AosSeLogStore::getLog(const u64 &logid)
{
	mLock->lock();
	u32 seqno = logid >> 32;
	const u32 offset = logid & eBitFlag;

	map<u32, u64>::iterator itr = mFileIdMap.find(seqno);
	aos_assert_rl(itr != mFileIdMap.end(), mLock, "");
	u64 fileid = itr->second;

	AosVfsMgrObjPtr vfsMgr = AosVfsMgrObj::getVfsMgr();
	aos_assert_rl(vfsMgr, mLock, "");

	OmnLocalFilePtr tmpFile = vfsMgr->openFile(fileid, mRdata AosMemoryCheckerArgs);
	aos_assert_rl(tmpFile, mLock, "");
	OmnFilePtr file = dynamic_cast<OmnFile*>(tmpFile.getPtr());
 
	u32 length = file->readBinaryU32(offset, 0);
	AosBuffPtr buff = OmnNew AosBuff(length AosMemoryCheckerArgs);
	file->readToBuff(offset+16, length, buff->data());
	buff->setDataLen(length);
	OmnString rslt(buff->data(), length);
	mLock->unlock();
	aos_assert_rl(rslt != "", mLock, "");
		
	return rslt;
}


bool
AosSeLogStore::deleteLog(const u64 &logid)
{
	return true;
}


bool
AosSeLogStore::createNewLogFile()
{
	// 1. set current offset 
	mCurOffset = 0;
	AosVfsMgrObjPtr vfsMgr = AosVfsMgrObj::getVfsMgr();
	aos_assert_r(vfsMgr, false);

	// 2. check the header file 
	OmnFilePtr file = NULL;
	if (!vfsMgr->openFileByStrKey(mVirtualId, mStrKey, mRdata AosMemoryCheckerArgs))
	{
		file = vfsMgr->createFileByStrKey(mVirtualId, mStrKey, eDftHeaderFileSize, true, mRdata AosMemoryCheckerArgs);        
		aos_assert_r(file, false);
		file->setU64(0, 0, true); 				//set logid into header
		file->setU64(sizeof(u64), 0, true);		//set doc's length into header
	}

	// 3. create new log file
	mCurFile = vfsMgr->createNewFile(mRdata, mVirtualId, mFileId, mFname, 0, false);
	aos_assert_r(mCurFile, false);
	OmnScreen << "create new file, fileid : " << mFileId << endl;

	return true;
}


bool
AosSeLogStore::storeInfoToHeader(
				const u32 &seqno,
				const u64 &fileid,
				const OmnString &str_key)
{
	AosVfsMgrObjPtr vfsMgr = AosVfsMgrObj::getVfsMgr();
	aos_assert_r(vfsMgr, false);

	OmnFilePtr headerFile = vfsMgr->openFileByStrKey(mVirtualId, str_key, mRdata AosMemoryCheckerArgs);
	aos_assert_r(headerFile, false);

	headerFile->setU32(headerFile->getLength(), seqno, true);
	headerFile->setU64(headerFile->getLength(), fileid, true);

	return true;
}


bool
AosSeLogStore::checkFile(const OmnString &loginfo)
{
	// 1.check current file 
	if (!mCurFile || mCurOffset + sizeof(u64) + loginfo.length() >= eDftMaxLogFileSize)
	{
		// seqno start from 1
		mSeqno++;

		// when create new log file,the function will check the header file
		createNewLogFile();
		mFileIdMap.insert(std::pair<u32,u64>(mSeqno, mFileId));
		storeInfoToHeader(mSeqno, mFileId, mStrKey);
	}

	// 2.check the files's number
	if (mFileIdMap.size() > eDftMaxFileNum)
	{
		cleanFile();
	}

	return true;
}


bool
AosSeLogStore::cleanFile()
{
	// 1. delete the first file
	map<u32,u64>::iterator itr = mFileIdMap.begin();
	aos_assert_r(itr != mFileIdMap.end(), false);
	u64 fileid = itr->second;

	AosVfsMgrObjPtr vfsMgr = AosVfsMgrObj::getVfsMgr();
	aos_assert_r(vfsMgr, false);
	vfsMgr->removeFile(fileid, mRdata);

	// 2. set fileid map
	while(itr->second == fileid)
	{
		mFileIdMap.erase(itr);
		itr = mFileIdMap.begin();
	}

	// 3. set headerFile 
	AosBuffPtr buff = OmnNew AosBuff(mFileIdMap.size()*eDftStep AosMemoryCheckerArgs);
	itr = mFileIdMap.begin();
	for (u32 i=0; i<mFileIdMap.size(); i++)
	{
		aos_assert_r(itr != mFileIdMap.end(), false);
		buff->setU32(itr->first);
		buff->setU64(itr->second);
		itr++;
	}

	OmnFilePtr headerFile = vfsMgr->openFileByStrKey(mVirtualId, mStrKey, mRdata AosMemoryCheckerArgs);
	aos_assert_r(headerFile, false);
	headerFile->put(sizeof(u64) * 2, buff->data(), mFileIdMap.size()*eDftStep, true);

	return true;
}


AosBuffPtr
AosSeLogStore::getLogBuff()
{
	// if the first get log buff, set mGetBuffLogid
	if (!sgGetLogBuffFlag)
	{
		sgGetLogBuffFlag = true;
		map<u32,u64>::iterator itr = mFileIdMap.begin();
		aos_assert_r(itr != mFileIdMap.end(), NULL);
		u32 seqno = itr->first;

		mGetBuffLogid = getNextLogid(seqno-1);
	}

	// 1. new buff
	AosBuffPtr buff = OmnNew AosBuff(eDftGetBuffsize AosMemoryCheckerArgs);

	// 2. get data from the logfile and put the data into the buff 
	bool rslt = putDataIntoBuff(buff); 
	aos_assert_r(rslt, NULL);

	return buff;
}


AosBuffPtr
AosSeLogStore::getLogBuff(const u64 logid)
{
	// 1. modify logid in header file 
	AosVfsMgrObjPtr vfsMgr = AosVfsMgrObj::getVfsMgr();
	aos_assert_r(vfsMgr, NULL);
	OmnFilePtr headerFile = vfsMgr->openFileByStrKey(mVirtualId, mStrKey, mRdata AosMemoryCheckerArgs);
	aos_assert_r(headerFile, NULL);
	headerFile->setU64(logid, 0, true);
	mGetBuffLogid = logid;
	
	// 1. new buff
	AosBuffPtr buff = OmnNew AosBuff(eDftGetBuffsize AosMemoryCheckerArgs);

	// 2. get data from the logfile and put the data into the buff 
	bool rslt = putDataIntoBuff(buff); 
	aos_assert_r(rslt, NULL);

	return buff;
}


bool
AosSeLogStore::putDataIntoBuff(const AosBuffPtr &buff)
{
	mLock->lock();
	AosVfsMgrObjPtr vfsMgr = AosVfsMgrObj::getVfsMgr();
	aos_assert_rl(vfsMgr, mLock, false);
	OmnFilePtr headerFile = vfsMgr->openFileByStrKey(mVirtualId, mStrKey, mRdata AosMemoryCheckerArgs);
	aos_assert_r(headerFile, false);

	u64 totalLen = 0;
	u32 endSeqno = 0;
	u32 startSeqno = mGetBuffLogid >> 32;
	while (totalLen < eDftGetBuffsize)
	{
		u32 seqno = mGetBuffLogid >> 32;
		const u32 offset = mGetBuffLogid & eBitFlag;

		map<u32, u64>::iterator itr = mFileIdMap.find(seqno);
		aos_assert_rl(itr != mFileIdMap.end(), mLock, false);
		u64 fileid = itr->second;

		OmnLocalFilePtr tmpFile = vfsMgr->openFile(fileid, mRdata AosMemoryCheckerArgs);
		aos_assert_rl(tmpFile, mLock, false);
		OmnFilePtr file = dynamic_cast<OmnFile*>(tmpFile.getPtr());

		u64 fileLen = file->getLength();
		if ((fileLen - offset) >= (eDftGetBuffsize - totalLen))
		{
			u64 val = file->readToBuff(offset, eDftGetBuffsize - totalLen, buff->data());
			aos_assert_rl(val > 0, mLock, false);
			totalLen = eDftGetBuffsize;
		}
		else
		{
			file->readToBuff(offset, fileLen - offset, buff->data());
			totalLen += (fileLen - offset);

			map<u32, u64>::iterator itr = mFileIdMap.begin();
			for(u32 i=0; i<mFileIdMap.size(); i++)
			{
				if (fileid == itr->second)
				{
					endSeqno = itr->first;
				}
			}

			// check next seqno 
			// if donot have more logfile 
			map<u32, u64>::iterator itr2 = mFileIdMap.find(endSeqno + 1);
			if (itr2 == mFileIdMap.end())
			{
				headerFile->setU64(getNextLogid(endSeqno), 0, true);
				mGetBuffNum = endSeqno - startSeqno + 1;
				mLock->unlock();
				return true;
			}

			// get next logid 
			mGetBuffLogid = getNextLogid(endSeqno);
		}

	}

	headerFile->setU64(getNextLogid(endSeqno), 0, true);
	mGetBuffNum = endSeqno - startSeqno + 1;

//	while (buff->dataLen() < eDftGetBuffsize)
//	{
//		u32 seqno = mGetBuffLogid >> 32;
//		const u32 offset = mGetBuffLogid & eBitFlag;
//
//		map<u32, u64>::iterator itr = mFileIdMap.find(seqno);
//		aos_assert_rl(itr != mFileIdMap.end(), mLock, false);
//		u64 fileid = itr->second;
//
//		AosVfsMgrObjPtr vfsMgr = AosVfsMgrObj::getVfsMgr();
//		aos_assert_rl(vfsMgr, mLock, false);
//
//		OmnLocalFilePtr tmpFile = vfsMgr->openFile(fileid, mRdata AosMemoryCheckerArgs);
//		aos_assert_rl(tmpFile, mLock, false);
//		OmnFilePtr file = dynamic_cast<OmnFile*>(tmpFile.getPtr());
//
//		// length = u32 + u64 + u32 + log
//		u32 length = file->readBinaryU32(offset, 0);
//		u64 tmpLogid = file->readBinaryU64(offset+sizeof(u32), 0);
//		u32 prevLen = file->readBinaryU32(offset+12, 0);
//
//		if (buff->dataLen()+length+32 >= eDftGetBuffsize) break;
//		buff->setU32(length);
//		buff->setU64(tmpLogid);
//		buff->setU32(prevLen);
//		u64 val = file->readToBuff(offset+16, length, buff->data() + sizeof(u32)*2 + sizeof(u64));
//		aos_assert_rl(val > 0, mLock, false);
//
//		////////////////////////////
//		// modify the mGetBuffLogid
//		mGetBuffLogid = getNextLogid(seqno);
//	}

	mLock->unlock();
	return true;
}


u64
AosSeLogStore::getNextLogid(const u32 seqno)
{
	u64 nextLogid = 0;
	u32 nextSeqno = seqno + 1;
	u64 fileid = mFileIdMap.find(nextSeqno)->second;

	AosVfsMgrObjPtr vfsMgr = AosVfsMgrObj::getVfsMgr();
	aos_assert_r(vfsMgr, 0);

	OmnLocalFilePtr tmpFile = vfsMgr->openFile(fileid, mRdata AosMemoryCheckerArgs);
	aos_assert_r(tmpFile, 0);
	OmnFilePtr file = dynamic_cast<OmnFile*>(tmpFile.getPtr());
 
	u64 offset = 0;
	u64 fileLen = file->getLength();
	while (offset < fileLen) 
	{
		u64 tmpLogid = file->readBinaryU64(offset+sizeof(u32), 0);
		if (nextSeqno == (tmpLogid >> 32))
		{
			nextLogid = tmpLogid;
			return nextLogid;
		}
		else
		{
			u32 tmpLength = file->readBinaryU32(offset, 0);
			offset += (16 + tmpLength);
		}
	}

	return nextLogid;
}




