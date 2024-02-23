#pragma once
#include "Reader.h"
#include "Writer.h"
#include <vector>
#include <map>
#include "common.h"
using Table = std::map<std::string, MySymbol>;
std::map<int, int> CountAllSymbols(Reader &reader);
Table MakeTable(const std::map<int, int> &counts);
Table MakeCanonic(const Table &codes);
void EncodeTable(const Table &table, Writer &archive);

void ZipOneFile(const std::string &filename, Writer &archive);
void ZipFiles(const std::string &arcname, const std::vector<std::string> &files);
