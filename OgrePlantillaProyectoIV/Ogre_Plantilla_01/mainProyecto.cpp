#include "Ogre\ExampleApplication.h"


class Example1 : public ExampleApplication
{

public:

	void crearAlasIzq(Ogre::ManualObject* manualAla, float x1, float x2, float y) {

		manualAla->begin("BaseWhiteNoLighting", RenderOperation::OT_TRIANGLE_STRIP);

			manualAla->position( x2, y, 5);
			manualAla->position( x1, y, 6);
			manualAla->position( x2, y, 1);
			manualAla->position( x1, y, 0);

			for(int i = 0; i < 5; i++){
				manualAla->index(i);
			}

		manualAla->end();
	}

	void crearAlasDer(Ogre::ManualObject* manualAla, float x1, float x2, float y) {

		manualAla->begin("BaseWhiteNoLighting", RenderOperation::OT_TRIANGLE_STRIP);


			manualAla->position( x1, y, 6);
			manualAla->position( x2, y, 5);
			manualAla->position( x2, y, 1);
			manualAla->position( x1, y, 0);

			for(int i = 0; i < 5; i++){
				manualAla->index(i);
			}

		manualAla->end();
	}

	void createCamera() {

		mCamera = mSceneMgr->createCamera("MyCamera1");
		mCamera->setPosition(0,10,50);
		mCamera->lookAt(0,0,-50);
		mCamera->setNearClipDistance(5);

	}

	void createScene()
	{

		mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0, 1.0, 1.0));
		mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
		mSceneMgr->setSkyBox(true, "Estrellas/SkyBox");
		//mSceneMgr->setSkyDome(true, "Estrellas/SkyDome", 1, 1);	

		Ogre::Entity* ent01 = mSceneMgr->createEntity("MyEntity1","ejes01.mesh");
		Ogre::SceneNode* node01 = mSceneMgr->createSceneNode("Node01");
		mSceneMgr->getRootSceneNode()->addChild(node01);
		node01->attachObject(ent01);

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
			materialTorretas ->getTechnique(0) ->getPass(0)->createTextureUnitState("tex_mTorretas01.png");
		
		Ogre::MaterialPtr materialTorretas2 = Ogre::MaterialManager::getSingleton().create(
			"OtrasPartes", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

		Ogre::TextureUnitState* torretaTexture2 =
			materialTorretas2 ->getTechnique(0) ->getPass(0)->createTextureUnitState("MtlPlat2.jpg");


		//Cuadricula
		//Ogre::Entity* entPlanoY = mSceneMgr->createEntity("planoYEnt","cuadriculaY01.mesh");
		//Ogre::SceneNode* nodePlanoY = mSceneMgr->createSceneNode("nodePlanoY");
		//mSceneMgr->getRootSceneNode()->addChild(nodePlanoY);
		//nodePlanoY->setPosition(0.0,0.0,6.0);
		//nodePlanoY->attachObject(entPlanoY);

		//Ogre::Entity* entPlanoX = mSceneMgr->createEntity("planoXEnt","cuadriculaX01.mesh");
		//Ogre::SceneNode* nodePlanoX = mSceneMgr->createSceneNode("nodePlanoX");
		//mSceneMgr->getRootSceneNode()->addChild(nodePlanoX);
		//nodePlanoX->setPosition(0.0,0.0,6.0);
		//nodePlanoX->attachObject(entPlanoX);

		/*
			**********  NAVE  **********
		
		const float x1 = 2.0;
		const float y1 = 1.7;
		const float z1 = 6.0;
		//parte de atras de la nave
		ManualObject* manual = mSceneMgr->createManualObject("manual");
		manual->begin("BaseWhiteNoLighting", RenderOperation::OT_TRIANGLE_STRIP);

			manual->position( 2.5, 0.0, z1-7);
			manual->position(  x1, -y1, z1);
			manual->position(  x1, -y1, z1-7);
			manual->position( -x1, -y1, z1);
			manual->position( -x1, -y1, z1-7);
			manual->position(-2.5, 0.0, z1);
			manual->position(-2.5, 0.0, z1-7);
			manual->position( -x1,  y1, z1);
			manual->position( -x1,  y1, z1-7);
			manual->position(  x1,  y1, z1);
			manual->position(  x1,  y1, z1-7);
			manual->position( 2.5, 0.0, z1);
			manual->position( 2.5, 0.0, z1-7);
			manual->position(  x1, -y1, z1);

			for(int i = 0; i < 15; i++){
				manual->index(i);
			}

		manual->end();
		manual->convertToMesh("MeshNave");
		Ogre::Entity* entNave = mSceneMgr->createEntity("MeshNave");
		Ogre::SceneNode* nodoNave = mSceneMgr->createSceneNode("NodoNave");
		mSceneMgr->getRootSceneNode()->addChild(nodoNave);
		nodoNave->attachObject(entNave);

		//cara de atras
		ManualObject* manualCara = mSceneMgr->createManualObject("manualCara");
		manualCara->begin("BaseWhiteNoLighting", RenderOperation::OT_TRIANGLE_STRIP);

			manualCara->position(-2.5, 0.0, z1);
			manualCara->position( -x1, -y1, z1);
			manualCara->position( -x1,  y1, z1);
			manualCara->position(  x1, -y1, z1);
			manualCara->position(  x1,  y1, z1);
			manualCara->position( 2.5, 0.0, z1);

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
		manualFrente->begin("BaseWhiteNoLighting", RenderOperation::OT_TRIANGLE_STRIP);

			manualFrente->position( 0.8, 0.0, z2);
			manualFrente->position(  x1, -y1, z2+7);
			manualFrente->position(  x2, -y2, z2);
			manualFrente->position( -x1, -y1, z2+7);
			manualFrente->position( -x2, -y2, z2);
			manualFrente->position(-2.5, 0.0, z2+7);
			manualFrente->position(-0.8, 0.0, z2);
			manualFrente->position( -x1,  y1, z2+7);
			manualFrente->position( -x2,  y2, z2);
			manualFrente->position(  x1,  y1, z2+7);
			manualFrente->position(  x2,  y2, z2);
			manualFrente->position( 2.5, 0.0, z2+7);
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
	*/




		/*
			**********  ALAS  **********
		*/
		//CARAS IZQUIERDAS ALAS
		Ogre::ManualObject* manualCaraAlaI02 = mSceneMgr->createManualObject("manualCaraAlaI02");
		crearAlasIzq(manualCaraAlaI02, -2, -7, 1.0);
		manualCaraAlaI02->convertToMesh("MeshAlaI02");
		Ogre::Entity* entAlaI02 = mSceneMgr->createEntity("MeshAlaI02");
		Ogre::SceneNode* nodoAlaI02 = mSceneMgr->createSceneNode("NodoAlaI02");
		mSceneMgr->getRootSceneNode()->addChild(nodoAlaI02);
		nodoAlaI02->roll(Ogre::Degree( -10 ) );
		//nodoNave->addChild(nodoAlaI02);
		nodoAlaI02->attachObject(entAlaI02);

		//Ogre::ManualObject* manualCaraAlaI02a = mSceneMgr->createManualObject("manualCaraAlaI02a");
		//crearAlasIzq(manualCaraAlaI02a, -2, -7, 0.5);
		//manualCaraAlaI02a->convertToMesh("MeshAlaI02a");
		//Ogre::Entity* entAlaI02a = mSceneMgr->createEntity("MeshAlaI02a");
		//Ogre::SceneNode* nodoAlaI02a = mSceneMgr->createSceneNode("NodoAlaI02a");
		//nodoAlaI02->addChild(nodoAlaI02a);
		//nodoAlaI02a->attachObject(entAlaI02a);

		Ogre::ManualObject* manualCaraAlaI01 = mSceneMgr->createManualObject("manualCaraAlaI01");
		crearAlasIzq(manualCaraAlaI01,-2, -7, 0.5);
		manualCaraAlaI01->convertToMesh("MeshAlaI01");
		Ogre::Entity* entAlaI01 = mSceneMgr->createEntity("MeshAlaI01");
		Ogre::SceneNode* nodoAlaI01 = mSceneMgr->createSceneNode("NodoAlaI01");
		mSceneMgr->getRootSceneNode()->addChild(nodoAlaI01);
		nodoAlaI01->roll(Ogre::Degree( 10 ) );
		nodoAlaI01->attachObject(entAlaI01);

		//Ogre::ManualObject* manualCaraAlaI01 = mSceneMgr->createManualObject("manualCaraAlaI01");
		//crearAlasIzq(manualCaraAlaI01, -2, -7, 0.0);
		//manualCaraAlaI01->convertToMesh("MeshAlaI01");
		//Ogre::Entity* entAlaI01 = mSceneMgr->createEntity("MeshAlaI01");
		//Ogre::SceneNode* nodoAlaI01 = mSceneMgr->createSceneNode("NodoAlaI01");
		//mSceneMgr->getRootSceneNode()->addChild(nodoAlaI01);
		//nodoNave->addChild(nodoAlaI01);
		//nodoAlaI01->attachObject(entAlaI01);



		//CARAS DERECHAS ALAS

		Ogre::ManualObject* manualCaraAlaD02 = mSceneMgr->createManualObject("manualCaraAlaD02");
		crearAlasDer(manualCaraAlaD02, 2, 7, 1.0);
		manualCaraAlaD02->convertToMesh("MeshAlaD02");
		Ogre::Entity* entAlaD02 = mSceneMgr->createEntity("MeshAlaD02");
		Ogre::SceneNode* nodoAlaD02 = mSceneMgr->createSceneNode("NodoAlaD02");
		mSceneMgr->getRootSceneNode()->addChild(nodoAlaD02);
		nodoAlaD02->roll(Ogre::Degree( 10 ) );
		//nodoNave->addChild(nodoAlaD02);
		nodoAlaD02->attachObject(entAlaD02);

		//Ogre::ManualObject* manualCaraAlaD02a = mSceneMgr->createManualObject("manualCaraAlaD02a");
		//crearAlasDer(manualCaraAlaD02a, 2, 7, 0.5);
		//manualCaraAlaD02a->convertToMesh("MeshAlaD02a");
		//Ogre::Entity* entAlaD02a = mSceneMgr->createEntity("MeshAlaD02a");
		//Ogre::SceneNode* nodoAlaD02a = mSceneMgr->createSceneNode("NodoAlaD02a");
		//nodoAlaD02->addChild(nodoAlaD02a);
		//nodoAlaD02a->attachObject(entAlaD02a);

		//Ogre::ManualObject* manualCaraAlaD01 = mSceneMgr->createManualObject("manualCaraAlaD01");
		//crearAlasDer(manualCaraAlaD01, 2, 7, 0.0);
		//manualCaraAlaD01->convertToMesh("MeshAlaD01");
		//Ogre::Entity* entAlaD01 = mSceneMgr->createEntity("MeshAlaD01");
		//Ogre::SceneNode* nodoAlaD01 = mSceneMgr->createSceneNode("NodoAlaD01");
		//mSceneMgr->getRootSceneNode()->addChild(nodoAlaD01);
		//nodoNave->addChild(nodoAlaD01);
		//nodoAlaD01->attachObject(entAlaD01);

		Ogre::ManualObject* manualCaraAlaD01 = mSceneMgr->createManualObject("manualCaraAlaD01");
		crearAlasDer(manualCaraAlaD01,2, 7, 0.5);
		manualCaraAlaD01->convertToMesh("MeshAlaD01");
		Ogre::Entity* entAlaD01 = mSceneMgr->createEntity("MeshAlaD01");
		Ogre::SceneNode* nodoAlaD01 = mSceneMgr->createSceneNode("NodoAlaD01");
		mSceneMgr->getRootSceneNode()->addChild(nodoAlaD01);
		nodoAlaD01->roll(Ogre::Degree( -10 ) );
		nodoAlaD01->attachObject(entAlaD01);

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
		nodoCanon01->setPosition(0.0,6.5,4.0);
		nodoCanon01->setScale(0.1,0.8,0.1);
		nodoCanon01->yaw(Degree(5));		// variar los angulos para que apunten al centro
		nodoCanon01->pitch(Degree(90));
		nodoCanon01->attachObject(entCanon01);

		// Pipe para el Canon (Hacer luego)
		/*Ogre::Entity* entPipeC01 = mSceneMgr->createEntity("usb_cilindro.mesh");
		Ogre::SceneNode* nodoPipeC01 = mSceneMgr->createSceneNode("NodoPipeC01");
		nodoCanon01->addChild(nodoPipeC01);
		nodoPipeC01->setPosition(0.0,6.0,0.0);
		nodoPipeC01->setScale(0.0,0.6,0.0);
		nodoPipeC01->attachObject(entPipeC01);*/

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
		// nodoLaser01->setPosition(0.0,6.5,4.0); // arreglar la posicion no está donde deberia
		

		// TORRETA 2 - Segunda a la izquierda

		// Cuerpo de la Torreta
		Ogre::Entity* entTorreta02 = mSceneMgr->createEntity("usb_cilindro02.mesh");
		Ogre::SceneNode* nodoTorreta02 = mSceneMgr->createSceneNode("NodoTorreta02");
		mSceneMgr->getRootSceneNode()->addChild(nodoTorreta02);
		nodoTorreta02->setPosition(-22.5,-5.0,-638.0);
		nodoTorreta02->attachObject(entTorreta02);
		entTorreta02->setMaterial(materialTorretas);

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
		nodoCanon02->setPosition(0.0,6.5,4.0);
		nodoCanon02->setScale(0.1,0.8,0.1);
		nodoCanon02->yaw(Degree(5));		// variar los angulos para que apunten al centro
		nodoCanon02->pitch(Degree(90));
		nodoCanon02->attachObject(entCanon02);

		// Pipe para la base de la torreta
		Ogre::Entity* entPipe02 = mSceneMgr->createEntity("usb_pipe.mesh");
		Ogre::SceneNode* nodoPipe02 = mSceneMgr->createSceneNode("NodoPipe02");
		nodoTorreta02->addChild(nodoPipe02);
		nodoPipe02->setPosition(0.0,-5.0,0.0);
		nodoPipe02->setScale(0.65,2.0,0.65);
		nodoPipe02->attachObject(entPipe02);
		entPipe02->setMaterial(materialTorretas2);

		// Laser de la torreta
		/*
		Ogre::Entity* entLaser02 = mSceneMgr->createEntity("usb_laser.mesh");
		Ogre::SceneNode* nodoLaser02 = mSceneMgr->createSceneNode("NodoLaser02");
		nodoTorreta02->addChild(nodoLaser02);
		nodoLaser02->setPosition(0.0,0.0,0.0);
		nodoLaser02->attachObject(entLaser02);
		*/
		// TORRETA 3 - Primera a la derecha
		
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
		nodoCanon03->setPosition(0.0,6.5,4.0);
		nodoCanon03->setScale(0.1,0.8,0.1);
		nodoCanon03->yaw(Degree(-5));		// variar los angulos para que apunten al centro
		nodoCanon03->pitch(Degree(90));
		nodoCanon03->attachObject(entCanon03);

		// Pipe para la base de la torreta
		Ogre::Entity* entPipe03 = mSceneMgr->createEntity("usb_pipe.mesh");
		Ogre::SceneNode* nodoPipe03 = mSceneMgr->createSceneNode("NodoPipe03");
		nodoTorreta03->addChild(nodoPipe03);
		nodoPipe03->setPosition(0.0,-5.0,0.0);
		nodoPipe03->setScale(0.65,2.0,0.65);
		nodoPipe03->attachObject(entPipe03);
		entPipe03->setMaterial(materialTorretas2);

		// Laser de la torreta
		/*
		Ogre::Entity* entLaser03 = mSceneMgr->createEntity("usb_laser.mesh");
		Ogre::SceneNode* nodoLaser03 = mSceneMgr->createSceneNode("NodoLaser03");
		nodoTorreta03->addChild(nodoLaser03);
		nodoLaser03->setPosition(0.0,0.0,0.0);
		nodoLaser03->attachObject(entLaser03);
		*/
		
		// TORRETA 4 - Segunda a la derecha

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
		nodoCanon04->setPosition(0.0,6.5,4.0);
		nodoCanon04->setScale(0.1,0.8,0.1);
		nodoCanon04->yaw(Degree(-5));		// variar los angulos para que apunten al centro
		nodoCanon04->pitch(Degree(90));
		nodoCanon04->attachObject(entCanon04);
		

		// Pipe para la base de la torreta
		Ogre::Entity* entPipe04 = mSceneMgr->createEntity("usb_pipe.mesh");
		Ogre::SceneNode* nodoPipe04 = mSceneMgr->createSceneNode("NodoPipe04");
		nodoTorreta04->addChild(nodoPipe04);
		nodoPipe04->setPosition(0.0,-5.0,0.0);
		nodoPipe04->setScale(0.65,2.0,0.65);
		nodoPipe04->attachObject(entPipe04);
		entPipe04->setMaterial(materialTorretas2);

		// Laser de la torreta
		/*
		Ogre::Entity* entLaser04 = mSceneMgr->createEntity("usb_laser.mesh");
		Ogre::SceneNode* nodoLaser04 = mSceneMgr->createSceneNode("NodoLaser04");
		nodoTorreta04->addChild(nodoLaser04);
		nodoLaser04->setPosition(0.0,0.0,0.0);
		nodoLaser04->attachObject(entLaser04);
		*/

	}

};


int main (void)
{

	Example1 app;
	app.go();
	return 0;
}