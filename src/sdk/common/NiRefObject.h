#ifndef NIREFOBJECT_H
#define NIREFOBJECT_H

// NiRefObject provides the reference counting functionality needed for use
// of Gamebryo smart pointers. A class derived from NiRefObject can be used
// with the template class NiPointer.

class NiRefObject
{
public:
    NiRefObject();
    virtual ~NiRefObject();
    void IncRefCount();
    void DecRefCount();
    unsigned int GetRefCount() const;
protected:
    virtual void DeleteThis();
private:
    unsigned int m_uiRefCount;
//    static unsigned int ms_uiObjects;
};

inline NiRefObject::NiRefObject()
{
    m_uiRefCount = 0;
//    NiAtomicIncrement(ms_uiObjects);
}
//---------------------------------------------------------------------------
inline NiRefObject::~NiRefObject()
{
//    NiAtomicDecrement(ms_uiObjects);
}
//---------------------------------------------------------------------------
inline void NiRefObject::IncRefCount()
{
//    NiAtomicIncrement(m_uiRefCount);

	m_uiRefCount ++;
}
//---------------------------------------------------------------------------
inline void NiRefObject::DecRefCount()
{
//  if (NiAtomicDecrement(m_uiRefCount) == 0)
	if (-- m_uiRefCount == 0)
        DeleteThis();
}
//---------------------------------------------------------------------------
inline unsigned int NiRefObject::GetRefCount() const
{
    return m_uiRefCount;
}

inline void NiRefObject::DeleteThis()
{
	delete this;
}

#endif // NIREFOBJECT_H
