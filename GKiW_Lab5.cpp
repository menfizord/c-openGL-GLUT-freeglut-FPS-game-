#include "stdafx.h"
#include "objLoader.h"
#include <ctime>
#pragma region Zmienne globalne
SCameraState player;
double T = 0.0;
int mouseX = 0;
int mouseY = 0;
bool captureMouse = true;
bool free3DMovement = false;
float mouseSensitivity = .15f;
////////////////////////////////////////////


#pragma endregion

bool loadObjs=true;
Game* game;
bool hasShoot = false;
bool hasShoot2 = false;
float recoil = 0.0f;
float recoil2 = 0.0f;
float recoilH = 0.0f;
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1360,720);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glutCreateWindow("M4 Vs. Fog");

	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnReshape);
	glutKeyboardFunc(OnKeyPress);
	glutKeyboardUpFunc(OnKeyUp);
	glutPassiveMotionFunc(OnMouseMove);
	glutMotionFunc(OnMouseMove);
	glutMouseFunc(mouse);

	glutTimerFunc(17, OnTimer, 0);
	glutTimerFunc(17, mustBeRefreshed, 1);
	//glEnable(GL_FOG);


	glEnable(GL_DEPTH_TEST);
	float gl_amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gl_amb);

	//glEnable(GL_LIGHTING); // Wlaczenie oswietlenia
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);


	glEnable(GL_LIGHT1); // pierwsza lampa po prawej
	glEnable(GL_LIGHT2); // druga lampa po prawej
	glEnable(GL_LIGHT3); // pierwsza lampa po lewej
	glEnable(GL_LIGHT4); // przedni koniec mapy
	glEnable(GL_LIGHT5); // tylni koniec mapy
	glEnable(GL_LIGHT6); // druga srodkowa po prawej
	glEnable(GL_LIGHT7); // ostatnia lampa po lewej
	glEnable(GL_LIGHT0); // ostatnia lampa po prawej
	// Inicjalizacja kamery:
	player.pos.x = -14.5f;
	player.pos.y = 0.12f;
	player.pos.z = 0.5f;

	player.dir.x = 1.0f;
	player.dir.y = -0.065f;
	player.dir.z = 0.004f;

	player.speed = .1f;
	srand(time(NULL));
	game = new Game();
	game->otherPreparationThings();
	game->loadTexts();
	game->loadObjs();
	
	glutMainLoop();
	delete game;


	return 0;
}

#pragma region Obsluga wejscia

bool keystate[255];

void OnKeyPress(unsigned char key, int x, int y) {
	if (!keystate[key]) {
		keystate[key] = true;
		OnKeyDown(key, x, y);
	}
}

void OnKeyDown(unsigned char key, int x, int y) {
	if (key == 27) {
		glutLeaveMainLoop();
	}

}

void OnKeyUp(unsigned char key, int x, int y) {
	keystate[key] = false;
}

void OnMouseMove(int x, int y) {
	mouseX = x;
	mouseY = y;
}

#pragma endregion
///OBSLUGA GUZIKOW MYSZKI

void mouse(int button, int state, int x, int y)
{
	if (game->gameState == Game::GameState::playing){ 
		if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)){
		game->player->Shoot(player.pos.x, player.pos.y, player.pos.z, player.dir.x, player.dir.y, player.dir.z);
		recoil = player.dir.y;
		recoilH = recoil;
		recoil2 = recoil + 0.1f;

		hasShoot = true;
		hasShoot2 = false;
		}

		if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP)){
		
		}
	}
}



///



void OnTimer(int id) {

	glutTimerFunc(17, OnTimer, 0);
	if (keystate['q']) {
		glutLeaveMainLoop();
	}
	#pragma region Ruch kamery
	if (game->gameState == Game::GameState::playing) {
		if (captureMouse) {
			player.velRY = -mouseSensitivity * (glutGet(GLUT_WINDOW_WIDTH) / 2 - mouseX);
			player.velRX = mouseSensitivity * (glutGet(GLUT_WINDOW_HEIGHT) / 2 - mouseY);
			glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
		}

		if (keystate['w']) {
			player.velM = player.speed;
		}
		if (keystate['s']) {
			player.velM = -player.speed;
		}
		if (keystate['a']) {
			player.velS = -player.speed;
		}
		if (keystate['d']) {
			player.velS = player.speed;
		}
		if (keystate['e']) {
			game->Grab();
		}


		float prevX, prevZ; //poprzednie polozenie wzgledem xa i zta
		prevX = player.pos.x;
		prevZ = player.pos.z;
		float T = acos(player.dir.y);
		float G = atan2(player.dir.z, player.dir.x);
		T -= player.velRX * .03f;
		G += player.velRY * .03f;
		player.dir.x = sin(T) * cos(G);
		player.dir.y = cos(T);
		player.dir.z = sin(T) * sin(G);

		vec3 per;
		per.x = -player.dir.z;
		per.y = 0;
		per.z = player.dir.x;
		float nextX;
		nextX = player.pos.x + player.dir.x * player.velM * .1f;
		nextX += per.x * player.velS * .1f;
		float nextZ = player.pos.z + player.dir.z * player.velM * .1f;
		nextZ += per.z * player.velS * .1f;
		/////////////////////////////////////////////////////////// OGRANICZENIE DLA XA
		if (player.pos.x >= -19.6f && player.pos.x <= -10.4f) {
			///ODKLEJANIE SIE OD SCIAN
			if (player.pos.x > -19.7f && player.pos.x < -19.5f) {
				if (nextX > player.pos.x) {
					player.pos.x = nextX;
				}
			}
			else if (player.pos.x > -10.6f && player.pos.x < -10.2f) {
				if (nextX<player.pos.x) {
					player.pos.x = nextX;
				}
			}
			else {
				player.pos.x = nextX;
			}
		}
		////////////////////////////////////////////////////////////////// OGTANICZENIE DLA ZTA
		if (player.pos.z > 0.01& player.pos.z < 0.8f) {
			if (player.pos.z > -0.96f && player.pos.z < 0.06f) {
				if (nextZ > player.pos.z) {
					player.pos.z = nextZ;
				}
			}
			else if (player.pos.z > 0.75f && player.pos.z < 0.85f) {
				if (nextZ < player.pos.z) {
					player.pos.z = nextZ;
				}

			}
			else {
				player.pos.z = nextZ;
			}
		}

		///////////////////////////////////////////////////////
		/*GRYWALNA CZESC MAPY TO Xe(-19.5; -10.6), Ze(0.05;0.8)*/
		///////////////////////////////////////////////////////

		player.velRX /= 1.2;
		player.velRY /= 1.2;
		player.velM /= 1.2;
		player.velS /= 1.2;

#pragma endregion
	}
	else if (game->gameState == Game::GameState::dead || game->gameState == Game::GameState::win) {
		if (keystate['r']) {
			player.pos.x = -14.5f;
			player.pos.y = 0.12f;
			player.pos.z = 0.5f;
			game->restartGame();

		}
	}
	else {
		if (keystate[' ']) {
			game->setState(Game::GameState::playing);
		}
	}


}

void mustBeRefreshed(int id) {

	glutTimerFunc(17, mustBeRefreshed, 1);
	/////////////////////////////////
	if (game->gameState == Game::GameState::playing) {

		game->getPlayerPos(player.pos.x, player.pos.y, player.pos.z);
		game->makeMob();
		game->deletingMobs();
		//	game->player->ifPlayerMoves(player.pos.x);
		float gl_fogcolor[] = { 0.2f, 0.2f, 0.2f, 1.0f }; // POZWOLILEM SOBIE UKRASC Z LAB6 BO TO WYGLADA NIELE
		glFogi(GL_FOG_MODE, GL_LINEAR);
		glFogfv(GL_FOG_COLOR, gl_fogcolor);
		glFogf(GL_FOG_START, 0.0f);
		glFogf(GL_FOG_END, game->getFog());

		///////////////////////////////////////
		if (hasShoot) {
			if (!hasShoot2) {
				player.dir.y += 0.008f;
				player.dir.z += 0.008f;
				recoil += 0.006f;
				if (recoil >recoil2) {
					recoil2 = recoil - 0.1f;
					hasShoot2 = true;
				}
			}
			else if (hasShoot2) {
				player.dir.y -= 0.006f;
				player.dir.z -= 0.008f;
				recoil -= 0.006f;
				if (recoil < recoilH) {
					hasShoot2 = false;
					hasShoot = false;
					recoilH = 0.0f;
				}
			}

		///////////////////////////////

		}
	}
}


void OnRender() {

	T = glutGet(GLUT_ELAPSED_TIME);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
	game->drawOnFront();
	gluLookAt(
		player.pos.x, player.pos.y, player.pos.z,
		player.pos.x + player.dir.x, player.pos.y + player.dir.y, player.pos.z + player.dir.z,
		0.0f, 1.0f, 0.0f
		);
#pragma region swiatlo

	float l_amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float l_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float l_spe[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float l_lightDir[3] = { 0.0f ,-1.0f , 0.0f };
#pragma region lampaPierwszaPrawo


	float l1_pos[] = { -16.0f, 0.6f, 0.9f, 1.0f };
	glLightfv(GL_LIGHT1, GL_AMBIENT, l_amb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, l_dif);
	glLightfv(GL_LIGHT1, GL_SPECULAR, l_spe);
	glLightfv(GL_LIGHT1, GL_POSITION, l1_pos);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, l_lightDir);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 80.0f);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 5.0f);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.0f);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 3.0f);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0f);
#pragma endregion LampaPierwszaPrawo

#pragma region lampaDrugaPrawo


	float l2_pos[] = { -12.0f, 0.55f, 0.9f, 1.0f };
	glLightfv(GL_LIGHT2, GL_AMBIENT, l_amb);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, l_dif);
	glLightfv(GL_LIGHT2, GL_SPECULAR, l_spe);
	glLightfv(GL_LIGHT2, GL_POSITION, l2_pos);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, l_lightDir);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 80.0f);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 5.0f);
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.0f);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 3.0f);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.0f);
#pragma endregion LampaDrugaPrawo



#pragma region lampaPierwszaLewo


	float l3_pos[] = { -16.0f, 0.55f, 0.1f, 1.0f };
	glLightfv(GL_LIGHT3, GL_AMBIENT, l_amb);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, l_dif);
	glLightfv(GL_LIGHT3, GL_SPECULAR, l_spe);
	glLightfv(GL_LIGHT3, GL_POSITION, l3_pos);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, l_lightDir);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 80.0f);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 5.0f);
	glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 0.0f);
	glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 3.0f);
	glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.0f);
#pragma endregion LampaPierwszaLewo



#pragma region lampaSrodekLewo

	float l6_pos[] = { -14.0f, 0.55f, 0.9f, 1.0f };
	glLightfv(GL_LIGHT6, GL_AMBIENT, l_amb);
	glLightfv(GL_LIGHT6, GL_DIFFUSE, l_dif);
	glLightfv(GL_LIGHT6, GL_SPECULAR, l_spe);
	glLightfv(GL_LIGHT6, GL_POSITION, l6_pos);
	glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, l_lightDir);
	glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, 80.0f);
	glLightf(GL_LIGHT6, GL_SPOT_EXPONENT, 5.0f);
	glLightf(GL_LIGHT6, GL_CONSTANT_ATTENUATION, 0.0f);
	glLightf(GL_LIGHT6, GL_LINEAR_ATTENUATION, 3.0f);
	glLightf(GL_LIGHT6, GL_QUADRATIC_ATTENUATION, 0.0f);
#pragma endregion LampaSrodekLewo

#pragma region przedniKoniec

	float l7_pos[] = { -18.0f, 0.55f, 0.9f, 1.0f };
	glLightfv(GL_LIGHT7, GL_AMBIENT, l_amb);
	glLightfv(GL_LIGHT7, GL_DIFFUSE, l_dif);
	glLightfv(GL_LIGHT7, GL_SPECULAR, l_spe);
	glLightfv(GL_LIGHT7, GL_POSITION, l7_pos);
	glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, l_lightDir);
	glLightf(GL_LIGHT7, GL_SPOT_CUTOFF, 80.0f);
	glLightf(GL_LIGHT7, GL_SPOT_EXPONENT, 5.0f);
	glLightf(GL_LIGHT7, GL_CONSTANT_ATTENUATION, 0.0f);
	glLightf(GL_LIGHT7, GL_LINEAR_ATTENUATION, 3.0f);
	glLightf(GL_LIGHT7, GL_QUADRATIC_ATTENUATION, 0.0f);
#pragma endregion lampaDalekoLewo

#pragma region lampaDelkoPrawo

	float l8_pos[] = { -18.0f, 0.55f, 0.1f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, l_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l_dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l_spe);
	glLightfv(GL_LIGHT0, GL_POSITION, l8_pos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, l_lightDir);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 80.0f);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 5.0f);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.0f);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 3.0f);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0f);
#pragma endregion lampaDelkoPrawo




	#pragma region przedniKoniec
	
		float l4_pos[] = { -9.68f, 1.35f, 0.5f, 1.0f };
		glLightfv(GL_LIGHT4, GL_AMBIENT, l_amb);
		glLightfv(GL_LIGHT4, GL_DIFFUSE, l_dif);
		glLightfv(GL_LIGHT4, GL_SPECULAR, l_spe);
		glLightfv(GL_LIGHT4, GL_POSITION, l4_pos);
		glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, l_lightDir);
		glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 80.0f);
		glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 5.0f);
		glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, 0.0f);
		glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, 3.0f);
		glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 0.0f);
	#pragma endregion przedniKoniec
	
	
	#pragma region tylniKoniec
	
		float l5_pos[] = { -20.35f, 1.5f, 0.5f, 1.0f };
		glLightfv(GL_LIGHT5, GL_AMBIENT, l_amb);
		glLightfv(GL_LIGHT5, GL_DIFFUSE, l_dif);
		glLightfv(GL_LIGHT5, GL_SPECULAR, l_spe);
		glLightfv(GL_LIGHT5, GL_POSITION, l5_pos);
		glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, l_lightDir);
		glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 80.0f);
		glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 5.0f);
		glLightf(GL_LIGHT5, GL_CONSTANT_ATTENUATION, 0.0f);
		glLightf(GL_LIGHT5, GL_LINEAR_ATTENUATION, 3.0f);
		glLightf(GL_LIGHT5, GL_QUADRATIC_ATTENUATION, 0.0f);
	#pragma endregion tylniKoniec





#pragma endregion swiatlo

	if (loadObjs) { //JEDNOKROTNE ZALADOWANIE OBJTOW
		player.dir.x = 1.0f;
		player.dir.y = -0.065f;
		player.dir.z = 0.004f;
		loadObjs = false;
	}

	game->draw();
	game->drawMobs();


	glutSwapBuffers();
	glFlush();
	glutPostRedisplay();

}

void OnReshape(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(60.0f, (float) width / height, .01f, 100.0f);
}
