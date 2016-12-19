
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
// 01/03/2010: Created by Chen Ding
////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include <dirent.h>
#include "GetLine/getline.h"
#include <fstream>
using namespace std;

char *welcome = \
	"*********************************************************************\n" 
	"*              Welcome to JimoSQL 0.1                             \n" 
	"*  Copyright (c) 2009-2014 Zykie Networks Inc. All rights reserved.\n"
	"*  Type \"?\" or \"help\" to list all the commands.\n"
	"************************************************************i********\n";
