 
#pragma warning( disable : 4996 ) 

 
#include <cstdlib>
#include <vector>
#include <iostream>
#include <string>
#include "G2D.h"

bool InterRectRect(V2 pos, int hauteur, int largeur, int x2, int y2, int hauteur2, int largeur2);
int rand_direction();

 
using namespace std;

struct _Inventaire {

	bool Key = false;

};
 
struct _Heros
{
	string texture =
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
	V2 Size;
	int IdTex; 
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
		"[      PPPPPP     ]"
		"[     PPPPPPPP    ]"
		"[    PPPPPPPPPP   ]"
		"[    PPPPPPPPPP   ]"
		"[    P     PPPP   ]"
		"[    PPW WPPPPP   ]"
		"[     PPPPPPPP    ]"
		"[      PPPPPP     ]"
		"[       PPPPPP    ]"
		"[    PPPPPPPPP    ]"
		"[   PPPPPPPPPP    ]"
		"[   PPPPPPPPPP    ]"
		"[   PP  PPPPP     ]"
		"[       PPPPP     ]"
		"[       PPPPP     ]"
		"[      PP PPP     ]";

	V2 Size;
	int IdTex;
	V2 Pos;
};

struct _Pistolet
{
	string texture =
		"[  MMMMMMMMMMMGGMM   ]"
		"[  MMMMMMMMMMMMMMMM  ]"
		"[  MMMMMMMMMMMMMGMG  ]"
		"[  GGGGGGGGMGGGGGGG  ]"
		"[          G  GGPG   ]"
		"[           GGGPPPG  ]"
		"[              GPPPG ]"
		"[               GPPG ]"
		"[               GGG  ]";

	V2 Size;
	int IdTex;
	V2 Pos = V2(45, 320);

};

void moveMomie(_Momie momie);

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

	// indique la présence d'un mur à la case (x,y)
	bool Mur(int x, int y) { return Map[(15 - y - 1)*15+x] == 'M'; }  

	int Lpix = 40;  // largeur en pixels des cases du labyrinthe

	_Heros Heros;   // data du héros
	_Key   Key;
	_Chest Chest;
	_Momie Momies_tab[3];
	_Pistolet Pistolet;
	GameData() {}
	int direction_init[3] = { 2,1,3 };

};

GameData G;


void render()
{
	G2D::ClearScreen(Color::Black);
	 
	for (int x = 0; x < 15; x++)
		for (int y = 0; y < 15; y++)
		{
			int xx = x * G.Lpix;
			int yy = y * G.Lpix;
			if ( G.Mur(x,y))
			   G2D::DrawRectangle(V2(xx, yy), V2(G.Lpix, G.Lpix), Color::Blue, true);
		}
		 
	// affichage du héro avec boite englobante et zoom x 2
	G2D::DrawRectangle(G.Heros.Pos,   G.Heros.Size, Color::Red );
	G2D::DrawRectWithTexture(G.Heros.IdTex, G.Heros.Pos,   G.Heros.Size);
	
	// affichage de la clef
	G2D::DrawRectWithTexture(G.Key.IdTex, G.Key.Pos, G.Key.Size);
	G2D::DrawRectWithTexture(G.Chest.IdTex, G.Chest.Pos, G.Chest.Size);
	G2D::DrawRectWithTexture(G.Momies_tab[0].IdTex, G.Momies_tab[0].Pos, G.Momies_tab[0].Size);
	G2D::DrawRectWithTexture(G.Momies_tab[1].IdTex, G.Momies_tab[1].Pos, G.Momies_tab[1].Size);
	G2D::DrawRectWithTexture(G.Momies_tab[2].IdTex, G.Momies_tab[2].Pos, G.Momies_tab[2].Size);

	G2D::DrawRectangle(V2((int(G.Heros.Pos.x / 40) - 1) * 40, int(G.Heros.Pos.y / 40) * 40), V2(40, 40), Color::Red);
	G2D::DrawRectangle(V2((int(G.Heros.Pos.x / 40) + 1) * 40, int(G.Heros.Pos.y / 40) * 40), V2(40, 40), Color::Red);
	G2D::DrawRectangle(V2((int(G.Heros.Pos.x / 40)) * 40, (int(G.Heros.Pos.y / 40) - 1) * 40), V2(40, 40), Color::Red);
	G2D::DrawRectangle(V2((int(G.Heros.Pos.x / 40)) * 40, (int(G.Heros.Pos.y / 40) + 1) * 40), V2(40, 40), Color::Red);
	G2D::DrawRectangle(V2((int(G.Heros.Pos.x / 40) - 1) * 40, (int(G.Heros.Pos.y / 40) + 1) * 40), V2(40, 40), Color::Red);
	G2D::DrawRectangle(V2((int(G.Heros.Pos.x / 40) + 1) * 40, (int(G.Heros.Pos.y / 40) + 1) * 40), V2(40, 40), Color::Red);

	G2D::DrawRectWithTexture(G.Pistolet.IdTex,G.Pistolet.Pos, G.Pistolet.Size);


	G2D::DrawRectangle(G.Momies_tab[0].Pos, G.Momies_tab[0].Size, Color::Red);
	  
	G2D::Show();
}

 
void Logic()
{
	//Déplacements et collisions avec les murs

	if ((InterRectRect(G.Heros.Pos, G.Heros.Size.y, G.Heros.Size.x, (int(G.Heros.Pos.x/40) - 1)*40, int(G.Heros.Pos.y/40)*40, 40, 40)) && G.Mur((G.Heros.Pos.x /40) - 1, G.Heros.Pos.y/40) || (G.Mur((G.Heros.Pos.x / 40) - 1, (G.Heros.Pos.y / 40) + 1) && ((InterRectRect(G.Heros.Pos, G.Heros.Size.y, G.Heros.Size.x, (int(G.Heros.Pos.x / 40) - 1) * 40, int(G.Heros.Pos.y / 40 + 1) * 40, 40, 40)))) ) {}
	else {
		if (G2D::IsKeyPressed(Key::LEFT))  G.Heros.Pos.x--;
	}
	if ((InterRectRect(G.Heros.Pos, G.Heros.Size.y, G.Heros.Size.x, (int(G.Heros.Pos.x/40) + 1)*40, int(G.Heros.Pos.y/40)*40, 40, 40)) && G.Mur((G.Heros.Pos.x / 40) + 1, (G.Heros.Pos.y / 40)) || (G.Mur((G.Heros.Pos.x / 40) + 1, (G.Heros.Pos.y / 40)+1) && ((InterRectRect(G.Heros.Pos, G.Heros.Size.y, G.Heros.Size.x, (int(G.Heros.Pos.x / 40) + 1) * 40, int(G.Heros.Pos.y / 40 + 1) * 40, 40, 40)))) ) {}
	else{
		if (G2D::IsKeyPressed(Key::RIGHT)) G.Heros.Pos.x++;
	}
	if (((InterRectRect(G.Heros.Pos, G.Heros.Size.y, G.Heros.Size.x, int(G.Heros.Pos.x/40)*40, (int(G.Heros.Pos.y/40) + 1)*40, 40, 40)) && G.Mur((G.Heros.Pos.x / 40), (G.Heros.Pos.y / 40) + 1)) || (G.Mur((G.Heros.Pos.x / 40) + 1, (G.Heros.Pos.y / 40) + 1) && ((InterRectRect(G.Heros.Pos, G.Heros.Size.y, G.Heros.Size.x, (int(G.Heros.Pos.x / 40) + 1) * 40, int(G.Heros.Pos.y / 40 + 1) * 40, 40, 40))))) {}
	else {
		if (G2D::IsKeyPressed(Key::UP))    G.Heros.Pos.y++;
	}
	if (((InterRectRect(G.Heros.Pos, G.Heros.Size.y, G.Heros.Size.x, int(G.Heros.Pos.x/40)*40, (int(G.Heros.Pos.y/40) - 1)*40, 40, 40)) && G.Mur((G.Heros.Pos.x / 40), (G.Heros.Pos.y / 40) - 1)) || (G.Mur((G.Heros.Pos.x / 40) + 1, (G.Heros.Pos.y / 40) - 1) && ((InterRectRect(G.Heros.Pos, G.Heros.Size.y, G.Heros.Size.x, (int(G.Heros.Pos.x / 40) + 1) * 40, int(G.Heros.Pos.y / 40 - 1) * 40, 40, 40))))) {}
	else{
		if (G2D::IsKeyPressed(Key::DOWN))  G.Heros.Pos.y--;
	}


	// Déplacement Momie
	for (int i = 0; i <3; i++) {
		if ((InterRectRect(G.Momies_tab[i].Pos, G.Momies_tab[i].Size.y, G.Momies_tab[i].Size.x, (int(G.Momies_tab[i].Pos.x / 40) - 1) * 40, int(G.Momies_tab[i].Pos.y / 40) * 40, 40, 40)) && G.Mur((G.Momies_tab[i].Pos.x / 40) - 1, G.Momies_tab[i].Pos.y / 40) || (G.Mur((G.Momies_tab[i].Pos.x / 40) - 1, (G.Momies_tab[i].Pos.y / 40) + 1) && ((InterRectRect(G.Momies_tab[i].Pos, G.Momies_tab[i].Size.y, G.Momies_tab[i].Size.x, (int(G.Momies_tab[i].Pos.x / 40) - 1) * 40, int(G.Momies_tab[i].Pos.y / 40 + 1) * 40, 40, 40)))))
		{
			G.Momies_tab[i].Pos.x++;
			G.direction_init[i] = rand_direction();
		}
		else {
			if (G.direction_init[i] == 0) { { G.Momies_tab[i].Pos.x--;} }
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
	}

}
 

void AssetsInit()
{
   // Size passé en ref et texture en param
   G.Heros.IdTex = G2D::InitTextureFromString(G.Heros.Size, G.Heros.texture);  
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

   G.Pistolet.IdTex = G2D::InitTextureFromString(G.Pistolet.Size, G.Pistolet.texture);
   G.Pistolet.Size = G.Pistolet.Size*1; // on peut zoomer la taille du sprite
}

int main(int argc, char* argv[])
{ 

	G2D::InitWindow(argc,argv,V2(G.Lpix * 15, G.Lpix * 15), V2(200,200), string("Labyrinthe"));
	  
	AssetsInit();

	G2D::Run(Logic,render);
 
}

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