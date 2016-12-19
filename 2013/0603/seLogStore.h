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
//
// Modification History:
// 06/17/2013 Create by Young Pan
////////////////////////////////////////////////////////////////////////////
#ifndef AOS_SeLogSvr_SeLogStore_h
#define AOS_SeLogSvr_SeLogStore_h

#include "ErrorMgr/ErrmsgId.h"
#include "ReliableFile/Ptrs.h"
#include "SearchEngine/Ptrs.h"
#include "SEUtil/Ptrs.h"
#include "SeLogSvr/Ptrs.h" 
//#include "SeLogSvr/LogAging.h"
//#include "SeLogSvr/MdlLogSvr.h"
//#include "SeLogSvr/SeLogEntry.h"
#include "SeLogUtil/LogUtil.h"
#include "SeLogUtil/LogOpr.h"
#include "Thread/Ptrs.h"
#include "Util/Ptrs.h"
#include "Util/RCObject.h"
#include "Util/RCObject.h"
#include "Util/File.h"
#include "UtilHash/HashedObj.h"
#include "XmlUtil/XmlTag.h"
#include "XmlUtil/SeXmlUtil.h"
#include <map>


class AosSeLogStore
{
	OmnDefineRCObject;

private:
	OmnFilePtr 			mCurFile;
	map<u32,u64>		mFileIdMap;
	u64					mFileId;
	u64					mGetBuffLogid;
	u32					mGetBuffNum;
	u32					mPreLogLen;
	u64					mCurOffset;
	u32					mVirtualId;
	u32					mSeqno;
	OmnString   		mFname;
	OmnString  	 		mLogName;
	OmnString 			mStrKey;
	AosRundataPtr		mRdata;
	OmnMutexPtr         mLock;
	
public:
	enum
	{
		eBitFlag = 0xffffffff,
		eDftStep = 12,
		eDftMaxFileNum = 10,			
		eDftGetBuffsize = 50000000,			// 50MB
		eDftMaxLogFileSize = 100000000,		// 500MB
		eDftHeaderFileSize = 20000000,      // 20MB

		eMaxKeyLength = 80
	};

public:
	AosSeLogStore();
	AosSeLogStore(
			const u32 &virtual_id,
			const OmnString &logname,
			const OmnString &strkey,
			const AosXmlTagPtr &log_doc);
	~AosSeLogStore();


	u64				addLog(
						const OmnString &loginfo, 
						u64 &logid);
	OmnString 		getLog(const u64 &logid);
	AosBuffPtr 		getLogBuff();
	AosBuffPtr 		getLogBuff(const u64 logid);
	bool 			deleteLog(const u64 &logid);
	u32 			getBuffNum() {return mGetBuffNum;}

private:
	bool 		init();
	bool		createNewLogFile();
	bool		storeInfoToHeader(
						const u32 &seqno,
						const u64 &fileid,
						const OmnString	&str_key);
	bool		checkFile(const OmnString &loginfo);
	bool 		cleanFile();
	u64			getNextLogid(const u32 seqno);
	bool		putDataIntoBuff(const AosBuffPtr &buff);
};
#endif


