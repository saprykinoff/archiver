#pragma once
#include <map>
#include <string>
#include "Reader.h"
#include "Writer.h"
#include <vector>
#include "Tries.h"
#include "common.h"
TrieDecode DecodeTable(Reader &archive);
bool UnzipOneFile(Reader &archive);
void UnzipFiles(const std::string &arcname);