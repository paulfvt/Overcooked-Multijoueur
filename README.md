# 🍳 ECEcooked — Simulation de Cuisine Coopérative en 2D

> **Un projet de programmation système et d'algorithmique de niveau ING1, développé en Langage C avec la bibliothèque graphique Allegro 5.**

**ECEcooked** est une adaptation fidèle en vue du dessus du célèbre jeu *Overcooked*. Développé entièrement en C, ce projet met en scène deux cuisiniers qui doivent collaborer en temps réel dans une cuisine dynamique pour préparer, assembler et servir des recettes de tacos, tout en faisant face à des imprévus (comme des invasions de cafards !).

---

## 🎮 Fonctionnalités du Gameplay & Expérience Utilisateur

- **👥 Coopération Locale Synchrone (2 Joueurs)** : Gestion de deux personnages avec des configurations de touches distinctes sur le même clavier.
- **🌮 Préparation et Assemblage de Recettes** : Récupération des tortillas, découpe des ingrédients (tomates, poivrons, fromage), cuisson de la viande sur les plaques, assemblage dans l'assiette et envoi de la commande.
- **🦟 Menace Dynamique (Le Cafard)** : Un ennemi autonome se déplace dans la cuisine pour perturber la préparation. Les joueurs disposent d'un système de tir de projectiles (balles) pour l'éliminer.
- **📈 Interface & Progression** :
  - **Menu Principal Interactif** : Navigation à la souris pour lancer la partie, sélectionner le niveau, consulter le Scoreboard ou quitter le jeu.
  - **Double Écran de Chargement** : Une première barre de progression fluide à l'initialisation, suivie d'un écran didactique rappelant les contrôles avant de lancer la partie.
  - **Sauvegarde du Score** : Enregistrement persistant des pseudos et des scores dans un fichier externe pour alimenter le tableau des scores.

---

## 🛠️ Architecture Technique & Algorithmes Clés

### 1. Génération Matricielle Dynamique de la Carte (`Niveau1.txt`)
La cuisine est générée dynamiquement par lecture d'un fichier matrice externe (`Niveau1.txt`). Chaque tuile (Tile) de $72 \times 72$ pixels est décodée et associée à une texture graphique :
- `b` : Sol (Zone de déplacement libre).
- `g` : Plan de travail / Comptoir standard.
- `d` : Plan de découpe (Interactions de hachage).
- `i` : Plaque de cuisson (Déclenchement du minuteur de cuisson de la viande).
- `h` : Poubelle (Pour jeter les ingrédients ou plats ratés).
- `k` : Point de livraison des commandes (Sortie).
- **Distributeurs d'ingrédients** : `e` (Assiettes), `f` (Tomates), `l` (Fromage), `m` (Poivrons), `n` (Tortillas), `o` (Viande), `p` (Salade).

### 2. Gestion Algorithmique de la File de Commandes (Doublement Chaînée)
Le défilement des commandes à l'écran repose sur une structure de **file doublement chaînée** (`File` composée de structures `Commande`).
- **Génération Aléatoire** : Des requêtes parmi 4 recettes (`EL_NORMAL`, `EL_CLASICO`, `EL_VEGANO`, `LA_TOTALIDAD`) apparaissent périodiquement.
- **Gestion temporelle** : Chaque commande possède sa propre barre de temps décroissante. Si le délai expire, la commande est retirée de la file avec une pénalité de score.

```text
[First Commande] <---> [Commande] <---> [Last Commande] ---> NULL

---

// Structure gérant l'état physique, la visée et l'inventaire d'un cuisinier
typedef struct {
    float x, y;                // Position courante
    float vx, vy;              // Vecteur vitesse
    float cx, cy;              // Coordonnées du point de visée
    float angle;               // Angle de déplacement (en radians)
    float rayon;               // Rayon pour la gestion de collision circulaire
    int cooldown;              // Cadence de tir des balles
    ALLEGRO_BITMAP *image;     // Sprite du personnage
    bool porteIngredient;      // Flag d'état (porte quelque chose ou non)
    char ingredientPorte[30];  // Nom de l'ingrédient tenu
} joueur;

// Structure de l'Assiette servant à l'assemblage des recettes
typedef struct Assiette {
    bool assiette;
    bool pain;
    bool poivronsdecoupe;
    bool tomatedecoupe;
    bool viandecuite;
    bool salade;
} Assiette;

// Structure d'un nœud de la file d'attente de commandes
typedef struct commande {
    int type;                  // Recette (EL_NORMAL, EL_CLASICO, etc.)
    unsigned int temps;        // Temps restant avant expiration
    ALLEGRO_BITMAP* imageCommande;
    struct commande* next;     // Pointeur vers l'élément suivant
    struct commande* prev;     // Pointeur vers l'élément précédent
} Commande;

```
---
```text
ECEcooked/
├── src/                          # Code source (.c) et fichiers d'en-tête (.h)
│   ├── main.c                    # Point d'entrée, initialisation d'Allegro 5 et boucle principale
│   ├── Gameplay.c / .h           # Boucle de jeu, logique des ticks physiques et des interactions
│   ├── Joueur.c / .h             # Déplacements, tirs et physique des personnages
│   ├── Ingredient.c / .h         # Recettes, assemblages et gestion de la file de commandes
│   ├── map.c / .h                # Lecteur de la matrice texte et rendu graphique du niveau
|   ├── Niveau1 / 2 / 3.txt       # Agencement matriciel de la cuisine
│   └── Menu.c / .h               # Interface du menu principal, scoreboard et écrans de chargement
│
├── assets/                       # Ressources multimédias
│   ├── Image/                    # Sprites des personnages, GIF cafard, ingrédients, décors, et HUD
│   └── musique/                  # Musique de fond (La Cucaracha) et effets sonores (.wav)
│
└── README.md                     # Présentation et documentation technique
