 
#pragma warning( disable : 4996 ) 

 
#include <cstdlib>
#include <vector>
#include <iostream>
#include <string>
#include "G2D.h"

bool InterRectRect(V2 pos, int hauteur, int largeur, int x2, int y2, int hauteur2, int largeur2);
void AssetsInit();
int rand_direction();
bool isPorteClosed(int x, int y);
bool isCheckPoint(int x, int y);
bool isCollisionGauche(int x, int y, int sizex, int sizey);
bool isCollisionDroite(int x, int y, int sizex, int sizey);
bool isCollisionHaut(int x, int y, int sizex, int sizey);
bool isCollisionBas(int x, int y, int sizex, int sizey);
bool isCollisionGauche(int x, int y, int sizex, int sizey, bool isMomie);
bool isCollisionDroite(int x, int y, int sizex, int sizey, bool isMomie);
bool isCollisionHaut(int x, int y, int sizex, int sizey, bool isMomie);
bool isCollisionBas(int x, int y, int sizex, int sizey, bool isMomie);
int frameBeforeSpawn();
void Mort();

 
using namespace std;

struct _Inventaire {

	bool Key;
	bool Munition;
	bool Pistolet;
	int nb_diamants;
};
 
struct _Heros
{
	string texture_droite =
		"[RRR  ]"
		"[RRWR ]"
		"[RRR  ]"
		"[YY   ]"
		"[YYY  ]"
		"[YY YG]"
		"[GG   ]"
		"[CC   ]"
		"[CC   ]"
		"[C C  ]"
		"[C C  ]";
	string texture_droite2 =
		"[RRR  ]"
		"[RRWR ]"
		"[RRR  ]"
		"[YY   ]"
		"[YYY  ]"
		"[YY YG]"
		"[GG   ]"
		"[CC   ]"
		"[CC   ]"
		"[CC   ]"
		"[CC   ]";
	string texture_gauche =
		"[  RRR]"
		"[ RWRR]"
		"[  RRR]"
		"[   YY]"
		"[  YYY]"
		"[GY YY]"
		"[   GG]"
		"[   CC]"
		"[   CC]"
		"[  C C]"
		"[  C C]";
	string texture_gauche2 =
		"[  RRR]"
		"[ RWRR]"
		"[  RRR]"
		"[   YY]"
		"[  YYY]"
		"[GY YY]"
		"[   GG]"
		"[   CC]"
		"[   CC]"
		"[   CC]"
		"[   CC]";

	V2 Size;
	int IdTexDroite;
	int IdTexDroite2;
	int IdTexGauche;
	int IdTexGauche2;
	V2 Pos;
	int hauteur = 11;
	int largeur = 5;
	int vies;
	int last_direction; // 0 : left | 1 : right
	V2 last_checkpoint;

	_Inventaire Inventaire;
};

struct _Key
{
	string texture =
		"[                      ]"
		"[     W W         WWWW ]"
		"[     W W        W    W]"
		"[   WWWWWWWWWWWWWW    W]"
  	    "[                W    W]"
		"[                 WWWW ]";


	V2 Size;
	int IdTex;
	V2 Pos;
};

struct _Chest {

	string texture =
		"[APRRRPAAPRRRPA]"
		"[OPRRRPOOPRRRPO]"
		"[DPZZZPDDPZZZPD]"
		"[DPZZZPDDPZZZPD]"
		"[OPRRRPOOPRRRPO]"
		"[OPRRDDDDDDRRPO]"
		"[OPPPOOOOOOPPPO]"
		"[OOOOOOZZOOOOOO]"
		"[AAAAOOZZOOAAAA]"
		"[OPPPOOOOOOPPPO]"
		"[OPRROOOOOORRPO]"
		"[OPPPPPPPPPPPPO]"
		"[OOOOOOOOOOOOOO]";

	V2 Size;
	int IdTex;
	V2 Pos;
};

struct _Momie
{
	string texture =

		"[       PPPPPP         ]"
		"[      PPPPPPPP        ]"
		"[     PPPPPPPPPP       ]"
		"[     PPPPPPPPPP       ]"
		"[     PKKKKKPPPP       ]"
		"[     PPWKWPPPPP       ]"
		"[      PPPPPPPP        ]"
		"[       PPPPPP         ]"
		"[        PPPPPP        ]"
		"[     PPPPPPPPP        ]"
		"[    PPPPPPPPPP        ]"
		"[    PPPPPPPPPP        ]"
		"[    PP  PPPPP         ]"
		"[        PPPPP         ]"
		"[        PPPPP         ]"
		"[       PP PPP         ]";

	V2 Pos;
	V2 Size;
	int IdTex;
	int direction;
	bool active;
};

struct _Munition {

	string texture_droite =
		"[KKKKKKKKKKKKKK    ]"
		"[KOOROOOOOOOORKK   ]"
		"[KOOROOOOOOOOROOK  ]"
		"[KOOROOOOOOOOROOOK ]"
		"[KOOROOOOOOOOROOOOK]"
		"[KOOROOOOOOOOROOOOK]"
		"[KOOROOOOOOOOROOOK ]"
		"[KOOROOOOOOOOROOK  ]"
		"[KOOROOOOOOOORKK   ]"
		"[KKKKKKKKKKKKKK    ]";

	string texture_gauche =
		"[    KKKKKKKKKKKKKK]"
		"[   KKROOOOOOOOROOK]"
		"[  KOOROOOOOOOOROOK]" 
		"[ KOOOROOOOOOOOROOK]"
		"[KOOOOROOOOOOOOROOK]"
		"[KOOOOROOOOOOOOROOK]"
		"[ KOOOROOOOOOOOROOK]"
		"[  KOOROOOOOOOOROOK]"
		"[   KKROOOOOOOOROOK]"
		"[    KKKKKKKKKKKKKK]";

	int IdTexDroite;
	int IdTexGauche;
	V2 Pos;
	V2 Size;
	bool active;
	int direction; // 0 : left | 1 : right

};

struct _Pistolet
{
	string texture_gauche =
		"[  MMMMMMMMMMMGGMM   ]"
		"[  MMMMMMMMMMMMMMMM  ]"
		"[  MMMMMMMMMMMMMGMG  ]"
		"[  GGGGGGGGMGGGGGGG  ]"
		"[          G  GGPG   ]"
		"[           GGGPPPG  ]"
		"[              GPPPG ]"
		"[               GPPG ]"
		"[               GGG  ]";
	string texture_droite =
		"[   MMGGMMMMMMMMMMM  ]"
		"[  MMMMMMMMMMMMMMMM  ]"
		"[  GMGMMMMMMMMMMMMM  ]"
		"[  GGGGGGMGGGGGGGGG  ]"
		"[   GPGG  G          ]"
		"[  GPPPGGG           ]"
		"[ GPPPG              ]"
		"[ GPPG               ]"
		"[  GGG               ]";

	V2 Pos;
	V2 Size;
	int IdTexGauche;
	int IdTexDroite;
};

struct _Diamant
{
	string texture =
		"[   WWWWWWWWWWW   ]"
		"[  WCCCWCCCWCCCW  ]"
		"[ WCCCWCCCCCWCCCW ]"
		"[WCCCWCCCCCCCWCCCW]"
		"[WWWWWWWWWWWWWWWWW]"
		"[ WCCWCCCCCCCWCCW ]"
		"[  WCCWCCCCCWCCW  ]"
		"[   WCCWCCCWCCW   ]"
		"[    WCCWCWCCW    ]"
		"[     WCCWCCW     ]"
		"[      WCCCW      ]"
		"[       WCW       ]"
		"[        W        ]";

	V2 Pos;
	V2 Size;
	int IdTex;
};

struct _CheckPoint {
	V2 Pos;
	V2 Size;
};

struct _Porte 
{
	V2 Pos;
	V2 Size;
	bool isClosed = false;
};

struct _Spawner
{
	string texture =
		"[PP PP PP PP]"
		"[PPPPPPPPPPP]"
		"[PPPPPPPPPPP]"
		"[PPPPPPPPPPP]"
		"[ PPPPPPPPP ]"
		"[ PPPPPPPPP ]"
		"[ PPPPPPPPP ]"
		"[ PPPPPPPPP ]"
		"[ PPPPPPPPP ]"
		"[ PPPPPPPPP ]"
		"[ PPPPPPPPP ]"
		"[ PPPPPPPPP ]"
		"[ PPPPPPPPP ]";

	V2 Pos;
	V2 Size;
	int IdTex;
	int Momies;
	int MomiesMax = 3;
	int nb_frame_before_spawn;
};

struct _Heart
{
	string texture =
		"[  RR   RR  ]"
		"[ RRRR RRRR ]"
		"[RRWWRRRRRRR]"
		"[RRWRRRRRRRR]"
		"[RRRRRRRRRRR]"
		"[ RRRRRRRRR ]"
		"[  RRRRRRR  ]"
		"[   RRRRR   ]"
		"[    RRR    ]"
		"[     R     ]";
	V2 Pos;
	V2 Size;
	int IdTex;
};

struct GameData
{

    string Map =
				 "MMMMMMMMMMMMMMM"
				 "M M           M"
				 "M M M MMM MMM M"
				 "M   M       M M"
				 "MMM M M MMM M M"
				 "M   M M     M M"
				 "M MMM MMM MMMMM"
				 "M   M  M      M"
				 "M M M  M M MM M"
				 "M M M  M M M  M"
				 "M M M MM M MMMM"
				 "M M M    M    M"
				 "M   M MMMMMMM M"
				 "M M      M    M"
				 "MMMMMMMMMMMMMMM";

	// indique la présence d'un mur à la case (x,y)
	bool Mur(int x, int y) { return Map[(15 - y - 1)*15+x] == 'M'; }  

	int Lpix = 40;  // largeur en pixels des cases du labyrinthe

	_Heros Heros;   // data du héros
	_Key   Key;
	_Chest Chest;
	vector<_Momie> Momies;

	int Ecran = 0;
	int time = 0;

	int n_frame = 0;

	_Pistolet Pistolet;
	_Munition Munition;

	_Diamant Diamants[3];

	_CheckPoint CheckPoints[3];

	_Porte Portes[6];
	_Spawner Spawners[2];

	int Score = 10000;

	GameData() {}

};

GameData G;


void render()
{
	G2D::ClearScreen(Color::Black);

	//Ecran d'accueil
	if (G.Ecran == 0) {

		G2D::DrawStringFontMono(V2(100, 500), "Labyrinthe", 60, 5, Color::Blue);
		G2D::DrawStringFontMono(V2(130, 450), "Press Enter", 50, 4, Color::White);
		G2D::DrawRectangle(V2(100, 100), V2(40, 40), Color::Black, true);
	}

	//Partie en cours
	if (G.Ecran == 1) {

		//Affichage des murs
		for (int x = 0; x < 15; x++) {
			for (int y = 0; y < 15; y++) {

				int xx = x * G.Lpix;
				int yy = y * G.Lpix;

				if (G.Mur(x, y)) {
					G2D::DrawRectangle(V2(xx, yy), V2(G.Lpix, G.Lpix), Color::Blue, true);
				}
			}
		}

		//Affichage des CheckPoints
		for (_CheckPoint& CheckPoint : G.CheckPoints) {
			G2D::DrawRectangle(CheckPoint.Pos, CheckPoint.Size, Color::Green, true);
		}

		//Affichage des vies restantes
		_Heart Heart;
		Heart.Pos = V2(40, 570);
		Heart.IdTex = G2D::InitTextureFromString(Heart.Size, Heart.texture);
		G2D::DrawRectWithTexture(Heart.IdTex,Heart.Pos,Heart.Size*2);
		G2D::DrawStringFontMono(V2(70, 572),std::to_string(G.Heros.vies), 20, 2, Color::Red);

		//Affichage Score
		G2D::DrawStringFontMono(V2(420, 570), "Score:" + std::to_string(G.Score), 20, 2, Color::Yellow);


		// affichage et animation du héros
		//G2D::DrawRectangle(G.Heros.Pos, G.Heros.Size, Color::Red);
		if (G2D::IsKeyPressed(Key::RIGHT)) {
			if (G.n_frame % 30 < 15) {
				G2D::DrawRectWithTexture(G.Heros.IdTexDroite, G.Heros.Pos, G.Heros.Size);
			}
			else {
				G2D::DrawRectWithTexture(G.Heros.IdTexDroite2, G.Heros.Pos, G.Heros.Size);
			}
			G.Heros.last_direction = 1;
		}
		else if (G2D::IsKeyPressed(Key::LEFT)) {
			if (G.n_frame % 30 < 15) {
				G2D::DrawRectWithTexture(G.Heros.IdTexGauche, G.Heros.Pos, G.Heros.Size);
			}
			else {
				G2D::DrawRectWithTexture(G.Heros.IdTexGauche2, G.Heros.Pos, G.Heros.Size);
			}
			G.Heros.last_direction = 0;
		}
		else if (G2D::IsKeyPressed(Key::UP) || G2D::IsKeyPressed(Key::DOWN)) {
			if (G.Heros.last_direction == 1) {
				if (G.n_frame % 30 < 15) {
					G2D::DrawRectWithTexture(G.Heros.IdTexDroite, G.Heros.Pos, G.Heros.Size);
				}
				else {
					G2D::DrawRectWithTexture(G.Heros.IdTexDroite2, G.Heros.Pos, G.Heros.Size);
				}
			}
			else {
				if (G.n_frame % 30 < 15) {
					G2D::DrawRectWithTexture(G.Heros.IdTexGauche, G.Heros.Pos, G.Heros.Size);
				}
				else {
					G2D::DrawRectWithTexture(G.Heros.IdTexGauche2, G.Heros.Pos, G.Heros.Size);
				}
			}
		}
		else {
			if (G.Heros.last_direction == 1) { G2D::DrawRectWithTexture(G.Heros.IdTexDroite2, G.Heros.Pos, G.Heros.Size); }
			else { G2D::DrawRectWithTexture(G.Heros.IdTexGauche2, G.Heros.Pos, G.Heros.Size); }
		}
		G.n_frame++;

		// affichage de la clef
		G2D::DrawRectWithTexture(G.Key.IdTex, G.Key.Pos, G.Key.Size);

		//Affichage du coffre
		G2D::DrawRectWithTexture(G.Chest.IdTex, G.Chest.Pos, G.Chest.Size);
		
		//Affichage des momies
		for (auto& Momie : G.Momies) {
			G2D::DrawRectWithTexture(Momie.IdTex, Momie.Pos, Momie.Size);
		}

		// Affichage du pistolet
		if (G.Heros.Inventaire.Pistolet) {
			if (G.Heros.last_direction == 0) {
				G2D::DrawRectWithTexture(G.Pistolet.IdTexGauche, G.Pistolet.Pos, G.Pistolet.Size);
			}
			else {
				G2D::DrawRectWithTexture(G.Pistolet.IdTexDroite, G.Pistolet.Pos, G.Pistolet.Size);
			}
		}
		else {
			G2D::DrawRectWithTexture(G.Pistolet.IdTexGauche, G.Pistolet.Pos, G.Pistolet.Size);
		}		

		//Affichage de la munition
		if (G.Munition.active == false) {
			G2D::DrawRectWithTexture(G.Munition.IdTexDroite, G.Munition.Pos, G.Munition.Size);
		}
		else {
			if (G.Munition.direction == 0) {
				G2D::DrawRectWithTexture(G.Munition.IdTexGauche, G.Munition.Pos, G.Munition.Size);
			}
			else {
				G2D::DrawRectWithTexture(G.Munition.IdTexDroite, G.Munition.Pos, G.Munition.Size);
			}
		}

		//Affichage du diamant
		for (_Diamant Diamant : G.Diamants) {
			G2D::DrawRectWithTexture(Diamant.IdTex, Diamant.Pos, Diamant.Size);
		}
		


		//Affichage des portes
		for (_Porte Porte : G.Portes) {
			if (Porte.isClosed) {
				Porte.Size = V2(40, 40);
			}
			else {
				Porte.Size = V2(40, 0);
			}
			G2D::DrawRectangle(Porte.Pos, Porte.Size, Color::Red, true);
		}

		//Affichage du spawner
		for (int i = 0; i < sizeof G.Spawners / sizeof G.Spawners[0]; i++) {
			G2D::DrawRectWithTexture(G.Spawners[i].IdTex, G.Spawners[i].Pos, G.Spawners[i].Size);
		}
		
		/*G2D::DrawRectangle(V2((int(G.Heros.Pos.x / 40) - 1) * 40, int(G.Heros.Pos.y / 40) * 40), V2(40, 40), Color::Red);
		G2D::DrawRectangle(V2((int(G.Heros.Pos.x / 40) + 1) * 40, int(G.Heros.Pos.y / 40) * 40), V2(40, 40), Color::Red);
		G2D::DrawRectangle(V2((int(G.Heros.Pos.x / 40)) * 40, (int(G.Heros.Pos.y / 40) - 1) * 40), V2(40, 40), Color::Red);
		G2D::DrawRectangle(V2((int(G.Heros.Pos.x / 40)) * 40, (int(G.Heros.Pos.y / 40) + 1) * 40), V2(40, 40), Color::Red);
		G2D::DrawRectangle(V2((int(G.Heros.Pos.x / 40) - 1) * 40, (int(G.Heros.Pos.y / 40) + 1) * 40), V2(40, 40), Color::Red);
		G2D::DrawRectangle(V2((int(G.Heros.Pos.x / 40) + 1) * 40, (int(G.Heros.Pos.y / 40) + 1) * 40), V2(40, 40), Color::Red);*/

	}

	//Partie gagnée
	if (G.Ecran == 2) {
		G2D::DrawStringFontMono(V2(200, 300), "WIN", 60, 4, Color::Green);
		G2D::DrawRectangle(V2(0, 0), V2(0, 0), Color::Black, true);
	}

	//Partie perdue
	if (G.Ecran == 3) {
		G2D::DrawStringFontMono(V2(100, 300), "GAME OVER", 60, 4, Color::Red);
		G2D::DrawRectangle(V2(0, 0), V2(0, 0), Color::Black, true);
	}
	  
	G2D::Show();
}

 
void Logic()
{

	//Ecran d'accueil
	if (G.Ecran == 0) {
		if (G2D::IsKeyPressed(Key::ENTER)) {
			G.Ecran = 4;
		}
	}

	//Initialisation
	if (G.Ecran == 4) {
		
		vector<_Momie> m;
		G.Momies = m;

		AssetsInit();

		G.Ecran = 1;
	}

	//Partie en cours
	if (G.Ecran == 1) {

		//Décrémentation du Score pendant l'avancement de la partie
		if (G.n_frame % 200 == 0) {
			G.Score -= 50;
		}

		//Déplacements du heros
		if (!isCollisionGauche(G.Heros.Pos.x, G.Heros.Pos.y, G.Heros.Size.x, G.Heros.Size.y)) {
			if (G2D::IsKeyPressed(Key::LEFT))  G.Heros.Pos.x--;
		}
		if (!isCollisionDroite(G.Heros.Pos.x, G.Heros.Pos.y, G.Heros.Size.x, G.Heros.Size.y)){
			if (G2D::IsKeyPressed(Key::RIGHT)) G.Heros.Pos.x++;
		}
		if (!isCollisionHaut(G.Heros.Pos.x, G.Heros.Pos.y, G.Heros.Size.x, G.Heros.Size.y)) {
			if (G2D::IsKeyPressed(Key::UP))    G.Heros.Pos.y++;
		}
		if (!isCollisionBas(G.Heros.Pos.x, G.Heros.Pos.y, G.Heros.Size.x, G.Heros.Size.y)) {
			if (G2D::IsKeyPressed(Key::DOWN))  G.Heros.Pos.y--;
		}

		//Collision avec la clef
		if (InterRectRect(G.Heros.Pos, G.Heros.Size.y, G.Heros.Size.x, G.Key.Pos.x, G.Key.Pos.y, G.Key.Size.y, G.Key.Size.x)) {
			G.Heros.Inventaire.Key = true;
			G.Key.Pos = V2(160, 570);
		}

		//Collision avec le coffre
		if (InterRectRect(G.Heros.Pos, G.Heros.Size.y, G.Heros.Size.x, G.Chest.Pos.x, G.Chest.Pos.y, G.Chest.Size.y, G.Chest.Size.x) && G.Heros.Inventaire.Key == true) {
			G.Heros.Inventaire.Key = false;
			G.Chest.Size = V2(0, 0);
			G.Ecran = 2;
			G.time = G2D::ElapsedTimeFromStartSeconds();
		}


		// Deplacements des Momies
		for (auto& Momie : G.Momies) {

			if (Momie.active) {
				if (isCollisionGauche(Momie.Pos.x, Momie.Pos.y, Momie.Size.x, Momie.Size.y, true))
				{
					Momie.Pos.x++;
					Momie.direction = rand_direction();
				}
				else {
					if (Momie.direction == 0) { { Momie.Pos.x--; } }
				}

				if (isCollisionDroite(Momie.Pos.x, Momie.Pos.y, Momie.Size.x, Momie.Size.y, true))
				{
					Momie.Pos.x--;
					Momie.direction = rand_direction();
				}
				else {
					if (Momie.direction == 1) { { Momie.Pos.x++; } }
				}

				if (isCollisionHaut(Momie.Pos.x, Momie.Pos.y, Momie.Size.x, Momie.Size.y, true))
				{
					Momie.Pos.y--;
					Momie.direction = rand_direction();
				}
				else {
					if (Momie.direction == 2) { { Momie.Pos.y++; } }
				}

				if (isCollisionBas(Momie.Pos.x, Momie.Pos.y, Momie.Size.x, Momie.Size.y, true))
				{
					Momie.Pos.y++;
					Momie.direction = rand_direction();
				}
				else {
					if (Momie.direction == 3) { { Momie.Pos.y--; } }
				}
			}
		}

		//Collision Héros avec une momie
		for (auto& Momie : G.Momies) {
			if (InterRectRect(G.Heros.Pos, G.Heros.Size.y, G.Heros.Size.x, Momie.Pos.x, Momie.Pos.y, Momie.Size.y, Momie.Size.x)) {
				Mort();
			}
		}

		//Collision avec le pistolet
		if (InterRectRect(G.Heros.Pos, G.Heros.Size.y, G.Heros.Size.x, G.Pistolet.Pos.x, G.Pistolet.Pos.y, G.Pistolet.Size.y, G.Pistolet.Size.x)) {
			G.Heros.Inventaire.Pistolet = true;
		}

		//Deplacements du pistolet
		if (G.Heros.Inventaire.Pistolet) {
			if (G.Heros.last_direction == 1) {
				G.Pistolet.Pos.x = G.Heros.Pos.x;
			}
			else {
				G.Pistolet.Pos.x = G.Heros.Pos.x - G.Heros.largeur;
			}
			G.Pistolet.Pos.y = G.Heros.Pos.y + G.Heros.hauteur / 2;
		}

		//Utilisation du pistolet
		if (G.Heros.Inventaire.Pistolet && G.Heros.Inventaire.Munition) {
			if (G2D::IsKeyPressed(Key::ENTER)) {
				G.Heros.Inventaire.Munition = false;
				G.Munition.active = true;
				G.Munition.direction = G.Heros.last_direction;
				G.Munition.Pos = G.Pistolet.Pos;
			}
		}

		//Collision avec la munition
		if (G.Munition.active == false) {
			//Le joueur ramasse la munition au sol
			if (InterRectRect(G.Heros.Pos, G.Heros.Size.y, G.Heros.Size.x, G.Munition.Pos.x, G.Munition.Pos.y, G.Munition.Size.y, G.Munition.Size.x)) {
				G.Heros.Inventaire.Munition = true;
				G.Munition.Pos = V2(200, 570);
			}
		}
		else {
			for (auto& Momie : G.Momies) {
				//Une momie reçoit la munition tirée ==> +500 points
				if (InterRectRect(Momie.Pos, Momie.Size.y, Momie.Size.x, G.Munition.Pos.x, G.Munition.Pos.y, G.Munition.Size.y, G.Munition.Size.x)) {
					G.Munition.active = false;
					G.Munition.Size = V2(0, 0);
					G.Munition.Pos = V2(0, 0);
					Momie.active = false;
					Momie.Size = V2(0, 0);
					Momie.Pos = V2(0, 0);
					G.Score += 1000;
				}
			}
		}

		//Deplacements de la munition
		if (G.Munition.active) {
			if (G.Munition.direction) {
				if (isCollisionDroite(G.Munition.Pos.x, G.Munition.Pos.y, G.Munition.Size.x, G.Munition.Size.y)) {
					G.Munition.active = false;
					G.Munition.Size = V2(0, 0);
					G.Munition.Pos = V2(0, 0);
				}
				G.Munition.Pos.x = G.Munition.Pos.x + 3;
			}
			else {
				if (isCollisionGauche(G.Munition.Pos.x, G.Munition.Pos.y, G.Munition.Size.x, G.Munition.Size.y)) {
					G.Munition.active = false;
					G.Munition.Size = V2(0, 0);
					G.Munition.Pos = V2(0, 0);
				}
				G.Munition.Pos.x = G.Munition.Pos.x - 3;
			}
		}


		//Gestion aléatoire de la fermeture des portes
		if (G.n_frame % 100 == 0) {
			for (_Porte& Porte : G.Portes) {

				int nb_rand = rand() % 2;

				if (nb_rand == 1) { 
					Porte.isClosed = true; 
				}
				else { 
					Porte.isClosed = false; 
				}
			}
		}

		//Gestion des checkpoints
		for (_CheckPoint& CheckPoint : G.CheckPoints) {
			if (InterRectRect(G.Heros.Pos, G.Heros.Size.y, G.Heros.Size.x, CheckPoint.Pos.x, CheckPoint.Pos.y, CheckPoint.Size.y, CheckPoint.Size.x)) {
				G.Heros.last_checkpoint = V2(CheckPoint.Pos.x + 5, CheckPoint.Pos.y + 5);
			}
		}

		//Gestion du spawn de momies
		for (int i = 0; i < sizeof G.Spawners / sizeof G.Spawners[0]; i++) {
			if (G.n_frame % G.Spawners[i].nb_frame_before_spawn == 0 && G.Spawners[i].Momies < G.Spawners[i].MomiesMax && G.n_frame != 0) {
				_Momie M;
				M.IdTex = G2D::InitTextureFromString(M.Size, M.texture);
				M.Pos = G.Spawners[i].Pos;
				M.Size = M.Size * 1.5;
				M.active = true;
				G.Momies.push_back(M);
				G.Spawners[i].Momies++;
				G.Spawners[i].nb_frame_before_spawn = frameBeforeSpawn();
			}
		}

		//Collision avec les Diamants
		for (_Diamant &Diamant : G.Diamants) {
			if (InterRectRect(G.Heros.Pos, G.Heros.Size.y, G.Heros.Size.x, Diamant.Pos.x, Diamant.Pos.y, Diamant.Size.y, Diamant.Size.x)) {
				G.Heros.Inventaire.nb_diamants+=1;
				if (G.Heros.Inventaire.nb_diamants == 1) Diamant.Pos = V2(250, 570);
				else if(G.Heros.Inventaire.nb_diamants == 2) Diamant.Pos = V2(270, 570);
				else Diamant.Pos = V2(290, 570);
				G.Score += 500;
			}
		}

		//Détection du game over
		if (G.Heros.vies < 1 || G.Score <= 0) {
			G.Ecran = 3;
			G.time = G2D::ElapsedTimeFromStartSeconds();
		}
	}

	//Partie gagnée
	if (G.Ecran == 2) {

		if (G2D::ElapsedTimeFromStartSeconds() - G.time > 3) {
			G.Ecran = 0;
		}
	}

	//Partie perdue
	if (G.Ecran == 3) {

		if (G2D::ElapsedTimeFromStartSeconds() - G.time > 3) {
			G.Ecran = 0;
		}
	}

}
 

void AssetsInit()
{
   // Size passé en ref et texture en param
	G.Heros.IdTexDroite = G2D::InitTextureFromString(G.Heros.Size, G.Heros.texture_droite);
	G.Heros.IdTexDroite2 = G2D::InitTextureFromString(G.Heros.Size, G.Heros.texture_droite2);
	G.Heros.IdTexGauche = G2D::InitTextureFromString(G.Heros.Size, G.Heros.texture_gauche);
	G.Heros.IdTexGauche2 = G2D::InitTextureFromString(G.Heros.Size, G.Heros.texture_gauche2);
	G.Heros.Pos = V2(45, 45);
	G.Heros.Size = G.Heros.Size * 2; // on peut zoomer la taille du sprite
	G.Heros.vies = 3;
	G.Heros.last_direction = 1;
	G.Heros.last_checkpoint = V2(45, 45);

	G.Heros.Inventaire.Key = false;
	G.Heros.Inventaire.Munition = false;
	G.Heros.Inventaire.Pistolet = false;
	G.Heros.Inventaire.nb_diamants = 0;

	G.Key.IdTex = G2D::InitTextureFromString(G.Key.Size, G.Key.texture);
	G.Key.Pos = V2(520, 140);
	G.Key.Size = G.Key.Size * 1.5; // on peut zoomer la taille du sprite

	G.Chest.IdTex = G2D::InitTextureFromString(G.Chest.Size, G.Chest.texture);
	G.Chest.Pos = V2(43, 530);
	G.Chest.Size = G.Chest.Size * 2;

	_Momie Momie1;
	_Momie Momie2;
	_Momie Momie3;

	Momie1.IdTex = G2D::InitTextureFromString(Momie1.Size, Momie1.texture);
	Momie1.Pos = V2(45, 240);
	Momie1.Size = Momie1.Size * 1.5;
	Momie1.active = true;

	Momie2.IdTex = G2D::InitTextureFromString(Momie2.Size, Momie2.texture);
	Momie2.Pos = V2(200, 240);
	Momie2.Size = Momie2.Size * 1.5;
	Momie2.active = true;

	Momie3.IdTex = G2D::InitTextureFromString(Momie3.Size, Momie3.texture);
	Momie3.Pos = V2(320, 240);
	Momie3.Size = Momie3.Size * 1.5;
	Momie3.active = true;

	G.Momies.push_back(Momie1);
	G.Momies.push_back(Momie2);
	G.Momies.push_back(Momie3);

	G.Pistolet.IdTexGauche = G2D::InitTextureFromString(G.Pistolet.Size, G.Pistolet.texture_gauche);
	G.Pistolet.IdTexDroite = G2D::InitTextureFromString(G.Pistolet.Size, G.Pistolet.texture_droite);
	G.Pistolet.Pos = V2(280, 360);

	G.Munition.IdTexDroite = G2D::InitTextureFromString(G.Munition.Size, G.Munition.texture_droite);
	G.Munition.IdTexGauche = G2D::InitTextureFromString(G.Munition.Size, G.Munition.texture_gauche);
	G.Munition.Pos = V2(530, 200);
	G.Munition.active = false;
	G.Munition.direction = 1;

	_Diamant Diamant1;
	_Diamant Diamant2;
	_Diamant Diamant3;

	Diamant1.IdTex = G2D::InitTextureFromString(Diamant1.Size, Diamant1.texture);
	Diamant1.Pos = V2(250, 300);
	Diamant2.IdTex = G2D::InitTextureFromString(Diamant2.Size, Diamant2.texture);
	Diamant2.Pos = V2(340, 50);
	Diamant3.IdTex = G2D::InitTextureFromString(Diamant3.Size, Diamant3.texture);
	Diamant3.Pos = V2(540, 540);

	G.Diamants[0] = Diamant1;
	G.Diamants[1] = Diamant2;
	G.Diamants[2] = Diamant3;

	G.CheckPoints[0].Pos = V2(40, 40);
	G.CheckPoints[0].Size = V2(40, 40);

	G.CheckPoints[1].Pos = V2(480, 200);
	G.CheckPoints[1].Size = V2(40, 40);

	G.CheckPoints[2].Pos = V2(360, 480);
	G.CheckPoints[2].Size = V2(40, 40);

	G.Portes[0].Pos = V2(80, 80);
	G.Portes[1].Pos = V2(120, 400);
	G.Portes[2].Pos = V2(160, 40);
	G.Portes[3].Pos = V2(160,520);
	G.Portes[4].Pos = V2(200, 480);
	G.Portes[5].Pos = V2(200, 160);

	for (_Porte Porte : G.Portes) {
	   Porte.Size = V2(40, 40);
	}

	_Spawner Spawner1;
	_Spawner Spawner2;

	Spawner1.IdTex = G2D::InitTextureFromString(Spawner1.Size, Spawner1.texture);
	Spawner1.Size = Spawner1.Size * 2;
	Spawner1.Pos = V2(400, 45);
	Spawner1.nb_frame_before_spawn = frameBeforeSpawn();
	Spawner1.Momies = 0;

	Spawner2.IdTex = G2D::InitTextureFromString(Spawner2.Size, Spawner2.texture);
	Spawner2.Size = Spawner2.Size * 2;
	Spawner2.Pos = V2(450, 450);
	Spawner2.nb_frame_before_spawn = frameBeforeSpawn();
	Spawner2.Momies = 0;

	G.Spawners[0] = Spawner1;
	G.Spawners[1] = Spawner2;
   
}

int main(int argc, char* argv[])
{ 

	G2D::InitWindow(argc,argv,V2(G.Lpix * 15, G.Lpix * 15), V2(200,200), string("Labyrinthe"));
	  
	G2D::Run(Logic,render);
 
}

//Détecter une collision entre 2 rectangles
bool InterRectRect(V2 pos, int hauteur, int largeur, int x2, int y2, int hauteur2, int largeur2) {

	if (pos.y + hauteur < y2) {
		return false;  // (1)
	}
	if (pos.y > y2 + hauteur2) {
		return false;  // (2)
	}
	if (pos.x > x2 + largeur2) {
		return false;  // (3)
	}
	if (pos.x + largeur < x2) {
		return false;
	}

	return true;
}

//Retourne un chiffre aléatoire en 0 et 4 afin de choisir une direction pour la momie
int rand_direction(){
	return rand() % 4;
}

//Retourne true s'il y a une porte fermee en (x, y), false sinon
bool isPorteClosed(int x, int y) {

	int pos_horizontal = x * 40;
	int pos_vertical = y * 40;

	for (_Porte &Porte : G.Portes) {
		if (Porte.Pos.x == pos_horizontal && Porte.Pos.y == pos_vertical && Porte.isClosed == true) return true;
	}

	return false;
}

//Retourne true s'il y a un checkpoint en (x, y), false sinon
bool isCheckPoint(int x, int y) {

	int pos_horizontal = x * 40;
	int pos_vertical = y * 40;

	for (_CheckPoint& CheckPoint : G.CheckPoints) {
		if (CheckPoint.Pos.x == pos_horizontal && CheckPoint.Pos.y == pos_vertical) {
			return true;
		}

		return false;
	}
}

//Detecte si un objet est bloque vers la gauche
bool isCollisionGauche(int x, int y, int sizex, int sizey) {

	if (InterRectRect(V2(x, y), sizey, sizex, (int(x / 40) - 1) * 40, int(y / 40) * 40, 40, 40) && G.Mur((x / 40) - 1, y / 40)) {
		return true;
	}
	if (InterRectRect(V2(x, y), sizey, sizex, (int(x / 40) - 1) * 40, int(y / 40 + 1) * 40, 40, 40) && G.Mur((x / 40) - 1, (y / 40) + 1)) {
		return true;
	}

	if (InterRectRect(V2(x, y), sizey, sizex, int(x / 40) * 40, int(y / 40) * 40, 40, 40) && G.Mur(x / 40, y / 40)) {
		return true;
	}
	if (InterRectRect(V2(x, y), sizey, sizex, int(x / 40) * 40, int(y / 40) * 40, 40, 40) && isPorteClosed(int(x / 40), int(y / 40))) {
		return true;
	}

	if (InterRectRect(V2(x, y), sizey, sizex, (int(x / 40) - 1) * 40, int(y / 40) * 40, 40, 40) && isPorteClosed(int(x / 40) - 1, int(y / 40))) {
		return true;
	}
	if (InterRectRect(V2(x, y), sizey, sizex, (int(x / 40) - 1) * 40, (int(y / 40) + 1) * 40, 40, 40) && isPorteClosed(int(x / 40) - 1, int(y / 40) + 1)) {
		return true;
	}

	return false;
}

//Surcharge avec un booleen isMomie
bool isCollisionGauche(int x, int y, int sizex, int sizey, bool isMomie) {

	if (InterRectRect(V2(x, y), sizey, sizex, (int(x / 40) - 1) * 40, int(y / 40) * 40, 40, 40) && G.Mur((x / 40) - 1, y / 40)) {
		return true;
	}
	if (InterRectRect(V2(x, y), sizey, sizex, (int(x / 40) - 1) * 40, int(y / 40 + 1) * 40, 40, 40) && G.Mur((x / 40) - 1, (y / 40) + 1)) {
		return true;
	}

	if (InterRectRect(V2(x, y), sizey, sizex, int(x / 40) * 40, int(y / 40) * 40, 40, 40) && G.Mur(x / 40, y / 40)) {
		return true;
	}
	if (InterRectRect(V2(x, y), sizey, sizex, int(x / 40) * 40, int(y / 40) * 40, 40, 40) && isPorteClosed(int(x / 40), int(y / 40))) {
		return true;
	}

	if (InterRectRect(V2(x, y), sizey, sizex, (int(x / 40) - 1) * 40, int(y / 40) * 40, 40, 40) && isPorteClosed(int(x / 40) - 1, int(y / 40))) {
		return true;
	}
	if (InterRectRect(V2(x, y), sizey, sizex, (int(x / 40) - 1) * 40, (int(y / 40) + 1) * 40, 40, 40) && isPorteClosed(int(x / 40) - 1, int(y / 40) + 1)) {
		return true;
	}

	if (isMomie) {
		if (InterRectRect(V2(x, y), sizey, sizex, (int(x / 40) - 1) * 40, int(y / 40) * 40, 40, 40) && isCheckPoint(int(x / 40) - 1, int(y / 40))) {
			return true;
		}
		if (InterRectRect(V2(x, y), sizey, sizex, (int(x / 40) - 1) * 40, (int(y / 40) + 1) * 40, 40, 40) && isCheckPoint(int(x / 40) - 1, int(y / 40) + 1)) {
			return true;
		}
	}

	return false;
}

//Detecte si un objet est bloque vers la droite
bool isCollisionDroite(int x, int y, int sizex, int sizey) {

	if (InterRectRect(V2(x,y), sizey, sizex, (int(x / 40) + 1) * 40 - 1, int(y / 40) * 40, 40, 41) && G.Mur((x / 40) + 1, y / 40)) {
		return true;
	}
	if (InterRectRect(V2(x, y), sizey, sizex, (int(x / 40) + 1) * 40, int(y / 40 + 1) * 40, 40, 40) && G.Mur((x / 40) + 1, (y / 40) + 1)) {
		return true;
	}

	if (InterRectRect(V2(x, y), sizey, sizex, int(x / 40) * 40, int(y / 40) * 40, 40, 40) && G.Mur(x / 40, y / 40)) {
		return true;
	}
	if (InterRectRect(V2(x, y), sizey, sizex, int(x / 40) * 40, int(y / 40) * 40, 40, 40) && isPorteClosed(int(x / 40), int(y / 40))) {
		return true;
	}

	if (InterRectRect(V2(x, y), sizey, sizex, (int(x / 40) + 1) * 40 - 1, int(y / 40) * 40, 40, 41) && isPorteClosed(int(x / 40) + 1, int(y / 40))) {
		return true;
	}
	if (InterRectRect(V2(x, y), sizey, sizex, (int(x / 40) + 1) * 40, (int(y / 40) + 1) * 40, 40, 40) && isPorteClosed(int(x / 40) + 1, int(y / 40) + 1)) {
		return true;
	}

	return false;
}

//Surcharge avec un booleen isMomie
bool isCollisionDroite(int x, int y, int sizex, int sizey, bool isMomie) {

	if (InterRectRect(V2(x, y), sizey, sizex, (int(x / 40) + 1) * 40 - 1, int(y / 40) * 40, 40, 41) && G.Mur((x / 40) + 1, y / 40)) {
		return true;
	}
	if (InterRectRect(V2(x, y), sizey, sizex, (int(x / 40) + 1) * 40, int(y / 40 + 1) * 40, 40, 40) && G.Mur((x / 40) + 1, (y / 40) + 1)) {
		return true;
	}

	if (InterRectRect(V2(x, y), sizey, sizex, int(x / 40) * 40, int(y / 40) * 40, 40, 40) && G.Mur(x / 40, y / 40)) {
		return true;
	}
	if (InterRectRect(V2(x, y), sizey, sizex, int(x / 40) * 40, int(y / 40) * 40, 40, 40) && isPorteClosed(int(x / 40), int(y / 40))) {
		return true;
	}

	if (InterRectRect(V2(x, y), sizey, sizex, (int(x / 40) + 1) * 40 - 1, int(y / 40) * 40, 40, 41) && isPorteClosed(int(x / 40) + 1, int(y / 40))) {
		return true;
	}
	if (InterRectRect(V2(x, y), sizey, sizex, (int(x / 40) + 1) * 40, (int(y / 40) + 1) * 40, 40, 40) && isPorteClosed(int(x / 40) + 1, int(y / 40) + 1)) {
		return true;
	}

	if (isMomie) {
		if (InterRectRect(V2(x, y), sizey, sizex, (int(x / 40) + 1) * 40 - 1, int(y / 40) * 40, 40, 41) && isCheckPoint(int(x / 40) + 1, int(y / 40))) {
			return true;
		}
		if (InterRectRect(V2(x, y), sizey, sizex, (int(x / 40) + 1) * 40, (int(y / 40) + 1) * 40, 40, 40) && isCheckPoint(int(x / 40) + 1, int(y / 40) + 1)) {
			return true;
		}
	}

	return false;
}

//Detecte si un objet est bloque vers le haut
bool isCollisionHaut(int x, int y, int sizex, int sizey) {

	if (InterRectRect(V2(x, y), sizey, sizex, int(x / 40) * 40, (int(y / 40) + 1) * 40 - 1 - 1, 41, 40) && G.Mur(x / 40, (y / 40) + 1)) {
		return true;
	}
	if (InterRectRect(V2(x, y), sizey, sizex, (int(x / 40) + 1) * 40, (int(y / 40) + 1) * 40, 40, 40) && G.Mur((x / 40) + 1, (y / 40) + 1)) {
		return true;
	}

	if (InterRectRect(V2(x, y), sizey, sizex, int(x / 40) * 40, int(y / 40) * 40, 40, 40) && G.Mur(x / 40, y / 40)) {
		return true;
	}
	if (InterRectRect(V2(x, y), sizey, sizex, int(x / 40) * 40, int(y / 40) * 40, 40, 40) && isPorteClosed(int(x / 40), int(y / 40))) {
		return true;
	}

	if (InterRectRect(V2(x, y), sizey, sizex, int(x / 40) * 40, (int(y / 40) + 1) * 40, 41, 40) && isPorteClosed(int(x / 40), int(y / 40) + 1)) {
		return true;
	}
	if (InterRectRect(V2(x, y), sizey, sizex, (int(x / 40) + 1) * 40, (int(y / 40) + 1) * 40, 40, 40) && isPorteClosed(int(x / 40) + 1, int(y / 40) + 1)) {
		return true;
	}

	return false;
}

//Surcharge avec un booleen isMomie
bool isCollisionHaut(int x, int y, int sizex, int sizey, bool isMomie) {

	if (InterRectRect(V2(x, y), sizey, sizex, int(x / 40) * 40, (int(y / 40) + 1) * 40 - 1 - 1, 41, 40) && G.Mur(x / 40, (y / 40) + 1)) {
		return true;
	}
	if (InterRectRect(V2(x, y), sizey, sizex, (int(x / 40) + 1) * 40, (int(y / 40) + 1) * 40, 40, 40) && G.Mur((x / 40) + 1, (y / 40) + 1)) {
		return true;
	}

	if (InterRectRect(V2(x, y), sizey, sizex, int(x / 40) * 40, int(y / 40) * 40, 40, 40) && G.Mur(x / 40, y / 40)) {
		return true;
	}
	if (InterRectRect(V2(x, y), sizey, sizex, int(x / 40) * 40, int(y / 40) * 40, 40, 40) && isPorteClosed(int(x / 40), int(y / 40))) {
		return true;
	}

	if (InterRectRect(V2(x, y), sizey, sizex, int(x / 40) * 40, (int(y / 40) + 1) * 40, 41, 40) && isPorteClosed(int(x / 40), int(y / 40) + 1)) {
		return true;
	}
	if (InterRectRect(V2(x, y), sizey, sizex, (int(x / 40) + 1) * 40, (int(y / 40) + 1) * 40, 40, 40) && isPorteClosed(int(x / 40) + 1, int(y / 40) + 1)) {
		return true;
	}

	if (isMomie) {
		if (InterRectRect(V2(x, y), sizey, sizex, int(x / 40) * 40, (int(y / 40) + 1) * 40, 41, 40) && isCheckPoint(int(x / 40), int(y / 40) + 1)) {
			return true;
		}
		if (InterRectRect(V2(x, y), sizey, sizex, (int(x / 40) + 1) * 40, (int(y / 40) + 1) * 40, 40, 40) && isCheckPoint(int(x / 40) + 1, int(y / 40) + 1)) {
			return true;
		}
	}

	return false;
}

//Detecte si un objet est bloque vers le bas
bool isCollisionBas(int x, int y, int sizex, int sizey) {

	if (InterRectRect(V2(x, y), sizey, sizex, int(x / 40) * 40, (int(y / 40) - 1) * 40, 40, 40) && G.Mur(x / 40, (y / 40) - 1)) {
		return true;
	}
	if (InterRectRect(V2(x, y), sizey, sizex, (int(x / 40) + 1) * 40, (int(y / 40) - 1) * 40, 40, 40) && G.Mur((x / 40) + 1, (y / 40) - 1)) {
		return true;
	}

	if (InterRectRect(V2(x, y), sizey, sizex, int(x / 40) * 40, int(y / 40) * 40, 40, 40) && G.Mur(x / 40, y / 40)) {
		return true;
	}
	if (InterRectRect(V2(x, y), sizey, sizex, int(x / 40) * 40, int(y / 40) * 40, 40, 40) && isPorteClosed(int(x / 40), int(y / 40))) {
		return true;
	}

	if (InterRectRect(V2(x, y), sizey, sizex, int(x / 40) * 40, (int(y / 40) - 1) * 40, 40, 40) && isPorteClosed(int(x / 40), int(y / 40) - 1)) {
		return true;
	}
	if (InterRectRect(V2(x, y), sizey, sizex, (int(x / 40) + 1) * 40, (int(y / 40) - 1) * 40, 40, 40) && isPorteClosed(int(x / 40) + 1, int(y / 40) - 1)) {
		return true;
	}

	return false;
}

//Surcharge avec un booleen isMomie
bool isCollisionBas(int x, int y, int sizex, int sizey, bool isMomie) {

	if (InterRectRect(V2(x, y), sizey, sizex, int(x / 40) * 40, (int(y / 40) - 1) * 40, 40, 40) && G.Mur(x / 40, (y / 40) - 1)) {
		return true;
	}
	if (InterRectRect(V2(x, y), sizey, sizex, (int(x / 40) + 1) * 40, (int(y / 40) - 1) * 40, 40, 40) && G.Mur((x / 40) + 1, (y / 40) - 1)) {
		return true;
	}

	if (InterRectRect(V2(x, y), sizey, sizex, int(x / 40) * 40, int(y / 40) * 40, 40, 40) && G.Mur(x / 40, y / 40)) {
		return true;
	}
	if (InterRectRect(V2(x, y), sizey, sizex, int(x / 40) * 40, int(y / 40) * 40, 40, 40) && isPorteClosed(int(x / 40), int(y / 40))) {
		return true;
	}

	if (InterRectRect(V2(x, y), sizey, sizex, int(x / 40) * 40, (int(y / 40) - 1) * 40, 40, 40) && isPorteClosed(int(x / 40), int(y / 40) - 1)) {
		return true;
	}
	if (InterRectRect(V2(x, y), sizey, sizex, (int(x / 40) + 1) * 40, (int(y / 40) - 1) * 40, 40, 40) && isPorteClosed(int(x / 40) + 1, int(y / 40) - 1)) {
		return true;
	}

	if (isMomie) {
		if (InterRectRect(V2(x, y), sizey, sizex, int(x / 40) * 40, (int(y / 40) - 1) * 40, 40, 40) && isCheckPoint(int(x / 40), int(y / 40) - 1)) {
			return true;
		}
		if (InterRectRect(V2(x, y), sizey, sizex, (int(x / 40) + 1) * 40, (int(y / 40) - 1) * 40, 40, 40) && isCheckPoint(int(x / 40) + 1, int(y / 40) - 1)) {
			return true;
		}
	}

	return false;
}

//Retourne un nombre aléatoire en 500 et 2000
int frameBeforeSpawn() {
	int r = rand() % 1500;
	return r + 500;
}

//Actions a executer lorsque le heros meurt
void Mort() {
	G.Heros.vies -= 1;
	G.Heros.Pos = G.Heros.last_checkpoint;
}