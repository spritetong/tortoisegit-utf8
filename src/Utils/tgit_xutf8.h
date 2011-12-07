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

#ifdef __cplusplus
}
#endif

#endif /* __TGIT_XUTF8__ */
