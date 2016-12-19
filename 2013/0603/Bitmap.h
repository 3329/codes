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
//
// Modification History:
// 06/14/2013 Created by Young Pan
////////////////////////////////////////////////////////////////////////////
#ifndef Aos_Bitmap_Bitmap_h
#define Aos_Bitmap_Bitmap_h

#include "Rundata/Ptrs.h"
#include "Util/RCObject.h"
#include "Util/RCObjImp.h"
#include <vector>
using namespace std;


class AosBitmap
{
private:
	vector<u8>			mIndex;
	

public:
	AosBitmap();
	~AosBitmap();
};
#endif

