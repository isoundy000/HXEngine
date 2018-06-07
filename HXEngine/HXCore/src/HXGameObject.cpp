#include "..\include\HXGameObject.h"
#include "HXMesh.h"
#include "HXCore.h"
#include "HXMath.h"
#include "HXRenderSystem.h"

namespace HX3D
{
	HXGameObject::HXGameObject(std::string strName, HXMesh* pMesh, HXRenderSystem* pRenderSystem)
	{
		m_strName = strName;
		m_pMesh = pMesh;
		m_pFather = NULL;
		m_pTransform = pRenderSystem->CreateTransform();
		/*mPostion = HXVector3D(0,0,0);
		mEulerDegree = HXVector3D(0,0,0);
		mScale = HXVector3D(1,1,1);*/
	}

	HXGameObject::~HXGameObject()
	{
		if (m_pMesh)
		{
			delete m_pMesh;
			m_pMesh = NULL;
		}
		if (m_pTransform)
		{
			delete m_pTransform;
			m_pTransform = NULL;
		}
	}

	void HXGameObject::Update()
	{
		if (m_pFather)
		{
			m_pTransform->CaculateModelMatrix(m_pFather->m_pTransform->mCurModelMatrix);
		}
		else
		{
			m_pTransform->CaculateModelMatrix();
		}
		if (m_pMesh)
		{
			m_pMesh->UpdateAnimation();
		}
	}

	/*void HXGameObject::Insert_To_RenderList(HXRenderList* pRenderList)
	{
		m_pMesh->Insert_To_RenderList(mPostion, mEulerDegree, mScale, pRenderList);
	}*/

	void HXGameObject::SetPostion(const HXVector3D& pos)
	{
		m_pTransform->mPostion = pos;
	}

	HXVector3D HXGameObject::GetPosition()
	{
		return m_pTransform->mPostion;
	}

	void HXGameObject::Move(const HXVector3D& mov)
	{
		m_pTransform->mPostion += mov;
	}

	void HXGameObject::SetRotation(const HXVector3D& rotation)
	{
		m_pTransform->mEulerDegree = rotation;
	}

	HXVector3D HXGameObject::GetRotation()
	{
		return m_pTransform->mEulerDegree;
	}

	void HXGameObject::Pitch(float fDegree)
	{
		m_pTransform->mEulerDegree.x = fDegree;
	}

	void HXGameObject::Yaw(float fDegree)
	{
		m_pTransform->mEulerDegree.y = fDegree;
	}

	void HXGameObject::Roll(float fDegree)
	{
		m_pTransform->mEulerDegree.z = fDegree;
	}

	void HXGameObject::SetScale(const HXVector3D& scale)
	{
		m_pTransform->mScale = scale;
	}
	HXVector3D HXGameObject::GetScale()
	{
		return m_pTransform->mScale;
	}

	HXMesh* HXGameObject::GetMesh()
	{
		return m_pMesh;
	}

	HXGameObject* HXGameObject::GetFather()
	{
		return m_pFather;
	}

	void HXGameObject::SetFather(HXGameObject* father)
	{
		m_pFather = father;
	}

	HXITransform* HXGameObject::GetTransform()
	{
		return m_pTransform;
	}
}


