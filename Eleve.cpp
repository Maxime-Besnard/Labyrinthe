 
#pragma warning( disable : 4996 ) 

 
#include <cstdlib>
#include <vector>
#include <iostream>
#include <string>
#include "G2D.h"

bool InterRectRect(V2 pos, int hauteur, int largeur, int x2, int y2, int hauteur2, int largeur2);
void AssetsInit();
int rand_direction();
 
using namespace std;

struct _Inventaire {

	bool Key = false;

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
				 "M M M MMMMMMM M"
				 "M M      M    M"
				 "MMMMMMMMMMMMMMM";

	// indique la pr�sence d'un mur � la case (x,y)
	bool Mur(int x, int y) { return Map[(15 - y - 1)*15+x] == 'M'; }  

	int Lpix = 40;  // largeur en pixels des cases du labyrinthe

	_Heros Heros;   // data du h�ros
	_Key   Key;
	_Chest Chest;
	_Momie Momies_tab[3];
	int direction_init[3] = { 2,1,3 };

	int Ecran = 0;
	int time = 0;

	int n_frame = 0;
	int last_direction = 1; // 0 : left | 1:right

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

		// affichage du h�ro avec boite englobante et zoom x 2
		G2D::DrawRectangle(G.Heros.Pos, G.Heros.Size, Color::Red);
		//G2D::DrawRectWithTexture(G.Heros.IdTex1, G.Heros.Pos, G.Heros.Size);
		if (G2D::IsKeyPressed(Key::RIGHT)) {
			if (G.n_frame % 30 < 15) {
				G2D::DrawRectWithTexture(G.Heros.IdTexDroite, G.Heros.Pos, G.Heros.Size);
			}
			else {
				G2D::DrawRectWithTexture(G.Heros.IdTexDroite2, G.Heros.Pos, G.Heros.Size);
			}
			G.last_direction = 1;
		}
		else if (G2D::IsKeyPressed(Key::LEFT)) {
			if (G.n_frame % 30 < 15) {
				G2D::DrawRectWithTexture(G.Heros.IdTexGauche, G.Heros.Pos, G.Heros.Size);
			}
			else {
				G2D::DrawRectWithTexture(G.Heros.IdTexGauche2, G.Heros.Pos, G.Heros.Size);
			}
			G.last_direction = 0;
		}
		if (G2D::IsKeyPressed(Key::UP) || G2D::IsKeyPressed(Key::DOWN)) {
			if (G.last_direction == 1) {
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
			if (G.last_direction == 1) { G2D::DrawRectWithTexture(G.Heros.IdTexDroite2, G.Heros.Pos, G.Heros.Size); }
			else { G2D::DrawRectWithTexture(G.Heros.IdTexGauche2, G.Heros.Pos, G.Heros.Size); }
		}

		

		// affichage de la clef
		G2D::DrawRectWithTexture(G.Key.IdTex, G.Key.Pos, G.Key.Size);
		G2D::DrawRectWithTexture(G.Chest.IdTex, G.Chest.Pos, G.Chest.Size);
		
		//Affichage des momies
		G2D::DrawRectWithTexture(G.Momies_tab[0].IdTex, G.Momies_tab[0].Pos, G.Momies_tab[0].Size);
		G2D::DrawRectWithTexture(G.Momies_tab[1].IdTex, G.Momies_tab[1].Pos, G.Momies_tab[1].Size);
		G2D::DrawRectWithTexture(G.Momies_tab[2].IdTex, G.Momies_tab[2].Pos, G.Momies_tab[2].Size);
		
		/*G2D::DrawRectangle(V2((int(G.Heros.Pos.x / 40) - 1) * 40, int(G.Heros.Pos.y / 40) * 40), V2(40, 40), Color::Red);
		G2D::DrawRectangle(V2((int(G.Heros.Pos.x / 40) + 1) * 40, int(G.Heros.Pos.y / 40) * 40), V2(40, 40), Color::Red);
		G2D::DrawRectangle(V2((int(G.Heros.Pos.x / 40)) * 40, (int(G.Heros.Pos.y / 40) - 1) * 40), V2(40, 40), Color::Red);
		G2D::DrawRectangle(V2((int(G.Heros.Pos.x / 40)) * 40, (int(G.Heros.Pos.y / 40) + 1) * 40), V2(40, 40), Color::Red);
		G2D::DrawRectangle(V2((int(G.Heros.Pos.x / 40) - 1) * 40, (int(G.Heros.Pos.y / 40) + 1) * 40), V2(40, 40), Color::Red);
		G2D::DrawRectangle(V2((int(G.Heros.Pos.x / 40) + 1) * 40, (int(G.Heros.Pos.y / 40) + 1) * 40), V2(40, 40), Color::Red);*/
	}

	//Partie gagn�e
	if (G.Ecran == 2) {
		G2D::DrawStringFontMono(V2(100, 300), "WIN", 60, 4, Color::Green);
		G2D::DrawRectangle(V2(0, 0), V2(0, 0), Color::Black, true);
	}
	  
	G2D::Show();
	G.n_frame++;
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

		AssetsInit();

		G.Ecran = 1;
	}

	//Partie en cours
	if (G.Ecran == 1) {

		//D�placements et collisions avec les murs
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

		// D�placement des Momies
		for (int i = 0; i < 3; i++) {

			if ((InterRectRect(G.Momies_tab[i].Pos, G.Momies_tab[i].Size.y, G.Momies_tab[i].Size.x, (int(G.Momies_tab[i].Pos.x / 40) - 1) * 40, int(G.Momies_tab[i].Pos.y / 40) * 40, 40, 40)) && G.Mur((G.Momies_tab[i].Pos.x / 40) - 1, G.Momies_tab[i].Pos.y / 40) || (G.Mur((G.Momies_tab[i].Pos.x / 40) - 1, (G.Momies_tab[i].Pos.y / 40) + 1) && ((InterRectRect(G.Momies_tab[i].Pos, G.Momies_tab[i].Size.y, G.Momies_tab[i].Size.x, (int(G.Momies_tab[i].Pos.x / 40) - 1) * 40, int(G.Momies_tab[i].Pos.y / 40 + 1) * 40, 40, 40)))))
			{
				G.Momies_tab[i].Pos.x++;
				G.direction_init[i] = rand_direction();
			}
			else {
				if (G.direction_init[i] == 0) { { G.Momies_tab[i].Pos.x--; } }
			}

			if ((InterRectRect(G.Momies_tab[i].Pos, G.Momies_tab[i].Size.y, G.Momies_tab[i].Size.x, (int(G.Momies_tab[i].Pos.x / 40) + 1) * 40, int(G.Momies_tab[i].Pos.y / 40) * 40, 40, 40)) && G.Mur((G.Momies_tab[i].Pos.x / 40) + 1, (G.Momies_tab[i].Pos.y / 40)) || (G.Mur((G.Momies_tab[i].Pos.x / 40) + 1, (G.Momies_tab[i].Pos.y / 40) + 1) && ((InterRectRect(G.Momies_tab[i].Pos, G.Momies_tab[i].Size.y, G.Momies_tab[i].Size.x, (int(G.Momies_tab[i].Pos.x / 40) + 1) * 40, int(G.Momies_tab[i].Pos.y / 40 + 1) * 40, 40, 40)))))
			{
				G.Momies_tab[i].Pos.x--;
				G.direction_init[i] = rand_direction();
			}
			else {
				if (G.direction_init[i] == 1) { { G.Momies_tab[i].Pos.x++; } }
			}

			if (((InterRectRect(G.Momies_tab[i].Pos, G.Momies_tab[i].Size.y, G.Momies_tab[i].Size.x, int(G.Momies_tab[i].Pos.x / 40) * 40, (int(G.Momies_tab[i].Pos.y / 40) + 1) * 40, 40, 40)) && G.Mur((G.Momies_tab[i].Pos.x / 40), (G.Momies_tab[i].Pos.y / 40) + 1)) || (G.Mur((G.Momies_tab[i].Pos.x / 40) + 1, (G.Momies_tab[i].Pos.y / 40) + 1) && ((InterRectRect(G.Momies_tab[i].Pos, G.Momies_tab[i].Size.y, G.Momies_tab[i].Size.x, (int(G.Momies_tab[i].Pos.x / 40) + 1) * 40, int(G.Momies_tab[i].Pos.y / 40 + 1) * 40, 40, 40)))))
			{
				G.Momies_tab[i].Pos.y--;
				G.direction_init[i] = rand_direction();
			}
			else {
				if (G.direction_init[i] == 2) { { G.Momies_tab[i].Pos.y++; } }
			}

			if (((InterRectRect(G.Momies_tab[i].Pos, G.Momies_tab[i].Size.y, G.Momies_tab[i].Size.x, int(G.Momies_tab[i].Pos.x / 40) * 40, (int(G.Momies_tab[i].Pos.y / 40) - 1) * 40, 40, 40)) && G.Mur((G.Momies_tab[i].Pos.x / 40), (G.Momies_tab[i].Pos.y / 40) - 1)) || (G.Mur((G.Momies_tab[i].Pos.x / 40) + 1, (G.Momies_tab[i].Pos.y / 40) - 1) && ((InterRectRect(G.Momies_tab[i].Pos, G.Momies_tab[i].Size.y, G.Momies_tab[i].Size.x, (int(G.Momies_tab[i].Pos.x / 40) + 1) * 40, int(G.Momies_tab[i].Pos.y / 40 - 1) * 40, 40, 40)))))
			{
				G.Momies_tab[i].Pos.y++;
				G.direction_init[i] = rand_direction();
			}
			else {
				if (G.direction_init[i] == 3) { { G.Momies_tab[i].Pos.y--; } }
			}
		}
	}

	//Partie gagn�e
	if (G.Ecran == 2) {
		//std::cout << G2D::ElapsedTimeFromStartSeconds() << "\n";

		if (G2D::ElapsedTimeFromStartSeconds() - G.time > 3) {
			G.Ecran = 0;
		}
	}

}
 

void AssetsInit()
{
   // Size pass� en ref et texture en param
   G.Heros.IdTexDroite = G2D::InitTextureFromString(G.Heros.Size, G.Heros.texture_droite);
   G.Heros.IdTexDroite2 = G2D::InitTextureFromString(G.Heros.Size, G.Heros.texture_droite2);
   G.Heros.IdTexGauche = G2D::InitTextureFromString(G.Heros.Size, G.Heros.texture_gauche);
   G.Heros.IdTexGauche2 = G2D::InitTextureFromString(G.Heros.Size, G.Heros.texture_gauche2);
   G.Heros.Size  = G.Heros.Size  * 2; // on peut zoomer la taille du sprite

   G.Key.IdTex   = G2D::InitTextureFromString(G.Key.Size, G.Key.texture);
   G.Key.Size    = G.Key.Size * 1.5; // on peut zoomer la taille du sprite

   G.Chest.IdTex = G2D::InitTextureFromString(G.Chest.Size, G.Chest.texture);
   G.Chest.Size = G.Chest.Size * 2;

   G.Momies_tab[0].IdTex = G2D::InitTextureFromString(G.Momies_tab[0].Size, G.Momies_tab[0].texture);
   G.Momies_tab[0].Size = G.Momies_tab[0].Size * 1.5;
   G.Momies_tab[0].Pos = V2(45, 240);

   G.Momies_tab[1].IdTex = G2D::InitTextureFromString(G.Momies_tab[1].Size, G.Momies_tab[1].texture);
   G.Momies_tab[1].Size = G.Momies_tab[1].Size * 1.5;
   G.Momies_tab[1].Pos = V2(200, 240);

   G.Momies_tab[2].IdTex = G2D::InitTextureFromString(G.Momies_tab[2].Size, G.Momies_tab[2].texture);
   G.Momies_tab[2].Size = G.Momies_tab[2].Size * 1.5;
   G.Momies_tab[2].Pos = V2(320, 240);

   
}

int main(int argc, char* argv[])
{ 

	G2D::InitWindow(argc,argv,V2(G.Lpix * 15, G.Lpix * 15), V2(200,200), string("Labyrinthe"));
	  
	AssetsInit();

	G2D::Run(Logic,render);
 
}

//D�tecter une collision entre 2 rectangles
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