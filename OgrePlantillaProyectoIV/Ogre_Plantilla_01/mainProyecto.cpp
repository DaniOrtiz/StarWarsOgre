#include "Ogre\ExampleApplication.h"

float ang = 10; 
float r = 0;
bool abiertas = false;
float angN = 0.0;
float maxX = 0.0;
float maxy = 0.0;

Ogre::AnimationState* animationLaser01;
Ogre::AnimationState* animationLaser02;
Ogre::AnimationState* animationLaser03;
Ogre::AnimationState* animationLaser04;

class FrameListenerClase : public Ogre::FrameListener { // Hereda de la clase FrameListener de Ogre, escucha algo

private:
	Ogre::Camera* _cam;
	Ogre::SceneNode* _nodoNave; // Creamos nodo

	OIS::InputManager* _man;
	OIS::Keyboard* _key; // Teclado
	OIS::Mouse* _mouse; // Mouse

	//movimiento alas
	Ogre::SceneNode*  _nodoAlaI01;  
	Ogre::SceneNode*  _nodoAlaI02;  
	Ogre::SceneNode*  _nodoAlaD01;  
	Ogre::SceneNode*  _nodoAlaD02;  

public:
	// Constructor que le asignamos el nodo que creamos
	FrameListenerClase(Ogre::SceneNode* nodoNave01, 
					   Ogre::SceneNode* nodoAlaI01, 
					   Ogre::SceneNode* nodoAlaI02, 
					   Ogre::SceneNode* nodoAlaD01, 
					   Ogre::SceneNode* nodoAlaD02, 
					   Ogre::Camera* cam, 
					   RenderWindow* win) {

		// Configuracion captura teclado y mouse
		// ESTO ES ASI PORQUE SI, NO CAMBIA
		size_t windowHnd = 0;
		std::stringstream windowHndStr;
		win->getCustomAttribute("WINDOW", &windowHnd);
		windowHndStr << windowHnd;

		OIS::ParamList pl;
		pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

		// Eventos

		_man = OIS::InputManager::createInputSystem(pl);
		_key = static_cast< OIS::Keyboard*>(_man->createInputObject(OIS::OISKeyboard, false));
		_mouse = static_cast< OIS::Mouse*>(_man->createInputObject(OIS::OISMouse, false));

		_nodoNave = nodoNave01;

		_nodoAlaI01 = nodoAlaI01;
		_nodoAlaI02 = nodoAlaI02;
		_nodoAlaD01 = nodoAlaD01;
		_nodoAlaD02 = nodoAlaD02;

		_cam = cam;
	}

	~FrameListenerClase() {
		_man ->destroyInputObject(_key);
		_man->destroyInputObject(_mouse);
		OIS::InputManager::destroyInputSystem(_man);
	}

	bool frameStarted(const Ogre::FrameEvent &evt) {
			
		_key->capture();
		_mouse->capture();

		float movSpeed = 10.0f;
		Ogre::Vector3 tcam(0,0,0);
		float a = 0.0;
		bool abiertas = false;

		Ogre::Vector3 x;

		if (_key->isKeyDown(OIS::KC_ESCAPE))
			return false;

		// Teclas para la mover la camara
			
		// Si presionamos la tecla w
		if(_key->isKeyDown(OIS::KC_W)){		
			maxy -= 0.53;
			if(maxy > -1300){
				tcam += Ogre::Vector3(0,0,-10);
			}
		}

		// Si presionamos la tecla a
		if(_key->isKeyDown(OIS::KC_A)){	
			maxX -= 0.6;
			if(maxX > -28){
				tcam += Ogre::Vector3(-10,0,0);	
				if( r < 0) r = 0;
				else if(r == 0) r = 0.3;
				_nodoNave->roll(Ogre::Degree(r));
			}else{
				maxX += 0.6;
			}
		}

		// Si presionamos la tecla d
		if(_key->isKeyDown(OIS::KC_D)){	
			maxX += 0.6;
			if(maxX < 28){
				tcam += Ogre::Vector3(10,0,0);
				if( r > 0) r = 0;
				else if(r == 0) r = -0.3;
				_nodoNave->roll(Ogre::Degree(r));				
			}else{
				maxX -= 0.6;
			}
		}


		if(_key->isKeyDown(OIS::KC_E)){	
			angN += 10 * evt.timeSinceLastFrame;
			if(angN < 20){
				_nodoAlaI01->roll(Ogre::Degree( 10 * evt.timeSinceLastFrame ) );
				_nodoAlaI02->roll(Ogre::Degree(-10 * evt.timeSinceLastFrame) );
				_nodoAlaD01->roll(Ogre::Degree( 10 * evt.timeSinceLastFrame ) );
				_nodoAlaD02->roll(Ogre::Degree(-10 * evt.timeSinceLastFrame ) );
			}else{
				angN -= 10 * evt.timeSinceLastFrame;
			}
		}

		if(_key->isKeyDown(OIS::KC_R)){		
			angN -= 10 * evt.timeSinceLastFrame;
			if(angN > 0){
				_nodoAlaI01->roll(Ogre::Degree(-10 * evt.timeSinceLastFrame ) );
				_nodoAlaI02->roll(Ogre::Degree( 10 * evt.timeSinceLastFrame) );
				_nodoAlaD01->roll(Ogre::Degree(-10 * evt.timeSinceLastFrame ) );
				_nodoAlaD02->roll(Ogre::Degree( 10 * evt.timeSinceLastFrame ) );	
			}else{
				angN += 10 * evt.timeSinceLastFrame;
			}
		}
		// Camara Control
		//float rotX = _mouse->getMouseState().X.rel * evt.timeSinceLastFrame * -1;
		//float rotY = _mouse->getMouseState().Y.rel * evt.timeSinceLastFrame * -1;
		//_cam->yaw(Ogre::Radian(rotX));
		//_cam->pitch(Ogre::Radian(rotY));
		_cam->moveRelative(tcam*movSpeed*evt.timeSinceLastFrame);
		_nodoNave->translate(tcam*movSpeed*evt.timeSinceLastFrame);

		//Animacion de los Laser
		
		animationLaser01 -> addTime(evt.timeSinceLastFrame);
		animationLaser02 -> addTime(evt.timeSinceLastFrame);
		animationLaser03 -> addTime(evt.timeSinceLastFrame);
		animationLaser04 -> addTime(evt.timeSinceLastFrame);
		
		return true;

	}
};

class Example1 : public ExampleApplication
{

public:
	Ogre::SceneNode* nodoNave;
	Ogre::FrameListener* FrameListener01; // Objeto de FrameListener

	Ogre::SceneNode* nodoAlaI02;
	Ogre::SceneNode* nodoAlaI01;
	Ogre::SceneNode* nodoAlaD01;
	Ogre::SceneNode* nodoAlaD02;

	//Ogre::SceneNode* nodeCamara;

	// Constructor
	Example1() {
		FrameListener01 = NULL;
	}

	// Para destruir la variable FrameListener cuando acabe el programa
	~Example1() {
		if (FrameListener01) {
			delete FrameListener01;
		}
	}

	// Metodo
	void createFrameListener() {
		FrameListener01 = new FrameListenerClase(nodoNave,nodoAlaI02,nodoAlaI01,nodoAlaD01,nodoAlaD02,mCamera, mWindow); 
		mRoot->addFrameListener(FrameListener01);
	}

	void createCamera() {

		mCamera = mSceneMgr->createCamera("MyCamera1");
		mCamera->setPosition(0.0,6,34);
		mCamera->lookAt(0,6,-50);
		mCamera->setNearClipDistance(5);
	}

	void createScene()
	{

		mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0, 1.0, 1.0));
		mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
		mSceneMgr->setSkyBox(true, "AndreaCenteno_Estrellas/SkyBox");

		Ogre::Entity* entEscena01 = mSceneMgr->createEntity("ogre_base01.mesh");
		mSceneMgr->getRootSceneNode()->attachObject(entEscena01);

		Ogre::Entity* entEscena02 = mSceneMgr->createEntity("ogre_fondo01.mesh");
		mSceneMgr->getRootSceneNode()->attachObject(entEscena02);

		Ogre::Entity* entEscena03 = mSceneMgr->createEntity("ogre_pared01.mesh");
		mSceneMgr->getRootSceneNode()->attachObject(entEscena03);

		Ogre::Entity* entEscena04 = mSceneMgr->createEntity("ogre_pared02.mesh");
		mSceneMgr->getRootSceneNode()->attachObject(entEscena04);

		Ogre::Entity* entEscena05 = mSceneMgr->createEntity("ogre_pared03.mesh");
		mSceneMgr->getRootSceneNode()->attachObject(entEscena05);

		Ogre::Entity* entEscena06 = mSceneMgr->createEntity("ogre_torretas01.mesh");
		mSceneMgr->getRootSceneNode()->attachObject(entEscena06);

		
		// Creando Texturas

		//Texturas para Torretas
		Ogre::MaterialPtr materialTorretas = Ogre::MaterialManager::getSingleton().create(
			"Cuerpo", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

		Ogre::TextureUnitState* torretaTexture =
			materialTorretas ->getTechnique(0) ->getPass(0)->createTextureUnitState("RustySteel.jpg");
		
		Ogre::MaterialPtr materialTorretas2 = Ogre::MaterialManager::getSingleton().create(
			"OtrasPartes", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

		Ogre::TextureUnitState* torretaTexture2 =
			materialTorretas2 ->getTechnique(0) ->getPass(0)->createTextureUnitState("tex_mTorretas01.png");

		Ogre::MaterialPtr materialTorretas3 = Ogre::MaterialManager::getSingleton().create(
			"Canon", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

		Ogre::TextureUnitState* torretaTexture3 =
			materialTorretas3 ->getTechnique(0) ->getPass(0)->createTextureUnitState("RustedMetal.jpg");

		Ogre::MaterialPtr materialLaser = Ogre::MaterialManager::getSingleton().create(
			"Laser", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

		Ogre::TextureUnitState* laserTexture =
			materialLaser ->getTechnique(0) ->getPass(0)->createTextureUnitState("nm_up.png");

		/*******************************************************	
					  _ __   __ ___   _____ 
					 | '_ \ / _` \ \ / / _ \
					 | | | | (_| |\ V /  __/
					 |_| |_|\__,_| \_/ \___|
		*******************************************************/
		const float x1 = 1.8;
		const float y1 = 1.7;
		const float z1 = 6.0;
		//parte de atras de la nave
		ManualObject* manual = mSceneMgr->createManualObject("manual");
		manual->begin("DanielaOrtiz_Nave/Gris", RenderOperation::OT_TRIANGLE_STRIP);

			manual->position( 2.3, 0.0, z1-7);
			manual->position(  x1, -y1, z1);
			manual->position(  x1, -y1, z1-7);
			manual->position( -x1, -y1, z1);
			manual->position( -x1, -y1, z1-7);
			manual->position(-2.3, 0.0, z1);
			manual->position(-2.3, 0.0, z1-7);
			manual->position( -x1,  y1, z1);
			manual->position( -x1,  y1, z1-7);
			manual->position(  x1,  y1, z1);
			manual->position(  x1,  y1, z1-7);
			manual->position( 2.3, 0.0, z1);
			manual->position( 2.3, 0.0, z1-7);
			manual->position(  x1, -y1, z1);

			for(int i = 0; i < 15; i++){
				manual->index(i);
			}

		manual->end();
		manual->convertToMesh("MeshNave");
		Ogre::Entity* entNave = mSceneMgr->createEntity("MeshNave");
		nodoNave = mSceneMgr->createSceneNode("NodoNave");
		mSceneMgr->getRootSceneNode()->addChild(nodoNave);
		nodoNave->attachObject(entNave);
		nodoNave->translate(0.0,-2,0.0);
		//entNave->setMaterialName("DanielaOrtiz_Nave/Gris");

		//cara de atras
		ManualObject* manualCara = mSceneMgr->createManualObject("manualCara");
		manualCara->begin("DanielaOrtiz_Nave/Gris", RenderOperation::OT_TRIANGLE_STRIP);

			manualCara->position(-2.3, 0.0, z1);
			manualCara->position( -x1, -y1, z1);
			manualCara->position( -x1,  y1, z1);
			manualCara->position(  x1, -y1, z1);
			manualCara->position(  x1,  y1, z1);
			manualCara->position( 2.3, 0.0, z1);

			for(int i = 0; i < 7; i++){
				manualCara->index(i);
			}

		manualCara->end();
		manualCara->convertToMesh("MeshNaveBase01");
		Ogre::Entity* entNaveBase01 = mSceneMgr->createEntity("MeshNaveBase01");
		Ogre::SceneNode* nodoNaveBase01 = mSceneMgr->createSceneNode("NodoNaveBase01");
		nodoNave->addChild(nodoNaveBase01);
		nodoNaveBase01->attachObject(entNaveBase01);

		const float x2 = 0.6;
		const float y2 = 0.4;
		const float z2 = -8.0;
		//parte de al frente
		ManualObject* manualFrente = mSceneMgr->createManualObject("manualFrente");
		manualFrente->begin("DanielaOrtiz_Nave/Gris", RenderOperation::OT_TRIANGLE_STRIP);

			manualFrente->position( 0.8, 0.0, z2);
			manualFrente->position(  x1, -y1, z2+7);
			manualFrente->position(  x2, -y2, z2);
			manualFrente->position( -x1, -y1, z2+7);
			manualFrente->position( -x2, -y2, z2);
			manualFrente->position(-2.3, 0.0, z2+7);
			manualFrente->position(-0.8, 0.0, z2);
			manualFrente->position( -x1,  y1, z2+7);
			manualFrente->position( -x2,  y2, z2);
			manualFrente->position(  x1,  y1, z2+7);
			manualFrente->position(  x2,  y2, z2);
			manualFrente->position( 2.3, 0.0, z2+7);
			manualFrente->position( 0.8, 0.0, z2);
			manualFrente->position(  x1, -y1, z2+7);

			for(int i = 0; i < 15; i++){
				manualFrente->index(i);
			}
  
		manualFrente->end();
		manualFrente->convertToMesh("MeshNaveBase02");
		Ogre::Entity* entNaveBase02 = mSceneMgr->createEntity("MeshNaveBase02");
		Ogre::SceneNode* nodoNaveBase02 = mSceneMgr->createSceneNode("NodoNaveBase02");
		nodoNave->addChild(nodoNaveBase02);
		nodoNaveBase02->attachObject(entNaveBase02);

		/*	        _           
			       | |          
			   __ _| | __ _ ___ 
			  / _` | |/ _` / __|
			 | (_| | | (_| \__ \
			  \__,_|_|\__,_|___/
		*/
		//	Mesh de las laas
		Ogre::ManualObject* manualAlaCara = mSceneMgr->createManualObject("manualAlaCara");
			manualAlaCara->begin("DanielaOrtiz_Nave/Gris", RenderOperation::OT_TRIANGLE_STRIP);

			manualAlaCara->position(2, 0.3, 6);
			manualAlaCara->position(8, 0.3, 4);
			manualAlaCara->position(8, 0.3, 2);
			manualAlaCara->position(2, 0.3, 0);

			for(int i = 0; i < 5; i++){
				manualAlaCara->index(i);
			}
		manualAlaCara->end();
		manualAlaCara->convertToMesh("MeshAlaCara");

		Ogre::ManualObject* manualAlaBorde = mSceneMgr->createManualObject("manualAlaBorde");
			manualAlaBorde->begin("DanielaOrtiz_Nave/Gris", RenderOperation::OT_TRIANGLE_STRIP);

			manualAlaBorde->position( 2, 0.3, 6);
			manualAlaBorde->position( 2, 0.0, 6);
			manualAlaBorde->position( 8, 0.3, 4);
			manualAlaBorde->position( 8, 0.0, 4);
			manualAlaBorde->position( 8, 0.3, 2);
			manualAlaBorde->position( 8, 0.0, 2);
			manualAlaBorde->position( 2, 0.3, 0);
			manualAlaBorde->position( 2, 0.0, 0);

			for(int i = 0; i < 9; i++){
				manualAlaBorde->index(i);
			}
		manualAlaBorde->end();
		manualAlaBorde->convertToMesh("MeshAlaBorde");

		//entidades
		Ogre::Entity* entAlaI02;
		Ogre::Entity* entAlaI01;
		Ogre::Entity* entAlaD01;
		Ogre::Entity* entAlaD02;

		//CARAS DERECHAS ALAS
		entAlaD01 = mSceneMgr->createEntity("MeshAlaCara");
		nodoAlaD01 = mSceneMgr->createSceneNode("NodoAlaD01");
		nodoNave->addChild(nodoAlaD01);
		nodoAlaD01->attachObject(entAlaD01);
		//borde
		Ogre::Entity* entAlaIB01 = mSceneMgr->createEntity("MeshAlaBorde");
		Ogre::SceneNode* nodoAlaIB01 = mSceneMgr->createSceneNode("NodoAlaIB01");
		nodoAlaD01->addChild(nodoAlaIB01);
		nodoAlaIB01->attachObject(entAlaIB01);

		entAlaD02 = mSceneMgr->createEntity("MeshAlaCara");
		nodoAlaD02 = mSceneMgr->createSceneNode("NodoAlaD02");
		nodoNave->addChild(nodoAlaD02);
		nodoAlaD02->translate(0.0,-0.305,0.0);
		nodoAlaD02->attachObject(entAlaD02);
		//borde
		Ogre::Entity* entAlaIB02 = mSceneMgr->createEntity("MeshAlaBorde");
		Ogre::SceneNode* nodoAlaIB02 = mSceneMgr->createSceneNode("NodoAlaIB02");
		nodoAlaD02->addChild(nodoAlaIB02);
		nodoAlaIB02->attachObject(entAlaIB02);

		//CARAS IZQUIERDAS ALAS
		entAlaI02 = mSceneMgr->createEntity("MeshAlaCara");
		nodoAlaI02 = mSceneMgr->createSceneNode("NodoAlaI02");
		nodoNave->addChild(nodoAlaI02);
		nodoAlaI02->yaw(Ogre::Degree( 180 ) );
		nodoAlaI02->translate(0.0,0.0,6);
		nodoAlaI02->attachObject(entAlaI02);
		//borde
		Ogre::Entity* entAlaB03 = mSceneMgr->createEntity("MeshAlaBorde");
		Ogre::SceneNode* nodoAlaB03 = mSceneMgr->createSceneNode("NodoAlaB03");
		nodoAlaI02->addChild(nodoAlaB03);
		nodoAlaB03->attachObject(entAlaB03);

		entAlaI01 = mSceneMgr->createEntity("MeshAlaCara");
		nodoAlaI01 = mSceneMgr->createSceneNode("NodoAlaI01");
		nodoNave->addChild(nodoAlaI01);
		nodoAlaI01->yaw(Ogre::Degree( 180 ) );
		nodoAlaI01->translate(0.0,-0.305,6);
		nodoAlaI01->attachObject(entAlaI01);
		//borde
		Ogre::Entity* entAlaB04 = mSceneMgr->createEntity("MeshAlaBorde");
		Ogre::SceneNode* nodoAlaB04 = mSceneMgr->createSceneNode("NodoAlaB04");
		nodoAlaI01->addChild(nodoAlaB04);
		nodoAlaB04->attachObject(entAlaB04);


		//turbinas
		Ogre::Entity* entTurbinas01 = mSceneMgr->createEntity("usb_cilindro.mesh");
		Ogre::SceneNode* nodoTurbinas01 = mSceneMgr->createSceneNode("NodoTurbinas01");
		nodoNave->addChild(nodoTurbinas01);
		nodoTurbinas01->setPosition(2.8,1,3);
		nodoTurbinas01->pitch(Ogre::Degree(90));
		nodoTurbinas01->setScale(0.26,0.4,0.26);
		nodoTurbinas01->attachObject(entTurbinas01);
		entTurbinas01->setMaterialName("DanielaOrtiz_Nave/Gris");

		Ogre::Entity* entTurbinas01a = mSceneMgr->createEntity("usb_cilindro.mesh");
		Ogre::SceneNode* nodoTurbinas01a = mSceneMgr->createSceneNode("NodoTurbinas01a");
		nodoTurbinas01->addChild(nodoTurbinas01a);
		nodoTurbinas01a->setPosition(-0.6,1.5,0.6);
		nodoTurbinas01a->setScale(0.8,1,0.8);
		nodoTurbinas01a->attachObject(entTurbinas01a);
		entTurbinas01a->setMaterialName("DanielaOrtiz_Nave/Gris");

		Ogre::Entity* entTurbinas02 = mSceneMgr->createEntity("usb_cilindro.mesh");
		Ogre::SceneNode* nodoTurbinas02 = mSceneMgr->createSceneNode("NodoTurbinas02");
		nodoNave->addChild(nodoTurbinas02);
		nodoTurbinas02->setPosition(-2.8,1,3);
		nodoTurbinas02->pitch(Ogre::Degree(90));
		nodoTurbinas02->setScale(0.26,0.4,0.26);
		nodoTurbinas02->attachObject(entTurbinas02);
		entTurbinas02->setMaterialName("DanielaOrtiz_Nave/Gris");

		Ogre::Entity* entTurbinas02a = mSceneMgr->createEntity("usb_cilindro.mesh");
		Ogre::SceneNode* nodoTurbinas02a = mSceneMgr->createSceneNode("NodoTurbinas02a");
		nodoTurbinas02->addChild(nodoTurbinas02a);
		nodoTurbinas02a->setPosition(0.6,1.5,0.6);
		nodoTurbinas02a->setScale(0.8,1,0.8);
		nodoTurbinas02a->attachObject(entTurbinas02a);
		entTurbinas02a->setMaterialName("DanielaOrtiz_Nave/Gris");

		Ogre::Entity* entTurbinas03 = mSceneMgr->createEntity("usb_cilindro.mesh");
		Ogre::SceneNode* nodoTurbinas03 = mSceneMgr->createSceneNode("NodoTurbinas03");
		nodoNave->addChild(nodoTurbinas03);
		nodoTurbinas03->setPosition(2.8,-1,3);
		nodoTurbinas03->pitch(Ogre::Degree(-90));
		nodoTurbinas03->setScale(0.26,0.4,0.26);
		nodoTurbinas03->attachObject(entTurbinas03);
		entTurbinas03->setMaterialName("DanielaOrtiz_Nave/Gris");

		Ogre::Entity* entTurbinas03a = mSceneMgr->createEntity("usb_cilindro.mesh");
		Ogre::SceneNode* nodoTurbinas03a = mSceneMgr->createSceneNode("NodoTurbinas03a");
		nodoTurbinas03->addChild(nodoTurbinas03a);
		nodoTurbinas03a->setPosition(-0.6,-1.5,0.6);
		nodoTurbinas03a->setScale(0.8,1,0.8);
		nodoTurbinas03a->attachObject(entTurbinas03a);
		entTurbinas03a->setMaterialName("DanielaOrtiz_Nave/Gris");

		Ogre::Entity* entTurbinas04 = mSceneMgr->createEntity("usb_cilindro.mesh");
		Ogre::SceneNode* nodoTurbinas04 = mSceneMgr->createSceneNode("NodoTurbinas04");
		nodoNave->addChild(nodoTurbinas04);
		nodoTurbinas04->setPosition(-2.8,-1,3);
		nodoTurbinas04->pitch(Ogre::Degree(-90));
		nodoTurbinas04->setScale(0.26,0.4,0.26);
		nodoTurbinas04->attachObject(entTurbinas04);
		entTurbinas04->setMaterialName("DanielaOrtiz_Nave/Gris");

		Ogre::Entity* entTurbinas04a = mSceneMgr->createEntity("usb_cilindro.mesh");
		Ogre::SceneNode* nodoTurbinas04a = mSceneMgr->createSceneNode("NodoTurbinas04a");
		nodoTurbinas04->addChild(nodoTurbinas04a);
		nodoTurbinas04a->setPosition(0.6,-1.5,0.6);
		nodoTurbinas04a->setScale(0.8,1,0.8);
		nodoTurbinas04a->attachObject(entTurbinas04a);
		entTurbinas04a->setMaterialName("DanielaOrtiz_Nave/Gris");


		/*
			**********  FIN NAVE  **********
		*/

		// Creando Torretas

		// TORRETA 1 - Primera de la izquierda

		// Cuerpo de la Torreta
		Ogre::Entity* entTorreta01 = mSceneMgr->createEntity("usb_cilindro02.mesh");
		Ogre::SceneNode* nodoTorreta01 = mSceneMgr->createSceneNode("NodoTorreta01");
		mSceneMgr->getRootSceneNode()->addChild(nodoTorreta01);
		nodoTorreta01->setPosition(-22.0,-5.0,-227.0);
		nodoTorreta01->attachObject(entTorreta01);
		entTorreta01->setMaterial(materialTorretas);

		// Forma para la parte de arriba de la torreta
		Ogre::Entity* entCurva01 = mSceneMgr->createEntity("usb_formacurva.mesh");
		Ogre::SceneNode* nodoCurva01 = mSceneMgr->createSceneNode("NodoCurva01");
		nodoTorreta01->addChild(nodoCurva01);
		nodoCurva01->setPosition(0.0,6.0,0.0);
		nodoCurva01->setScale(0.3,0.8,0.0);
		nodoCurva01->attachObject(entCurva01);
		entCurva01->setMaterial(materialTorretas2);

		// Canon de la torreta
		Ogre::Entity* entCanon01 = mSceneMgr->createEntity("usb_cilindro.mesh");
		Ogre::SceneNode* nodoCanon01 = mSceneMgr->createSceneNode("NodoCanon01");
		nodoTorreta01->addChild(nodoCanon01);
		nodoCanon01->setPosition(0.8,7.0,3.7);
		nodoCanon01->setScale(0.1,0.6,0.1);
		nodoCanon01->yaw(Degree(15));		
		nodoCanon01->pitch(Degree(90));
		nodoCanon01->attachObject(entCanon01);
		entCanon01->setMaterial(materialTorretas3);

		// Punta del Canon 
		Ogre::Entity* entPuntaC01 = mSceneMgr->createEntity("usb_cilindro.mesh");
		Ogre::SceneNode* nodoPuntaC01 = mSceneMgr->createSceneNode("NodoPuntaC01");
		nodoCanon01->addChild(nodoPuntaC01);
		nodoPuntaC01->setPosition(0.0,6.0,0.0);
		nodoPuntaC01->setScale(1.4,0.1,1.4);
		entPuntaC01->setMaterial(materialTorretas2);
		nodoPuntaC01->attachObject(entPuntaC01);

		// Pipe para la base de la torreta
		Ogre::Entity* entPipe01 = mSceneMgr->createEntity("usb_pipe.mesh");
		Ogre::SceneNode* nodoPipe01 = mSceneMgr->createSceneNode("NodoPipe01");
		nodoTorreta01->addChild(nodoPipe01);
		nodoPipe01->setPosition(0.0,-5.0,0.0);
		nodoPipe01->setScale(0.65,2.0,0.65);
		nodoPipe01->attachObject(entPipe01);
		entPipe01->setMaterial(materialTorretas2);

		// Laser de la torreta
		Ogre::Entity* entLaser01 = mSceneMgr->createEntity("usb_laser.mesh");
		Ogre::SceneNode* nodoLaser01 = mSceneMgr->createSceneNode("NodoLaser01");
		nodoCanon01->addChild(nodoLaser01);
		nodoLaser01->attachObject(entLaser01);
		entLaser01->setMaterial(materialLaser);
		nodoLaser01->setPosition(0.0,10.5,0.0);
		
		// Animacion del Laser
		
		float duration = 4.0f;
		Ogre::Animation* animationLaserT01 = mSceneMgr -> createAnimation("animationLaserT01",duration);
		animationLaserT01 -> setInterpolationMode(Animation::IM_SPLINE);
		Ogre::NodeAnimationTrack* trackLaser01 = animationLaserT01->createNodeTrack(0,nodoLaser01);
		Ogre::TransformKeyFrame* key;
		key = trackLaser01 -> createNodeKeyFrame(0.0);
		key -> setTranslate(Vector3(0,10,0));
		key -> setScale(Vector3(1.0,1.0,1.0));
		key = trackLaser01 -> createNodeKeyFrame(2.0);
		key -> setTranslate(Vector3(0,105,0));
		key -> setScale(Vector3(2.0,2.0,2.0));
		key = trackLaser01 -> createNodeKeyFrame(2.5);
		key -> setTranslate(Vector3(0,205,0));
		key -> setScale(Vector3(2.5,2.5,2.5));
		key = trackLaser01 -> createNodeKeyFrame(3.0);
		key -> setTranslate(Vector3(0,300,0));
		key -> setScale(Vector3(4.5,2.5,4.5));
		key = trackLaser01 -> createNodeKeyFrame(4.0);
		key -> setTranslate(Vector3(0,400,0));
		key -> setScale(Vector3(6.5,2.5,6.5));
		key = trackLaser01 -> createNodeKeyFrame(5.0);
		key -> setTranslate(Vector3(0,500,0));
		key -> setScale(Vector3(0,0,0));
		
		animationLaser01 = mSceneMgr -> createAnimationState("animationLaserT01");
		animationLaser01 -> setEnabled(true);
		animationLaser01 -> setLoop(true);
		

		// TORRETA 2 - Segunda de la izquierda

		// Cuerpo de la Torreta
		Ogre::Entity* entTorreta02 = mSceneMgr->createEntity("usb_cilindro02.mesh");
		Ogre::SceneNode* nodoTorreta02 = mSceneMgr->createSceneNode("NodoTorreta02");
		mSceneMgr->getRootSceneNode()->addChild(nodoTorreta02);
		nodoTorreta02->setPosition(-22.5,-5.0,-638.0);
		nodoTorreta02->attachObject(entTorreta02);
		entTorreta02->setMaterial(materialTorretas);
		//entTorreta02->setMaterialName("Examples/SphereMappedRustySteell");

		// Forma para la parte de arriba de la torreta
		Ogre::Entity* entCurva02 = mSceneMgr->createEntity("usb_formacurva.mesh");
		Ogre::SceneNode* nodoCurva02 = mSceneMgr->createSceneNode("NodoCurva02");
		nodoTorreta02->addChild(nodoCurva02);
		nodoCurva02->setPosition(0.0,6.0,0.0);
		nodoCurva02->setScale(0.3,0.8,0.0);
		nodoCurva02->attachObject(entCurva02);
		entCurva02->setMaterial(materialTorretas2);

		// Canon de la torreta
		Ogre::Entity* entCanon02 = mSceneMgr->createEntity("usb_cilindro.mesh");
		Ogre::SceneNode* nodoCanon02 = mSceneMgr->createSceneNode("NodoCanon02");
		nodoTorreta02->addChild(nodoCanon02);
		nodoCanon02->setPosition(0.8,7.0,3.7);
		nodoCanon02->setScale(0.1,0.6,0.1);
		nodoCanon02->yaw(Degree(15));		
		nodoCanon02->pitch(Degree(90));
		nodoCanon02->attachObject(entCanon02);
		entCanon02->setMaterial(materialTorretas3);


		// Punta del Canon 
		Ogre::Entity* entPuntaC02 = mSceneMgr->createEntity("usb_cilindro.mesh");
		Ogre::SceneNode* nodoPuntaC02 = mSceneMgr->createSceneNode("NodoPuntaC02");
		nodoCanon02->addChild(nodoPuntaC02);
		nodoPuntaC02->setPosition(0.0,6.0,0.0);
		nodoPuntaC02->setScale(1.4,0.1,1.4);
		entPuntaC02->setMaterial(materialTorretas2);
		nodoPuntaC02->attachObject(entPuntaC02);

		// Pipe para la base de la torreta
		Ogre::Entity* entPipe02 = mSceneMgr->createEntity("usb_pipe.mesh");
		Ogre::SceneNode* nodoPipe02 = mSceneMgr->createSceneNode("NodoPipe02");
		nodoTorreta02->addChild(nodoPipe02);
		nodoPipe02->setPosition(0.0,-5.0,0.0);
		nodoPipe02->setScale(0.65,2.0,0.65);
		nodoPipe02->attachObject(entPipe02);
		entPipe02->setMaterial(materialTorretas2);

		// Laser de la torreta
		Ogre::Entity* entLaser02 = mSceneMgr->createEntity("usb_laser.mesh");
		Ogre::SceneNode* nodoLaser02 = mSceneMgr->createSceneNode("NodoLaser02");
		nodoCanon02->addChild(nodoLaser02);
		nodoLaser02->setPosition(0.0,10.5,0.0);
		nodoLaser02->attachObject(entLaser02);
		entLaser02->setMaterial(materialLaser);

		// Animacion del Laser
		
		float duration2 = 4.0f;
		Ogre::Animation* animationLaserT02 = mSceneMgr -> createAnimation("animationLaserT02",duration2);
		animationLaserT02 -> setInterpolationMode(Animation::IM_SPLINE);
		Ogre::NodeAnimationTrack* trackLaser02 = animationLaserT02->createNodeTrack(0,nodoLaser02);
		Ogre::TransformKeyFrame* key2;
		key2 = trackLaser02 -> createNodeKeyFrame(0.0);
		key2 -> setTranslate(Vector3(0,10,0));
		key2 -> setScale(Vector3(1.0,1.0,1.0));
		key2 = trackLaser02 -> createNodeKeyFrame(2.0);
		key2 -> setTranslate(Vector3(0,105,0));
		key2 -> setScale(Vector3(2.0,2.0,2.0));
		key2 = trackLaser02 -> createNodeKeyFrame(2.5);
		key2 -> setTranslate(Vector3(0,205,0));
		key2 -> setScale(Vector3(2.5,2.5,2.5));
		key2 = trackLaser02 -> createNodeKeyFrame(3.0);
		key2 -> setTranslate(Vector3(0,300,0));
		key2 -> setScale(Vector3(4.5,2.5,4.5));
		key2 = trackLaser02 -> createNodeKeyFrame(4.0);
		key2 -> setTranslate(Vector3(0,400,0));
		key2 -> setScale(Vector3(6.5,2.5,6.5));
		key2 = trackLaser02 -> createNodeKeyFrame(5.0);
		key2 -> setTranslate(Vector3(0,500,0));
		key2 -> setScale(Vector3(0,0,0));
		
		animationLaser02 = mSceneMgr -> createAnimationState("animationLaserT02");
		animationLaser02 -> setEnabled(true);
		animationLaser02 -> setLoop(true);
		
		// TORRETA 3 - Primera de la derecha
		
		// Cuerpo de la Torreta
		Ogre::Entity* entTorreta03 = mSceneMgr->createEntity("usb_cilindro02.mesh");
		Ogre::SceneNode* nodoTorreta03 = mSceneMgr->createSceneNode("NodoTorreta03");
		mSceneMgr->getRootSceneNode()->addChild(nodoTorreta03);
		nodoTorreta03->setPosition(22.0,-5.0,-407.5);
		nodoTorreta03->attachObject(entTorreta03);
		entTorreta03->setMaterial(materialTorretas);

		// Forma para la parte de arriba de la torreta
		Ogre::Entity* entCurva03 = mSceneMgr->createEntity("usb_formacurva.mesh");
		Ogre::SceneNode* nodoCurva03 = mSceneMgr->createSceneNode("NodoCurva03");
		nodoTorreta03->addChild(nodoCurva03);
		nodoCurva03->setPosition(0.0,6.0,0.0);
		nodoCurva03->setScale(0.3,0.8,0.0);
		nodoCurva03->attachObject(entCurva03);
		entCurva03->setMaterial(materialTorretas2);

		// Canon de la torreta
		Ogre::Entity* entCanon03 = mSceneMgr->createEntity("usb_cilindro.mesh");
		Ogre::SceneNode* nodoCanon03 = mSceneMgr->createSceneNode("NodoCanon03");
		nodoTorreta03->addChild(nodoCanon03);
		nodoCanon03->setPosition(-0.8,7.0,3.7);
		nodoCanon03->setScale(0.1,0.6,0.1);
		nodoCanon03->yaw(Degree(-15));		
		nodoCanon03->pitch(Degree(90));
		nodoCanon03->attachObject(entCanon03);
		entCanon03->setMaterial(materialTorretas3);

		// Punta del Canon 
		Ogre::Entity* entPuntaC03 = mSceneMgr->createEntity("usb_cilindro.mesh");
		Ogre::SceneNode* nodoPuntaC03 = mSceneMgr->createSceneNode("NodoPuntaC03");
		nodoCanon03->addChild(nodoPuntaC03);
		nodoPuntaC03->setPosition(0.0,6.0,0.0);
		nodoPuntaC03->setScale(1.4,0.1,1.4);
		entPuntaC03->setMaterial(materialTorretas2);
		nodoPuntaC03->attachObject(entPuntaC03);

		// Pipe para la base de la torreta
		Ogre::Entity* entPipe03 = mSceneMgr->createEntity("usb_pipe.mesh");
		Ogre::SceneNode* nodoPipe03 = mSceneMgr->createSceneNode("NodoPipe03");
		nodoTorreta03->addChild(nodoPipe03);
		nodoPipe03->setPosition(0.0,-5.0,0.0);
		nodoPipe03->setScale(0.65,2.0,0.65);
		nodoPipe03->attachObject(entPipe03);
		entPipe03->setMaterial(materialTorretas2);

		// Laser de la torreta
		Ogre::Entity* entLaser03 = mSceneMgr->createEntity("usb_laser.mesh");
		Ogre::SceneNode* nodoLaser03 = mSceneMgr->createSceneNode("NodoLaser03");
		nodoCanon03->addChild(nodoLaser03);
		nodoLaser03->setPosition(0.0,10.5,0.0);
		nodoLaser03->attachObject(entLaser03);
		entLaser03->setMaterial(materialLaser);

		// Animacion del Laser
		
		float duration3 = 4.0f;
		Ogre::Animation* animationLaserT03 = mSceneMgr -> createAnimation("animationLaserT03",duration3);
		animationLaserT03 -> setInterpolationMode(Animation::IM_SPLINE);
		Ogre::NodeAnimationTrack* trackLaser03 = animationLaserT03->createNodeTrack(0,nodoLaser03);
		Ogre::TransformKeyFrame* key3;
		key3 = trackLaser03 -> createNodeKeyFrame(0.0);
		key3 -> setTranslate(Vector3(0,10,0));
		key3 -> setScale(Vector3(1.0,1.0,1.0));
		key3 = trackLaser03 -> createNodeKeyFrame(2.0);
		key3 -> setTranslate(Vector3(0,105,0));
		key3 -> setScale(Vector3(2.0,2.0,2.0));
		key3 = trackLaser03 -> createNodeKeyFrame(2.5);
		key3 -> setTranslate(Vector3(0,205,0));
		key3 -> setScale(Vector3(2.5,2.5,2.5));
		key3 = trackLaser03 -> createNodeKeyFrame(3.0);
		key3 -> setTranslate(Vector3(0,300,0));
		key3 -> setScale(Vector3(4.5,2.5,4.5));
		key3 = trackLaser03 -> createNodeKeyFrame(4.0);
		key3 -> setTranslate(Vector3(0,400,0));
		key3 -> setScale(Vector3(6.5,2.5,6.5));
		key3 = trackLaser03 -> createNodeKeyFrame(5.0);
		key3 -> setTranslate(Vector3(0,500,0));
		key3 -> setScale(Vector3(0,0,0));
		
		animationLaser03 = mSceneMgr -> createAnimationState("animationLaserT03");
		animationLaser03 -> setEnabled(true);
		animationLaser03 -> setLoop(true);
		
		// TORRETA 4 - Segunda de la derecha

		// Cuerpo de la Torreta
		Ogre::Entity* entTorreta04 = mSceneMgr->createEntity("usb_cilindro02.mesh");
		Ogre::SceneNode* nodoTorreta04 = mSceneMgr->createSceneNode("NodoTorreta04");
		mSceneMgr->getRootSceneNode()->addChild(nodoTorreta04);
		nodoTorreta04->setPosition(22.0,-5.0,-883.0);
		nodoTorreta04->attachObject(entTorreta04);
		entTorreta04->setMaterial(materialTorretas);

		// Forma para la parte de arriba de la torreta
		Ogre::Entity* entCurva04 = mSceneMgr->createEntity("usb_formacurva.mesh");
		Ogre::SceneNode* nodoCurva04 = mSceneMgr->createSceneNode("NodoCurva04");
		nodoTorreta04->addChild(nodoCurva04);
		nodoCurva04->setPosition(0.0,6.0,0.0);
		nodoCurva04->setScale(0.3,0.8,0.0);
		nodoCurva04->attachObject(entCurva04);
		entCurva04->setMaterial(materialTorretas2);

		// Canon de la torreta
		Ogre::Entity* entCanon04 = mSceneMgr->createEntity("usb_cilindro.mesh");
		Ogre::SceneNode* nodoCanon04 = mSceneMgr->createSceneNode("NodoCanon04");
		nodoTorreta04->addChild(nodoCanon04);
		nodoCanon04->setPosition(-0.8,7.0,3.7);
		nodoCanon04->setScale(0.1,0.6,0.1);
		nodoCanon04->yaw(Degree(-15));		
		nodoCanon04->pitch(Degree(90));
		nodoCanon04->attachObject(entCanon04);
		entCanon04->setMaterial(materialTorretas3);
		
		// Punta del Canon 
		Ogre::Entity* entPuntaC04 = mSceneMgr->createEntity("usb_cilindro.mesh");
		Ogre::SceneNode* nodoPuntaC04 = mSceneMgr->createSceneNode("NodoPuntaC04");
		nodoCanon04->addChild(nodoPuntaC04);
		nodoPuntaC04->setPosition(0.0,6.0,0.0);
		nodoPuntaC04->setScale(1.4,0.1,1.4);
		entPuntaC04->setMaterial(materialTorretas2);
		nodoPuntaC04->attachObject(entPuntaC04);

		// Pipe para la base de la torreta
		Ogre::Entity* entPipe04 = mSceneMgr->createEntity("usb_pipe.mesh");
		Ogre::SceneNode* nodoPipe04 = mSceneMgr->createSceneNode("NodoPipe04");
		nodoTorreta04->addChild(nodoPipe04);
		nodoPipe04->setPosition(0.0,-5.0,0.0);
		nodoPipe04->setScale(0.65,2.0,0.65);
		nodoPipe04->attachObject(entPipe04);
		entPipe04->setMaterial(materialTorretas2);

		// Laser de la torreta
		Ogre::Entity* entLaser04 = mSceneMgr->createEntity("usb_laser.mesh");
		Ogre::SceneNode* nodoLaser04 = mSceneMgr->createSceneNode("NodoLaser04");
		nodoCanon04->addChild(nodoLaser04);
		nodoLaser04->setPosition(0.0,10.5,0.0);
		nodoLaser04->attachObject(entLaser04);
		entLaser04->setMaterial(materialLaser);

		// Animacion del Laser
		
		float duration4 = 4.0f;
		Ogre::Animation* animationLaserT04 = mSceneMgr -> createAnimation("animationLaserT04",duration4);
		animationLaserT04 -> setInterpolationMode(Animation::IM_SPLINE);
		Ogre::NodeAnimationTrack* trackLaser04 = animationLaserT04->createNodeTrack(0,nodoLaser04);
		Ogre::TransformKeyFrame* key4;
		key4 = trackLaser04 -> createNodeKeyFrame(0.0);
		key4 -> setTranslate(Vector3(0,10,0));
		key4 -> setScale(Vector3(1.0,1.0,1.0));
		key4 = trackLaser04 -> createNodeKeyFrame(2.0);
		key4 -> setTranslate(Vector3(0,105,0));
		key4 -> setScale(Vector3(2.0,2.0,2.0));
		key4 = trackLaser04 -> createNodeKeyFrame(2.5);
		key4 -> setTranslate(Vector3(0,205,0));
		key4 -> setScale(Vector3(2.5,2.5,2.5));
		key4 = trackLaser04 -> createNodeKeyFrame(3.0);
		key4 -> setTranslate(Vector3(0,300,0));
		key4 -> setScale(Vector3(4.5,2.5,4.5));
		key4 = trackLaser04 -> createNodeKeyFrame(4.0);
		key4 -> setTranslate(Vector3(0,400,0));
		key4 -> setScale(Vector3(6.5,2.5,6.5));
		key4 = trackLaser04 -> createNodeKeyFrame(5.0);
		key4 -> setTranslate(Vector3(0,500,0));
		key4 -> setScale(Vector3(0,0,0));
		
		animationLaser04 = mSceneMgr -> createAnimationState("animationLaserT04");
		animationLaser04 -> setEnabled(true);
		animationLaser04 -> setLoop(true);

	}

};


int main (void)
{

	Example1 app;
	app.go();
	return 0;
}