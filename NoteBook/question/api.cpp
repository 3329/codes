AosRundataPtr rdata
AosXmlTagPtr def

mServerId = def->getAttrInt("server_id", -1);
aos_assert_rr(mServerId >= 0, rdata, false);

mDirname = def->getAttrStr("dirname", "");
aos_assert_rr(mDirnamr != "", rdata, false);

mDocTemplate = def->getFirstChild("doctemplate");

mDir = OmnNew OmnDirDesc(mDirname);

OmnNotImplementedYet

bool rslt = mDir->getFisrFile(fname);
AosXmlTagPtr file = OmnNew OmnFile(fname, OmnFile::eReadOnly AosMemoryCheckerArgs);
AosBuffPtr buff = OmnNew AosBuff(eBuffSize AosMemoryCheckArgs);

char *data = buff->data();
int64_t data_len = eBuffSize;

file->readToBuff(start_pos, data_len, &data[start_pos]);
buff->setDataLen(start_pos);
rdata->setWorkingDoc(doc, true);

