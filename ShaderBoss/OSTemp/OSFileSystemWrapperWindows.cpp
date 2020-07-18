#include "OSFileSystemWrapper.h"
#include <windows.h>
#include <shobjidl.h>
#include <shlwapi.h>
#include <cstring>
#include <atlstr.h>

using namespace std;
using namespace ShaderBoss;


std::string OSFileSystemWrapper::LoadFileDialoug(const std::string& basePath)
{
	OPENFILENAME ofn;

	wchar_t filename[255];

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = filename;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(filename);
	ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	GetOpenFileName(&ofn);

	return std::string(CStringA(ofn.lpstrFile));
}