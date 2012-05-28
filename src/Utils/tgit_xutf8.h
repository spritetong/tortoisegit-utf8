#ifndef __TGIT_XUTF8__
#define __TGIT_XUTF8__

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/

/* Indicates UTF-8 is enabled. */
#define __XUTF8_ENABLED__

/* Set this macro to support bugfix for TortoiseGit. */
#define __TGIT_XUTF8_BUGFIX__

/* Set this macro to disable all changes of TortoiseGit except UTF-8 support. */
//#define __TGIT_XUTF8_LEGACY__

/******************************************************************************/

#define CP_GIT_XACP		CP_ACP
#ifdef __XUTF8_ENABLED__
#define CP_GIT_XUTF8	CP_UTF8
#else
#define CP_GIT_XUTF8	CP_ACP
#endif

/******************************************************************************/
/* Fix compilation bugs. */
#define git_lasterror get_git_last_error
#define git_tree_entry_2object git_tree_entry_to_object

/******************************************************************************/

#ifdef __cplusplus
extern "C++"
{

#include <io.h>
#include <fcntl.h>

#if defined(__AFX_H__)
class CStdioFileUtf8: public CStdioFile
{
public:
	CStdioFileUtf8(): CStdioFile() {}
	CStdioFileUtf8(FILE* pOpenStream): CStdioFile(pOpenStream) {}
	CStdioFileUtf8(LPCTSTR lpszFileName, UINT nOpenFlags):
		CStdioFile(lpszFileName, nOpenFlags) {}
	
	virtual BOOL Open(LPCTSTR lpszFileName, UINT nOpenFlags,
		CFileException* pError = NULL)
	{
		BOOL ret = CStdioFile::Open(lpszFileName, nOpenFlags, pError);
		if (ret && !(nOpenFlags & typeBinary))
			_setmode(_fileno(m_pStream), _O_U8TEXT);
		return ret;
	}
};
#define CStdioFile CStdioFileUtf8
#endif /* __AFX_H__ */

}
#endif /* __cplusplus */

#ifdef __cplusplus
}
#endif

#endif /* __TGIT_XUTF8__ */
