#include "Model.h"
#include "StringProc.h"
#include "Err.h"
#include <map>


//LoaderFunction Model::Loader(const std::string& FileFormat, LoaderFunction F)
//{
//	static std::map<std::string, LoaderFunction> LoaderMap;
//	std::string S = FileFormat;
//	StringProc::lowerCase(&S);
//	
//	if(!F)
//	{
//		std::map<std::string, LoaderFunction>::iterator it = LoaderMap.find(S);
//		if (it == LoaderMap.end())
//		{
//			Err::Report("Could not find Model Loader for format: " +S);
//			return 0;
//		}
//		else
//		{
//			return it->second;
//		}
//	}
//	else
//	{
//		LoaderMap[S] = F;
//		return LoaderMap[S];
//	}
//
//}