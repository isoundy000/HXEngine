#include "HXInspectorWidget.h"
#include <QLabel.h>
//#include <QSpinBox.h>
#include <QBoxLayout.h>
#include <QFormLayout>
#include "HXFogLinear.h"
#include <QHeaderView.h>
#include "HXGLCamera.h"
#include "HXSceneManager.h"
#include "HXRenderSystem.h"

HXInspectorWidget::HXInspectorWidget(QWidget* parent) : QTreeWidget(parent)
, selectedGameObject(NULL)
, fogData(NULL)
, ambientData(NULL)
, cameraData(NULL)
{
	// fog
	checkboxFog = new QCheckBox();
	//checkboxFog->setText("use fog");

	comboboxFogType = new QComboBox();
	comboboxFogType->addItem("FOG_Linear");
	comboboxFogType->addItem("FOG_EXP");
	comboboxFogType->addItem("FOG_EXPX");

	spinboxFogColorR = new QSpinBox();
	spinboxFogColorR->setRange(COLOR_MIN, COLOR_MAX);

	spinboxFogColorG = new QSpinBox();
	spinboxFogColorG->setRange(COLOR_MIN, COLOR_MAX);

	spinboxFogColorB = new QSpinBox();
	spinboxFogColorB->setRange(COLOR_MIN, COLOR_MAX);

	spinboxFogStart = new QDoubleSpinBox();
	spinboxFogStart->setRange(MIN, MAX);

	spinboxFogEnd = new QDoubleSpinBox();
	spinboxFogEnd->setRange(MIN, MAX);

	// ambient
	spinboxAmbientColorR = new QSpinBox();
	spinboxAmbientColorR->setRange(COLOR_MIN, COLOR_MAX);

	spinboxAmbientColorG = new QSpinBox();
	spinboxAmbientColorG->setRange(COLOR_MIN, COLOR_MAX);

	spinboxAmbientColorB = new QSpinBox();
	spinboxAmbientColorB->setRange(COLOR_MIN, COLOR_MAX);

	// camera
	spinboxCameraNear = new QDoubleSpinBox();
	spinboxCameraNear->setRange(MIN, MAX);

	spinboxCameraFar = new QDoubleSpinBox();
	spinboxCameraFar->setRange(MIN, MAX);

	pushbuttonCameraTransSync = new QPushButton();
	pushbuttonCameraTransSync->setText("Sync transform");

	spinboxCameraPositionX = new QDoubleSpinBox();
	spinboxCameraPositionX->setRange(MIN, MAX);

	spinboxCameraPositionY = new QDoubleSpinBox();
	spinboxCameraPositionY->setRange(MIN, MAX);

	spinboxCameraPositionZ = new QDoubleSpinBox();
	spinboxCameraPositionZ->setRange(MIN, MAX);

	spinboxCameraRotationX = new QDoubleSpinBox();
	spinboxCameraRotationX->setRange(MIN, MAX);

	spinboxCameraRotationY = new QDoubleSpinBox();
	spinboxCameraRotationY->setRange(MIN, MAX);

	spinboxCameraRotationZ = new QDoubleSpinBox();
	spinboxCameraRotationZ->setRange(MIN, MAX);

	// gameobject
	editGameObjectName = new QLineEdit();

	spinboxPositionX = new QDoubleSpinBox();
	spinboxPositionX->setRange(MIN, MAX);

	spinboxPositionY = new QDoubleSpinBox();
	spinboxPositionY->setRange(MIN, MAX);

	spinboxPositionZ = new QDoubleSpinBox();
	spinboxPositionZ->setRange(MIN, MAX);

	spinboxRotationX = new QDoubleSpinBox();
	spinboxRotationX->setRange(MIN, MAX);

	spinboxRotationY = new QDoubleSpinBox();
	spinboxRotationY->setRange(MIN, MAX);

	spinboxRotationZ = new QDoubleSpinBox();
	spinboxRotationZ->setRange(MIN, MAX);

	spinboxScaleX = new QDoubleSpinBox();
	spinboxScaleX->setRange(MIN, MAX);

	spinboxScaleY = new QDoubleSpinBox();
	spinboxScaleY->setRange(MIN, MAX);

	spinboxScaleZ = new QDoubleSpinBox();
	spinboxScaleZ->setRange(MIN, MAX);

	// ------------------------------------Layout--------------------------------------------
	QFont font("Microsoft YaHei", 10, 75);
	QFont subFont("Microsoft YaHei", 8, 75);

	QTreeWidget* treeWidget = this;
	QHeaderView *head = treeWidget->header();
	head->setSectionResizeMode(QHeaderView::ResizeToContents);
	treeWidget->setIndentation(8);
	treeWidget->setColumnCount(2);

	QTreeWidgetItem *title = new QTreeWidgetItem;
	title->setFont(0, font);
	title->setText(0, "Inspector");
	title->setText(1, "");
	treeWidget->setHeaderItem(title);
	
	// fog
	fog = new QTreeWidgetItem;
	fog->setText(0, "Fog");
	treeWidget->addTopLevelItem(fog);
	fog->setHidden(true);
	// use fog
	QTreeWidgetItem *usefog = new QTreeWidgetItem;
	usefog->setText(0, "enable");
	fog->addChild(usefog);
	treeWidget->setItemWidget(usefog, 1, checkboxFog);
	// fog type
	QTreeWidgetItem *fogtype = new QTreeWidgetItem;
	fogtype->setText(0, "type");
	fog->addChild(fogtype);
	treeWidget->setItemWidget(fogtype, 1, comboboxFogType);
	// fog color
	QTreeWidgetItem *fogcolor = new QTreeWidgetItem;
	fogcolor->setText(0, "color");
	fog->addChild(fogcolor);
		// fog color R
	QTreeWidgetItem *fogcolorR = new QTreeWidgetItem;
	fogcolorR->setText(0, "R");
	fogcolor->addChild(fogcolorR);
	treeWidget->setItemWidget(fogcolorR, 1, spinboxFogColorR);
		// fog color G
	QTreeWidgetItem *fogcolorG = new QTreeWidgetItem;
	fogcolorG->setText(0, "G");
	fogcolor->addChild(fogcolorG);
	treeWidget->setItemWidget(fogcolorG, 1, spinboxFogColorG);
		// fog color B
	QTreeWidgetItem *fogcolorB = new QTreeWidgetItem;
	fogcolorB->setText(0, "B");
	fogcolor->addChild(fogcolorB);
	treeWidget->setItemWidget(fogcolorB, 1, spinboxFogColorB);
	// fog start
	QTreeWidgetItem *fogstart = new QTreeWidgetItem;
	fogstart->setText(0, "start");
	fog->addChild(fogstart);
	treeWidget->setItemWidget(fogstart, 1, spinboxFogStart);
	// fog end
	QTreeWidgetItem *fogend = new QTreeWidgetItem;
	fogend->setText(0, "end");
	fog->addChild(fogend);
	treeWidget->setItemWidget(fogend, 1, spinboxFogEnd);

	//ambient
	ambient = new QTreeWidgetItem;
	ambient->setText(0, "AmbientLight");
	treeWidget->addTopLevelItem(ambient);
	ambient->setHidden(true);
	// ambient color
	QTreeWidgetItem *ambientcolor = new QTreeWidgetItem;
	ambientcolor->setText(0, "color");
	ambient->addChild(ambientcolor);
	// ambient color R
	QTreeWidgetItem *ambientcolorR = new QTreeWidgetItem;
	ambientcolorR->setText(0, "R");
	ambientcolor->addChild(ambientcolorR);
	treeWidget->setItemWidget(ambientcolorR, 1, spinboxAmbientColorR);
	// ambient color G
	QTreeWidgetItem *ambientcolorG = new QTreeWidgetItem;
	ambientcolorG->setText(0, "G");
	ambientcolor->addChild(ambientcolorG);
	treeWidget->setItemWidget(ambientcolorG, 1, spinboxAmbientColorG);
	// ambient color B
	QTreeWidgetItem *ambientcolorB = new QTreeWidgetItem;
	ambientcolorB->setText(0, "B");
	ambientcolor->addChild(ambientcolorB);
	treeWidget->setItemWidget(ambientcolorB, 1, spinboxAmbientColorB);

	// camera
	camera = new QTreeWidgetItem;
	camera->setText(0, "MainCamera");
	treeWidget->addTopLevelItem(camera);
	camera->setHidden(true);
	// camera near
	QTreeWidgetItem *nearz = new QTreeWidgetItem;
	nearz->setText(0, "near z");
	camera->addChild(nearz);
	treeWidget->setItemWidget(nearz, 1, spinboxCameraNear);
	// camera far
	QTreeWidgetItem *farz = new QTreeWidgetItem;
	farz->setText(0, "far z");
	camera->addChild(farz);
	treeWidget->setItemWidget(farz, 1, spinboxCameraFar);

	// camera transform
	QTreeWidgetItem *camTrans = new QTreeWidgetItem;
	camTrans->setText(0, "transform");
	camera->addChild(camTrans);
	treeWidget->setItemWidget(camTrans, 1, pushbuttonCameraTransSync);
	// camera position
	QTreeWidgetItem *camPos = new QTreeWidgetItem;
	camPos->setText(0, "position");
	camTrans->addChild(camPos);
	// position X
	QTreeWidgetItem *camPosX = new QTreeWidgetItem;
	camPosX->setText(0, "X");
	camPos->addChild(camPosX);
	treeWidget->setItemWidget(camPosX, 1, spinboxCameraPositionX);
	// position Y
	QTreeWidgetItem *camPosY = new QTreeWidgetItem;
	camPosY->setText(0, "Y");
	camPos->addChild(camPosY);
	treeWidget->setItemWidget(camPosY, 1, spinboxCameraPositionY);
	// position Z
	QTreeWidgetItem *camPosZ = new QTreeWidgetItem;
	camPosZ->setText(0, "Z");
	camPos->addChild(camPosZ);
	treeWidget->setItemWidget(camPosZ, 1, spinboxCameraPositionZ);

	// camera rotation
	QTreeWidgetItem *camRot = new QTreeWidgetItem;
	camRot->setText(0, "rotation");
	camTrans->addChild(camRot);
	// rotation X
	QTreeWidgetItem *camRotX = new QTreeWidgetItem;
	camRotX->setText(0, "X");
	camRot->addChild(camRotX);
	treeWidget->setItemWidget(camRotX, 1, spinboxCameraRotationX);
	// rotation Y
	QTreeWidgetItem *camRotY = new QTreeWidgetItem;
	camRotY->setText(0, "Y");
	camRot->addChild(camRotY);
	treeWidget->setItemWidget(camRotY, 1, spinboxCameraRotationY);
	// rotation Z
	QTreeWidgetItem *camRotZ = new QTreeWidgetItem;
	camRotZ->setText(0, "Z");
	camRot->addChild(camRotZ);
	treeWidget->setItemWidget(camRotZ, 1, spinboxCameraRotationZ);

	// gameobject
	gameobject = new QTreeWidgetItem;
	gameobject->setText(0, "GameObject");
	treeWidget->addTopLevelItem(gameobject);
	gameobject->setHidden(true);
	// gameobject name
	QTreeWidgetItem *goname = new QTreeWidgetItem;
	goname->setText(0, "name");
	gameobject->addChild(goname);
	treeWidget->setItemWidget(goname, 1, editGameObjectName);
	// gameobject transform
	QTreeWidgetItem *transform = new QTreeWidgetItem;
	transform->setText(0, "transform");
	gameobject->addChild(transform);
	// gameobject position
	QTreeWidgetItem *position = new QTreeWidgetItem;
	position->setText(0, "position");
	transform->addChild(position);
		// position X
	QTreeWidgetItem *positionX = new QTreeWidgetItem;
	positionX->setText(0, "X");
	position->addChild(positionX);
	treeWidget->setItemWidget(positionX, 1, spinboxPositionX);
		// position Y
	QTreeWidgetItem *positionY = new QTreeWidgetItem;
	positionY->setText(0, "Y");
	position->addChild(positionY);
	treeWidget->setItemWidget(positionY, 1, spinboxPositionY);
		// position Z
	QTreeWidgetItem *positionZ = new QTreeWidgetItem;
	positionZ->setText(0, "Z");
	position->addChild(positionZ);
	treeWidget->setItemWidget(positionZ, 1, spinboxPositionZ);

	// gameobject rotation
	QTreeWidgetItem *rotation = new QTreeWidgetItem;
	rotation->setText(0, "rotation");
	transform->addChild(rotation);
		// rotation X
	QTreeWidgetItem *rotationX = new QTreeWidgetItem;
	rotationX->setText(0, "X");
	rotation->addChild(rotationX);
	treeWidget->setItemWidget(rotationX, 1, spinboxRotationX);
		// rotation Y
	QTreeWidgetItem *rotationY = new QTreeWidgetItem;
	rotationY->setText(0, "Y");
	rotation->addChild(rotationY);
	treeWidget->setItemWidget(rotationY, 1, spinboxRotationY);
		// rotation Z
	QTreeWidgetItem *rotationZ = new QTreeWidgetItem;
	rotationZ->setText(0, "Z");
	rotation->addChild(rotationZ);
	treeWidget->setItemWidget(rotationZ, 1, spinboxRotationZ);

	// gameobject scale
	QTreeWidgetItem *scale = new QTreeWidgetItem;
	scale->setText(0, "scale");
	transform->addChild(scale);
		// scale X
	QTreeWidgetItem *scaleX = new QTreeWidgetItem;
	scaleX->setText(0, "X");
	scale->addChild(scaleX);
	treeWidget->setItemWidget(scaleX, 1, spinboxScaleX);
		// scale Y
	QTreeWidgetItem *scaleY = new QTreeWidgetItem;
	scaleY->setText(0, "Y");
	scale->addChild(scaleY);
	treeWidget->setItemWidget(scaleY, 1, spinboxScaleY);
		// scale Z
	QTreeWidgetItem *scaleZ = new QTreeWidgetItem;
	scaleZ->setText(0, "Z");
	scale->addChild(scaleZ);
	treeWidget->setItemWidget(scaleZ, 1, spinboxScaleZ);

	
	// ------------------------------------QFormLayout-------------------------------------
	//QFormLayout* inspectorLayout = new QFormLayout();
	//QFont font("Microsoft YaHei", 10, 75);
	//QFont subFont("Microsoft YaHei", 8, 75);

	//// fog
	//QLabel* fog = new QLabel(tr("Fog"));
	//fog->setFont(font);
	//inspectorLayout->addRow(fog);
	//inspectorLayout->addRow(checkboxFog);
	//inspectorLayout->addRow(QStringLiteral("fog type"), comboboxFogType);

	//inspectorLayout->addRow(QStringLiteral("Color R"), spinboxFogColorR);
	//inspectorLayout->addRow(QStringLiteral("Color G"), spinboxFogColorG);
	//inspectorLayout->addRow(QStringLiteral("Color B"), spinboxFogColorB);

	//inspectorLayout->addRow(QStringLiteral("Color Start"), spinboxFogStart);
	//inspectorLayout->addRow(QStringLiteral("Color End"), spinboxFogEnd);

	//inspectorLayout->addRow(new QLabel(tr("-----------------------------")));

	//// gameobject
	//QLabel* gameobject = new QLabel(tr("GameObject"));
	//gameobject->setFont(font);
	//inspectorLayout->addRow(gameobject);
	//inspectorLayout->addRow(editGameObjectName);

	////inspectorLayout->addRow(new QLabel(tr("-----------------------------")));

	//QLabel* transform = new QLabel(tr("Transform"));
	//transform->setFont(subFont);
	//inspectorLayout->addRow(transform);
	//inspectorLayout->addRow(QStringLiteral("Position X"), spinboxPositionX);
	//inspectorLayout->addRow(QStringLiteral("Position Y"), spinboxPositionY);
	//inspectorLayout->addRow(QStringLiteral("Position Z"), spinboxPositionZ);
	//inspectorLayout->addRow(new QLabel(tr("")));
	//inspectorLayout->addRow(QStringLiteral("Rotation X"), spinboxRotationX);
	//inspectorLayout->addRow(QStringLiteral("Rotation Y"), spinboxRotationY);
	//inspectorLayout->addRow(QStringLiteral("Rotation Z"), spinboxRotationZ);
	//inspectorLayout->addRow(new QLabel(tr("")));
	//inspectorLayout->addRow(QStringLiteral("Scale X"), spinboxScaleX);
	//inspectorLayout->addRow(QStringLiteral("Scale Y"), spinboxScaleY);
	//inspectorLayout->addRow(QStringLiteral("Scale Z"), spinboxScaleZ);
	//inspectorLayout->addRow(new QLabel(tr("-----------------------------")));

	//setLayout(inspectorLayout);


	// fog
	connect(checkboxFog, SIGNAL(toggled(bool)), this, SLOT(FogToggled(bool)));
	connect(comboboxFogType, SIGNAL(activated(int)), this, SLOT(FogTypeActivated(int)));

	connect(spinboxFogColorR, SIGNAL(valueChanged(int)), this, SLOT(FogColorRChanged(int)));
	connect(spinboxFogColorG, SIGNAL(valueChanged(int)), this, SLOT(FogColorGChanged(int)));
	connect(spinboxFogColorB, SIGNAL(valueChanged(int)), this, SLOT(FogColorBChanged(int)));

	connect(spinboxFogStart, SIGNAL(valueChanged(double)), this, SLOT(FogStartChanged(double)));
	connect(spinboxFogEnd, SIGNAL(valueChanged(double)), this, SLOT(FogEndChanged(double)));

	// ambient
	connect(spinboxAmbientColorR, SIGNAL(valueChanged(int)), this, SLOT(AmbientColorRChanged(int)));
	connect(spinboxAmbientColorG, SIGNAL(valueChanged(int)), this, SLOT(AmbientColorGChanged(int)));
	connect(spinboxAmbientColorB, SIGNAL(valueChanged(int)), this, SLOT(AmbientColorBChanged(int)));

	// camera
	connect(spinboxCameraNear, SIGNAL(valueChanged(double)), this, SLOT(CameraNearChanged(double)));
	connect(spinboxCameraFar, SIGNAL(valueChanged(double)), this, SLOT(CameraFarChanged(double)));

	connect(pushbuttonCameraTransSync, SIGNAL(clicked()), this, SLOT(TransSyncOnClick()));

	connect(spinboxCameraPositionX, SIGNAL(valueChanged(double)), this, SLOT(CameraPositionXValueChanged(double)));
	connect(spinboxCameraPositionY, SIGNAL(valueChanged(double)), this, SLOT(CameraPositionYValueChanged(double)));
	connect(spinboxCameraPositionZ, SIGNAL(valueChanged(double)), this, SLOT(CameraPositionZValueChanged(double)));

	connect(spinboxCameraRotationX, SIGNAL(valueChanged(double)), this, SLOT(CameraRotationXValueChanged(double)));
	connect(spinboxCameraRotationY, SIGNAL(valueChanged(double)), this, SLOT(CameraRotationYValueChanged(double)));
	connect(spinboxCameraRotationZ, SIGNAL(valueChanged(double)), this, SLOT(CameraRotationZValueChanged(double)));

	// gameobject
	connect(editGameObjectName, &QLineEdit::textChanged, this, &HXInspectorWidget::GameObjectNameChanged);
	connect(spinboxPositionX, SIGNAL(valueChanged(double)), this, SLOT(PositionXValueChanged(double)));
	connect(spinboxPositionY, SIGNAL(valueChanged(double)), this, SLOT(PositionYValueChanged(double)));
	connect(spinboxPositionZ, SIGNAL(valueChanged(double)), this, SLOT(PositionZValueChanged(double)));

	connect(spinboxRotationX, SIGNAL(valueChanged(double)), this, SLOT(RotationXValueChanged(double)));
	connect(spinboxRotationY, SIGNAL(valueChanged(double)), this, SLOT(RotationYValueChanged(double)));
	connect(spinboxRotationZ, SIGNAL(valueChanged(double)), this, SLOT(RotationZValueChanged(double)));

	connect(spinboxScaleX, SIGNAL(valueChanged(double)), this, SLOT(ScaleXValueChanged(double)));
	connect(spinboxScaleY, SIGNAL(valueChanged(double)), this, SLOT(ScaleYValueChanged(double)));
	connect(spinboxScaleZ, SIGNAL(valueChanged(double)), this, SLOT(ScaleZValueChanged(double)));
}

HXInspectorWidget::~HXInspectorWidget()
{

}

void HXInspectorWidget::SetGameObjectInfo(HXGameObject* pGameObject)
{
	selectedGameObject = pGameObject;
	if (selectedGameObject)
	{
		gameobject->setHidden(false);
	}
	else
	{
		gameobject->setHidden(true);
		return;
	}
	SetGameObjectName();
	SetGameObjectTransform();
}

void HXInspectorWidget::SetFogInfo(HXFogBase* pFog)
{
	fogData = pFog;
	if (pFog)
	{
		fog->setHidden(false);
		////checkboxFog->setCheckable(pFog->useFog);
		////checkboxFog->toggled(pFog->useFog);
		//checkboxFog->setChecked(true);
		if (pFog->useFog)
		{
			checkboxFog->setCheckState(Qt::Checked);
		}
		else
		{
			checkboxFog->setCheckState(Qt::Unchecked);
		}

		spinboxFogColorR->setValue(pFog->fogColor.r);
		spinboxFogColorG->setValue(pFog->fogColor.g);
		spinboxFogColorB->setValue(pFog->fogColor.b);
		if (pFog->fogType == HXFogType::FOG_Linear)
		{
			comboboxFogType->setCurrentIndex(0);
			HXFogLinear* pFogLinear = (HXFogLinear*)pFog;
			spinboxFogStart->setValue(pFogLinear->fogStart);
			spinboxFogEnd->setValue(pFogLinear->fogEnd);
		}
	}
	else
	{
		fog->setHidden(true);
	}
}

void HXInspectorWidget::SetAmbientInfo(HXCOLOR* pAmbient)
{
	ambientData = pAmbient;
	if (ambientData)
	{
		ambient->setHidden(false);
		spinboxAmbientColorR->setValue(pAmbient->r);
		spinboxAmbientColorG->setValue(pAmbient->g);
		spinboxAmbientColorB->setValue(pAmbient->b);
	}
	else
	{
		ambient->setHidden(true);
	}
}

void HXInspectorWidget::SetCameraInfo(HXICamera* pCamera)
{
	cameraData = (HXGLCamera*)pCamera;
	if (cameraData)
	{
		camera->setHidden(false);

		spinboxCameraNear->setValue(cameraData->mNear);
		spinboxCameraFar->setValue(cameraData->mFar);

		spinboxCameraPositionX->setValue(cameraData->transform->mPostion.x);
		spinboxCameraPositionY->setValue(cameraData->transform->mPostion.y);
		spinboxCameraPositionZ->setValue(cameraData->transform->mPostion.z);

		spinboxCameraRotationX->setValue(cameraData->transform->mEulerDegree.x);
		spinboxCameraRotationY->setValue(cameraData->transform->mEulerDegree.y);
		spinboxCameraRotationZ->setValue(cameraData->transform->mEulerDegree.z);
	}
	else
	{
		camera->setHidden(true);
	}
}

void HXInspectorWidget::SetGameObjectName()
{
	if (selectedGameObject)
	{
		editGameObjectName->setText(selectedGameObject->GetName().c_str());
	}
	else
	{
		editGameObjectName->setText("");
	}
}

void HXInspectorWidget::SetGameObjectTransform()
{
	if (selectedGameObject && selectedGameObject->GetTransform())
	{
		HXITransform* pTransform = selectedGameObject->GetTransform();

		spinboxPositionX->setValue(pTransform->GetPosition().x);
		spinboxPositionY->setValue(pTransform->GetPosition().y);
		spinboxPositionZ->setValue(pTransform->GetPosition().z);

		spinboxRotationX->setValue(pTransform->GetRotation().x);
		spinboxRotationY->setValue(pTransform->GetRotation().y);
		spinboxRotationZ->setValue(pTransform->GetRotation().z);

		spinboxScaleX->setValue(pTransform->GetScale().x);
		spinboxScaleY->setValue(pTransform->GetScale().y);
		spinboxScaleZ->setValue(pTransform->GetScale().z);
	}
	else
	{
		spinboxPositionX->setValue(0);
		spinboxPositionY->setValue(0);
		spinboxPositionZ->setValue(0);

		spinboxRotationX->setValue(0);
		spinboxRotationY->setValue(0);
		spinboxRotationZ->setValue(0);

		spinboxScaleX->setValue(0);
		spinboxScaleY->setValue(0);
		spinboxScaleZ->setValue(0);
	}
}

void HXInspectorWidget::GameObjectNameChanged(const QString& name)
{
	if (selectedGameObject)
	{
		selectedGameObject->SetName(name.toStdString());
	}
}

void HXInspectorWidget::PositionXValueChanged(double value)
{
	if (selectedGameObject)
	{
		HXVector3D pos = selectedGameObject->GetTransform()->GetPosition();
		selectedGameObject->GetTransform()->SetPosition(HXVector3D(value, pos.y, pos.z));
	}
}
void HXInspectorWidget::PositionYValueChanged(double value)
{
	if (selectedGameObject)
	{
		HXVector3D pos = selectedGameObject->GetTransform()->GetPosition();
		selectedGameObject->GetTransform()->SetPosition(HXVector3D(pos.x, value, pos.z));
	}
}
void HXInspectorWidget::PositionZValueChanged(double value)
{
	if (selectedGameObject)
	{
		HXVector3D pos = selectedGameObject->GetTransform()->GetPosition();
		selectedGameObject->GetTransform()->SetPosition(HXVector3D(pos.x, pos.y, value));
	}
}

void HXInspectorWidget::RotationXValueChanged(double value)
{
	if (selectedGameObject)
	{
		HXVector3D rotate = selectedGameObject->GetTransform()->GetRotation();
		selectedGameObject->GetTransform()->SetRotation(HXVector3D(value, rotate.y, rotate.z));
	}
}
void HXInspectorWidget::RotationYValueChanged(double value)
{
	if (selectedGameObject)
	{
		HXVector3D rotate = selectedGameObject->GetTransform()->GetRotation();
		selectedGameObject->GetTransform()->SetRotation(HXVector3D(rotate.x, value, rotate.z));
	}
}
void HXInspectorWidget::RotationZValueChanged(double value)
{
	if (selectedGameObject)
	{
		HXVector3D rotate = selectedGameObject->GetTransform()->GetRotation();
		selectedGameObject->GetTransform()->SetRotation(HXVector3D(rotate.x, rotate.y, value));
	}
}

void HXInspectorWidget::ScaleXValueChanged(double value)
{
	if (selectedGameObject)
	{
		HXVector3D scale = selectedGameObject->GetTransform()->GetScale();
		selectedGameObject->GetTransform()->SetScale(HXVector3D(value, scale.y, scale.z));
	}
}
void HXInspectorWidget::ScaleYValueChanged(double value)
{
	if (selectedGameObject)
	{
		HXVector3D scale = selectedGameObject->GetTransform()->GetScale();
		selectedGameObject->GetTransform()->SetScale(HXVector3D(scale.x, value, scale.z));
	}
}
void HXInspectorWidget::ScaleZValueChanged(double value)
{
	if (selectedGameObject)
	{
		HXVector3D scale = selectedGameObject->GetTransform()->GetScale();
		selectedGameObject->GetTransform()->SetScale(HXVector3D(scale.x, scale.y, value));
	}
}

void HXInspectorWidget::FogToggled(bool useFog)
{
	if (fogData)
	{
		fogData->useFog = useFog;
	}
}

void HXInspectorWidget::FogTypeActivated(int index)
{
	// TODO: 暂时只实现了线性雾
}

void HXInspectorWidget::FogColorRChanged(int value)
{
	if (fogData)
	{
		fogData->fogColor.r = value;
	}
}
void HXInspectorWidget::FogColorGChanged(int value)
{
	if (fogData)
	{
		fogData->fogColor.g = value;
	}
}
void HXInspectorWidget::FogColorBChanged(int value)
{
	if (fogData)
	{
		fogData->fogColor.b = value;
	}
}

void HXInspectorWidget::FogStartChanged(double value)
{
	if (fogData && fogData->fogType == HXFogType::FOG_Linear)
	{
		HXFogLinear* fogLinear = (HXFogLinear*)fogData;
		fogLinear->fogStart = value;
	}
}

void HXInspectorWidget::FogEndChanged(double value)
{
	if (fogData && fogData->fogType == HXFogType::FOG_Linear)
	{
		HXFogLinear* fogLinear = (HXFogLinear*)fogData;
		fogLinear->fogEnd = value;
	}
}

void HXInspectorWidget::AmbientColorRChanged(int value)
{
	if (ambientData)
	{
		ambientData->r = value;
	}
}
void HXInspectorWidget::AmbientColorGChanged(int value)
{
	if (ambientData)
	{
		ambientData->g = value;
	}
}
void HXInspectorWidget::AmbientColorBChanged(int value)
{
	if (ambientData)
	{
		ambientData->b = value;
	}
}

void HXInspectorWidget::CameraNearChanged(double value)
{
	if (cameraData)
	{
		cameraData->mNear = value;
		float gAspect = (float)HXRenderSystem::gCurScreenWidth / (float)HXRenderSystem::gCurScreenHeight;
		cameraData->UpdateProjectionMatrix(-1, 1, -gAspect, gAspect, cameraData->mNear, cameraData->mFar);
	}
}

void HXInspectorWidget::CameraFarChanged(double value)
{
	if (cameraData)
	{
		cameraData->mFar = value;
		float gAspect = (float)HXRenderSystem::gCurScreenWidth / (float)HXRenderSystem::gCurScreenHeight;
		cameraData->UpdateProjectionMatrix(-1, 1, -gAspect, gAspect, cameraData->mNear, cameraData->mFar);
	}
}

void HXInspectorWidget::TransSyncOnClick()
{
	SetCameraInfo(HXSceneManager::GetInstance()->GetMainCamera());
}

void HXInspectorWidget::CameraPositionXValueChanged(double value)
{
	if (cameraData)
	{
		HXVector3D pos = cameraData->transform->GetPosition();
		cameraData->transform->SetPosition(HXVector3D(value, pos.y, pos.z));
	}
}
void HXInspectorWidget::CameraPositionYValueChanged(double value)
{
	if (cameraData)
	{
		HXVector3D pos = cameraData->transform->GetPosition();
		cameraData->transform->SetPosition(HXVector3D(pos.x, value, pos.z));
	}
}
void HXInspectorWidget::CameraPositionZValueChanged(double value)
{
	if (cameraData)
	{
		HXVector3D pos = cameraData->transform->GetPosition();
		cameraData->transform->SetPosition(HXVector3D(pos.x, pos.y, value));
	}
}

void HXInspectorWidget::CameraRotationXValueChanged(double value)
{
	if (cameraData)
	{
		HXVector3D rotate = cameraData->transform->GetRotation();
		cameraData->transform->SetRotation(HXVector3D(value, rotate.y, rotate.z));
	}
}
void HXInspectorWidget::CameraRotationYValueChanged(double value)
{
	if (cameraData)
	{
		HXVector3D rotate = cameraData->transform->GetRotation();
		cameraData->transform->SetRotation(HXVector3D(rotate.x, value, rotate.z));
	}
}
void HXInspectorWidget::CameraRotationZValueChanged(double value)
{
	if (cameraData)
	{
		HXVector3D rotate = cameraData->transform->GetRotation();
		cameraData->transform->SetRotation(HXVector3D(rotate.x, rotate.y, value));
	}
}