 
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
 
using namespace std;

struct _Inventaire {

	bool Key = false;
	bool Pistolet = false;
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
	V2 Pos = V2(45,45);
	int hauteur = 11;
	int largeur = 5;
	int vies = 3;
	int last_direction = 1; // 0 : left | 1:right

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
	V2 Pos = V2(40, 200);
};

struct _Chest {

	string texture =
		"[                      ]"
		"[       PPPPPPPP       ]"
		"[     PPPPPPPPPPPP     ]"
		"[   PPPPPPPPPPPPPPPP   ]"
		"[   PPPPPPPPPPPPPPPP   ]"
		"[   PPPPPPOOOOOPPPPP   ]"
		"[   PPPPPPOOOOOPPPPP   ]"
		"[   PPPPPPOOOOOPPPPP   ]"
		"[   PPPPPPPOOOPPPPPP   ]"
		"[   PPPPPPPOOOPPPPPP   ]"
		"[   PPPPPPPPPPPPPPPP   ]"
		"[   PPPPPPPPPPPPPPPP   ]"
		"[   PPPPPPPPPPPPPPPP   ]"
		"[   PPPPPPPPPPPPPPPP   ]";

	V2 Size;
	int IdTex;
	V2 Pos = V2(35,120);
};

struct _Momie
{
	string texture =

		"[       PPPPPP         ]"
		"[      PPPPPPPP        ]"
		"[     PPPPPPPPPP       ]"
		"[     PPPPPPPPPP       ]"
		"[     P     PPPP       ]"
		"[     PPW WPPPPP       ]"
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

	V2 Size;
	int IdTex;
	V2 Pos = V2(35, 240);
	int direction=0;
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

	V2 Size;
	int IdTexGauche;
	int IdTexDroite;
	V2 Pos = V2(500, 45);
};

struct _Diamand
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

	V2 Size;
	int IdTex;
	V2 Pos = V2(450, 130);
};

struct _Porte 
{
	V2 Pos;
	V2 Size;
	bool isClosed=false;
	int direction_fermeture; // 0:se ferme vers le haut | 1:vers le bas | 2:vers la droite | 3:vers la gauche
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
	int IdTex;
	V2 Size;
	int max_spawn = 2;
	int nb_spawned = 0;
	int nb_frame_before_spawn;
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

	_Diamand Diamand;

	_Porte Portes[3];

	_Spawner Spawners[2];

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
		for (int x = 0; x < 15; x++)
			for (int y = 0; y < 15; y++)
			{
				int xx = x * G.Lpix;
				int yy = y * G.Lpix;
				if (G.Mur(x, y))
					G2D::DrawRectangle(V2(xx, yy), V2(G.Lpix, G.Lpix), Color::Blue, true);
			}

		//Affichage des vies restantes
		G2D::DrawStringFontMono(V2(40, 570), "Vies : " + std::to_string(G.Heros.vies), 20, 2, Color::Red);


		// affichage et animation du héros
		G2D::DrawRectangle(G.Heros.Pos, G.Heros.Size, Color::Red);
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

		//Affichage Coffre
		G2D::DrawRectWithTexture(G.Chest.IdTex, G.Chest.Pos, G.Chest.Size);

		//Affichage des momies
		for (auto &Momie : G.Momies) {
			G2D::DrawRectWithTexture(Momie.IdTex, Momie.Pos, Momie.Size);
		}

		// Affichage Pistolet
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

		//Affichage Dimand
		G2D::DrawRectWithTexture(G.Diamand.IdTex, G.Diamand.Pos, G.Diamand.Size);

		//Affichage Porte
		for (_Porte Porte : G.Portes) {
			if (Porte.isClosed) {
				Porte.Size = V2(40, 0);
			}
			else {
				Porte.Size = V2(40, 40);
			}
			G2D::DrawRectangle(Porte.Pos, Porte.Size, Color::Red, true);
		}

		//Affichage Spawners
		for (int i = 0; i < sizeof G.Spawners / sizeof G.Spawners[0];i++) {
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
		G2D::DrawStringFontMono(V2(100, 300), "WIN", 60, 4, Color::Green);
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
		_Heros h;
		_Key k;
		_Chest c;


		G.Heros = h;
		G.Key = k;
		G.Chest = c;

		vector<_Momie> New_Momies;
		G.Momies = New_Momies;
		AssetsInit();

		G.Ecran = 1;
	}

	//Partie en cours
	if (G.Ecran == 1) {

		//Déplacements et collisions avec les murs et les portes
		if ((InterRectRect(G.Heros.Pos, G.Heros.Size.y, G.Heros.Size.x, (int(G.Heros.Pos.x / 40) - 1) * 40, int(G.Heros.Pos.y / 40) * 40, 40, 40)) && G.Mur((G.Heros.Pos.x / 40) - 1, G.Heros.Pos.y / 40) || (G.Mur((G.Heros.Pos.x / 40) - 1, (G.Heros.Pos.y / 40) + 1) && ((InterRectRect(G.Heros.Pos, G.Heros.Size.y, G.Heros.Size.x, (int(G.Heros.Pos.x / 40) - 1) * 40, int(G.Heros.Pos.y / 40 + 1) * 40, 40, 40))))) {}
		else {
			if (G2D::IsKeyPressed(Key::LEFT))  G.Heros.Pos.x--;
		}
		if ((InterRectRect(G.Heros.Pos, G.Heros.Size.y, G.Heros.Size.x, (int(G.Heros.Pos.x / 40) + 1) * 40 - 1, int(G.Heros.Pos.y / 40) * 40, 41, 41)) && G.Mur((G.Heros.Pos.x / 40) + 1, (G.Heros.Pos.y / 40)) || (G.Mur((G.Heros.Pos.x / 40) + 1, (G.Heros.Pos.y / 40) + 1) && ((InterRectRect(G.Heros.Pos, G.Heros.Size.y, G.Heros.Size.x, (int(G.Heros.Pos.x / 40) + 1) * 40, int(G.Heros.Pos.y / 40 + 1) * 40, 40, 40))))) {}
		else {
			if (G2D::IsKeyPressed(Key::RIGHT)) G.Heros.Pos.x++;
		}
		if (((InterRectRect(G.Heros.Pos, G.Heros.Size.y, G.Heros.Size.x, int(G.Heros.Pos.x / 40) * 40, (int(G.Heros.Pos.y / 40) + 1) * 40 - 1, 41, 41)) && G.Mur((G.Heros.Pos.x / 40), (G.Heros.Pos.y / 40) + 1)) || (G.Mur((G.Heros.Pos.x / 40) + 1, (G.Heros.Pos.y / 40) + 1) && ((InterRectRect(G.Heros.Pos, G.Heros.Size.y, G.Heros.Size.x, (int(G.Heros.Pos.x / 40) + 1) * 40, int(G.Heros.Pos.y / 40 + 1) * 40, 40, 40))))) {}
		else {
			if (G2D::IsKeyPressed(Key::UP))    G.Heros.Pos.y++;
		}
		if (((InterRectRect(G.Heros.Pos, G.Heros.Size.y, G.Heros.Size.x, int(G.Heros.Pos.x / 40) * 40, (int(G.Heros.Pos.y / 40) - 1) * 40, 40, 40)) && G.Mur((G.Heros.Pos.x / 40), (G.Heros.Pos.y / 40) - 1)) || (G.Mur((G.Heros.Pos.x / 40) + 1, (G.Heros.Pos.y / 40) - 1) && ((InterRectRect(G.Heros.Pos, G.Heros.Size.y, G.Heros.Size.x, (int(G.Heros.Pos.x / 40) + 1) * 40, int(G.Heros.Pos.y / 40 - 1) * 40, 40, 40))))) {}
		else {
			if (G2D::IsKeyPressed(Key::DOWN))  G.Heros.Pos.y--;
		}


		//Collision avec la clef
		if (InterRectRect(G.Heros.Pos, G.Heros.Size.y, G.Heros.Size.x, G.Key.Pos.x, G.Key.Pos.y, G.Key.Size.y, G.Key.Size.x)) {
			G.Heros.Inventaire.Key = true;
			G.Key.Size = V2(0, 0);
			G.Key.Pos = V2(0, 0);
		}

		//Collision avec le coffre
		if (InterRectRect(G.Heros.Pos, G.Heros.Size.y, G.Heros.Size.x, G.Chest.Pos.x, G.Chest.Pos.y, G.Chest.Size.y, G.Chest.Size.x) && G.Heros.Inventaire.Key == true) {
			G.Heros.Inventaire.Key = false;
			G.Chest.Size = V2(0, 0);
			G.Ecran = 2;
			G.time = G2D::ElapsedTimeFromStartSeconds();
		}

		//Collision avec la momie
		for (auto &Momie: G.Momies) {
			if (InterRectRect(G.Heros.Pos, G.Heros.Size.y, G.Heros.Size.x, Momie.Pos.x, Momie.Pos.y, Momie.Size.y, Momie.Size.x)) {
				G.Heros.vies -= 1;
				G.Heros.Pos = V2(45, 45);
			}

		}

		//Collision avec le pistolet
		if (InterRectRect(G.Heros.Pos, G.Heros.Size.y, G.Heros.Size.x, G.Pistolet.Pos.x, G.Pistolet.Pos.y, G.Pistolet.Size.y, G.Pistolet.Size.x)) {
			G.Heros.Inventaire.Pistolet = true;
		}

		//Deplacement Pistolet
		if (G.Heros.Inventaire.Pistolet) {
			if (G.Heros.last_direction == 1) {
				G.Pistolet.Pos.x = G.Heros.Pos.x;
			}
			else {
				G.Pistolet.Pos.x = G.Heros.Pos.x - G.Heros.largeur;
			}
			G.Pistolet.Pos.y = G.Heros.Pos.y + G.Heros.hauteur / 2;
		}

		// Déplacement des Momies
		for (auto &Momie : G.Momies) {

			if ((InterRectRect(Momie.Pos, Momie.Size.y, Momie.Size.x, (int(Momie.Pos.x / 40) - 1) * 40, int(Momie.Pos.y / 40) * 40, 40, 40)) && G.Mur((Momie.Pos.x / 40) - 1, Momie.Pos.y / 40) || (G.Mur((Momie.Pos.x / 40) - 1, (Momie.Pos.y / 40) + 1) && ((InterRectRect(Momie.Pos, Momie.Size.y, Momie.Size.x, (int(Momie.Pos.x / 40) - 1) * 40, int(Momie.Pos.y / 40 + 1) * 40, 40, 40)))))
			{
				Momie.Pos.x++;
				Momie.direction = rand_direction();
			}
			else {
				if (Momie.direction == 0) { { Momie.Pos.x--; } }
			}

			if ((InterRectRect(Momie.Pos, Momie.Size.y, Momie.Size.x, (int(Momie.Pos.x / 40) + 1) * 40, int(Momie.Pos.y / 40) * 40, 40, 40)) && G.Mur((Momie.Pos.x / 40) + 1, (Momie.Pos.y / 40)) || (G.Mur((Momie.Pos.x / 40) + 1, (Momie.Pos.y / 40) + 1) && ((InterRectRect(Momie.Pos, Momie.Size.y, Momie.Size.x, (int(Momie.Pos.x / 40) + 1) * 40, int(Momie.Pos.y / 40 + 1) * 40, 40, 40)))))
			{
				Momie.Pos.x--;
				Momie.direction = rand_direction();
			}
			else {
				if (Momie.direction == 1) { { Momie.Pos.x++; } }
			}

			if (((InterRectRect(Momie.Pos, Momie.Size.y, Momie.Size.x, int(Momie.Pos.x / 40) * 40, (int(Momie.Pos.y / 40) + 1) * 40, 40, 40)) && G.Mur((Momie.Pos.x / 40), (Momie.Pos.y / 40) + 1)) || (G.Mur((Momie.Pos.x / 40) + 1, (Momie.Pos.y / 40) + 1) && ((InterRectRect(Momie.Pos, Momie.Size.y, Momie.Size.x, (int(Momie.Pos.x / 40) + 1) * 40, int(Momie.Pos.y / 40 + 1) * 40, 40, 40)))))
			{
				Momie.Pos.y--;
				Momie.direction = rand_direction();
			}
			else {
				if (Momie.direction == 2) { { Momie.Pos.y++; } }
			}

			if (((InterRectRect(Momie.Pos, Momie.Size.y, Momie.Size.x, int(Momie.Pos.x / 40) * 40, (int(Momie.Pos.y / 40) - 1) * 40, 40, 40)) && G.Mur((Momie.Pos.x / 40), (Momie.Pos.y / 40) - 1)) || (G.Mur((Momie.Pos.x / 40) + 1, (Momie.Pos.y / 40) - 1) && ((InterRectRect(Momie.Pos, Momie.Size.y, Momie.Size.x, (int(Momie.Pos.x / 40) + 1) * 40, int(Momie.Pos.y / 40 - 1) * 40, 40, 40)))))
			{
				Momie.Pos.y++;
				Momie.direction = rand_direction();
			}
			else {
				if (Momie.direction == 3) { { Momie.Pos.y--; } }
			}
		}

		//Spawn de Momies
		for (int i = 0; i < sizeof G.Spawners / sizeof G.Spawners[0];i++) {
			if (G.n_frame % G.Spawners[i].nb_frame_before_spawn == 0 && G.Spawners[i].nb_spawned < G.Spawners[i].max_spawn) {
				_Momie M;
				M.IdTex = G2D::InitTextureFromString(M.Size, M.texture);
				M.Size = M.Size * 1.5;
				M.Pos = G.Spawners[i].Pos;
				G.Momies.push_back(M);
				G.Spawners[i].nb_spawned++;
			}
		}

		//Détection du game over
		if (G.Heros.vies < 1) {
			G.Ecran = 3;
			G.time = G2D::ElapsedTimeFromStartSeconds();
		}

		//Gestion aléatoire fermeture des portes
		if (G.n_frame % 100 == 0) {
			for (_Porte &Porte : G.Portes) {
				int nb_rand = rand() % 2;
				if (nb_rand == 1) { Porte.isClosed = true; }
				else { Porte.isClosed = false; }
			}
			
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
	G.Heros.Size = G.Heros.Size * 2; // on peut zoomer la taille du sprite

   G.Key.IdTex   = G2D::InitTextureFromString(G.Key.Size, G.Key.texture);
   G.Key.Size    = G.Key.Size * 1.5; // on peut zoomer la taille du sprite

   G.Chest.IdTex = G2D::InitTextureFromString(G.Chest.Size, G.Chest.texture);
   G.Chest.Size = G.Chest.Size * 2;

   //G.Momies[0].IdTex = G2D::InitTextureFromString(G.Momies[0].Size, G.Momies[0].texture);
   //G.Momies[0].Size = G.Momies[0].Size * 1.5;
   //G.Momies[0].Pos = V2(45, 240);

   //G.Momies[1].IdTex = G2D::InitTextureFromString(G.Momies[1].Size, G.Momies[1].texture);
   //G.Momies[1].Size = G.Momies[1].Size * 1.5;
   //G.Momies[1].Pos = V2(200, 240);

   //G.Momies[2].IdTex = G2D::InitTextureFromString(G.Momies[2].Size, G.Momies[2].texture);
   //G.Momies[2].Size = G.Momies[2].Size * 1.5;
   //G.Momies[2].Pos = V2(320, 240);
   _Momie Momie1;
   _Momie Momie2;
   _Momie Momie3;

   Momie1.IdTex = G2D::InitTextureFromString(Momie1.Size, Momie1.texture);
   Momie1.Size = Momie1.Size * 1.5;
   Momie1.Pos = V2(45, 240);

   Momie2.IdTex = G2D::InitTextureFromString(Momie2.Size, Momie2.texture);
   Momie2.Size = Momie2.Size * 1.5;
   Momie2.Pos = V2(200, 240);

   Momie3.IdTex = G2D::InitTextureFromString(Momie3.Size, Momie3.texture);
   Momie3.Size = Momie3.Size * 1.5;
   Momie3.Pos = V2(320, 240);

   G.Momies.push_back(Momie1);
   G.Momies.push_back(Momie2);
   G.Momies.push_back(Momie3);


   G.Pistolet.IdTexGauche = G2D::InitTextureFromString(G.Pistolet.Size, G.Pistolet.texture_gauche);
   G.Pistolet.IdTexDroite = G2D::InitTextureFromString(G.Pistolet.Size, G.Pistolet.texture_droite);
   G.Pistolet.Size = G.Pistolet.Size * 1;

   G.Diamand.IdTex = G2D::InitTextureFromString(G.Diamand.Size, G.Diamand.texture);
   G.Diamand.Size = G.Diamand.Size * 1;

   G.Portes[0].Pos = V2(80, 80);
   G.Portes[1].Pos = V2(120, 400);
   G.Portes[2].Pos = V2(160, 40);
   for (_Porte Porte : G.Portes) {
	   Porte.Size = V2(40, 40);
   }


   _Spawner Spawner1;
   _Spawner Spawner2;

   Spawner1.IdTex = G2D::InitTextureFromString(Spawner1.Size, Spawner1.texture);
   Spawner1.Size = Spawner1.Size * 2;
   Spawner1.Pos = V2(400, 45);
   Spawner1.nb_frame_before_spawn = rand() % 100;

   Spawner2.IdTex = G2D::InitTextureFromString(Spawner2.Size, Spawner2.texture);
   Spawner2.Size = Spawner2.Size * 2;
   Spawner2.Pos = V2(450, 450);
   Spawner2.nb_frame_before_spawn = rand() % 100;

   G.Spawners[0] = Spawner1;
   G.Spawners[1] = Spawner2;
}

int main(int argc, char* argv[])
{ 

	G2D::InitWindow(argc,argv,V2(G.Lpix * 15, G.Lpix * 15), V2(200,200), string("Labyrinthe"));
	  
	//AssetsInit();

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

int rand_direction(){
	return rand() % 4;
}

bool isPorteClosed(int x, int y) {
	int pos_horizontal = x * 40;
	int pos_vertical = y * 40;
	for (_Porte &Porte : G.Portes) {
		if (Porte.Pos.x == pos_horizontal && Porte.Pos.y == pos_vertical && Porte.isClosed==true) return true;
	}
	return false;
}