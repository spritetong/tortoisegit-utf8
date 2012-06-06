/**
* SharedMutex.cpp
* @Author   Tu Yongce <yongce (at) 126 (dot) com>
* @Created  2008-11-17
* @Modified 2008-11-17
* @Version  0.1
*/
#include "StdAfx.h"
#include "SharedMutex.h"


SharedMutex::SharedMutex(): m_sharedNum(0), m_exclusiveNum(0), m_lockType(LOCK_NONE), m_mutex(0), m_sharedEvent(0),m_exclusiveEvent(0)
{
  
}

SharedMutex::~SharedMutex()
{

}

void SharedMutex::Release()
{
	if (m_mutex)
	{
		::CloseHandle(m_mutex);
		m_mutex = NULL;
	}
	if (m_sharedEvent)
	{
		::CloseHandle(m_sharedEvent);
		m_sharedEvent = NULL;
	}
	if (m_exclusiveEvent)
	{
		::CloseHandle(m_exclusiveEvent);
		m_exclusiveEvent = NULL;
	}
}
void SharedMutex::Init()
{
	m_sharedNum = m_exclusiveNum = 0;
	m_lockType = LOCK_NONE;

	// �������ڱ����ڲ����ݵĻ�����
    m_mutex = ::CreateMutex(NULL, FALSE, NULL);
    // ��������ͬ����������̵߳��¼����ֶ��¼���
    m_sharedEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
    // ��������ͬ����ռ�����̵߳��¼����Զ��¼���
    m_exclusiveEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);
}

// ��ȡ�������Ȩ
bool SharedMutex::AcquireShared(DWORD waitTime)
{
    ::WaitForSingleObject(m_mutex, INFINITE);
    ++m_sharedNum;
    if (m_lockType == LOCK_EXCLUSIVE) {
        DWORD retCode = ::SignalObjectAndWait(m_mutex, m_sharedEvent, waitTime, FALSE);
        if (retCode == WAIT_OBJECT_0) {
            return true;
        } else {
            if (retCode == WAIT_TIMEOUT)
                ::SetLastError(WAIT_TIMEOUT);
            return false;
        }
    }
    m_lockType = LOCK_SHARED;
    ::ReleaseMutex(m_mutex);
    return true;
}

// �ͷŹ������Ȩ
void SharedMutex::ReleaseShared()
{
    //assert(m_lockType == LOCK_SHARED);
    ::WaitForSingleObject(m_mutex, INFINITE);
    --m_sharedNum;
    if (m_sharedNum == 0) {
        if (m_exclusiveNum > 0) {
            // ����һ����ռ�����߳�
            m_lockType = LOCK_EXCLUSIVE;
            ::SetEvent(m_exclusiveEvent);
        } else {
            // û�еȴ��߳�
            m_lockType = LOCK_NONE;
        }
    }
    ::ReleaseMutex(m_mutex);
}

// ��ȡ��ռ����Ȩ
bool SharedMutex::AcquireExclusive(DWORD waitTime)
{

    ::WaitForSingleObject(m_mutex, INFINITE);
    ++m_exclusiveNum;
    if (m_lockType != LOCK_NONE) {
        DWORD retCode = ::SignalObjectAndWait(m_mutex, m_exclusiveEvent, waitTime, FALSE);
        if (retCode == WAIT_OBJECT_0) {
            return true;
        } else {
            if (retCode == WAIT_TIMEOUT)
                ::SetLastError(WAIT_TIMEOUT);
            return false;
        }
    }
    m_lockType = LOCK_EXCLUSIVE;
    ::ReleaseMutex(m_mutex);
    return true;
}

// �ͷŶ�ռ����Ȩ
void SharedMutex::ReleaseExclusive()
{
//    assert(m_lockType == LOCK_EXCLUSIVE);
    ::WaitForSingleObject(m_mutex, INFINITE);
    --m_exclusiveNum;
    // ��ռ�����߳�����
    if (m_exclusiveNum > 0) {
        // ����һ����ռ�����߳�
        ::SetEvent(m_exclusiveEvent);
    } else if (m_sharedNum > 0) {
        // ���ѵ�ǰ���й�������߳�
        m_lockType = LOCK_SHARED;
        ::PulseEvent(m_sharedEvent);
    } else {
        // û�еȴ��߳�
        m_lockType = LOCK_NONE;
    }
    ::ReleaseMutex(m_mutex);
}
